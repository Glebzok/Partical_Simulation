#include "widget.h"
#include "ui_widget.h"
#include <string.h>
#include <QDir>

QTextStream& operator<<(QTextStream &stream, std::vector<double> v)
{
    for (double i = 0 ; i != v.size(); i++ )
        stream << v.at(i) << ' ';
    return stream;
}

Widget::Widget(QWidget *parent, vector<Particle*> ps, QString name) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->ps = ps;
    this->name = name;
    TimeElapsed = 0;

    QDir dir("/home/gottlieb/Documents/C++/Simulation/Saves/");
     dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (auto i : list){
        QString system_name = i.fileName().replace(QString(".txt"), QString(""));
        this->ui->listWidget->addItem(system_name);
    }
    this->ui->listWidget->setCurrentItem(this->ui->listWidget->item(0));
}

Widget::~Widget()

{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int size = this->ps.size();
    QVector<double> X, Y;
    for(int i = 0; i != this->ps.size(); i++){
        X.push_back(this->ps.at(i)->x.at(0));
        Y.push_back(this->ps.at(i)->y.at(0));
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(X,Y);

    double xMAX = this->ps.at(0)->x[0];
    double xMIN = this->ps.at(0)->x[0];
    double yMAX = this->ps.at(0)->y[0];
    double yMIN = this->ps.at(0)->y[0];


    for(int i = 0; i != this->ps.size(); i++){
        double xMax = *max_element(this->ps.at(i)->x.begin(),this->ps.at(i)->x.end());
        xMAX = (xMAX - xMax > 0.01)?xMAX:xMax;
        double xMin = *min_element(this->ps.at(i)->x.begin(),this->ps.at(i)->x.end());
        xMIN = (xMIN - xMin < 0.01)?xMIN:xMin;
        double yMax = *max_element(this->ps.at(i)->y.begin(),this->ps.at(i)->y.end());
        yMAX = (yMAX - yMax > 0.01)?yMAX:yMax;
        double yMin = *min_element(this->ps.at(i)->y.begin(),this->ps.at(i)->y.end());
        yMIN = (yMIN - yMin < 0.01)?yMIN:yMin;
}
    double Max = (xMAX - yMAX > 0.01)?xMAX:yMAX;
    double Min = (xMIN - yMIN < 0.01)?xMIN:yMIN;

    ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
    //формируем вид точек
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->widget->xAxis->setRange(xMIN, xMAX);
    ui->widget->yAxis->setRange(yMIN, yMAX);
    ui->widget->replot();


    playBackTimer = new QTimer(this); //создание экземпляра таймера
    connect(playBackTimer, SIGNAL(timeout()), this, SLOT(PlaybackStep())); //привязка события к функции PlaybackStep()
    playBackTimer->start(16);
}

void Widget::PlaybackStep()
{
    QVector<double> X, Y;

    if(!this->ui->checkBox->checkState() == Qt::CheckState()){
        for(int i = 0; i != this->ps.size(); i++){
            for(int j = 0; j != TimeElapsed; j++){
                X.push_back(this->ps.at(i)->x.at(j));
                Y.push_back(this->ps.at(i)->y.at(j));
            }
        }
    }
    else{
        for(int i = 0; i != this->ps.size(); i++){
            X.push_back(this->ps.at(i)->x.at(TimeElapsed));
            Y.push_back(this->ps.at(i)->y.at(TimeElapsed));
        }
    }

    TimeElapsed+=1;
    if(TimeElapsed >this->ps.at(0)->x.size() - 1)
        TimeElapsed = 0;

    //ui->widget->clearGraphs();
    ui->widget->graph(0)->setData(X,Y);
    ui->widget->replot();
}

void Widget::on_pushButton_3_clicked()
{
    QString file_name = "/home/gottlieb/Documents/C++/Simulation/Saves/" + this->name;

    QFile file(file_name + ".txt");
    for(int i = 0; i!= 100; i++){
        if (!QFile::exists(file.fileName())){
            file.open(QIODevice::WriteOnly);

            break;
        }
        else{
            QString ind(QString::number(i));
            QString name = file_name + ind + ".txt";

            file.setFileName(name);
        }
    }
    QTextStream out(&file);
    long number_of_particles = this->ps.size();
    out << number_of_particles << ' ';
    long number_of_steps = this->ps.at(0)->t.size();
    out << number_of_steps << ' ';
    for(long i = 0; i != this->ps.size(); i++){
        out << this->ps.at(i)->x;
        out << this->ps.at(i)->y;
        out << this->ps.at(i)->z;
    }
    file.close();

    QDir dir("/home/gottlieb/Documents/C++/Simulation/Saves/");
     dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    this->ui->listWidget->clear();
    for (auto i : list){
        QString system_name = i.fileName().replace(QString(".txt"), QString(""));
        this->ui->listWidget->addItem(system_name);
    }
}



void Widget::on_pushButton_2_clicked()
{
    QString file_name = "/home/gottlieb/Documents/C++/Simulation/Saves/" + this->ui->listWidget->currentItem()->text() + ".txt";

    QFile file(file_name);
    if (QFile::exists(file.fileName()))
        file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    long number_of_particles;
    in >> number_of_particles;

    long number_of_steps;
    in >> number_of_steps;

    vector<Particle*> ps = {};
    for(long i = 0; i != number_of_particles; i++){
        Particle* p = new Particle();
        double foo;
        for(long i = 0; i != number_of_steps; i++){
            in >> foo;
            p->x.push_back(foo);
        }
        for(long i = 0; i != number_of_steps; i++){
            in >> foo;
            p->y.push_back(foo);
        }
        for(long i = 0; i != number_of_steps; i++){
            in >> foo;
            p->z.push_back(foo);
        }
        ps.push_back(p);
    }
    if(this->playBackTimer->isActive())
        this->playBackTimer->stop();
    this->TimeElapsed = 0;
    this->ps = ps;

    file.close();
}
