// Copyright (c) 2014-2019 winking324
//

#include "view/bluetooth_widget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>


namespace auto_pi {


enum class BluetoothTableColumn {
  kName = 0,
  kAddress = 1,
};


BluetoothWidget::BluetoothWidget(QWidget *parent) : QWidget(parent) {
  auto *layout = new QVBoxLayout(this);
  auto *check_box_layout = new QHBoxLayout(this);

  bluetooth_list_ = new QTableWidget(this);
  scan_button_ = new QPushButton("Scan", this);

  bluetooth_list_->setColumnCount(4);
  bluetooth_list_->setHorizontalHeaderLabels(
        QStringList{"NAME", "ADDRESS"});

  bluetooth_list_->horizontalHeader()->setHighlightSections(false);
  bluetooth_list_->setSelectionBehavior(QAbstractItemView::SelectRows);
  bluetooth_list_->setSelectionMode(QAbstractItemView::SingleSelection);

  layout->addWidget(bluetooth_list_);

  layout->addLayout(check_box_layout);
  layout->addWidget(scan_button_);
  setLayout(layout);

  connect(scan_button_, SIGNAL(released()), this, SLOT(OnScan()));

  connect(bluetooth_list_, &QTableWidget::itemDoubleClicked,
          this, &BluetoothWidget::OnItemDoubleClicked);
}

void BluetoothWidget::OnScan() {
  scan_button_->setText("Scanning");
  scan_button_->setDisabled(true);

  devices_.clear();
  ClearDeviceList();

  discovery_agent_ = new BluetoothDiscoveryAgent(this);
  connect(discovery_agent_, &BluetoothDiscoveryAgent::ErrorEvent,
          this, &BluetoothWidget::OnDiscoveryError);
  connect(discovery_agent_, &BluetoothDiscoveryAgent::DeviceDiscoveredEvent,
          this, &BluetoothWidget::OnDeviceDiscovered);
  connect(discovery_agent_, &QThread::finished, this,
          &BluetoothWidget::OnDiscoveryFinished);
  discovery_agent_->start();
}

void BluetoothWidget::OnDiscoveryFinished() {
  scan_button_->setText("Scan");
  scan_button_->setDisabled(false);

  discovery_agent_->deleteLater();
}

void BluetoothWidget::OnDiscoveryError(BluetoothDiscoveryError code) {
  (void)code;
}

void BluetoothWidget::OnDeviceDiscovered(QString addr, QString name) {
  AddDeviceInfo(std::move(addr), std::move(name));
}

void BluetoothWidget::OnItemDoubleClicked(QTableWidgetItem *item) {
  int selected_row = item->row();
  auto *addr_item = bluetooth_list_->item(
        selected_row, static_cast<int>(BluetoothTableColumn::kAddress));

  auto iter = devices_.find(addr_item->text());
  if (iter != devices_.end()) {
    emit DeviceSelectedEvent(iter.key(), iter.value());
  }

  emit ItemSelectedEvent();
}

void BluetoothWidget::ClearDeviceList() {
  while (bluetooth_list_->rowCount() > 0) {
    bluetooth_list_->removeRow(0);
  }
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

  auto *name_item = new QTableWidgetItem(name);
  auto *addr_item = new QTableWidgetItem(addr);
  name_item->setFlags(name_item->flags() & ~Qt::ItemIsEditable);
  addr_item->setFlags(addr_item->flags() & ~Qt::ItemIsEditable);

  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kName), name_item);
  bluetooth_list_->setItem(
        last_row, static_cast<int>(BluetoothTableColumn::kAddress), addr_item);

  devices_.insert(addr, name);
}


}  // namespace auto_pi
