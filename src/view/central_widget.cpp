// Copyright (c) 2014-2019 winking324
//


#include "view/central_widget.h"


namespace auto_pi {


enum class StackedWidgetIndex : int {
  kBluetooth = 1,
};


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) {
  bluetooth_widget_ = new BluetoothWidget(this);

  layout_ = new QStackedLayout(this);
  layout_->insertWidget(
        static_cast<int>(StackedWidgetIndex::kBluetooth), bluetooth_widget_);

  setLayout(layout_);
}


}  // namespace auto_pi

