// Copyright (c) 2014-2019 winking324
//


#include "view/lcd_number.h"
#include <QPixmap>
#include <QVector>


namespace auto_pi {


LCDNumber::LCDNumber(uint32_t number, QWidget *parent) : QWidget(parent) {
  layout_ = new QHBoxLayout(this);
  layout_->setAlignment(Qt::AlignCenter);

  Display(number);

  setLayout(layout_);
}

void LCDNumber::Display(uint32_t number) {
  static const QVector<QString> kNumberIcon = {
    ":/0.png", ":/1.png", ":/2.png", ":/3.png", ":/4.png",
    ":/5.png", ":/6.png", ":/7.png", ":/8.png", ":/9.png"
  };

  auto numbers_str = QString::number(number);
  if (numbers_str.size() != numbers_.size()) {
    auto resize = numbers_str.size() - numbers_.size();
    if (resize > 0) {
      for (auto i = 0; i < resize; ++i) {
        auto *label = new QLabel(this);
        layout_->addWidget(label);
        numbers_.push_back(label);
      }
    } else {
      auto iter = numbers_.begin();
      for (auto i = 0; i < -resize; ++i) {
        layout_->removeWidget(*iter);
        delete *iter;

        iter = numbers_.erase(iter);
      }
    }
  }

  auto number_iter = numbers_.begin();
  for (auto iter = numbers_str.begin(); iter != numbers_str.end();
       ++iter,++number_iter) {
    (*number_iter)->setPixmap(QPixmap(kNumberIcon[QString(*iter).toInt()]).scaled(QSize(80, 80), Qt::KeepAspectRatio));
  }
}


}  // namespace auto_pi
