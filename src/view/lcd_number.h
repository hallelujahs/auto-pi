// Copyright (c) 2014-2019 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <QList>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>


namespace auto_pi {


class LCDNumber : public QWidget {
  Q_OBJECT
public:
  explicit LCDNumber(uint32_t number = 0, QWidget *parent = nullptr);

  void Display(uint32_t number);

 private:
  QHBoxLayout *layout_;
  QList<QLabel *> numbers_;
};


}  // namespace auto_pi
