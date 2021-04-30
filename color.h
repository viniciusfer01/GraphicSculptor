#ifndef COLOR_H
#define COLOR_H

#include <QWidget>

/**
 * @brief A classe Color é responsável pela ferramenta de alteração de cores.
 */
class Color : public QWidget{
    Q_OBJECT
private:
    int r,g,b;
public:
    explicit Color(QWidget *parent = nullptr);
    /**
     * @brief paintEvent permite o desenho do grid por uma matriz de cubos.
     */
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    /**
     * @brief set_r altera o valor da cor vermelha
     */
    void set_r(int _r);
    /**
     * @brief set_g altera o valor da cor verde
     */
    void set_g(int _g);
    /**
     * @brief set_b altera o valor da cor azul
     */
    void set_b(int _b);
};

#endif // COLOR_H
