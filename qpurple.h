#ifndef QPURPLE_H
#define QPURPLE_H

#include <QObject>

#include <QSocketNotifier>
#include <QTimer>

#include <glib.h>
#include "purple.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>

#define CUSTOM_USER_DIRECTORY  "/dev/null"
#define CUSTOM_PLUGIN_PATH     ""
#define PLUGIN_SAVE_PREF       "/purple/nullclient/plugins/saved"
#define UI_ID                  "hermes"

#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)

namespace QPurple {

    typedef struct _PurpleGLibIOClosure {
            PurpleInputFunction function;
            guint result;
            gpointer data;
    } PurpleGLibIOClosure;
}

void qpurple_init(); // call this in main to start libpurple

#endif
