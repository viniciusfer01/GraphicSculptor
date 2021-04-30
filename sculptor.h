#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "vector"
#include <iostream>

using namespace std;
enum{XY,YZ,XZ};

/**
 * @brief O struct Voxel cria uma entidade em três dimensões.
 * @param r é a componente resposável pela cor vermelha
 * @param g é a componente resposável pela cor verde
 * @param b é a componente resposável pela cor blue
 * @param a é a componente resposável pela transparência
 * @param isOn é a componente resposável pela construção ou não do Voxel
 */
struct Voxel {
  float r,g,b; // Cores.
  float a; // Transparência.
  bool isOn; // Incluir ou não.
};

/**
 * @brief A classe Sculptor é responsável por gerar uma matriz para o ambiente onde serão esculpidos os objetos.
 */
class Sculptor {
protected:
  /**
   * @brief v é uma matriz tridimensional, formada a partir de um ponteiro para ponteiro para ponteiro para Voxel.
   */
  Voxel ***v; // Matriz 3D.
  /**
   * @brief nx armazena a quantidadede de elementos na direção x da matriz.
   */
  int nx;
  /**
   * @brief ny armazena a quantidadede de elementos na direção y da matriz.
   */
  int ny;
  /**
   * @brief nz armazena a quantidadede de elementos na direção z da matriz.
   */
  int nz;
  /**
   * @brief r armazena o valor referenete a cor vermelha.
   */
  float r;
  /**
   * @brief g armazena o valor referenete a cor verde.
   */
  float g;
  /**
   * @brief r armazena o valor referenete a cor azul.
   */
  float b;
  /**
   * @brief g armazena o valor referenete a transparência.
   */
  float a;
public:
  /**
   * @brief A função Sculptor aloca uma matriz para o ambiente onde serão esculpidos os objetos.
   * @param _nx é o valor referente a dimensão do objeto na direção x.
   * @param _ny é o valor referente a dimensão do objeto na direção y.
   * @param _nz é o valor referente a dimensão do objeto na direção z.
   */
  Sculptor(int _nx, int _ny, int _nz);
  /**
   * @brief A função ~Sculptor é o destructor da função <b>Sculptor</b>.
   * @sa Sculptor.
   */
  ~Sculptor();
  /**
   * @brief A função setColor atribui as cores ao objeto que será esculpido.
   * @brief O valor das cores é um número float que pode variar de 0 à 1, que representam, respectivamente, ausência ou valor máximo de cor.
   * @param r é o parâmetro com o valor correspondente à cor <b>Vermelha</b>;
   * @param g é o parâmetro com o valor correspondente à cor <b>Verde</b>;
   * @param b é o parâmetro com o valor correspondente à cor <b>Azul</b>;
   */
  void setColor(float r, float g, float b, float alpha);
  /**
   * @brief A função putVoxel cria um Voxel no ambiente, na posição definida pelo usuário.
   * @param x é o parâmetro com o valor da coordenada x;
   * @param y é o parâmetro com o valor da coordenada y;
   * @param z é o parâmetro com o valor da coordenada z;
   */
  void putVoxel(int x, int y, int z);
  /**
   * @brief A função cutVoxel remove um Voxel na posição definida pelo usuário.
   * @brief Os parâmetros utilizados por esta função são os mesmos da <b>putVoxel</b>.
   * @sa putVoxel
   */
  void cutVoxel(int x, int y, int z);
  /**
   * @brief A função putBox cria uma entidade de Voxels no formato de uma cubo.
   * @brief Esta função utiliza os valores de índice 0 como iniciadores, que vão até os valores de índice 1, em cada uma das coordenadas.
   * @param x0,y0,z0 são os valores das coordenadas as quais o cubo será construído.
   * @param x1,y1,z1 são os valores que delimitam até qual coordenada o cubo será construído.
   */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief A função cutBox remove uma sequência de Voxels no formato de um cubo.
   * @brief Os parâmetros utilizados por esta função são os mesmos da <b>putBox</b>.
   * @sa putBox
   */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief A função putSphere cria uma entidade de Voxels no formato de uma esfera.
   * @param xcenter é o parâmetro com o valor do centro da esfera na coordenada x;
   * @param ycenter é o parâmetro com o valor do centro da esfera na coordenada y;
   * @param zcenter é o parâmetro com o valor do centro da esfera na coordenada z;
   * @param radius é o parâmetro com o valor do raio da esfera.
   */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief A função cutSphere remove(ou corta) uma sequência de Voxels no formato de uma esfera.
   * @brief Os parâmetros utilizados por esta função são os mesmos da <b>putSphere</b>.
   * @sa putSphere
   */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief Criar uma sequência de Voxels em forma de elipsóide.
   * @param xcenter é o parâmetro com o valor do centro da elipsóide na coordenada x;
   * @param ycenter é o parâmetro com o valor do centro da elipsóide na coordenada y;
   * @param zcenter é o parâmetro com o valor do centro da elipsóide na coordenada z;
   * @param rx é o parâmetro com o valor do raio da elipsóide na coordenada x;
   * @param ry é o parâmetro com o valor do raio da elipsóide na coordenada y;
   * @param rz é o parâmetro com o valor do raio da elipsóide na coordenada z;
   */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief A função cutEllipsoid remove(ou corta) uma sequência de Voxels no formato de um elipsóide.
   * @brief Os parâmetros utilizados por esta função são os mesmos da <b>cutEllipsoid</b>.
   * @sa cutEllipsoid
   */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief Criar arquivo para leitura do desenho, contendo as dimensões e as cores utilizando.
   */
  void writeOFF(char* filename);
  /**
   * @brief readMx é a função responsável por possibilitar a interação entre as vistas de planos 2D do ambiente.
   * @param dim guarda o valor da coordenada que será associada ao plano.
   * @param pl guarda o valor do Plano que será observado.
   */
  vector<vector<Voxel>> readMx(int dim=0, int pl = XY);
};
#endif // SCULPTOR_H
