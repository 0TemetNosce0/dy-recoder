#include "Widget.h"

#include <QApplication>
#include "capture/ScreenCapture/WindowHelper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    //test

    std::vector<DX::Monitor> monitors =  DX::GetMonitors();
    auto DXGIMonitors = DX::EnumerateAdapters();
    return a.exec();

}
