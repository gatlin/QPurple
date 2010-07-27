#include <QMap>
#include "qpurple.h"
#include "qpurpleionotifier.h"
#include "qpurpletimer.h"

namespace QPurple {

    // unique handle for our input events (QPurpleIONotifiers and QPurpleTimers)
    unsigned int unique_handle = 0;

    QMap< int , QPurpleIONotifier* > notifierMap;
    QMap< int , QPurpleTimer* > timerMap;

    // Event loop functions

    static guint qt_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction function,
                                                               gpointer data)
    {
            PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
            int handle;

            closure->function = function;
            closure->data = data;

            // modified from the nullclient source to integrate with Qt
            handle = unique_handle++; // this will be unique, certainly
            notifierMap[handle] = new QPurpleIONotifier(fd, closure, condition);

            return handle;
    }

    static gboolean qt_input_remove(guint handle) {
            int toReturn = 0;
            QPurpleIONotifier *tmp = notifierMap.take(handle);
            if (!tmp->defaultConstructed) {
                    toReturn = 1;
                    delete tmp; }
            return toReturn;
    }

    static guint qt_timer_add(guint interval, GSourceFunc function, gpointer data) {
            int handle = unique_handle++;
            timerMap[handle] = new QPurpleTimer(function, data, interval);
            return handle;
    }

    static guint qt_timer_add_seconds(guint interval, GSourceFunc function, gpointer data) {
            return qt_timer_add(interval * 1000,function, data);
    }

    static gboolean qt_timer_remove(guint handle) {
            int toReturn = 0;
            QPurpleTimer *tmp = timerMap.take(handle);
            if (!tmp->defaultConstructed) { // we removed something
                    toReturn = 1;
                    delete tmp; }

            return toReturn;
    }

    static PurpleEventLoopUiOps qt_eventloops =
    {
            qt_timer_add,
            qt_timer_remove,
            qt_input_add,
            qt_input_remove,
            NULL,
            qt_timer_add_seconds,

            /* padding */
            NULL,
            NULL,
            NULL
    };

    static void
    qt_write_conv(PurpleConversation *conv, const char *who, const char *alias,
                            const char *message, PurpleMessageFlags flags, time_t mtime)
    {
            printf("(%s) %s %s: %s\n", purple_conversation_get_name(conv),
                            purple_utf8_strftime("(%H:%M:%S)", localtime(&mtime)),
                            who, message);
    }

    static PurpleConversationUiOps null_conv_uiops =
    {
            NULL,           /* create_conversation  */
            NULL,           /* destroy_conversation */
            NULL,           /* write_chat           */
            NULL,           /* write_im             */
            qt_write_conv,  /* write_conv           */
            NULL,           /* chat_add_users       */
            NULL,           /* chat_rename_user     */
            NULL,           /* chat_remove_users    */
            NULL,           /* chat_update_user     */
            NULL,           /* present              */
            NULL,           /* has_focus            */
            NULL,           /* custom_smiley_add    */
            NULL,           /* custom_smiley_write  */
            NULL,           /* custom_smiley_close  */
            NULL,           /* send_confirm         */
            NULL,
            NULL,
            NULL,
            NULL
    };

    static void
    qt_ui_init(void)
    {
            /**
             * This should initialize the UI components for all the modules. Here we
             * just initialize the UI for conversations.
             */
            purple_conversations_set_ui_ops(&null_conv_uiops);
    }

    static PurpleCoreUiOps null_core_uiops =
    {
            NULL,
            NULL,
            qt_ui_init,
            NULL,

            /* padding */
            NULL,
            NULL,
            NULL,
            NULL
    };

    static void
    _init_libpurple(void)
    {
            /* Set a custom user directory (optional) */
            purple_util_set_user_dir(CUSTOM_USER_DIRECTORY);

            /* We do not want any debugging for now to keep the noise to a minimum. */
            purple_debug_set_enabled(FALSE);

            /* Set the core-uiops, which is used to
             * 	- initialize the ui specific preferences.
             * 	- initialize the debug ui.
             * 	- initialize the ui components for all the modules.
             * 	- uninitialize the ui components for all the modules when the core terminates.
             */
            purple_core_set_ui_ops(&null_core_uiops);

            /* Set the uiops for the eventloop. If your client is glib-based, you can safely
             * copy this verbatim. */
            purple_eventloop_set_ui_ops(&qt_eventloops);

            /* Set path to search for plugins. The core (libpurple) takes care of loading the
             * core-plugins, which includes the protocol-plugins. So it is not essential to add
             * any path here, but it might be desired, especially for ui-specific plugins. */
            purple_plugins_add_search_path(CUSTOM_PLUGIN_PATH);

            /* Now that all the essential stuff has been set, let's try to init the core. It's
             * necessary to provide a non-NULL name for the current ui to the core. This name
             * is used by stuff that depends on this ui, for example the ui-specific plugins. */
            if (!purple_core_init(UI_ID)) {
                    /* Initializing the core failed. Terminate. */
                    fprintf(stderr,
                                    "libpurple initialization failed. Dumping core.\n"
                                    "Please report this!\n");
                    abort();
            }

            /* Create and load the buddylist. */
            purple_set_blist(purple_blist_new());
            purple_blist_load();

            /* Load the preferences. */
            purple_prefs_load();

            /* Load the desired plugins. The client should save the list of loaded plugins in
             * the preferences using purple_plugins_save_loaded(PLUGIN_SAVE_PREF) */
            purple_plugins_load_saved(PLUGIN_SAVE_PREF);

            /* Load the pounces. */
            //purple_pounces_load();
    }
}

void qpurple_init() {
    QPurple::_init_libpurple();
}
