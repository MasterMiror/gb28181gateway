/*
 * TtxService.h
 *
 *  Created on: Dec 5, 2018
 *      Author: cy
 */

#ifndef SRC_TTXSERVICE_H_
#define SRC_TTXSERVICE_H_
#include <string>
#include <vector>
using namespace std;

typedef struct _deviceInfo/*设备信息结构体*/
{
	string deviceID;  		/*目标设备/区域/系统的编码*/
	string name;      		/*设备/区域/系统名称*/
	string manufacturer;	/*设备厂商*/
	string model;			/*设备型号*/
	string owner;			/*设备归属*/
	string civilCode;		/*行政区域*/
	string block;			/*警区*/
	string address;			/*安装地址*/
	int parental;			/*是否有子设备*/
	string parentID;		/*父设备/区域/系统ID*/
	int safetyWay;			/*信令安全模式/0为不采用/2为S/MIME签名方式/3为S/MIME加密签名同时采用方式/4为数字摘要方式*/
	int registerWay;		/*注册方式/1为符合sip3261标准的认证注册模式/2为基于口令的双向认证注册模式/3为基于数字证书的双向认证注册模式*/
	string certNum;			/*证书序列号*/
	int certifiable;		/*证书有效标识/0为无效/1为有效*/
	string errCode;			/*无效原因码*/
	string endTime;			/*证书终止有效期*/
	int secrecy;			/*保密属性/0为不涉密/1为涉密*/
	string ipAddress;		/*设备/区域/系统IP地址*/
	int    port;			/*设备/区域/系统端口*/
	string password;		/*设备口令*/
	string status;			/*设备状态*/
	double longitude;		/*经度*/
	double latitude;		/*纬度*/
} DeviceInfo;

class TtxService {
public:
	TtxService();
	virtual ~TtxService();
public:
	string Login();
	string GetRtspUrl(string deviceId);
	vector<DeviceInfo> GetDeviceList();

private:
	string 	 m_strAddress;
	int  	 m_nPort;
};

#endif /* SRC_TTXSERVICE_H_ */
