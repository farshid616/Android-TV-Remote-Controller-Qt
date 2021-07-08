#include <QtTest>

#include "messagehandlertestcase.h"
#include "settingshandlertestcase.h"

int main(int argc, char *argv[])
{
   int status = 0;

   {
       MessageHandlerTestCase ta;
       status |= QTest::qExec(&ta, argc, argv);
   }

   {
       SettingsHandlerTestCase tb;
       status |= QTest::qExec(&tb, argc, argv);
   }

   return status;
}
