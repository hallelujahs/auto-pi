// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceInfo>


namespace auto_pi {


class OBDClient : public QObject {
  Q_OBJECT
 public:
  explicit OBDClient(QObject *parent = nullptr);

  bool IsSetted();

  bool IsConnected();

 signals:

 public slots:
  void OnDeviceSelected(const QBluetoothDeviceInfo &info);

  void OnServiceSelected(const QBluetoothServiceInfo &info);

 private:
  QBluetoothSocket *obd_connection_;
};


}  // namespace auto_pi
