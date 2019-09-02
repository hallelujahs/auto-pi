// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QString>


namespace auto_pi {


struct GlobalConfig {
  void LoadConfig();

  void SaveConfig();

  QString obd_device_address;
};


}  // namespace auto_pi
