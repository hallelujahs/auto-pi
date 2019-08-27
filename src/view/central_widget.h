// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QStackedLayout>

#include "view/bluetooth_widget.h"


namespace auto_pi {


class CentralWidget : public QWidget {
  Q_OBJECT
 public:
  explicit CentralWidget(QWidget *parent = nullptr);

 signals:

 public slots:

 private:
  BluetoothWidget *bluetooth_widget_;

  QStackedLayout *layout_;
};


}  // namespace auto_pi

