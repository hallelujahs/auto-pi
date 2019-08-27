// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QBluetoothDeviceDiscoveryAgent>


namespace auto_pi {


class BluetoothAgent : public QObject {
  Q_OBJECT

 public:
  explicit BluetoothAgent(QObject *parent = nullptr);

  void ScanDevice();

 public slots:
  void OnScanFinished();

 signals:
  void DeviceDiscoveredEvent(const QBluetoothDeviceInfo &info);

 private:
  QBluetoothDeviceDiscoveryAgent *discovery_agent_;
};


}  // namespace auto_pi
