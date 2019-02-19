#include "platformanddeviceinfo.h"
#include "ui_platformanddeviceinfo.h"
#include <stdio.h>

PlatformAndDeviceInfo::PlatformAndDeviceInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlatformAndDeviceInfo)
{
    ui->setupUi(this);

    this->setWindowTitle("平台和设备信息");
    this->setWindowState(Qt::WindowMaximized);

    devices=NULL;
    //得到平台数量
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
    getPlatformNum(&platformNum);
    //给平台列表分配内存
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
    platforms=(cl_platform_id*)malloc(sizeof(cl_platform_id)*platformNum);
    //得到平台列表
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
    getPlatforms(platforms);
    //初始化平台索引组合框
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
    initPlatformIndex();
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
}

PlatformAndDeviceInfo::~PlatformAndDeviceInfo()
{
    delete ui;

    if(platforms!=NULL)
    {
        free(platforms);
        platforms=NULL;
    }
    if(devices!=NULL)
    {
        free(devices);
        devices=NULL;
    }
}

//得到平台数量
void PlatformAndDeviceInfo::getPlatformNum(cl_uint *num)
{
	int ret = 0;
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
//CHECK_ERROR(clGetPlatformIDs(0,NULL,num));
    if ((ret = clGetPlatformIDs(0,NULL,num)) < 0) {
		printf("ret = %d\n", ret);
		exit(0);
	}
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
}

//得到平台列表
void PlatformAndDeviceInfo::getPlatforms(cl_platform_id *platformList)
{
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
    CHECK_ERROR(clGetPlatformIDs(platformNum,platformList,NULL));
	printf("%d\t%s\n", __LINE__, __FUNCTION__);
}

//初始化平台索引组合框
void PlatformAndDeviceInfo::initPlatformIndex()
{
    ui->platformIndexCombo->clear();
    for(int i=1;i<=platformNum;i++)
    {
        ui->platformIndexCombo->addItem(QString("平台%1").arg(i));
    }
}

//平台索引组合框的索引值改变时触发
void PlatformAndDeviceInfo::on_platformIndexCombo_currentIndexChanged(int index)
{
    if(index==-1)
    {
        return;
    }
    size_t paramSize;
    char *paramValue;

    //平台名
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_NAME,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_NAME,paramSize,paramValue,NULL));
    ui->platformNameLineEdit->clear();
    ui->platformNameLineEdit->setText(paramValue);
    free(paramValue);

    //平台开发商
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_VENDOR,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_VENDOR,paramSize,paramValue,NULL));
    ui->platformVendorLineEdit->clear();
    ui->platformVendorLineEdit->setText(paramValue);
    free(paramValue);

    //OpenCL版本
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_VERSION,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_VERSION,paramSize,paramValue,NULL));
    ui->OpenCLVersionLineEdit->clear();
    ui->OpenCLVersionLineEdit->setText(paramValue);
    free(paramValue);

    //OpenCL简档
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_PROFILE,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetPlatformInfo(platforms[index],CL_PLATFORM_PROFILE,paramSize,paramValue,NULL));
    ui->OpenCLProfileLineEdit->clear();
    ui->OpenCLProfileLineEdit->setText(paramValue);
    free(paramValue);

    //初始化设备索引组合框
    if(devices!=NULL)
    {
        free(devices);
        devices=NULL;
    }
    cl_uint deviceNum;
    CHECK_ERROR(clGetDeviceIDs(platforms[index],CL_DEVICE_TYPE_GPU,0,NULL,&deviceNum));
    devices=(cl_device_id*)malloc(sizeof(cl_device_id)*deviceNum);
    CHECK_ERROR(clGetDeviceIDs(platforms[index],CL_DEVICE_TYPE_GPU,deviceNum,devices,NULL));
    ui->deviceIndexCombo->clear();
    for(int i=1;i<=deviceNum;i++)
    {
        ui->deviceIndexCombo->addItem(QString("设备%1").arg(i));
    }
}

