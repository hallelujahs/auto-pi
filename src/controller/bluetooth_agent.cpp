// Copyright (c) 2014-2019 winking324
//


#include "controller/bluetooth_agent.h"
#include <QTime>
#include <QDebug>
#include <QBluetoothUuid>


namespace auto_pi {


BluetoothAgent::BluetoothAgent(QObject *parent) : QObject(parent) {
  discovery_agent_ = new QBluetoothDeviceDiscoveryAgent(this);
}

void BluetoothAgent::ScanDevice() {
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &BluetoothAgent::DeviceDiscoveredEvent);
  connect(discovery_agent_, SIGNAL(finished()), this, SLOT(OnScanFinished()));

  discovery_agent_->start();
  qInfo() << QTime::currentTime().toString("hh:mm:ss.zzz");
}

void BluetoothAgent::OnScanFinished() {
  discovery_agent_->stop();
//  auto devices = discovery_agent_->discoveredDevices();
  qInfo() << "scan finished: " << QTime::currentTime().toString("hh:mm:ss.zzz");
//          << ", size: " << devices.size();
//  for (const auto &dev : devices) {
//    if (dev.isValid())
//      qInfo() << dev.name() << " " << dev.address().toString() << " " << dev.deviceUuid().toUInt32() << " " << dev.rssi();
//  }
}



}  // namespace auto_pi
