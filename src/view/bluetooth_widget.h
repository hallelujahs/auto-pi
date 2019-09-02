// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include "controller/bluetooth_agent.h"


namespace auto_pi {


class BluetoothWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BluetoothWidget(QWidget *parent = nullptr);

 signals:
  void ItemSelectedEvent(QString addr);

 public slots:
  void OnScan();

  void OnScanFinished();

  void OnDeviceDiscovered(const QBluetoothDeviceInfo &info);

  void OnItemDoubleClicked(QListWidgetItem *item);

 private:
  BluetoothAgent *agent_;
  QPushButton *scan_button_;
  QListWidget *bluetooth_list_;
};


}  // namespace auto_pi
