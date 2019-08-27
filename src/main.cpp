// Copyright (c) 2014-2019 winking324
//


#include <QIcon>
#include <QApplication>
#include "view/main_window.h"


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/icon.png"));
  auto_pi::MainWindow w;
  w.show();

  return a.exec();
}


