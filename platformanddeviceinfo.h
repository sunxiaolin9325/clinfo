#ifndef PLATFORMANDDEVICEINFO_H
#define PLATFORMANDDEVICEINFO_H

#include <QWidget>
#include "tool.h"

namespace Ui {
class PlatformAndDeviceInfo;
}

class PlatformAndDeviceInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlatformAndDeviceInfo(QWidget *parent = 0);
    ~PlatformAndDeviceInfo();

    //得到平台数量
    void getPlatformNum(cl_uint *num);
    //得到平台列表
    void getPlatforms(cl_platform_id *platformList);
    //初始化平台索引组合框
    void initPlatformIndex();

private slots:
    //平台索引组合框的索引值改变时触发
    void on_platformIndexCombo_currentIndexChanged(int index);
    //设备索引组合框的索引值改变时触发
    void on_deviceIndexCombo_currentIndexChanged(int index);
    //点击清空按钮时触发
    void on_clearBtn_clicked();
    //点击显示按钮时触发
    void on_displayBtn_clicked();
    //点击退出按钮时触发
    void on_quitBtn_clicked();

private:
    Ui::PlatformAndDeviceInfo *ui;

    //平台数量
    cl_uint platformNum;
    //平台列表
    cl_platform_id *platforms;
    //设备列表
    cl_device_id *devices;
};

#endif // PLATFORMANDDEVICEINFO_H
