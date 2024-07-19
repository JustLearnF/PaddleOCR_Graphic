#include "worker_ui.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>


Worker_ui::Worker_ui(QMainWindow *parent)
{
    this->parent=parent;
    this->timer = new QTimer();
}

void Worker_ui::onMiniumWindow()
{
    this->parent->showMinimized();
}

void Worker_ui::onCloseWindow()
{
    this->parent->close();
}

bool Worker_ui::onSelectFiles()
{
    this->selectedfiles = QFileDialog::getOpenFileNames(this->parent,QStringLiteral("选择文件"),"./","File(*.png *.jpg *.jiff)");
    if(this->selectedfiles.isEmpty()){
        return false;
    }
    return true;
}

void Worker_ui::showResults()
{
    QDesktopServices::openUrl(QUrl("file:./output",QUrl::TolerantMode));
}

void Worker_ui::updateProgress()
{
    this->timer->start(1000);
}

void Worker_ui::stopTimer()
{
    this->timer->stop();
}

QStringList Worker_ui::filepathToFilename()
{
    QStringList result;
    for(QString path : this->selectedfiles){
        QFileInfo fileinfo = QFileInfo(path);
        result.append(fileinfo.fileName());
    }
    return result;
}
