#---------------------------------------------------------------------
# PART 1: General Setting
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
OBJECTS_DIR = .objs
QT += core gui network bluetooth

include(gitversion.pri)

#---------------------------------------------------------------------
# PART 2: target, library, flags
TARGET = bin/auto-pi
INCLUDEPATH += src
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/lib -L/usr/local/lib
LIBS += -lbluetooth
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

#---------------------------------------------------------------------
# PART 3: Clean
QMAKE_CLEAN += $(TARGET) $(QMAKE_TARGET) bin/auto-pi

#---------------------------------------------------------------------
# PART 4: Input
SOURCES += \
    src/controller/bluetooth_client.cpp \
    src/controller/bluetooth_discovery_agent.cpp \
    src/controller/global_config.cpp \
    src/controller/log_controller.cpp \
    src/controller/obd_client.cpp \
    src/main.cpp \
    src/view/bluetooth_widget.cpp \
    src/view/central_widget.cpp \
    src/view/config_widget.cpp \
    src/view/display_widget.cpp \
    src/view/lcd_number.cpp \
    src/view/main_window.cpp
HEADERS += \
    src/commons/singleton.h \
    src/controller/bluetooth_client.h \
    src/controller/bluetooth_discovery_agent.h \
    src/controller/global_config.h \
    src/controller/log_controller.h \
    src/controller/obd_client.h \
    src/view/bluetooth_widget.h \
    src/view/central_widget.h \
    src/view/config_widget.h \
    src/view/display_widget.h \
    src/view/lcd_number.h \
    src/view/main_window.h
RESOURCES += \
    resource.qrc