//设备索引组合框的索引值改变时触发
void PlatformAndDeviceInfo::on_deviceIndexCombo_currentIndexChanged(int index)
{
    if(index==-1)
    {
        return;
    }
    size_t paramSize;
    char *paramValue;
    cl_uint paramValue1;
    size_t *paramValue2;
    size_t paramValue3;
    cl_bool paramValue4;

    //设备名
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_NAME,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_NAME,paramSize,paramValue,NULL));
    ui->deviceNameLineEdit->clear();
    ui->deviceNameLineEdit->setText(paramValue);
    free(paramValue);

    //开发商名
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_VENDOR,0,NULL,&paramSize));
    paramValue=(char*)malloc(sizeof(char)*paramSize);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_VENDOR,paramSize,paramValue,NULL));
    ui->deviceVendorLineEdit->clear();
    ui->deviceVendorLineEdit->setText(paramValue);
    free(paramValue);

    //并行计算核数目
    paramSize=sizeof(cl_uint);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_COMPUTE_UNITS,paramSize,&paramValue1,NULL));
    ui->countKernelNumLineEdit->clear();
    ui->countKernelNumLineEdit->setText(QString("%1").arg(paramValue1));

    //最大维度
    paramSize=sizeof(cl_uint);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,paramSize,&paramValue1,NULL));
    ui->maxDimLineEdit->clear();
    ui->maxDimLineEdit->setText(QString("%1").arg(paramValue1));

    //各个维度上的最大工作项
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_WORK_ITEM_SIZES,0,NULL,&paramSize));
    paramValue2=(size_t*)malloc(sizeof(size_t)*paramSize);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_WORK_ITEM_SIZES,paramSize,paramValue2,NULL));
    QString tmpStr="";
    for(int i=0;i<paramValue1;i++)
    {
        if(i==0)
        {
            tmpStr+=QString("(%1,").arg(paramValue2[i]);
        }
        else if(i==paramValue1-1)
        {
            tmpStr+=QString("%1)").arg(paramValue2[i]);
        }
        else
        {
            tmpStr+=QString("%1,").arg(paramValue2[i]);
        }
    }
    ui->maxWorkItemLineEdit->clear();
    ui->maxWorkItemLineEdit->setText(tmpStr);
    free(paramValue2);

    //工作组中最大工作项数目
    paramSize=sizeof(size_t);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_WORK_GROUP_SIZE,paramSize,&paramValue3,NULL));
    ui->maxItemInGroupLineEdit->clear();
    ui->maxItemInGroupLineEdit->setText(QString("%1").arg(paramValue3));

    //是否支持图像
    paramSize=sizeof(cl_bool);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_IMAGE_SUPPORT,paramSize,&paramValue4,NULL));
    ui->isSupportImgLineEdit->clear();
    if(paramValue4)
    {
        ui->isSupportImgLineEdit->setText("True");
    }
    else
    {
        ui->isSupportImgLineEdit->setText("False");
    }

    //读图像对象的最大数目
    paramSize=sizeof(cl_uint);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_READ_IMAGE_ARGS,paramSize,&paramValue1,NULL));
    ui->maxReadImgNumLineEdit->clear();
    ui->maxReadImgNumLineEdit->setText(QString("%1").arg(paramValue1));

    //写图像对象的最大数目
    paramSize=sizeof(cl_uint);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_MAX_WRITE_IMAGE_ARGS,paramSize,&paramValue1,NULL));
    ui->maxWriteImgNumLineEdit->clear();
    ui->maxWriteImgNumLineEdit->setText(QString("%1").arg(paramValue1));

    //2D图像的最大宽度
    paramSize=sizeof(size_t);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_IMAGE2D_MAX_WIDTH,paramSize,&paramValue3,NULL));
    ui->maxWidthLineEdit->clear();
    ui->maxWidthLineEdit->setText(QString("%1").arg(paramValue3));

    //2D图像的最大高度
    paramSize=sizeof(size_t);
    CHECK_ERROR(clGetDeviceInfo(devices[index],CL_DEVICE_IMAGE2D_MAX_HEIGHT,paramSize,&paramValue3,NULL));
    ui->maxHeightLineEdit->clear();
    ui->maxHeightLineEdit->setText(QString("%1").arg(paramValue3));
}

//点击清空按钮时触发
void PlatformAndDeviceInfo::on_clearBtn_clicked()
{
    ui->platformIndexCombo->clear();
    ui->deviceIndexCombo->clear();
    ui->platformNameLineEdit->clear();
    ui->platformVendorLineEdit->clear();
    ui->OpenCLVersionLineEdit->clear();
    ui->OpenCLProfileLineEdit->clear();
    ui->deviceNameLineEdit->clear();
    ui->deviceVendorLineEdit->clear();
    ui->maxDimLineEdit->clear();
    ui->countKernelNumLineEdit->clear();
    ui->maxWorkItemLineEdit->clear();
    ui->maxItemInGroupLineEdit->clear();
    ui->isSupportImgLineEdit->clear();
    ui->maxReadImgNumLineEdit->clear();
    ui->maxWriteImgNumLineEdit->clear();
    ui->maxWidthLineEdit->clear();
    ui->maxHeightLineEdit->clear();
}

//点击显示按钮时触发
void PlatformAndDeviceInfo::on_displayBtn_clicked()
{
    initPlatformIndex();
}

//点击退出按钮时触发
void PlatformAndDeviceInfo::on_quitBtn_clicked()
{
    this->close();
}
