// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QMap>
#include <QList>
#include <QString>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>


namespace auto_pi {


class BluetoothAgent : public QObject {
  Q_OBJECT

 public:
  explicit BluetoothAgent(QObject *parent = nullptr);

  void ScanDevice();

  QString DeviceAddress(const QString &name);

 public slots:
  void OnScanFinished();

 signals:
  void DeviceDiscoveredEvent(const QBluetoothDeviceInfo &info);

  void ScanFinishedEvent();

 private:
  void ScanHistoricalDevices();

 private:
  QBluetoothDeviceDiscoveryAgent *discovery_agent_;
  QList<QBluetoothDeviceInfo> devices_;
  QMap<QString, QString> historical_devices_;
};


}  // namespace auto_pi
