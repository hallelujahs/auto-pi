// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QObject>
#include "controller/bluetooth_client.h"


namespace auto_pi {


class OBDClient : public QObject {
  Q_OBJECT
 public:
  explicit OBDClient(QObject *parent = nullptr);

  bool IsSetted();

  bool IsConnected();

 signals:

 public slots:
  // signals from |BluetoothWidget|
  void OnDeviceSelected(const QString &addr, const QString &name);

 private:
  bool is_connected_;
};


}  // namespace auto_pi
