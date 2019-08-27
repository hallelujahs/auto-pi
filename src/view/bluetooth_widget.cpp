// Copyright (c) 2014-2019 winking324
//

#include "view/bluetooth_widget.h"

#include <QVBoxLayout>


namespace auto_pi {


BluetoothWidget::BluetoothWidget(QWidget *parent) : QWidget(parent) {
  agent_ = new BluetoothAgent(this);

  auto *layout = new QVBoxLayout(this);
  bluetooth_list_ = new QListWidget(this);

  layout->addWidget(bluetooth_list_);
  setLayout(layout);

  connect(agent_, SIGNAL(DeviceDiscoveredEvent(const QBluetoothDeviceInfo &)),
          this, SLOT(OnDeviceDiscovered(const QBluetoothDeviceInfo &)));

  agent_->ScanDevice();
}

void BluetoothWidget::OnDeviceDiscovered(const QBluetoothDeviceInfo &info) {
  bluetooth_list_->addItem(info.name() + "-" + info.address().toString());
}


}  // namespace auto_pi
