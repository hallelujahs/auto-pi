// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QTimer>
#include <QLabel>
#include <QWidget>
#include <QPushButton>


namespace auto_pi {


class ConfigWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ConfigWidget(QWidget *parent = nullptr);

 signals:
  void OkEvent();

  void OBDEvent();

 public slots:
  void OnUpdateTimer();

  void OnReboot();

  void OnPowerOff();

 protected:
  virtual void showEvent(QShowEvent *event) override;

  virtual void hideEvent(QHideEvent *event) override;

 private:
  void UpdateIp();

  void UpdateOBDStatus();

 private:
  QTimer *update_timer_;
  QLabel *local_ip_;
  QLabel *obd_status_;

  QPushButton *config_obd_;
  QPushButton *reboot_;
  QPushButton *power_off_;
  QPushButton *confirm_;
};


}  // namespace auto_pi
