#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    core = new RecoderCore;

    //声音初始化
    auto inputDevices = core->GetWASAPIAudioInputDevices();


    if(inputDevices.size()>0){
        ui->input->addItem("defaut","");
        for (auto & devices: inputDevices) {
            ui->input->addItem(devices.name,devices.id);
        }

    }else{

        ui->input->addItem("no","NO");
    }

//    core->changeAudioInputDevice("");
    auto outputDevices = core->GetWASAPIAudioOutputDevices();
    if(outputDevices.size()>0){
        ui->output->addItem("defaut","");

        for (auto & devices: outputDevices) {
            ui->output->addItem(devices.name,devices.id);
        }
    }else{

        ui->output->addItem("no","NO");
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_input_currentIndexChanged(int index)
{
//    QString id = ui->input->itemData(index).toString();
//    core->changeAudioInputDevice(id);

}

void Widget::on_output_currentIndexChanged(int index)
{
    QString id = ui->output->itemData(index).toString();
    core->changeAudioOutputDevice(id);
}



