#include "Widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    //test

//    std::vector<DX::Monitor> monitors =  DX::GetMonitors();
//    auto DXGIMonitors = DX::EnumerateAdapters();

//    DXGIScreenCapture capture;
//    capture.Init(1);
//        capture.AquireFrame();
//        capture.CaptureImage("d:/test.png");
    return a.exec();

}
