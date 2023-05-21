
#include "qtgrandorder.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtGrandOrder w;
    w.show();
    return a.exec();
}
