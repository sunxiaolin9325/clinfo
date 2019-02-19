#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T13:20:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlatformAndDeviceInfo
TEMPLATE = app


SOURCES += main.cpp\
        platformanddeviceinfo.cpp

HEADERS  += platformanddeviceinfo.h \
    tool.h

FORMS    += platformanddeviceinfo.ui

#添加OpenCL的头文件
INCLUDEPATH +=/opt/data/libmali/include/original/

#添加OpenCL的库文件
LIBS += -lGAL -lOpenCL
