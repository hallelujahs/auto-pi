// Copyright (c) 2014-2019 winking324
//


#include "controller/obd_client.h"

#include "commons/singleton.h"
#include "controller/global_config.h"


namespace auto_pi {


OBDClient::OBDClient(QObject *parent) : QObject(parent) {
}

bool OBDClient::IsSetted() {
  return !Singleton<GlobalConfig>::Instance()->obd_device_address.isEmpty();
}

bool OBDClient::IsConnected() {
  return obd_connection_->isOpen();
}


}  // namespace auto_pi
