// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QMap>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QTableWidget>
#include "controller/bluetooth_discovery_agent.h"


namespace auto_pi {


class BluetoothWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BluetoothWidget(QWidget *parent = nullptr);

 signals:
  void ItemSelectedEvent();

  void DeviceSelectedEvent(const QString &addr, const QString &name);

 public slots:
  void OnScan();

  void OnDiscoveryFinished();

  void OnDiscoveryError(BluetoothDiscoveryError code);

  void OnDeviceDiscovered(QString addr, QString name);

  void OnItemDoubleClicked(QTableWidgetItem *item);

 private:
  void ClearDeviceList();

  void AddDeviceInfo(QString addr, QString name);

 private:
  QPushButton *scan_button_;
  QTableWidget *bluetooth_list_;

  BluetoothDiscoveryAgent *discovery_agent_;
  QMap<QString, QString> devices_;
};


}  // namespace auto_pi
