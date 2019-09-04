// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QString>
#include <QStackedLayout>

#include "view/config_widget.h"
#include "view/display_widget.h"
#include "view/bluetooth_widget.h"


namespace auto_pi {


class CentralWidget : public QWidget {
  Q_OBJECT
 public:
  explicit CentralWidget(QWidget *parent = nullptr);

 signals:

 public slots:
  void OnConfig();

  void OnConfigOBD();

  void OnConfigOk();

  void OnBluetooth();

 private:
  ConfigWidget *config_widget_;
  DisplayWidget *display_widget_;
  BluetoothWidget *bluetooth_widget_;

  QStackedLayout *layout_;
};


}  // namespace auto_pi

