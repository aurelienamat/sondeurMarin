#include "sondeurMarin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    sondeurMarin window;
    window.show();
    return app.exec();
}
