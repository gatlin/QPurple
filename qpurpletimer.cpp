#include "qpurple.h"
#include "qpurpletimer.h"

namespace QPurple {

    QPurpleTimer::QPurpleTimer()
        : func(NULL), data(NULL), defaultConstructed(1) {

    }

    QPurpleTimer::QPurpleTimer(GSourceFunc f, gpointer d, int i)
            : func(f), data(d), defaultConstructed(0) {
            this->timer = new QTimer();
            this->timer->setInterval(i);
            connect(this->timer, SIGNAL(timeout()),this, SLOT(callFunc()));
            this->timer->start(i);
    }

    QPurpleTimer::~QPurpleTimer() {
            this->timer->stop();
            delete this->timer;
    }

    void QPurpleTimer::callFunc() {
            gboolean res = this->func(this->data);
            if (!res)
                    this->timer->stop();
    }

}
