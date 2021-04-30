#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include "sculptor.h"
#include "vector"
#include <iostream>

using namespace std;
/**
 * @brief A classe Plotter é resposável por permitir a criação de desenhos.
 */
class Plotter : public QWidget{
    Q_OBJECT
private:


public:
    /**
     * @brief Plotter especifíca um  o Widget para ser colocado no layout.
     * @param parent é uma ponteiro que aponta pra um valor nulo e faz com que não seja preciso um pai específico para o Widget.
     */
    explicit Plotter(QWidget *parent = nullptr);
         /**
         * @brief paintEvent é um evento que permite o desenho do grid por meio de uma mtriz de cubos.
         */
        void paintEvent(QPaintEvent *event);
        /**
         * @brief mousePressEvent é um evento que permite o desenho do voxel quando o mouse é clicado.
         */
        void mousePressEvent(QMouseEvent *event);
        /**
         * @brief mouseReleaseEvent é um evento que desativa o desenho do voxel quando o mouse deixa de ser clicado.
         */
        void mouseReleaseEvent(QMouseEvent *event);
        /**
         * @brief shape é uma função que designa a forma geometrica a ser desenhada.
         * @param sh guarda a forma geometrica que será desenhada.
         */
        void shape(int sh);

        Sculptor *s;

        int sh = 1;
        int dim, pl;
        int sx, sy, sz;
        int r, g, b, a;
        int rad, rx, ry,rz;
        int x,y,z;
        int h, w;
    private:
        vector<vector<Voxel>> p;
        QColor lineColor;
        int cor;
        QAction *actionMudaCor;
        int cube;
        int square;
        int px, py, pz;
        bool press;
        int mx, my;
    signals:
        /**
         * @brief moveX é a função resposável por guardar as posições X do mouse.
         */
        void moveX(int);
        /**
         * @brief moveY é a função resposável por guardar as posições Y do mouse.
         */
        void moveY(int);
        /**
         * @brief clickX é a função resposável por guardar as posições X do mouse quando clicado.
         */
        void clickX(int);
        /**
         * @brief clickY é a função resposável por guardar as posições Y do mouse quando clicado
         */
        void clickY(int);
        /**
         * @brief planeChosen é a função resposável por guardar o plano que foi escolhido para o desenho.
         */
        void planeChosen(int);
    public slots:
        /**
         * @brief changeDimX é a função resposável pelo tamanho da dimensão X da caixa.
         * @param dimx armazena o valor da dimensão X.
         */
        void changeDimX(int dimx);
        /**
         * @brief changeDimY é a função resposável pelo tamanho da dimensão Y da caixa.
         * @param dimy armazena o valor da dimensão Y.
         */
        void changeDimY(int dimy);
        /**
         * @brief changeDimZ é a função resposável pelo tamanho da dimensão Z da caixa.
         * @param dimz armazena o valor da dimensão Z.
         */
        void changeDimZ(int dimz);
        /**
         * @brief changeRaio é a função resposável pelo tamanho do raio.
         * @param raio armazena o valor do raio da Esfera.
         */
        void changeRaio(int raio);
        /**
         * @brief changeRx é a função responsável por alterar o raio no eixo x da elipsoide.
         * @param radx armazena o valor do raio no eixo x escolhido pelo usuário
         */
        void changeRx(int radx);
        /**
         * @brief changeRy é a função responsável por alterar o raio no eixo y da elipsoide.
         * @param rady armazena o valor do raio no eixo y escolhido pelo usuário
         */
        void changeRy(int rady);
        /**
         * @brief changeRz é a função responsável por alterar o raio no eixo z da elipsoide.
         * @param radz armazena o valor do raio no eixo z escolhido pelo usuário
         */
        void changeRz(int radz);
        /**
         * @brief changeRed é a função responsável por alterar a cor <b>Vermelho</b> do voxel a ser desenhado.
         * @param red armazena o valor do canal r que o usuário escolheu.
         */
        void changeRed(int red);
        /**
         * @brief changeGreen é a função responsável por alterar a cor <b>Verde</b> do voxel a ser desenhado.
         * @param green armazena o valor do canal g que o usuário escolheu.
         */
        void changeGreen(int green);
        /**
         * @brief changeBlue é a função responsável por alterar a cor <b>Azul</b> do voxel a ser desenhado.
         * @param blue armazena o valor do canal b que o usuário escolheu.
         */
        void changeBlue(int blue);
        /**
         * @brief changeAlfa é a função responsável por alterar a transparência do voxel a ser desenhado.
         * @param alpha armazena o valor da transparência que o usuário escolheu.
         */
        void changeAlfa(int alpha);
        /**
         * @brief changePlano é a função responsável por alterar qual parcela do plano o usuário está visualizando.
         * @param pln armazena o valor do plano que o usuário escolheu.
         */
        void changePlano(int pln);
        /**
         * @brief criaOff é a função responsável por chamar writeOFF(), que salva o arquivo no formato OFF.
         */
        void criaOff();
        /**
         * @brief mouseMoveEvent é um evento que permite o desenho do voxel durante o movimento do mouse enquanto ele estiver pressionado.
         */
        void mouseMoveEvent(QMouseEvent *event);

public slots:

signals:

};

#endif // PLOTTER_H

