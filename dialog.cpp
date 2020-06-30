#include "dialog.h"
#include "ui_dialog.h"
#include"C:/Users/Tomislav1/Desktop/RabotaQT/final1/countriesdata.h"
#include<QFile>
#include<QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    CountriesData *model = new CountriesData(this);

    //File read
    QFile file("C:/Users/Tomislav1/Desktop/RabotaQT/final1/countries/countries.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<file.errorString();
    }
    else{
        qDebug()<<"Success";
    }

    QTextStream in(&file);

    while(!in.atEnd()) {


        QString line = in.readLine();
        QStringList fields = line.split(",");
        //Setting data

        model->addCountry(Country(fields[2],fields[0],fields[1]));
       // qDebug()<<model.
    }


    file.close();

    // end file read

    ui->listView->setModel(model);
    ui->listView->show();



}

Dialog::~Dialog()
{
    delete ui;
}
