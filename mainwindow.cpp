#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QLineEdit>
#include<QFile>
#include<QDebug>
#include<QStandardItemModel>
#include<Qt>
#include<QBitmap>
#include"country.h"


QVector<Country>countries;
// Function returns flag number of the country
// when provided a prefix number of the same country
// it iterates throughout the container "countries"
inline QString findFlag(QString prefixNumber){
    QString flagNumber;
    for(int i = 0;i<countries.size();i++){
        if(countries[i].getPrefixNumber()==prefixNumber){
            flagNumber = countries[i].getFlagNumber();

        }
    }
    return flagNumber;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QStandardItemModel *rowModel = new QStandardItemModel(this);



    // File read
    // Opens and reads file from repository, if the file exsists and the reading is completed
    // it's printed out "Success", else the reason that caused error is printed out.
    QFile file(":/countries/countries/countries.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<file.errorString();
    }
    else{
        qDebug()<<"Success";
    }
    QTextStream in(&file);

    // Setting data
    // The text is read from the text file line by line, each line is splitted at the comma
    // since the file is CSV. After the split data is inserted in the rowModel which is how
    // each row of data will appear on the list. Whitespaces from the data are removed and
    //then is loaded to the container which isp used to iterate trough the data if needed.
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        rowModel->appendRow(new QStandardItem(QIcon(":/flags/flags/"+fields[0]+".jpg"), fields[2]+"+"+ fields[1].simplified().remove(" ")));

        QString flags_no_space = fields[0].simplified().remove(" ");
        QString prefix_no_space = fields[1].simplified().remove(" ");
        Country country(fields[2],flags_no_space,fields[1].simplified().remove(" "));
        countries.push_back(country);

    }

    file.close(); // closing file
    ui->listView->setModel(rowModel); // setting model

    //Background
    ui->centralwidget->setStyleSheet("background-image:url(:/resources/resources/bgd_bubbles.png);");

    //Send Button
    ui->pushButton_send->setStyleSheet(" background-image:url(:/resources/resources/btn_white_normal.png); "
                                 "background-repeat: no-repeat;"
                                 "height: 28px ; width: 41px;"
                                 "background-position: center;"
                                 "background-color:transparent");
    ui->pushButton_send->setText("Send");

    //LineEdit
    QBitmap map(":/resources/resources/field_normal.png");
    ui->lineEdit->setMask(map.mask());
    ui->lineEdit->setPlaceholderText("enter phone number");

    //Text Edit
    ui->textEdit->setStyleSheet("background-color:white");
    ui->textEdit->setPlaceholderText("Type message");

    // Word count
    ui->label_numberCount->setStyleSheet("background-color:transparent");
    ui->label_numberCount->setText("0");


    // listView
    ui->listView->hide();
    ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setStyleSheet("background-color:white");


    // combo arrow push btn
    ui->pushButton_arrow->setStyleSheet("background-image : url(:/resources/resources/combo_arrow.png);"
                                    "background-repeat: no-repeat;"
                                    "background-position: center;"
                                    "background-color:transparent");
    ui->pushButton_arrow->setText("");


    // call button
    ui->pushButton_call->setStyleSheet("background-image : url(:/resources/resources/icons8-phone-24.png);"
                                    "background-repeat: no-repeat;"
                                    "background-position: center");
    ui->pushButton_call->setText("");


    // see rates label
    ui->label_seeRates->setStyleSheet("background-color:transparent");
    ui->label_seeRates->setText("See rates");


    // call label
    ui->label_Call->setStyleSheet("background-color:transparent");
    ui->label_Call->setText("Call");


    // credit label
    ui->label_Credit->setStyleSheet("background-color:transparent");
    ui->label_Credit->setText("Credit");


    // credit num label
    ui->label_textNumber->setStyleSheet("background-color:transparent");
    ui->label_textNumber->setNum(0.00);


    // buy credit label
    ui->label_buyCredit->setStyleSheet("background-color:transparent");
    ui->label_buyCredit->setText("Buy credit");


    ui->label_numberTextMessages->setText("/0");
    ui->label_numberTextMessages->setStyleSheet("background-color:transparent");

    // Default character counter
    ui->label_numberCount->setNum(160);

}


MainWindow::~MainWindow()
{
    delete ui;
}

// Text number
// Counts the text if the number of characters exeeds 160, the number of
// text messages requiered to send all characters updates and the character
// counter resets.
void MainWindow::on_textEdit_textChanged()
{
    static int maxTextLenght = 160;
    static int numberTextMessages = 0;
    int currentLenght = ui->textEdit->toPlainText().length(); // getting the current lentght from the text area
    currentLenght = maxTextLenght-currentLenght;
    ui->label_numberCount->setNum(currentLenght);
    if(currentLenght==0){
        numberTextMessages++;
        maxTextLenght=(numberTextMessages+1)*160;
    }
    ui->label_numberTextMessages->setText("/"+QString::number(numberTextMessages));
}


// On item selected from listview data is extracted from the current index,
// from the data the prefix is displayed on the line edit, also it's used to find
// the flag number of the current country from the container
void MainWindow::on_listView_clicked(const QModelIndex &index)
{

    QString itemText = index.data(Qt::DisplayRole).toString(); // extracting data
    QStringList dataList = itemText.split("+"); // splitting the name of the country and prefix number
    QString prefixNumber = dataList[1];
    QString flagNumber = findFlag(prefixNumber);

    ui->lineEdit->setText(prefixNumber);
    ui->pushButton_arrow->setStyleSheet("background-image:url(:/flags/flags/"+flagNumber+".jpg);"
                                        "background-repeat: no-repeat;"
                                        "background-position: center");
     ui->listView->hide();

}

// Hide list
void MainWindow::on_lineEdit_selectionChanged()
{
    ui->listView->hide();
}



// When the text is changed on the lineEdit it checks the entered prefix number with all the prefix numbers
// in the container "countries" and if there is a match , the icon is changed to the flag that matches the
// prefix number.
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

    for(int i = 0;i<countries.size();i++){
        if(countries[i].getPrefixNumber()==arg1)
            ui->pushButton_arrow->setStyleSheet(" background-image:url(:/flags/flags/"+countries[i].getFlagNumber()+".jpg);"
                                            "background-repeat: no-repeat;"
                                            "background-position: center");
    }

}
// Same as previous, just when the editing is finished
void MainWindow::on_lineEdit_editingFinished()
{
    for(int i = 0;i<countries.size();i++){
        if(countries[i].getPrefixNumber()==ui->lineEdit->text())
            ui->pushButton_arrow->setStyleSheet(" background-image:url(:/flags/flags/"+countries[i].getFlagNumber()+".jpg);"
                                            "background-repeat: no-repeat;"
                                            "background-position: center");
    }
}

void MainWindow::on_pushButton_arrow_clicked()
{
   ui->listView->show();
}
