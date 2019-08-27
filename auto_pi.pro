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
DEFINES += QT_DEPRECATED_WARNINGS

#---------------------------------------------------------------------
# PART 3: Clean
QMAKE_CLEAN += $(TARGET) $(QMAKE_TARGET) bin/auto-pi

#---------------------------------------------------------------------
# PART 4: Input
SOURCES += \
    src/main.cpp \
    src/view/bluetooth_widget.cpp \
    src/view/central_widget.cpp \
    src/view/main_window.cpp \
    src/controller/bluetooth_agent.cpp
HEADERS += \
#    src/commons/definations.h \
    src/view/bluetooth_widget.h \
    src/view/central_widget.h \
    src/view/main_window.h \
    src/controller/bluetooth_agent.h
RESOURCES += \
    resource.qrc
