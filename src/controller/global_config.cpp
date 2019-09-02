// Copyright (c) 2014-2019 winking324
//


#include "controller/global_config.h"
#include <QSettings>


namespace auto_pi {


void GlobalConfig::LoadConfig() {
  QSettings settings;
  settings.beginGroup("bluetooth");
  obd_device_address = settings.value("obd").toString();
  settings.endGroup();
}

void GlobalConfig::SaveConfig() {
  QSettings settings;
  settings.beginGroup("bluetooth");
  settings.setValue("obd", obd_device_address);
  settings.endGroup();
}


}  // namespace auto_pi
