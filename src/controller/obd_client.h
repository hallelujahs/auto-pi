// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QObject>
#include <QBluetoothSocket>
#include <QBluetoothDeviceInfo>
#include <QBluetoothLocalDevice>
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
  // signals from |BluetoothWidget|
  void OnDeviceSelected(const QBluetoothDeviceInfo &info);

  void OnServiceSelected(const QBluetoothServiceInfo &info);

  // signals from |QBluetoothLocalDevice|
  void	OnDeviceConnected(const QBluetoothAddress &address);

  void	OnDeviceDisconnected(const QBluetoothAddress &address);

  void	OnLocalDeviceError(QBluetoothLocalDevice::Error error);

  void	OnHostModeStateChanged(QBluetoothLocalDevice::HostMode state);

  void	OnPairingDisplayConfirmation(const QBluetoothAddress &address,
                                     QString pin);

  void	OnPairingDisplayPinCode(const QBluetoothAddress &address, QString pin);

  void	OnPairingFinished(const QBluetoothAddress &address,
                          QBluetoothLocalDevice::Pairing pairing);

  // signals from |QBluetoothSocket|
  void OnConnected();

  void OnDisconnected();

  void OnLocalDeviceError(QBluetoothSocket::SocketError error);

  void OnStateChanged(QBluetoothSocket::SocketState state);

  void OnReadyRead();

 private:
  bool is_connected_;

  QBluetoothDeviceInfo device_info_;
  QBluetoothSocket *connection_;
  QBluetoothLocalDevice *local_device_;
};


}  // namespace auto_pi
