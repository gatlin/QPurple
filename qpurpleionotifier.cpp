#include "qpurple.h"
#include "qpurpleionotifier.h"

namespace QPurple {
    QPurpleIONotifier::QPurpleIONotifier()
            :  defaultConstructed(1) {
    }

    QPurpleIONotifier::QPurpleIONotifier (int fd, PurpleGLibIOClosure *c, PurpleInputCondition pic)
            : closure(c), purpleInputCondition(pic), defaultConstructed(0) {

            //if (pic & PURPLE_GLIB_WRITE_COND) {
            if (pic & PURPLE_INPUT_WRITE) {
                    this->writeCond = new QSocketNotifier(fd, QSocketNotifier::Write);
                    QObject::connect(this->writeCond, SIGNAL(activated(int)), this, SLOT(callFunc(int)));
            } else {
                    this->writeCond = NULL; }

            if (pic & PURPLE_INPUT_READ) {
                    this->readCond = new QSocketNotifier(fd, QSocketNotifier::Read);
                    QObject::connect(this->readCond, SIGNAL(activated(int)), this, SLOT(callFunc(int)));
            } else {
                    this->readCond = NULL; }
    }

    QPurpleIONotifier::~QPurpleIONotifier() {
            if (this->readCond != NULL) {
                this->readCond->setEnabled(false);
                delete this->readCond; }
            if (this->writeCond != NULL) {
                this->writeCond->setEnabled(false);
                delete this->writeCond; }
    }

    // analogous to purple_glib_io_invoke from nullclient
    void QPurpleIONotifier::callFunc(int fd) {
            closure->function(closure->data, fd,
                              this->purpleInputCondition);
    }
}
