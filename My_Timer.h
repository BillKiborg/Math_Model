#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <QtWidgets>
#include "MyGridLayout.h"

//===============================
class My_Timer : public QWidget {
    Q_OBJECT
private:
    QTime*          time_start      = nullptr; 
    QTime*          time_stop       = nullptr;
    MyGridLayout*   playout         = nullptr;
    bool            stop_flag       = false;    

protected:
    void timerEvent(QTimerEvent*) override;

public:
    My_Timer();
    void build_layout();
    void update_time();

public slots:
    void timer_start();
    void timer_stop();

};
//===============================

#endif

