// Copyright (c) 2014-2019 winking324
//

#pragma once  // NOLINT(build/header_guard)


#include <QObject>


namespace auto_pi {


class Bluetooth : public QObject {
  Q_OBJECT

 public:
  explicit Bluetooth(QObject *parent = nullptr);

 signals:

 public slots:

};


}  // namespace auto_pi
