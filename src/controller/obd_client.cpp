// Copyright (c) 2014-2019 winking324
//


#include "controller/obd_client.h"
#include <QDebug>
#include "commons/singleton.h"
#include "controller/global_config.h"


namespace auto_pi {


OBDClient::OBDClient(QObject *parent) : QObject(parent) {
  obd_connection_ = new QBluetoothSocket(this);
}

bool OBDClient::IsSetted() {
  return !Singleton<GlobalConfig>::Instance()->obd_device_address.isEmpty();
}

bool OBDClient::IsConnected() {
  return obd_connection_->isOpen();
}

void OBDClient::OnDeviceSelected(const QBluetoothDeviceInfo &info) {
  Singleton<GlobalConfig>::Instance()->obd_device_address =
      info.address().toString();
  qInfo() << "on device selected: " << info.address().toString();
}

void OBDClient::OnServiceSelected(const QBluetoothServiceInfo &info) {
  Singleton<GlobalConfig>::Instance()->obd_device_address =
      info.device().address().toString();
  qInfo() << "on service selected: " << info.device().address().toString();
}


}  // namespace auto_pi
