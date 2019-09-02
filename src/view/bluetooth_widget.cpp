// Copyright (c) 2014-2019 winking324
//

#include "view/bluetooth_widget.h"

#include <QDebug>
#include <QVBoxLayout>


namespace auto_pi {


BluetoothWidget::BluetoothWidget(QWidget *parent) : QWidget(parent) {
  agent_ = new BluetoothAgent(this);

  auto *layout = new QVBoxLayout(this);
  bluetooth_list_ = new QListWidget(this);
  scan_button_ = new QPushButton("Scan", this);

  layout->addWidget(bluetooth_list_);
  layout->addWidget(scan_button_);
  setLayout(layout);

  connect(agent_, SIGNAL(DeviceDiscoveredEvent(const QBluetoothDeviceInfo &)),
          this, SLOT(OnDeviceDiscovered(const QBluetoothDeviceInfo &)));
  connect(agent_, SIGNAL(ScanFinishedEvent()), this, SLOT(OnScanFinished()));

  connect(scan_button_, SIGNAL(released()), this, SLOT(OnScan()));

  connect(bluetooth_list_, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(OnItemDoubleClicked(QListWidgetItem*)));
}

void BluetoothWidget::OnScan() {
  scan_button_->setText("Scanning");
  scan_button_->setDisabled(true);
  bluetooth_list_->clear();
  agent_->ScanDevice();
}

void BluetoothWidget::OnScanFinished() {
  scan_button_->setText("Scan");
  scan_button_->setDisabled(false);
}

void BluetoothWidget::OnDeviceDiscovered(const QBluetoothDeviceInfo &info) {
  bluetooth_list_->addItem(info.name());
}

void BluetoothWidget::OnItemDoubleClicked(QListWidgetItem *item) {
  auto addr = agent_->DeviceAddress(item->text());
  qInfo() << "select: " << item->text() << ", address: " << addr;
  emit ItemSelectedEvent(addr);
}


}  // namespace auto_pi
