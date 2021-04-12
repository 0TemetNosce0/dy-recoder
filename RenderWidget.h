#pragma once

#include <QWidget>
#define GREY_COLOR_BACKGROUND 0xFF4C4C4C
class RenderWidget:public QWidget
{
    Q_OBJECT
public:
    RenderWidget(QWidget * parent = nullptr,
                 Qt::WindowFlags flags = Qt::WindowFlags());

    OBSDisplay display;

    void CreateDisplay();

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void DisplayCreated(RenderWidget *window);
    void DisplayResized();

public:


    virtual QPaintEngine *paintEngine() const override;

    inline obs_display_t *GetDisplay() const { return display; }

    uint32_t backgroundColor = GREY_COLOR_BACKGROUND;

    QColor GetDisplayBackgroundColor() const;
    void SetDisplayBackgroundColor(const QColor &color);
    void UpdateDisplayBackgroundColor();
};

