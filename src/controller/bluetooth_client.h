// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QThread>


namespace auto_pi {


class BluetoothClient : public QThread {
  Q_OBJECT

 public:
  explicit BluetoothClient(QObject *parent = nullptr);

 signals:

 public slots:

 private:
  void run() override;

};


}  // namespace auto_pi
