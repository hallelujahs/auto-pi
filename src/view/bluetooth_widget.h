// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QList>
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QTableWidget>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceDiscoveryAgent>


namespace auto_pi {


class BluetoothWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BluetoothWidget(QWidget *parent = nullptr);

 signals:
  void ItemSelectedEvent();

  void DeviceSelectedEvent(const QBluetoothDeviceInfo &info);

  void ServiceSelectedEvent(const QBluetoothServiceInfo &info);

 public slots:
  void OnScan();

  void OnDeviceScanFinished();

  void OnServiceScanFinished();

  void OnDeviceDiscovered(const QBluetoothDeviceInfo &info);

  void OnServiceDiscovered(const QBluetoothServiceInfo &info);

  void OnItemDoubleClicked(QTableWidgetItem *item);

 private:
  void ClearDeviceList();

  void AddDeviceInfo(const QString &type, const QBluetoothDeviceInfo &info);

 private:
  QCheckBox *scan_device_;
  QCheckBox *scan_service_;

  QPushButton *scan_button_;
  QTableWidget *bluetooth_list_;

  QBluetoothDeviceDiscoveryAgent *device_agent_;
  QBluetoothServiceDiscoveryAgent *service_agent_;

  QList<QBluetoothDeviceInfo> devices_;
  QList<QBluetoothServiceInfo> services_;
};


}  // namespace auto_pi
