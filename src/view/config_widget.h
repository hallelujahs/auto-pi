// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


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

 private:
  void UpdateOBDStatus();

 private:
  QLabel *obd_status_label_;
  QPushButton *obd_button_;
  QPushButton *ok_button_;
};


}  // namespace auto_pi
