// Copyright (c) 2014-2019 winking324
//


#include "controller/obd_client.h"

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <QDebug>

#include "commons/singleton.h"
#include "controller/global_config.h"


namespace auto_pi {


OBDClient::OBDClient(QObject *parent) : QObject(parent) {
  is_connected_ = false;
}

bool OBDClient::IsSetted() {
  return !Singleton<GlobalConfig>::Instance()->obd_device_address.isEmpty();
}

bool OBDClient::IsConnected() {
  return is_connected_;
}

void OBDClient::OnDeviceSelected(const QString &addr, const QString &name) {
}

}  // namespace auto_pi
