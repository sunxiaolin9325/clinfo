#include "platformanddeviceinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlatformAndDeviceInfo w;
    w.show();

    return a.exec();
}
