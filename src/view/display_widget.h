// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QTimer>
#include <QLabel>
#include <QWidget>
#include <QVector>
#include <QPushButton>

#include "view/lcd_number.h"


namespace auto_pi {


enum class WarningSigns {
  kBattery = 0,  // 电池
  kAirbagSeatBeltSystem = 1,  // 气囊
  kDrowsy = 2,  // 疲劳驾驶
  kEngine = 3,  // 发动机
  kOilPressure = 4,  // 机油
  kTirePressure = 5,  // 胎压
  kEngineTemperature = 6,  // 水温
  kParkingBrake = 7,  // 手刹
  kDoorOpen = 8,  // 车门
  kGasoline = 9,  // 汽油
  kSeatbelt = 10,  // 安全带
};


class DisplayWidget : public QWidget {
  Q_OBJECT
 public:
  explicit DisplayWidget(QWidget *parent = nullptr);

  void SetWarningSign(WarningSigns sign, bool is_on);

 signals:
  void ConfigEvent();

 public slots:

 private:
  void InitWarningSigns();

 private:
  QTimer *test_timer_;
  QVector<QLabel *> sign_labels_;
  QPushButton *config_button_;

  LCDNumber *speed_;
};


}  // namespace auto_pi

