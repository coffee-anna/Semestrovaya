#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Полёт материального тела, брошенного под углом к горизонту, с учётом сопротивления среды");

}

MainWindow::~MainWindow()
{
    delete ui;
}


//Обработчики изменения спинбоксов(при изменении значений записываем таковые в соответствующие переменные )
void MainWindow::on_mBox_valueChanged(double arg1)
{
    m=ui->mBox->value();
}

void MainWindow::on_gBox_valueChanged(double arg1)
{
    g=ui->gBox->value();
}

void MainWindow::on_vBox_valueChanged(double arg1)
{
    v=ui->vBox->value();
}

void MainWindow::on_aBox_valueChanged(double arg1)
{
    alph=ui->aBox->value();
}

void MainWindow::on_kBox_valueChanged(double arg1)
{
    k=ui->kBox->value();
}

void MainWindow::on_TBox_valueChanged(double arg1)
{
    T=ui->TBox->value();
}
//(Обработчик нажатия на кнопку "Начать")
void MainWindow::on_pushButton_clicked()
{
    ui->widget->setChart(graph);//Теперь виджет будет показывать наш график
    QLocale loc(QLocale::Russian);//Для работы со String и использования русского языка
    graph->removeAllSeries();//Стираем график, оси, обновляем переменные, дабы избежать наложения графиков в случае, когда пользователь не выполнил сброс
    graph->removeAxis(axisX);
    graph->removeAxis(axisY);
    maxH=0;//Обновляем значения максиамальной высоты и дистанции
    distanceMax=0;
    ui->maxHLabel->setText(loc.toString(maxH));//прикладываем их к графику
    ui->maxDistance->setText(loc.toString(distanceMax));
    QLineSeries* series=new QLineSeries;//Создаем новый series для нашего графика
    ui->GLabel->setText("График полета тела");//Даем определение маркеру над графиком
    graph->addSeries(series);//Сразу включаем series в график
    series->append(0,0);//Ставим точку 0, т.к. любой бросок будет сделан из нее
    x = 0; // координата по Х
    y = 0; // координата по У
    vx = v * qCos(alph / 180 * PI); // скоротсь по Х
    vy = v * qSin(alph / 180 * PI); // скорость по У
    ax = -k * vx; // ускорение по Х
    ay = -k * vy - g; // ускорение по У

    //проходимся и вычисляем значения
    for (double t = 0; t < T && y >= 0; t += dt)
    {

    // обновляем ускорения
    ax = -k * vx;
    ay = -k * vy - g;

    // обновляем скорости
    vx += ax * dt;
    vy += ay * dt;

    // обновляем координаты
    x += vx * dt;
    y += vy * dt;

    // обновляем максимальную высоту и расстояние
    if (y > maxH)
    maxH = y;
    if (x > distanceMax)
    distanceMax = x;
    //Наносим точки на график, обновляем показатели максимальной высоты и расстояния на графике
    series->append(x,y);
     ui->maxHLabel->setText(loc.toString(maxH));
     ui->maxDistance->setText(loc.toString(distanceMax));
     }
     //Начинаем оформление графика
     double Xmax=x, Ymax=maxH;
     //Устанавливаем цвет самого графика, размер линии
     QPen pen=series->pen();
     pen.setColor("DarkCyan");
     pen.setWidth(4);
     series->setPen(pen);//подключаем ручку к графику

     axisX = new QValueAxis; //Создаем ось X
     axisX->setRange(0,Xmax);//Задаем размер оси
     axisX->setLabelFormat("%.3f");//Задаем формат отображения исел на оси
     axisX->setTitleText("X(Дальность броска)");
     axisX->setTitleBrush(Qt::black);// Цвет названия
     axisX->setLabelsColor(Qt::black);// Цвет оси
     graph->addAxis(axisX, Qt::AlignBottom);//Располагаем ось X внизу.
     series->attachAxis(axisX);//Прикладываем ось к series

     axisY = new QValueAxis; //Создаем ось Y
     axisY->setRange(0,Ymax+Ymax/10);//Задаем размер оси
     axisY->setLabelFormat("%.3f");//Задаем формат отображения чисел на оси
     axisY->setTitleText("Y(Высота броска)");//Задаем название оси
     axisY->setTitleBrush(Qt::black);// Цвет названия
     axisY->setLabelsColor(Qt::black);// Цвет оси
     graph->addAxis(axisY, Qt::AlignLeft);//Располагаем ось сбоку, слева
     series->attachAxis(axisY);//Прикладываем ось к series


}

void MainWindow::on_EraseButton_clicked()  //Обработчик нажатия на кнопку "Сброс"
{
    QLocale loc(QLocale::Russian);//Задаем для переводов в String
    graph->removeAllSeries();//Стираем график
    maxH=0;//Обновляем значения максиамальной высоты и дистанции
    distanceMax=0;
    ui->maxHLabel->setText(loc.toString(maxH));//прикладываем их к графику
    ui->maxDistance->setText(loc.toString(distanceMax));
    ui->maxHLabel->update();//обновляем
    ui->maxDistance->update();
    graph->removeAxis(axisX);
    graph->removeAxis(axisY);
    graph->setTitle("");
    ui->GLabel->setText(" ");


}

void MainWindow::on_ExitButton_clicked()
{
    close();//Закрываем программу
}
