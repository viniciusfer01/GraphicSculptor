#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <string>
#include <math.h>

using namespace std;

#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];
        for(int i=0; i<nx; i++){
            v[i] = new Voxel*[ny];
                for(int j=0; j<ny; j++){
                    v[i][j] = new Voxel[nz];
                }
        }

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
    cout << "Construtor Ok!" << endl;
}

Sculptor::~Sculptor(){

    if(nx==0||ny==0||nz==0){
        //falha no destructor
        return;
    }

    delete [] v[0][0];
    delete [] v[0];
    delete [] v;

}

void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r; //corresponde a cor vermelha.
    this->g = g; //corresponde a cor verde.
    this->b = b; //corresponde a cor azul.
    this->a = alpha; //corresponde a opacidade.
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;  //exibe o voxel.
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                cutVoxel(i,j,k);
                v[i][i][j].r = r;
                v[i][i][j].g = g;
                v[i][i][j].b = b;
                v[i][i][j].a = a;
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int i,j,k;
    for(i=0;i<nx;i++){
        for(j=0;j<ny;j++){
            for(k=0;k<nz;k++){
            //Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a presença de um Voxel no local.
                if(((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter)) <= radius*radius){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    //Seguindo a mesma lógica do putSphere, porém agora ao invés de chamar putVoxel será chamado a função cutVoxel, para retirar um voxel.

    int i,j,k;
    for(i=0;i<nx;i++){
        for(j=0;j<ny;j++){
            for(k=0;k<nz;k++){
                //Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a retirada de um Voxel no local.
                if(((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter)) <= radius*radius){
                    v[i][j][k].isOn = false;
                }
            }
        }
     }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;
    for(i=(xcenter-rx); i<=(xcenter+rx); i++){
        for(j=(ycenter-ry); j<=(ycenter+ry); j++){
            for(k=(zcenter-rz); k<=(zcenter+rz); k++){
                // Condição que verifica se a equação do elipsoid é respeitada e posteriormente habilita a presença de um Voxel no local, caso ela seja respeitada.
                if(pow(float(i-xcenter)/float(rx),2) + pow(float(j-ycenter)/float(ry),2) + pow(float(k-zcenter)/float(rz),2) <= 1){
                    v[i][j][k].isOn=true;
                    v[i][j][k].r=r;
                    v[i][j][k].b=b;
                    v[i][j][k].g=g;
                    v[i][j][k].a=a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;
    for(i=(xcenter-rx); i<=(xcenter+rx); i++){
        for(j=(ycenter-ry); j<=(ycenter+ry); j++){
            for(k=(zcenter-rz); k<=(zcenter+rz); k++){
                // Condição que verifica se a equação do elipsoid é respeitada e posteriormente habilita a retirada de um Voxel no local, caso ela seja respeitada.
                if(pow(float(i-xcenter)/float(rx),2) + pow(float(j-ycenter)/float(ry),2) + pow(float(k-zcenter)/float(rz),2) <= 1){
                    v[i][j][k].isOn=false;
                    }
                }
            }
        }
}

void Sculptor::writeOFF(char *filename){
    int NVoxels = 0, NVertices, NFaces;
    float faces = 0;

    ofstream fout;

    fout.open(filename);
    if (!fout.is_open()){
       exit(1);
       cout << "Não foi possivel gravar no arquivo";
    }

    fout << "OFF \n";

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if (v[i][j][k].isOn == true){
                    NVoxels++;
                }
            }
        }
    }

    NVertices = 8*NVoxels;
    NFaces = 6*NVoxels;

    fout << NVertices << " " << NFaces << " " << 0 << endl;

    //Vertices do cubo sendo inseridos no aqruivo OFF
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].isOn){
                    fout << i-0.5 << " " << j+0.5 << " " << k-0.5 << endl
                         << i-0.5 << " " << j-0.5 << " " << k-0.5 << endl
                         << i+0.5 << " " << j-0.5 << " " << k-0.5 << endl
                         << i+0.5 << " " << j+0.5 << " " << k-0.5 << endl
                         << i-0.5 << " " << j+0.5 << " " << k+0.5 << endl
                         << i-0.5 << " " << j-0.5 << " " << k+0.5 << endl
                         << i+0.5 << " " << j-0.5 << " " << k+0.5 << endl
                         << i+0.5 << " " << j+0.5 << " " << k+0.5 << endl;
                 }
            }
        }
    }
    //Faces do cubo sendo inseridos no arquivo OFF
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout << 4 << " " << 0+faces << " " << 3+faces << " " << 2+faces << " " << 1+faces << " "
                         << v[i][j][k].r/255 << " " << v[i][j][k].g/255  << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl
                         << 4 << " " << 4+faces << " " << 5+faces << " " << 6+faces << " " << 7+faces<< " "
                         << v[i][j][k].r/255 << " " << v[i][j][k].g/255 << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl
                         << 4 << " " << 0+faces << " " << 1+faces << " " << 5+faces << " " << 4+faces << " "
                         << v[i][j][k].r/255  << " " << v[i][j][k].g/255  << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl
                         << 4 << " " << 0+faces << " " << 4+faces << " " << 7+faces << " " << 3+faces << " "
                         << v[i][j][k].r/255 << " " << v[i][j][k].g/255 << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl
                         << 4 << " " << 3+faces << " " << 7+faces << " " << 6+faces << " " << 2+faces << " "
                         << v[i][j][k].r/255 << " " << v[i][j][k].g/255 << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl
                         << 4 << " " << 1+faces << " " << 2+faces << " " << 6+faces << " " << 5+faces<< " "
                         << v[i][j][k].r/255 << " " << v[i][j][k].g/255 << " " << v[i][j][k].b/255 << " " << v[i][j][k].a/255 << endl;
                    faces = faces+8;

                 }
            }
        }
    }

    fout.close();
}

vector<vector<Voxel>> Sculptor::readMx(int dim, int pl){
    vector<vector<Voxel>> m;
    vector<Voxel> l;
    if (pl == XY){
        l.resize(ny);
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                l[j].isOn = v[i][j][dim].isOn;
                l[j].r = v[i][j][dim].r;
                l[j].g = v[i][j][dim].g;
                l[j].b = v[i][j][dim].b;
                l[j].a = v[i][j][dim].a;
            }
            m.push_back(l);
        }
    }
    if (pl == YZ){
        l.resize(nz);
        for(int i = 0; i<ny; i++){
            for(int j = 0; j<nz; j++){
                l[j].isOn = v[dim][i][j].isOn;
                l[j].r = v[dim][i][j].r;
                l[j].g = v[dim][i][j].g;
                l[j].b = v[dim][i][j].b;
                l[j].a = v[dim][i][j].a;
            }
            m.push_back(l);
        }
    }

    if (pl == XZ){
        l.resize(nx);
        for(int i = 0; i<nz; i++){
            for(int j = 0; j<nx; j++){
                l[j].isOn = v[j][dim][i].isOn;
                l[j].r = v[j][dim][i].r;
                l[j].g = v[j][dim][i].g;
                l[j].b = v[j][dim][i].b;
                l[j].a = v[j][dim][i].a;
            }
            m.push_back(l);
        }
    }
    l.clear();
    return m;
}
