#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_textEdit_textChanged();

    void on_listView_clicked(const QModelIndex &index);

    void on_lineEdit_selectionChanged();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_editingFinished();

    void on_pushButton_arrow_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
