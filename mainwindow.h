#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>      //Подключаем наше окно
#include <QtMath>           //Для математических действий
#include <QString>          //Для работы со строковыми типами
#include <QDoubleValidator> //Для работы с вещественными типами
#include  <QLocale>         //Для объекта loc, который так же будет работать со string'овыми типами
#include <QPen>             //Для настройки ручек для графиков
#include<QtCharts/QtCharts> //Для самих графиков
#include<QApplication>      //Для работы с виджетами, управления GUI
using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double m,g,v,k,T=0,alph,dt = 0.01,vx,vy,ax,ay,maxH=0,distanceMax=0,x,y; //Объявим лавные переменные и объекты глобально, чтобы спокойно с ними работать
    double PI=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091;
    QChart*graph=new QChart;
    QValueAxis *axisX, *axisY;




private slots:
    void on_pushButton_clicked();

    void on_mBox_valueChanged(double arg1);

    void on_gBox_valueChanged(double arg1);

    void on_vBox_valueChanged(double arg1);

    void on_aBox_valueChanged(double arg1);

    void on_kBox_valueChanged(double arg1);

    void on_TBox_valueChanged(double arg1);

    void on_EraseButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
