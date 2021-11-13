#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    std::cin>>A;
    std::cout<<A<<std::endl;

    //



    ui->setupUi(this);

    h = 0.1;
    xBegin = -3;
    xEnd = 3 + h;

    ui->widget->xAxis->setRange(-4,4);
    ui->widget->yAxis->setRange(-10,10);

    N = (xEnd - xBegin) / h + 2;

    for(X = xBegin ; X <= xEnd ; X += h)
    {
        res = 0;
        for(int  i = 0; i < A.get_degree() ; i++)
        {
         res += A[i]* qPow(X,A.get_degree()- i -1);
        }
        x.push_back(X);
        y.push_back(res);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    timer->start(20);
    X = xBegin;
    x.clear();
    y.clear();
}

void MainWindow::TimerSlot()
{
    if(time <=20*N)
    {
        if (X<=xEnd)
        {
            res = 0;
            for(int  i = 0; i < A.get_degree() ; i++)
            {
             res += A[i]* qPow(X,A.get_degree()- i -1);
            }
            x.push_back(X);
            y.push_back(res);
            X+=h;
        }
        time += 20;
    }
    else
    {
        time = 0;
        timer->stop();
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}

