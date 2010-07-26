#ifndef QPURPLEIONOTIFIER_H
#define QPURPLEIONOTIFIER_H

#include "qpurple.h"

namespace QPurple {

    class QPurpleIONotifier : QObject {
            Q_OBJECT // required by Qt

            QSocketNotifier *readCond, *writeCond;
            PurpleGLibIOClosure *closure;
            PurpleInputCondition purpleInputCondition;
    public:
            QPurpleIONotifier();
            QPurpleIONotifier(int fd, PurpleGLibIOClosure *c, PurpleInputCondition pic);
            ~QPurpleIONotifier();
            int defaultConstructed;

    public slots:
            void callFunc(int fd);
    };
}

#endif // QPURPLEIONOTIFIER_H
