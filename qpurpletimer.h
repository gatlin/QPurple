#ifndef QPURPLETIMER_H
#define QPURPLETIMER_H

#include "qpurple.h"

namespace QPurple {

    class QPurpleTimer : QObject {
            Q_OBJECT // required by Qt

            GSourceFunc func;
            gpointer data;
            QTimer *timer;
    public:
            QPurpleTimer();
            QPurpleTimer(GSourceFunc f, gpointer d, int i);
            ~QPurpleTimer();
            int defaultConstructed;

    public slots:
            void callFunc();
    };
}

#endif // QPURPLETIMER_H
