#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QThread>
#include "worker_ui.h"
#include "worker_ocr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Worker_ui *workerui;
    Worker_ocr *workerocr;

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void startDetectAll();

private slots:
    void overDetect();

    void updateP();

    void on_MiniumWindow_clicked();

    void on_CloseWindow_clicked();


    void on_SelectFiles_clicked();

    void on_ClearAll_clicked();

    void on_StartDetect_clicked();

    void on_ShowResult_clicked();

private:
    Ui::MainWindow *ui;
    void initAll();
    QPoint clickPos;
    QThread *ocrthread;
};
#endif // MAINWINDOW_H
