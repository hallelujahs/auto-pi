// Copyright (c) 2014-2019 winking324
//


#include "controller/bluetooth_agent.h"
#include <QTime>
#include <QDebug>
#include <QSettings>
#include <QBluetoothUuid>


namespace auto_pi {


BluetoothAgent::BluetoothAgent(QObject *parent) : QObject(parent) {
  discovery_agent_ = new QBluetoothDeviceDiscoveryAgent(this);
  discovery_agent_->setLowEnergyDiscoveryTimeout(5000);
}

void BluetoothAgent::ScanDevice() {
  connect(discovery_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &BluetoothAgent::DeviceDiscoveredEvent);
  connect(discovery_agent_, SIGNAL(finished()), this, SLOT(OnScanFinished()));

  discovery_agent_->start();
  qInfo() << QTime::currentTime().toString("hh:mm:ss.zzz");
}

QString BluetoothAgent::DeviceAddress(const QString &name) {
  for (const auto &dev : devices_) {
    if (dev.name() == name) {
      return dev.address().toString();
    }
  }

  return "";
}

void BluetoothAgent::OnScanFinished() {
  devices_ = discovery_agent_->discoveredDevices();
  qInfo() << "scan finished: " + QTime::currentTime().toString("hh:mm:ss.zzz");
  emit ScanFinishedEvent();
}

void BluetoothAgent::ScanHistoricalDevices() {
  QSettings settings;
  auto device_count = settings.beginReadArray("historical_bluetooth_devices");
  for (auto i = 0; i < device_count; ++i) {
    settings.setArrayIndex(i);
    historical_devices_.insert(settings.value("address").toString(),
                               settings.value("name").toString());
  }
  settings.endArray();
}



}  // namespace auto_pi
