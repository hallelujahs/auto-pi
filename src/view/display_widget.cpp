// Copyright (c) 2014-2019 winking324
//


#include "view/display_widget.h"
#include <QRgb>
#include <QIcon>
#include <QColor>
#include <QBrush>
#include <QPalette>
#include <QGridLayout>


namespace auto_pi {


DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent) {
  QPalette background_palette;
  background_palette.setBrush(QPalette::Background, QColor(0, 0, 0));
  setPalette(background_palette);
  setAutoFillBackground(true);

  auto *layout = new QGridLayout(this);

  for (auto i = 0; i < 8; ++i) {
    layout->setRowMinimumHeight(i, 40);
  }
  for (auto i = 0; i < 12; ++i) {
    layout->setColumnMinimumWidth(i, 40);
  }

  speed_ = new QLCDNumber(this);
  speed_->setSegmentStyle(QLCDNumber::Flat);
  auto speed_palette = QPalette();
  speed_palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
  speed_palette.setColor(QPalette::Background, QColor(0, 0, 0));
  speed_->setPalette(speed_palette);
  speed_->setStyleSheet("alignment:center;");
//  speed_->setStyleSheet("border:1px;text-align:center;");
  speed_->display(110);
  layout->addWidget(speed_, 2, 3, 4, 6);

  config_button_ = new QPushButton(this);
  config_button_->setStyleSheet("width:40px;height:40px;border-image:url(:/config.png);");
  layout->addWidget(config_button_, 7, 11, 1, 1);

  setLayout(layout);

  connect(config_button_, &QPushButton::released,
          this, &DisplayWidget::ConfigEvent);
}


}  // namespace auto_pi
