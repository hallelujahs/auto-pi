// Copyright (c) 2014-2019 winking324
//

#include "view/bluetooth_widget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>


namespace auto_pi {


enum class BluetoothTableColumn {
  kType = 0,
  kRssi = 1,
  kName = 2,
  kAddress = 3
};


BluetoothWidget::BluetoothWidget(QWidget *parent) : QWidget(parent) {
  device_agent_ = new QBluetoothDeviceDiscoveryAgent(this);
  device_agent_->setLowEnergyDiscoveryTimeout(5000);
  service_agent_ = new QBluetoothServiceDiscoveryAgent(this);

  discovery_agent_ = new BluetoothDiscoveryAgent(this);

  auto *layout = new QVBoxLayout(this);
  auto *check_box_layout = new QHBoxLayout(this);

  scan_device_ = new QCheckBox("Device", this);
  scan_service_ = new QCheckBox("Service", this);

  bluetooth_list_ = new QTableWidget(this);
  scan_button_ = new QPushButton("Scan", this);

  bluetooth_list_->setColumnCount(4);
  bluetooth_list_->setHorizontalHeaderLabels(
        QStringList{"T", "RSSI", "NAME", "ADDRESS"});

  bluetooth_list_->horizontalHeader()->setHighlightSections(false);
  bluetooth_list_->horizontalHeader()->setSectionResizeMode(
        static_cast<int>(BluetoothTableColumn::kType),
        QHeaderView::ResizeToContents);
  bluetooth_list_->horizontalHeader()->setSectionResizeMode(
        static_cast<int>(BluetoothTableColumn::kRssi),
        QHeaderView::ResizeToContents);

  bluetooth_list_->setSelectionBehavior(QAbstractItemView::SelectRows);
  bluetooth_list_->setSelectionMode(QAbstractItemView::SingleSelection);

  layout->addWidget(bluetooth_list_);

  check_box_layout->addWidget(scan_service_);
  check_box_layout->addWidget(scan_device_);
  scan_service_->setChecked(false);
  scan_device_->setChecked(true);

  layout->addLayout(check_box_layout);
  layout->addWidget(scan_button_);
  setLayout(layout);

  connect(scan_button_, SIGNAL(released()), this, SLOT(OnScan()));

  connect(bluetooth_list_, &QTableWidget::itemDoubleClicked,
          this, &BluetoothWidget::OnItemDoubleClicked);

  connect(device_agent_, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &BluetoothWidget::OnDeviceDiscovered);
  connect(device_agent_, &QBluetoothDeviceDiscoveryAgent::finished,
          this, &BluetoothWidget::OnDeviceScanFinished);

  connect(service_agent_, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
          this, &BluetoothWidget::OnServiceDiscovered);
  connect(service_agent_, &QBluetoothServiceDiscoveryAgent::finished,
          this, &BluetoothWidget::OnServiceScanFinished);

  connect(discovery_agent_, &BluetoothDiscoveryAgent::ErrorEvent,
          this, &BluetoothWidget::OnDiscoveryError);
  connect(discovery_agent_, &BluetoothDiscoveryAgent::DeviceDiscoveredEvent,
          this, &BluetoothWidget::OnDeviceDiscovered2);
  connect(discovery_agent_, &QThread::finished, this,
          &BluetoothWidget::OnDeviceScanFinished);
}

void BluetoothWidget::OnScan() {
  if (!scan_service_->isChecked() && !scan_device_->isChecked()) {
    return;
  }

  scan_button_->setText("Scanning");
  scan_button_->setDisabled(true);
  scan_service_->setDisabled(true);
  scan_device_->setDisabled(true);

  ClearDeviceList();

  discovery_agent_->start();

//  if (scan_service_->isChecked()) {
//    qInfo() << "start bluetooth service scaning";
//    service_agent_->start();
//  } else {
//    qInfo() << "start bluetooth device scaning";
//    device_agent_->start();
//  }
}

void BluetoothWidget::OnDeviceScanFinished() {
  //devices_ = device_agent_->discoveredDevices();
  //qInfo() << "end bluetooth scaning, sacn device count: " << devices_.size();

  scan_button_->setText("Scan");
  scan_button_->setDisabled(false);
  scan_service_->setDisabled(false);
  scan_device_->setDisabled(false);
}

void BluetoothWidget::OnServiceScanFinished() {
  services_ = service_agent_->discoveredServices();
  qInfo() << "end bluetooth scaning, sacn service count: " << services_.size();

  if (scan_device_->isChecked()) {
    qInfo() << "start bluetooth device scaning";
    device_agent_->start();
  } else {
    scan_button_->setText("Scan");
    scan_button_->setDisabled(false);
    scan_service_->setDisabled(false);
    scan_device_->setDisabled(false);
  }
}

void BluetoothWidget::OnDeviceDiscovered(const QBluetoothDeviceInfo &info) {
  static const QString kServiceType = "D";
//  AddDeviceInfo(kServiceType, info);
}

void BluetoothWidget::OnServiceDiscovered(const QBluetoothServiceInfo &info) {
  static const QString kServiceType = "S";
//  AddDeviceInfo(kServiceType, info.device());
}

void BluetoothWidget::OnDiscoveryError(BluetoothDiscoveryError code) {
  (void)code;
}

void BluetoothWidget::OnDeviceDiscovered2(QString addr, QString name) {
  AddDeviceInfo(std::move(addr), std::move(name));
}

void BluetoothWidget::OnItemDoubleClicked(QTableWidgetItem *item) {
  int selected_row = item->row();
  auto *type_item = bluetooth_list_->item(
        selected_row, static_cast<int>(BluetoothTableColumn::kType));
  auto *addr_item = bluetooth_list_->item(
        selected_row, static_cast<int>(BluetoothTableColumn::kAddress));

  if (type_item->text() == "S") {
    for (const auto &service : services_) {
      auto device = service.device();
      if (device.address().toString() == addr_item->text()) {
        emit ServiceSelectedEvent(service);
        break;
      }
    }
  } else {
    for (const auto &device : devices_) {
      if (device.address().toString() == addr_item->text()) {
        emit DeviceSelectedEvent(device);
        break;
      }
    }
  }
  emit ItemSelectedEvent();
}

void BluetoothWidget::ClearDeviceList() {
  while (bluetooth_list_->rowCount() > 0) {
    bluetooth_list_->removeRow(0);
  }
}

void BluetoothWidget::AddDeviceInfo(const QString &type,
                                    const QBluetoothDeviceInfo &info) {
  if (info.address().toString() == "") {
    qWarning() << "scan device address empty";
    return;
  }

  auto find_items =
      bluetooth_list_->findItems(info.address().toString(), Qt::MatchContains);
  if (!find_items.empty()) {
    qInfo() << "scan device: " << info.address() << " already in list, ignore";
    return;
  }

  auto last_row = bluetooth_list_->rowCount();
  bluetooth_list_->insertRow(last_row);

  auto *type_item = new QTableWidgetItem(type);
  auto *rssi_item = new QTableWidgetItem(QString::number(info.rssi()));
  auto *name_item = new QTableWidgetItem(info.name());
  auto *addr_item = new QTableWidgetItem(info.address().toString());
  type_item->setFlags(type_item->flags() & ~Qt::ItemIsEditable);
  rssi_item->setFlags(rssi_item->flags() & ~Qt::ItemIsEditable);
  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  addr_item->setFlags(addr_item->flags() & ~Qt::ItemIsEditable);

  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kType), type_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kRssi), rssi_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kName), name_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kAddress), addr_item);

  auto service_uuids = info.serviceUuids();
  QString service_uuids_str;
  if (!service_uuids.isEmpty()) {
    service_uuids_str = service_uuids.begin()->toString();
    std::accumulate(std::next(service_uuids.begin()), service_uuids.end(),
                    service_uuids_str,
                    [&](QString out_str, const QBluetoothUuid &uuid){
      return out_str + "," + uuid.toString();
    });
  }

  qDebug() << "[" << type << "|" << info.rssi() << "] name: " << info.name()
           << ", address" << info.address().toString() << ", type: "
           << info.coreConfigurations() << ", major: "
           << info.majorDeviceClass() << ", minor: " << info.minorDeviceClass()
           << ", service: " << info.serviceClasses() << ", device uuid: "
           << info.deviceUuid().toString() << ", service uuids: "
           << service_uuids_str;
}

void BluetoothWidget::AddDeviceInfo(QString addr, QString name) {
  if (addr == "") {
    qWarning() << "scan device address empty";
    return;
  }

  auto find_items =
      bluetooth_list_->findItems(addr, Qt::MatchContains);
  if (!find_items.empty()) {
    qInfo() << "scan device: " << addr << " already in list, ignore";
    return;
  }

  auto last_row = bluetooth_list_->rowCount();
  bluetooth_list_->insertRow(last_row);

  auto *type_item = new QTableWidgetItem("D");
  auto *rssi_item = new QTableWidgetItem(0);
  auto *name_item = new QTableWidgetItem(name);
  auto *addr_item = new QTableWidgetItem(addr);
  type_item->setFlags(type_item->flags() & ~Qt::ItemIsEditable);
  rssi_item->setFlags(rssi_item->flags() & ~Qt::ItemIsEditable);
  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  addr_item->setFlags(addr_item->flags() & ~Qt::ItemIsEditable);

  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kType), type_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kRssi), rssi_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kName), name_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kAddress), addr_item);
}


}  // namespace auto_pi
