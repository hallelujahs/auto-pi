// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QListWidget>
#include "controller/bluetooth_agent.h"


namespace auto_pi {


class BluetoothWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BluetoothWidget(QWidget *parent = nullptr);

 signals:

 public slots:
  void OnDeviceDiscovered(const QBluetoothDeviceInfo &info);

 private:
  BluetoothAgent *agent_;

  QListWidget *bluetooth_list_;
};


}  // namespace auto_pi
