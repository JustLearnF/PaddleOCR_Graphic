#include "worker_ocr.h"
#include <QFile>

Worker_ocr::Worker_ocr(QMainWindow *parent)
{
    this->parent=parent;
}

void Worker_ocr::passFiles(QStringList selectedFiles)
{
    this->selectedfiles = selectedFiles;
}

void Worker_ocr::setFilesName(QStringList filesname)
{
    this->filesname = filesname;
}

std::vector<cv::String> Worker_ocr::getCVImgPath()
{
    std::vector<cv::String> imglist;
    for(QString imgpath : this->selectedfiles){
        imglist.push_back(imgpath.toLocal8Bit().data());
    }
    return imglist;
}

void Worker_ocr::saveText()
{
    for(QString filename : this->filesname)
    for(std::vector<OCRPredictResult> imgresult : this->results){
        QFile file("./output/"+filename+".txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        for(OCRPredictResult result : imgresult){
            file.write(QString::fromStdString(result.text).toUtf8());
        }
        file.close();
    }
}

void Worker_ocr::doWork()
{
    std::vector<cv::String> imglist = this->getCVImgPath();
    this->results=detectAll(imglist);
    this->saveText();
    this->results.clear();
    this->selectedfiles.clear();
    emit overAll();
}
