/*
 * SipUA.h
 *
 *  Created on: Dec 5, 2018
 *      Author: cy
 */

#ifndef SRC_SIPUA_H_
#define SRC_SIPUA_H_
#include <string>
#include <osipparser2/osip_message.h>
#include <osipparser2/osip_parser.h>
#include <osipparser2/osip_port.h>
#include <eXosip2/eXosip.h>
#include <eXosip2/eX_setup.h>
#include <eXosip2/eX_register.h>
#include <eXosip2/eX_options.h>
#include <eXosip2/eX_message.h>
#include <boost/property_tree/ptree.hpp>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Log.h"    // include the header file for Boost Log.
using namespace std;
using namespace boost::log;

typedef struct _GatewayInfo //网关信息结构体
{
	string  severId;   //SIP服务器ID
	string  serverIP;  //SIP服务器IP地址
	int 	serverPort;//SIP服务器IP端口
	string  deviceId;  //设备ID
	string	devicePwd; //设备password
	string  address;   //设备IP
	int 	listenPort;//设备监听端口
	int 	mediaPort; //媒体端口
	string  deviceName;//设备名陈
	string  manufacturer;//设备厂商
	string	model;//设备型号
	string 	firmware;//设备固件版本
	string 	deviceEncode;//是否编码
	string  deviceRecord;//是否录像
}CyGatewayInfo;


class SipUA {
public:
	SipUA();
	virtual ~SipUA();

public:
	int SetGatewayParams(boost::property_tree::ptree pt);
	int eXosipInit();
	int eXosipRelease();
	eXosip_event_t *eXosipEventWait();
	int  eXosipDefultAction(eXosip_event_t *pEvent);
	int  eXosipEventHandle(eXosip_event_t *pEvent);
public:
	// 注册
	int SendRegister(int expires);
	// 刷新注册
	int SendRefreshRegister();
	// 注销
	int SendUnRegister();
	// 发送Invite消息
	int SendInvite();
	// 发送Message消息
	int SendMessage();
	// 发送ACK消息
	int SendAck();
	// 发送Notify消息
	int SendNotify();
	// 200 OK or 其它状态码
	int SendCodeMsg(int code);
	// 发送心跳
	int SendHeatBeat();
	// Recv register
	int RecvRegister(eXosip_event_t *pEvent);
	//接收Invite消息
	int RecvInvite();
	//接收Message消息
	int RecvMessage();
	//接收Bye消息
	int RecvBye();
	//接收Subscribe消息
	int RecvSubscribe();
	//接收200 OK or 其它状态码
	int RecvCodeMsg();
	// SIP From
	string GetFromHeader();
	// SIP TO
	string GetToHeader();
	// SIP Contact
	string GetContactHeader();
protected:
	int ParseMessageBody();
	int ParseInviteBody();
private:
	// 处理平台设备查询
	int ProcessCatalog();
	// 处理平台信息查询
	int ProcessDeviceInfo();
	// 处理平台状态查询
	int ProcessDeviceStatus();
	// 处理历史视频查询
	int ProcessRecordInfo();
	// Register, UnRegister, RefreshReister
	int SendRegisterCore(int expires, int type);
private:
	eXosip_t*		m_pSipCtx;
	int         	m_nRegisterId;
	CyGatewayInfo	m_stGatewayInfo;
private:
	//在自己的class里面定义一个日志输出通道对象
	sources::severity_logger<trivial::severity_level> m_logger;
};

#endif /* SRC_SIPUA_H_ */
