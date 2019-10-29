// Copyright (c) 2014-2019 winking324
//


#include "controller/obd_client.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <QDebug>
#include <QLowEnergyConnectionParameters>

#include "commons/singleton.h"
#include "controller/global_config.h"


namespace auto_pi {


OBDClient::OBDClient(QObject *parent) : QObject(parent) {
  local_device_ = new QBluetoothLocalDevice(this);
  connection_ = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  is_connected_ = false;

  connect(local_device_, SIGNAL(error(QBluetoothLocalDevice::Error)),
          this, SLOT(OnLocalDeviceError(QBluetoothLocalDevice::Error)));
  connect(local_device_, &QBluetoothLocalDevice::deviceConnected,
          this, &OBDClient::OnDeviceConnected);
  connect(local_device_, &QBluetoothLocalDevice::deviceDisconnected,
          this, &OBDClient::OnDeviceDisconnected);
  connect(local_device_, &QBluetoothLocalDevice::hostModeStateChanged,
          this, &OBDClient::OnHostModeStateChanged);
  connect(local_device_, &QBluetoothLocalDevice::pairingDisplayConfirmation,
          this, &OBDClient::OnPairingDisplayConfirmation);
  connect(local_device_, &QBluetoothLocalDevice::pairingDisplayPinCode,
          this, &OBDClient::OnPairingDisplayPinCode);
  connect(local_device_, &QBluetoothLocalDevice::pairingFinished,
          this, &OBDClient::OnPairingFinished);

  connect(connection_, SIGNAL(error(QBluetoothSocket::SocketError)),
          this, SLOT(OnLocalDeviceError(QBluetoothSocket::SocketError)));
  connect(connection_, &QBluetoothSocket::connected,
          this, &OBDClient::OnConnected);
  connect(connection_, &QBluetoothSocket::disconnected,
          this, &OBDClient::OnDisconnected);
  connect(connection_, &QBluetoothSocket::stateChanged,
          this, &OBDClient::OnStateChanged);
  connect(connection_, &QBluetoothSocket::readyRead,
          this, &OBDClient::OnReadyRead);
}

bool OBDClient::IsSetted() {
  return !Singleton<GlobalConfig>::Instance()->obd_device_address.isEmpty();
}

bool OBDClient::IsConnected() {
  return is_connected_;
}

void OBDClient::OnDeviceSelected(const QBluetoothDeviceInfo &info) {
  Singleton<GlobalConfig>::Instance()->obd_device_address =
      info.address().toString();
  qInfo() << "on device selected: " << info.address().toString();

  static const QBluetoothUuid kUuid(
        QString("00001101-0000-1000-8000-00805F9B34FB"));
  connection_->connectToService(info.address(), kUuid);

  struct sockaddr_rc addr = { 0 };
  int s, status;
  char *dest = info.address().toString().toLocal8Bit().data();

  // allocate a socket
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( dest, &addr.rc_bdaddr );

  // connect to server
  status = ::connect(s, (struct sockaddr *)&addr, sizeof(addr));

  // send a message
  if( status == 0 ) {
    qInfo() << "connect and send message";
    status = write(s, "hello!", 6);
  }

  if ( status < 0 ) {
    qInfo() << "connect or write failed: " << status;
  }

  close(s);
}

void OBDClient::OnServiceSelected(const QBluetoothServiceInfo &info) {
  Singleton<GlobalConfig>::Instance()->obd_device_address =
      info.device().address().toString();
  qInfo() << "on service selected: " << info.device().address().toString();
}

void OBDClient::OnDeviceConnected(const QBluetoothAddress &address) {
  qInfo() << "obd client local device on connected: " << address.toString();
  qInfo() << "obd client local device status: " << connection_->state();
}

void OBDClient::OnDeviceDisconnected(const QBluetoothAddress &address) {
  qInfo() << "obd client local device on disconnected: " << address.toString();
}

void OBDClient::OnLocalDeviceError(QBluetoothLocalDevice::Error error) {
  qInfo() << "obd client local device on error: " << error;
}

void OBDClient::OnHostModeStateChanged(QBluetoothLocalDevice::HostMode state) {
  qInfo() << "obd client local device host mode state changed: " << state;
}

void OBDClient::OnPairingDisplayConfirmation(const QBluetoothAddress &address,
                                             QString pin) {
  qInfo() << "obd client local device paring display confirmation: "
          << address.toString() << ", pin: " << pin;
  local_device_->pairingConfirmation(true);
}

void OBDClient::OnPairingDisplayPinCode(const QBluetoothAddress &address,
                                        QString pin) {
  qInfo() << "obd client local device paring display pincode: "
          << address.toString() << ", pin: " << pin;
}

void OBDClient::OnPairingFinished(const QBluetoothAddress &address,
                                  QBluetoothLocalDevice::Pairing pairing) {
  qInfo() << "obd client local device paring finished: "
          << address.toString() << ", pin: " << pairing;
}

void OBDClient::OnConnected() {
  qInfo() << "obd client connected";
  is_connected_ = true;
}

void OBDClient::OnDisconnected() {
  qInfo() << "obd client disconnected";
  is_connected_ = false;
}

void OBDClient::OnLocalDeviceError(QBluetoothSocket::SocketError error) {
  qInfo() << "obd client error: " << error;
}

void OBDClient::OnStateChanged(QBluetoothSocket::SocketState state) {
  qInfo() << "obd client state changed: " << state;
}

void OBDClient::OnReadyRead() {
  qInfo() << "obd client ready read";
  QByteArray buf = connection_->readAll();
  qInfo() << "obd client read: " << buf.toHex(':');
}


}  // namespace auto_pi
