#ifndef WORKER_OCR_H
#define WORKER_OCR_H
#include <QObject>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include "utility.h"
#include "ppocr.h"


class Worker_ocr:public QObject
{
    Q_OBJECT
public:
    Worker_ocr(QMainWindow *parent);
    QMainWindow *parent;
    void passFiles(QStringList selectedFiles);
    void setFilesName(QStringList filesname);
signals:
    void overAll();
public slots:
    void doWork();
private:
    QStringList selectedfiles;
    QStringList filesname;
    std::vector<std::vector<OCRPredictResult>> results;
    std::vector<cv::String> getCVImgPath();
    void saveText();
};

#endif // WORKER_OCR_H
