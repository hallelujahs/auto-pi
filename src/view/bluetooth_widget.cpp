// Copyright (c) 2014-2019 winking324
//

#include "view/bluetooth_widget.h"


namespace auto_pi {


BluetoothWidget::BluetoothWidget(QWidget *parent) : QWidget(parent) {
  agent_ = new BluetoothAgent(this);

  bluetooth_list_ = new QListWidget(this);

  connect(agent_, SIGNAL(DeviceDiscoveredEvent(const QBluetoothDeviceInfo &)),
          this, SLOT(OnDeviceDiscovered(const QBluetoothDeviceInfo &)));

  agent_->ScanDevice();
}

void BluetoothWidget::OnDeviceDiscovered(const QBluetoothDeviceInfo &info) {
  bluetooth_list_->addItem(info.name() + "-" + info.address().toString());
}


}  // namespace auto_pi
