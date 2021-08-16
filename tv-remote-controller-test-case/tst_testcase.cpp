#include <QtTest>
#include "messagehandlertestcase.h"
#include "settingshandlertestcase.h"
#include "devicemodeltestcase.h"

#include <QtQuickTest>
//QUICK_TEST_MAIN(example)

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

   {
       DeviceModelTestCase tc;
       status |= QTest::qExec(&tc, argc, argv);
   }


   return status;
}
