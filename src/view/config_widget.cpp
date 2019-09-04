// Copyright (c) 2014-2019 winking324
//


#include "view/config_widget.h"

#include <QGridLayout>
#include <QNetworkInterface>

#include "commons/singleton.h"
#include "controller/obd_client.h"


namespace auto_pi {


ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent) {
  auto *layout = new QGridLayout(this);
  layout->setAlignment(Qt::AlignTop);

  update_timer_ = new QTimer(this);
  ip_label_ = new QLabel(this);
  obd_status_label_ = new QLabel(this);
  obd_button_ = new QPushButton("Set", this);
  ok_button_ = new QPushButton("OK", this);

  update_timer_->setInterval(1000);

  int row = 0;
  layout->addWidget(new QLabel("IP", this), row, 0);
  layout->addWidget(ip_label_, row, 1);

  layout->addWidget(new QLabel("OBD", this), ++row, 0);
  layout->addWidget(obd_status_label_, row, 1);
  layout->addWidget(obd_button_, row , 2);

  layout->addWidget(ok_button_, ++row, 2);

  setLayout(layout);

  connect(ok_button_, &QPushButton::released, this, &ConfigWidget::OkEvent);
  connect(obd_button_, &QPushButton::released, this, &ConfigWidget::OBDEvent);
  connect(update_timer_, &QTimer::timeout, this, &ConfigWidget::OnUpdateTimer);
}

void ConfigWidget::OnUpdateTimer() {
  UpdateIp();
  UpdateOBDStatus();
}

void ConfigWidget::showEvent(QShowEvent *) {
  UpdateIp();
  UpdateOBDStatus();
  update_timer_->start();
}

void ConfigWidget::hideEvent(QHideEvent *) {
  update_timer_->stop();
}

void ConfigWidget::UpdateIp() {
  auto addresses = QNetworkInterface::allAddresses();
  for (const auto &address : addresses) {
    if(address.protocol() != QAbstractSocket::IPv4Protocol) {
      continue;
    }

    auto ip_str = address.toString();
    if (ip_str == "127.0.0.1") {
      continue;
    }
    ip_label_->setText(ip_str);
    break;
  }
}

void ConfigWidget::UpdateOBDStatus() {
  auto *obd_client = Singleton<OBDClient>::Instance();
  if (!obd_client->IsSetted()) {
    obd_status_label_->setPixmap(QPixmap(":/bluetooth_notset.png"));
    return;
  }

  if (!obd_client->IsConnected()) {
    obd_status_label_->setPixmap(QPixmap(":/bluetooth_unconnect.png"));
    return;
  }

  obd_status_label_->setPixmap(QPixmap(":/bluetooth_connected.png"));
}


}  // namespace auto_pi
