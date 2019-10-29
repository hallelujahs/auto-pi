// Copyright (c) 2014-2019 winking324
//


#include "view/config_widget.h"

#include <QProcess>
#include <QGridLayout>
#include <QNetworkInterface>

#include "commons/singleton.h"
#include "controller/obd_client.h"


namespace auto_pi {


ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent) {
  auto *layout = new QGridLayout(this);
  layout->setAlignment(Qt::AlignTop);

  update_timer_ = new QTimer(this);
  local_ip_ = new QLabel(this);
  obd_status_ = new QLabel(this);
  config_obd_ = new QPushButton("Set", this);

  reboot_ = new QPushButton("Reboot", this);
  power_off_ = new QPushButton("PowerOff", this);
  confirm_ = new QPushButton("OK", this);

  update_timer_->setInterval(1000);

  int row = 0;
  layout->addWidget(new QLabel("IP", this), row, 0);
  layout->addWidget(local_ip_, row, 1);

  layout->addWidget(new QLabel("OBD", this), ++row, 0);
  layout->addWidget(obd_status_, row, 1);
  layout->addWidget(config_obd_, row , 2);

  layout->addWidget(reboot_, ++row, 0);
  layout->addWidget(power_off_, row, 1);
  layout->addWidget(confirm_, row, 2);

  setLayout(layout);

  connect(config_obd_, &QPushButton::released, this, &ConfigWidget::OBDEvent);
  connect(update_timer_, &QTimer::timeout, this, &ConfigWidget::OnUpdateTimer);

  connect(confirm_, &QPushButton::released, this, &ConfigWidget::OkEvent);
  connect(reboot_, &QPushButton::released, this, &ConfigWidget::OnReboot);
  connect(power_off_, &QPushButton::released, this, &ConfigWidget::OnPowerOff);
}

void ConfigWidget::OnUpdateTimer() {
  UpdateIp();
  UpdateOBDStatus();
}

void ConfigWidget::OnReboot() {
  qInfo() << "reboot";
  QProcess process;
  process.startDetached("shutdown -r now");
}

void ConfigWidget::OnPowerOff() {
  qInfo() << "power off";
  QProcess process;
  process.startDetached("shutdown -P now");
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
    local_ip_->setText(ip_str);
    qInfo() << "scan local ip: " << ip_str;
    update_timer_->setInterval(10 * 1000);
    break;
  }
}

void ConfigWidget::UpdateOBDStatus() {
  auto *obd_client = Singleton<OBDClient>::Instance();
  if (!obd_client->IsSetted()) {
    obd_status_->setPixmap(QPixmap(":/bluetooth_notset.png"));
    return;
  }

  if (!obd_client->IsConnected()) {
    obd_status_->setPixmap(QPixmap(":/bluetooth_unconnect.png"));
    return;
  }

  obd_status_->setPixmap(QPixmap(":/bluetooth_connected.png"));
}


}  // namespace auto_pi
