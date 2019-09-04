// Copyright (c) 2014-2019 winking324
//


#include "view/display_widget.h"

#include <QMap>
#include <QRgb>
#include <QIcon>
#include <QDebug>
#include <QColor>
#include <QBrush>
#include <QPixmap>
#include <QPalette>
#include <QGridLayout>
#include <QRandomGenerator>


namespace auto_pi {


DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent) {
  // for resolution w: 480 h: 320
  static const int kMaxRow = 8;
  static const int kMaxCol = 12;
  static const int kGridSize = 40;

  QPalette background_palette;
  background_palette.setBrush(QPalette::Background, QColor(0, 0, 0));
  setPalette(background_palette);
  setAutoFillBackground(true);

  auto *layout = new QGridLayout(this);
  for (auto i = 0; i < kMaxRow; ++i) {
    layout->setRowMinimumHeight(i, kGridSize);
  }
  for (auto i = 0; i < kMaxCol; ++i) {
    layout->setColumnMinimumWidth(i, kGridSize);
  }
  setLayout(layout);

  speed_ = new LCDNumber(110, this);
  layout->addWidget(speed_, 2, 3, 4, 6);

  InitWarningSigns();

  config_button_ = new QPushButton(this);
  config_button_->setStyleSheet("width:40px;height:40px;"
                                "border-image:url(:/config.png);");
  layout->addWidget(config_button_, 7, 11, 1, 1);

  // TODO(winking): remove
  SetWarningSign(WarningSigns::kEngine, true);

  connect(config_button_, &QPushButton::released,
          this, &DisplayWidget::ConfigEvent);

  // TODO(winking): remove
  test_timer_ = new QTimer(this);
  test_timer_->setInterval(500);
  test_timer_->callOnTimeout([this](){
    speed_->Display(QRandomGenerator::global()->bounded(120));
  });
  test_timer_->start();
}

void DisplayWidget::SetWarningSign(WarningSigns sign, bool is_on) {
  sign_labels_[static_cast<int>(sign)]->setVisible(is_on);
}

void DisplayWidget::InitWarningSigns() {
  if (sign_labels_.size() > 0) {
    qInfo() << "signs already initialized";
    return;
  }

  static const int kMaxSigns = 11;
  static const QMap<WarningSigns, QString> kWarningSignIcons = {
    {WarningSigns::kAirbagSeatBeltSystem, ":/sign_airbag.png"},
    {WarningSigns::kBattery, ":/sign_battery.png"},
    {WarningSigns::kDoorOpen, ":/sign_door_open.png"},
    {WarningSigns::kDrowsy, ":/sign_drowsy.png"},
    {WarningSigns::kEngine, ":/sign_engine.png"},
    {WarningSigns::kGasoline, ":/sign_gasoline.png"},
    {WarningSigns::kOilPressure, ":/sign_oil_pressure.png"},
    {WarningSigns::kParkingBrake, ":/sign_parking_brake.png"},
    {WarningSigns::kSeatbelt, ":/sign_seat_belt.png"},
    {WarningSigns::kEngineTemperature, ":/sign_temperature.png"},
    {WarningSigns::kTirePressure, ":/sign_tire.png"},
  };

  sign_labels_.resize(kMaxSigns);
  auto iter = kWarningSignIcons.begin();
  while (iter != kWarningSignIcons.end()) {
    auto pos = static_cast<int>(iter.key());
    auto *sign_label = new QLabel(this);
    sign_label->setStyleSheet(tr("width:40px;height:40px;border-image:url(") +
                              iter.value() + tr(");"));
    sign_label->setVisible(false);
    sign_labels_[pos] = sign_label;

    dynamic_cast<QGridLayout *>(this->layout())->addWidget(
          sign_label, 7, pos, 1, 1);
    ++iter;
  }
}


}  // namespace auto_pi
