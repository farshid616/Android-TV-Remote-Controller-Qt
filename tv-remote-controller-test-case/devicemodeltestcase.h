#ifndef DEVICEMODELTESTCASE_H
#define DEVICEMODELTESTCASE_H

#include <QObject>

class DeviceModelTestCase: public QObject
{
    Q_OBJECT

public:
    DeviceModelTestCase();
private slots:
    void DeviceModelCreationTest();
    void DeviceModelRoleDataReturnTest();
};

#endif // DEVICEMODELTESTCASE_H
