#include "plotter.h"
#include "sculptor.h"
#include "QMessageBox"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QPointF>
#include <QDebug>
#include <cstring>


Plotter::Plotter(QWidget *parent) : QWidget(parent){
    sx=50; sy=50; sz=50;
        s = new Sculptor(sx,sy,sz);
            dim=0; pl=XY;
            x=0; y=0; z=0; rad=0; rx=0;ry=0;rz=0;

            r = 1; g=1; b=1; a = 254;

            sh=1;

}

void Plotter::paintEvent(QPaintEvent *event){
    QPainter pa(this);
        QPen pen;
        QBrush brush;
        pen.setColor(QColor(0,0,0));
        pen.setWidth(1);
        pa.setPen(pen);
        brush.setColor(QColor(255,255,255));
        brush.setStyle(Qt::SolidPattern);
        pa.setBrush(brush);
        p.clear();
        p = s->readMx(dim,pl);
        int dim1 = width()/p[0].size();
        int dim2 = height()/p.size();
        (dim1>=dim2) ? square=dim2 : square=dim1;
        w = dim1;
        h = dim2;
        for(unsigned int i =0; i<p.size(); i++){
               for(unsigned int j =0; j<p[0].size(); j++){
                pa.drawRect(i*square,j*square,square, square);
        }
    }

        for(unsigned int i=0; i<p.size();i++){
               for(unsigned int j=0; j<p[0].size();j++){
                    if(p[i][j].isOn){
                        brush.setStyle(Qt::SolidPattern);
                        brush.setColor(QColor(p[i][j].r,p[i][j].g,p[i][j].b,p[i][j].a));
                        pa.setBrush(brush);
                        qDebug() << p[i][j].r <<p[i][j].g <<p[i][j].b;
                        pa.drawRect(i*square,j*square,square, square);
                    }
               }
            }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event){
    if(!(event->button() == Qt::LeftButton)){
    press = false;
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event){
    if(press){
        emit clickX(event->x());
        emit clickY(event->y());
        press = true;
        mx = (event->x())/square;
        my = (event->y())/square;
        emit moveX(mx);
        emit moveY(my);

          if(pl == XY){
              px=mx;
              py=my;
              pz=dim;
          }else if(pl == YZ){
              py=mx;
              pz=my;
              px=dim;
          }else if(pl== XZ){
              pz=mx;
              px=my;
              py=dim;
          }
          Plotter::shape(sh);
        }
}

void Plotter::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton ){
    emit clickX(event->x());
    emit clickY(event->y());
    press = true;
      mx = (event->x())/square;
      my = (event->y())/square;
    emit moveX(mx);
    emit moveY(my);

      if(pl == XY){
              px=mx;
              py=my;
              pz=dim;
          }

          else if(pl == YZ){
              py=mx;
              pz=my;
              px=dim;
          }

          else if(pl== XZ){
              pz=mx;
              px=my;
              py=dim;
          }
      Plotter::shape(sh);
  }
}

void Plotter::shape(int sh){
    if(sh == 1){
       s->setColor(r,g,b,a);
       s->putVoxel(px,py,pz);
    }
    if(sh == 2){
       s->cutVoxel(px,py,pz);
    }
    if(sh == 3){
        s->setColor(r,g,b,a);
        s->putBox(px,(px+x),py,(py+y),pz,(pz+z));
    }
    if(sh == 4){
       s->cutBox(px,(px+x),py,(py+y),pz,(pz+z));
    }
    if(sh == 5){
        s->setColor(r,g,b,a);
        s->putSphere(px,py,pz,rad);
    }
    if(sh == 6){
       s->cutSphere(px,py,pz,rad);
    }
    if(sh == 7){
        s->setColor(r,g,b,a);
        s->putEllipsoid(px,py,pz,rx,ry,rz);
    }
    if(sh == 8){
       s->cutEllipsoid(px,py,pz,rx,ry,rz);
    }
    repaint();
}

void Plotter::changeRed(int red){   if(red <= 255 && red >=0)
    r = red;
}
void Plotter::changeGreen(int green){
    g = green;
}
void Plotter::changeBlue(int blue){
    b = blue;
}
void Plotter::changeAlfa(int alpha){
    a = alpha;
}

void Plotter::changeDimX(int size){
    x=size;
}
void Plotter::changeDimY(int size){
    y=size;
}
void Plotter::changeDimZ(int size){
    z=size;
}
void Plotter::changeRaio(int rd){
    rad=rd;
}
void Plotter::changeRx(int radx){
    rx=radx;
}
void Plotter::changeRy(int rady){
    ry=rady;
}
void Plotter::changeRz(int radz){
    rz=radz;
}
void Plotter::changePlano(int pln){
    dim = pln;
    repaint();
}

void Plotter::criaOff(){
    s->writeOFF((char*)"teste.off");
    QMessageBox box;
    QString msg;
    msg = "O arquivo .OFF foi criado.";
    box.setText(msg);
    box.exec();
}


