// Copyright (c) 2014-2019 winking324
//


#include "controller/bluetooth_discovery_agent.h"
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/hci_lib.h>
#include <QDebug>


namespace auto_pi {


const static int kMaxDiscoveryInterval = 8;
const static int kMaxDiscoveryDeviceCount = 255;


BluetoothDiscoveryAgent::BluetoothDiscoveryAgent(QObject *parent)
  : QThread(parent) {
  devices_ = new inquiry_info[kMaxDiscoveryDeviceCount];
}

BluetoothDiscoveryAgent::~BluetoothDiscoveryAgent() {
  delete []devices_;
}

void BluetoothDiscoveryAgent::run() {
  int adapter_id = hci_get_route(nullptr);
  int sock = hci_open_dev(adapter_id);

  if (adapter_id < 0 || sock < 0) {
    qCritical() << "error opening socket";
    emit ErrorEvent(BluetoothDiscoveryError::kErrorOpenSocket);
    return;
  }

  int dev_cnt = hci_inquiry(adapter_id, kMaxDiscoveryInterval,
                            kMaxDiscoveryDeviceCount, nullptr,
                            &devices_, IREQ_CACHE_FLUSH);
  if (dev_cnt < 0) {
    qInfo() << "bluetooth discovery failed";
    close(sock);
    emit ErrorEvent(BluetoothDiscoveryError::kErrorDiscovery);
    return;
  }

  char addr[19] = {0};
  char name[248] = {0};
  for (int i = 0; i < dev_cnt; ++i) {
    ba2str(&(devices_ + i)->bdaddr, addr);
    memset(name, 0, sizeof(name));
    int ret = hci_read_remote_name(sock, &(devices_ + i)->bdaddr,
                                   sizeof(name), name, 0);
    if (ret != 0) {
      strcpy(name, "[unknown]");
    }

    qInfo() << "bluetooth discovery device: " << addr << ", name: " << name;
    emit DeviceDiscoveredEvent(addr, name);
  }

  close(sock);
}


}  // namespace auto_pi
