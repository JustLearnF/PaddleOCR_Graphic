#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(QApplication::applicationDirPath() + "/icon.png"));
    this->initAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initAll()
{
    this->setWindowFlag(Qt::FramelessWindowHint);//无边框
    this->setFixedSize(this->width(),this->height());//固定大小
    this->workerui = new Worker_ui(this);//创建ui界面worker
    this->workerocr = new Worker_ocr(this);//创建ocr识别worker
    this->ocrthread = new QThread();//创建多线程
    ui->FilesList->setVisible(false);
    ui->ClearAll->setVisible(false);
    ui->StartDetect->setEnabled(false);
    connect(this->workerui->timer,&QTimer::timeout,this,&MainWindow::updateP);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        this->clickPos = e->pos();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton  //左键点击并且移动
        && e->pos().x()>=0      //范围在窗口的上面部分
        && e->pos().y()>=0
        && e->pos().y() <= 70)
    {
        move(e->pos()+pos()-clickPos);  //移动窗口
    }
}

void MainWindow::overDetect()
{
    this->workerui->stopTimer();
    ui->ProgressBar->setValue(100);
    ui->StartDetect->setEnabled(true);
    ui->ClearAll->setEnabled(true);
}

void MainWindow::updateP()
{
    if(ui->ProgressBar->value()<99){
    ui->ProgressBar->setValue(ui->ProgressBar->value()+9);
    }
}


/*
    UI事件
*/
void MainWindow::on_MiniumWindow_clicked()
{
    this->workerui->onMiniumWindow();
}


void MainWindow::on_CloseWindow_clicked()
{
    this->workerui->onCloseWindow();
}


void MainWindow::on_SelectFiles_clicked()
{
    bool isselected = this->workerui->onSelectFiles();
    if(isselected){
        ui->SelectFiles->setVisible(false);
        ui->FilesList->setVisible(true);
        ui->ClearAll->setVisible(true);
        ui->StartDetect->setEnabled(true);
        QStringList filesname = this->workerui->filepathToFilename();
        ui->FilesList->addItems(filesname);
        this->workerocr->setFilesName(filesname);
        filesname.clear();
    }
}


void MainWindow::on_ClearAll_clicked()
{
    ui->SelectFiles->setVisible(true);
    ui->FilesList->setVisible(false);
    ui->ClearAll->setVisible(false);
    ui->StartDetect->setEnabled(false);
    ui->FilesList->clear();
    this->workerui->selectedfiles.clear();
}


void MainWindow::on_StartDetect_clicked()
{
    ui->ProgressBar->setValue(0);
    ui->StartDetect->setEnabled(false);
    ui->ClearAll->setEnabled(false);
    this->workerocr->passFiles(this->workerui->selectedfiles);
    this->workerocr->moveToThread(this->ocrthread);
    connect(this,&MainWindow::startDetectAll,this->workerocr,&Worker_ocr::doWork);
    connect(this->workerocr,&Worker_ocr::overAll,this,&MainWindow::overDetect);
    this->ocrthread->start();
    emit this->startDetectAll();
    this->workerui->updateProgress();
}


void MainWindow::on_ShowResult_clicked()
{
    this->workerui->showResults();
}

