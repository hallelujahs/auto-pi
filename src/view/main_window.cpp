// Copyright (c) 2014-2019 winking324
//

#include "view/main_window.h"


namespace auto_pi {


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {
  central_widget_ = new CentralWidget(this);
  setCentralWidget(central_widget_);

  setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
  showFullScreen();
}


}  // namespace auto_pi

