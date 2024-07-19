#ifndef WORKER_UI_H
#define WORKER_UI_H

#include <QMainWindow>
#include <QTimer>

class Worker_ui
{
public:
    Worker_ui(QMainWindow *parent);
    QMainWindow *parent;
    QStringList selectedfiles;
    QTimer *timer;
    void onMiniumWindow();
    void onCloseWindow();
    bool onSelectFiles();
    void showResults();
    void updateProgress();
    void stopTimer();
    QStringList filepathToFilename();
};

#endif // WORKER_UI_H
