#include "My_Timer.h"

using This_Class = My_Timer;

This_Class::My_Timer() {
    //------------------------
    setWindowTitle("Timer");
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setFixedSize(270, 100);    
    move(22, 31);
    show();
    setFont(QFont("Text", 20));
    build_layout();

    startTimer(0);
    //------------------------
}

void This_Class::timerEvent(QTimerEvent*) {
    //----------------------------------------
    if (time_start) {        
        if (!stop_flag) update_time();
    }
    //----------------------------------------
}

void This_Class::update_time() {
    //------------------------------------------------
    auto&   p_layout        = *playout;
    auto    table           = static_cast<QLabel*>(p_layout["table"]);
    auto    m_sec           = time_start->msecsTo(QTime::currentTime());    

    QTime current_time(0, 0, 0, 0);
    current_time = current_time.addMSecs(m_sec);    

    QString message;
    if (current_time.hour() < 10) message += "0";
    message += QString::number(current_time.hour()) + ":";

    if (current_time.minute() < 10) message += "0";
    message += QString::number(current_time.minute()) + ":";

    if (current_time.second() < 10) message += "0";
    message += QString::number(current_time.second()) + ":";

    if (current_time.msec() < 10) message += "00";
    else if (current_time.msec() < 100) message += "0";
    message += QString::number(current_time.msec()) + ";";

    table->setText(message);
    //------------------------------------------------
}

void This_Class::build_layout() {
    //------------------------------------------------
    playout             = new MyGridLayout;
    auto table          = new QLabel("00:00:00:000;");
    auto button_start   = new QPushButton("Start");
    auto button_stop    = new QPushButton("Stop");

    table->setObjectName("table");

    playout->addWidget(table, 0, 0, 1, 2);
    playout->addWidget(button_start, 1, 0);
    playout->addWidget(button_stop, 1, 1);
    playout->setSpacing(0);

    setLayout(playout);

    connect(
        button_start,   SIGNAL(clicked()),
        this,           SLOT(timer_start())
    );

    connect(
        button_stop,    SIGNAL(clicked()),
        this,           SLOT(timer_stop())
    );
    //-------------------------------------------------
}

void This_Class::timer_start() {
    //------------------------
    if (!time_start) {
        time_start  = new QTime;
        *time_start = QTime::currentTime();
    }
    else {
        if (stop_flag) {
            stop_flag   = false;
            *time_start = time_start->addMSecs(
                time_start->msecsTo(QTime::currentTime()) - time_start->msecsTo(*time_stop)
            );
        }
    }
    //------------------------
}

void This_Class::timer_stop() {
    //------------------------
    if (!time_stop) {
        time_stop = new QTime;
    }    

    if (time_start) {

        if (!stop_flag) {
            stop_flag = true;
            *time_stop = QTime::currentTime();            
        }        
        else {
            stop_flag = false;

            delete time_start;
            time_start = nullptr;

            auto& layout = *playout;
            static_cast<QLabel*>(layout["table"])->setText("00:00:00:000;");
        }       
        
    }    
    //------------------------
}