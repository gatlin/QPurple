#include <QtCore/QCoreApplication>
#include "../qpurple/qpurple.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qpurple_init();
    char* res = 0;
    PurpleAccount *theAccount, *anotherAccount;

     /* Create the account */
     theAccount = purple_account_new("nebobot@jabber.org", "prpl-jabber");

     /* Get the password for the account */
     //password = getpass("Password: ");
     purple_account_set_password(theAccount, "stoner");

     /* It's necessary to enable the account first. */
     purple_account_set_enabled(theAccount, UI_ID, TRUE);

     anotherAccount = purple_account_new("redhed2k3","prpl-aim");
     purple_account_set_password(anotherAccount,"stoner");
     purple_account_set_enabled(anotherAccount, UI_ID, TRUE);

    return a.exec();
}
