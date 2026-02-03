#include "../control/Control.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Control cont;


    cont.showWindow();
    return a.exec();
}
