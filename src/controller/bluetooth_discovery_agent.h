// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <QThread>


namespace auto_pi {


enum class BluetoothDiscoveryError {
  kOk = 0,
  kErrorOpenSocket = 1,
  kErrorDiscovery = 2,
};


class BluetoothDiscoveryAgent : public QThread {
  Q_OBJECT
 public:
  explicit BluetoothDiscoveryAgent(QObject *parent = nullptr);

  ~BluetoothDiscoveryAgent();

 signals:
  void DeviceDiscoveredEvent(QString addr, QString name);

  void ErrorEvent(BluetoothDiscoveryError code);

 private:
  void run() override;

 private:
  inquiry_info *devices_;
};


}  // namespace auto_pi
