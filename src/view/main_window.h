// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)

#include <QMainWindow>
#include "view/central_widget.h"


namespace auto_pi {


class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);

 private:
  CentralWidget *central_widget_;
};


}  // namespace auto_pi

