#pragma once

#include <QWidget>
#define GREY_COLOR_BACKGROUND 0xFF4C4C4C
class RenderWidget:public QWidget
{
    Q_OBJECT
public:
    RenderWidget(QWidget * parent = nullptr,
                 Qt::WindowFlags flags = Qt::WindowFlags());


};

