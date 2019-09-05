// Copyright (c) 2014-2019 winking324
//


#include <QApplication>
#include "view/main_window.h"
#include "controller/log_controller.h"


int main(int argc, char *argv[]) {
  qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS",
          QByteArray("/dev/input/event0:rotate=90"));
  qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("79"));
  qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("52"));
  qputenv("QT_QPA_EGLFS_WIDTH", QByteArray("480"));
  qputenv("QT_QPA_EGLFS_HEIGHT", QByteArray("320"));

  QCoreApplication::setOrganizationName("winking.io");
  QCoreApplication::setOrganizationDomain("winking.io");
  QCoreApplication::setApplicationName("auto-pi");
  QApplication a(argc, argv);

  auto_pi::InitLog();

  auto_pi::MainWindow w;
  w.show();

  return a.exec();
}


