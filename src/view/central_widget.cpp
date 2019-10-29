// Copyright (c) 2014-2019 winking324
//


#include "view/central_widget.h"
#include <QDebug>
#include "commons/singleton.h"
#include "controller/obd_client.h"


namespace auto_pi {


enum class StackedWidgetIndex : int {
  kDisplay = 0,
  kConfig = 1,
  kBluetooth = 2,
};


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) {
  config_widget_ = new ConfigWidget(this);
  display_widget_ = new DisplayWidget(this);
  bluetooth_widget_ = new BluetoothWidget(this);

  layout_ = new QStackedLayout(this);
  layout_->insertWidget(
        static_cast<int>(StackedWidgetIndex::kDisplay), display_widget_);
  layout_->insertWidget(
        static_cast<int>(StackedWidgetIndex::kConfig), config_widget_);
  layout_->insertWidget(
        static_cast<int>(StackedWidgetIndex::kBluetooth), bluetooth_widget_);

  setLayout(layout_);

  connect(display_widget_, &DisplayWidget::ConfigEvent,
          this, &CentralWidget::OnConfig);
  connect(config_widget_, &ConfigWidget::OBDEvent,
          this, &CentralWidget::OnConfigOBD);
  connect(config_widget_, &ConfigWidget::OkEvent,
          this, &CentralWidget::OnConfigOk);
  connect(bluetooth_widget_, &BluetoothWidget::ItemSelectedEvent,
          this, &CentralWidget::OnBluetooth);
}

void CentralWidget::OnConfig() {
  qInfo() << "[W] change to config widget";
  layout_->setCurrentIndex(static_cast<int>(StackedWidgetIndex::kConfig));
}

void CentralWidget::OnConfigOBD() {
  qInfo() << "[W] change to bluetooth widget";
  auto *obd_client = Singleton<OBDClient>::Instance();
  connect(bluetooth_widget_, &BluetoothWidget::DeviceSelectedEvent,
          obd_client, &OBDClient::OnDeviceSelected);

  layout_->setCurrentIndex(static_cast<int>(StackedWidgetIndex::kBluetooth));
}

void CentralWidget::OnConfigOk() {
  qInfo() << "[W] change to display widget";
  layout_->setCurrentIndex(static_cast<int>(StackedWidgetIndex::kDisplay));
}

void CentralWidget::OnBluetooth() {
  qInfo() << "[W] change to config widget";
  auto *obd_client = Singleton<OBDClient>::Instance();
  bluetooth_widget_->disconnect(obd_client);
  layout_->setCurrentIndex(static_cast<int>(StackedWidgetIndex::kConfig));
}


}  // namespace auto_pi

