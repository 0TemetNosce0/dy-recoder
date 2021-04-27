#include "RenderWidget.h"
#include <QWindow>
#include <QScreen>
#include <QResizeEvent>
#include <QShowEvent>

#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
#define SUPPORTS_FRACTIONAL_SCALING
#endif

static inline void GetScaleAndCenterPos(int baseCX, int baseCY, int windowCX,
                                        int windowCY, int &x, int &y,
                                        float &scale)
{
    double windowAspect, baseAspect;
    int newCX, newCY;

    windowAspect = double(windowCX) / double(windowCY);
    baseAspect = double(baseCX) / double(baseCY);

    if (windowAspect > baseAspect) {
        scale = float(windowCY) / float(baseCY);
        newCX = int(double(windowCY) * baseAspect);
        newCY = windowCY;
    } else {
        scale = float(windowCX) / float(baseCX);
        newCX = windowCX;
        newCY = int(float(windowCX) / baseAspect);
    }

    x = windowCX / 2 - newCX / 2;
    y = windowCY / 2 - newCY / 2;
}

static inline void GetCenterPosFromFixedScale(int baseCX, int baseCY,
                                              int windowCX, int windowCY,
                                              int &x, int &y, float scale)
{
    x = (float(windowCX) - float(baseCX) * scale) / 2.0f;
    y = (float(windowCY) - float(baseCY) * scale) / 2.0f;
}

static inline QSize GetPixelSize(QWidget *widget)
{
#ifdef SUPPORTS_FRACTIONAL_SCALING
    return widget->size() * widget->devicePixelRatioF();
#else
    return widget->size() * widget->devicePixelRatio();
#endif
}
static inline long long color_to_int(const QColor &color)
{
    auto shift = [&](unsigned val, int shift) {
        return ((val & 0xff) << shift);
    };

    return shift(color.red(), 0) | shift(color.green(), 8) |
           shift(color.blue(), 16) | shift(color.alpha(), 24);
}

static inline QColor rgba_to_color(uint32_t rgba)
{
    return QColor::fromRgb(rgba & 0xFF, (rgba >> 8) & 0xFF,
                           (rgba >> 16) & 0xFF, (rgba >> 24) & 0xFF);
}
RenderWidget::RenderWidget(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    setAttribute(Qt::WA_NativeWindow);


}
