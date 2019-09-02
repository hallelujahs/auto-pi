// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QLabel>
#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>


namespace auto_pi {


class DisplayWidget : public QWidget {
  Q_OBJECT
 public:
  explicit DisplayWidget(QWidget *parent = nullptr);

 signals:
  void ConfigEvent();

 public slots:

 private:
  QPushButton *config_button_;
  QLCDNumber *speed_;
};


}  // namespace auto_pi

