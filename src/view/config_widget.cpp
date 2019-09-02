// Copyright (c) 2014-2019 winking324
//


#include "view/config_widget.h"

#include <QGridLayout>

#include "commons/singleton.h"
#include "controller/obd_client.h"


namespace auto_pi {


ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent) {
  auto *layout = new QGridLayout(this);
  layout->setAlignment(Qt::AlignTop);

  obd_status_label_ = new QLabel(this);
  obd_button_ = new QPushButton("Set", this);
  ok_button_ = new QPushButton("OK", this);

  UpdateOBDStatus();

  int row = 0;
  layout->addWidget(new QLabel("OBD", this), row, 0);
  layout->addWidget(obd_status_label_, row, 1);
  layout->addWidget(obd_button_, row , 2);

  layout->addWidget(ok_button_, ++row, 2);

  setLayout(layout);

  connect(ok_button_, &QPushButton::released, this, &ConfigWidget::OkEvent);
  connect(obd_button_, &QPushButton::released, this, &ConfigWidget::OBDEvent);
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
