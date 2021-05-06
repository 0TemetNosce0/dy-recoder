#pragma once

#include <QComboBox>
#include <QWidget>
#include <RecoderCore.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    RecoderCore *core = nullptr;
public slots:
    void on_input_currentIndexChanged(int index);
    void on_output_currentIndexChanged(int index);
};
