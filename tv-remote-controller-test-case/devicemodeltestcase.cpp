#include "devicemodeltestcase.h"

#include <QtTest>
#include "devicemodel.h"

DeviceModelTestCase::DeviceModelTestCase()
{

}

void DeviceModelTestCase::DeviceModelCreationTest()
{
    DeviceInfo device_info{0, "test_device", "1.1.1.1"};
    DeviceModel device_model;
    QVERIFY(device_model.rowCount() == 0);
    device_model.addDevice(device_info);
    QVERIFY(device_model.rowCount() == 1);
}

void DeviceModelTestCase::DeviceModelRoleDataReturnTest()
{
    DeviceInfo device_info{0, "test_device", "1.1.1.1"};
    DeviceModel device_model;
    device_model.addDevice(device_info);
    QVERIFY(device_model.data(device_model.index(0), DeviceModel::NameRole) == "test_device");
    QVERIFY(device_model.data(device_model.index(0), DeviceModel::IpRole) == "1.1.1.1");
    QVERIFY(device_model.data(device_model.index(0), DeviceModel::IndexRole) == 0);
}


