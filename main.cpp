#include <QtGui/QGuiApplication>
#include <QWindow>
#include "RW.H"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    RW rw;
    rw.setAnimating(true);
    rw.show();

    return app.exec();

}
