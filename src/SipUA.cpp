/*
 * SipUA.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: cy
 */
#include <iostream>
#include <sstream>
#include "SipUA.h"

SipUA::SipUA() {
	// TODO Auto-generated constructor stub
	m_pSipCtx = NULL;
	m_nRegisterId = 0;/*注册ID/用来更新注册或取消注册*/
}

SipUA::~SipUA() {
	// TODO Auto-generated destructor stub
	eXosipRelease();
}
int SipUA::SetGatewayParams(boost::property_tree::ptree pt)
{
	// 公安平台
	m_stGatewayInfo.severId = pt.get<std::string>("Security.DeviceId");
	m_stGatewayInfo.serverIP = pt.get<std::string>("Security.Address");
	m_stGatewayInfo.serverPort = pt.get<int>("Security.Port");

	// 网关配置
	m_stGatewayInfo.deviceId = pt.get<std::string>("Local.DeviceId");
	m_stGatewayInfo.devicePwd = pt.get<std::string>("Local.DevicePwd");
	m_stGatewayInfo.address = pt.get<std::string>("Local.Address");
	m_stGatewayInfo.listenPort = pt.get<int>("Local.ListenPort");
	m_stGatewayInfo.mediaPort = pt.get<int>("Local.MediaPort");
	m_stGatewayInfo.deviceName = pt.get<std::string>("Local.DeviceName");
	m_stGatewayInfo.manufacturer = pt.get<std::string>("Local.Manufacturer");
	m_stGatewayInfo.model = pt.get<std::string>("Local.Model");
	m_stGatewayInfo.firmware = pt.get<std::string>("Local.Firmware");
	m_stGatewayInfo.deviceEncode = pt.get<std::string>("Local.DeviceEncode");
	return 0;
}
int SipUA::eXosipInit()
{
	m_pSipCtx = eXosip_malloc();
	//初始化库
	if (OSIP_SUCCESS !=  eXosip_init(m_pSipCtx))
	{
		return -1;
	}
	std::cout << "eXosip_init success." <<std::endl;


	BOOST_LOG_SEV(m_logger, trivial::severity_level::info) << __FUNCTION__ << ": @line(" << __LINE__ << "). " <<"eXosip_init success.";



	eXosip_set_user_agent(m_pSipCtx, NULL);
	//监听
	if (OSIP_SUCCESS != eXosip_listen_addr(m_pSipCtx, IPPROTO_UDP, NULL, m_stGatewayInfo.listenPort,AF_INET, 0))
	{
		std::cout << "eXosip_listen_addr failure" << std::endl;
		return -1;
	}
	//设置监听网卡
	if (OSIP_SUCCESS != eXosip_set_option(m_pSipCtx,EXOSIP_OPT_SET_IPV4_FOR_GATEWAY,m_stGatewayInfo.address.c_str()))
	{
		std::cout << "IPV4 failure" << std::endl;
		return -1;
	}
	return 0;
}
int SipUA::eXosipRelease()
{
	if(m_pSipCtx)
	{
		eXosip_quit(m_pSipCtx);
	}
	return 0;
}

eXosip_event_t* SipUA::eXosipEventWait()
{
	return eXosip_event_wait(m_pSipCtx, 0, 0);
}

int  SipUA::eXosipDefultAction(eXosip_event_t *pEvent)
{
	//usleep(500 * 1000);
	eXosip_lock(m_pSipCtx);
	//一般处理401/407采用库默认处理
	eXosip_default_action(m_pSipCtx, pEvent);
	//eXosip_automatic_action(context_eXosip);
	eXosip_unlock(m_pSipCtx);
	return 0;
}

int  SipUA::eXosipEventHandle(eXosip_event_t *pEvent)
{
	osip_message_t *g_answer = NULL;
	switch (pEvent->type)
	{
	//需要继续验证REGISTER是什么类型
	case EXOSIP_REGISTRATION_SUCCESS:
	case EXOSIP_REGISTRATION_FAILURE:
	{
		RecvRegister(pEvent);
	}
	break;
	case EXOSIP_MESSAGE_NEW:
	{

	}
	break;
	case EXOSIP_MESSAGE_ANSWERED:/*200OK*/
	break;
	case EXOSIP_CALL_ACK:/*ACK*/
	break;
	case EXOSIP_CALL_REINVITE:
	break;

	case EXOSIP_CALL_RELEASED: /*BYE*/
	break;
	case EXOSIP_IN_SUBSCRIPTION_NEW:
	break;
	case EXOSIP_SUBSCRIPTION_NOTIFY:
	break;
	default:
		cout << "The sip event type that not be precessed.the event "
			"type is : " << pEvent->type << endl;
		break;
	}

	return 0;
}
// 注册
int SipUA::SendRegister(int expires)
{
	if (0 > SendRegisterCore(3000, 0))
	{
		cout << "发送注册失败" << endl;
		return -1;
	}
	return 0;
}
// 刷新注册
int SipUA::SendRefreshRegister()
{
	return 0;
}

// 注销
int SipUA::SendUnRegister()
{
	return 0;
}
// 发送Invite消息
int SipUA::SendInvite()
{
	return 0;
}
// 发送Message消息
int SipUA::SendMessage()
{
	return 0;
}
// 发送ACK消息
int SipUA::SendAck()
{
	return 0;
}
// 发送Notify消息
int SipUA::SendNotify()
{
	return 0;
}
// 200 OK or 其它状态码
int SipUA::SendCodeMsg(int code)
{
	return 0;
}
// 发送心跳
int SipUA::SendHeatBeat()
{
	return 0;
}

// Recv Register
int SipUA::RecvRegister(eXosip_event_t *pEvent)
{
	cout<<"收到状态码:"<<pEvent->response->status_code<<"报文"<<endl;
	if(pEvent->response->status_code == 401)
	{
		cout<<"发送鉴权报文"<<endl;
	}
	else if(pEvent->response->status_code == 200)
	{
		cout<<"接收成功"<<endl;
	}
	else
	{}
	return 0;

}
//接收Invite消息
int SipUA::RecvInvite()
{
	return 0;
}
//接收Message消息
int SipUA::RecvMessage()
{
	return 0;
}
//接收Bye消息
int SipUA::RecvBye()
{
	return 0;
}
//接收Subscribe消息
int RecvSubscribe()
{
	return 0;
}
//接收200 OK or 其它状态码
int SipUA::RecvCodeMsg()
{
	return 0;
}

int SipUA::ParseMessageBody()
{
	return 0;
}
int SipUA::ParseInviteBody()
{
	return 0;
}

// SIP From
string SipUA::GetFromHeader()
{
	stringstream stream;
	stream << "sip:" << m_stGatewayInfo.deviceId << "@" << m_stGatewayInfo.address << ":" << m_stGatewayInfo.listenPort;
	return stream.str();

}
// SIP TO
string SipUA::GetToHeader()
{
	stringstream stream;
	stream << "sip:" << m_stGatewayInfo.severId << "@" << m_stGatewayInfo.serverIP << ":" << m_stGatewayInfo.serverPort;
	return stream.str();

}
// SIP Contact
string SipUA::GetContactHeader()
{
	return GetFromHeader();
}

// 处理平台设备查询
int SipUA::ProcessCatalog()
{
	return 0;
}
// 处理平台信息查询
int SipUA::ProcessDeviceInfo()
{
	return 0;
}
// 处理平台状态查询
int SipUA::ProcessDeviceStatus()
{
	return 0;
}
// 处理历史视频查询
int SipUA::ProcessRecordInfo()
{
	return 0;
}
int SipUA::SendRegisterCore(int expires, int type)
{
	cout << "=============================================" << endl;
	if (type == 0)
	{
		cout << "注册请求信息：" << endl;
	}
	else if (type == 1)
	{
		cout << "刷新注册信息：" << endl;
	}
	else
	{
		cout << "注销信息:" << endl;
	}
	//服务器注册
	static osip_message_t *regMsg = 0;
	int ret;

	eXosip_add_authentication_info(m_pSipCtx,
								   m_stGatewayInfo.deviceName.c_str(),
								   m_stGatewayInfo.deviceId.c_str(),
								   m_stGatewayInfo.devicePwd.c_str(),
								   "MD5",
								   NULL);
	eXosip_lock(m_pSipCtx);
	//发送注册信息 401响应由eXosip2库自动发送
	if (0 == m_nRegisterId)
	{
		// 注册消息的初始化
		m_nRegisterId = eXosip_register_build_initial_register(m_pSipCtx,
					   	   	   	   	   	   	   	   	   	   	   GetFromHeader().c_str(),
															   GetToHeader().c_str(),
															   GetContactHeader().c_str(),
															   expires,
															   &regMsg);
		if (m_nRegisterId <= 0)
		{
			return -1;
		}
	}
	else
	{
		// 构建注册消息
		ret = ::eXosip_register_build_register(m_pSipCtx, m_nRegisterId, expires, &regMsg);
		if (ret != OSIP_SUCCESS)
		{
			return ret;
		}
		//添加注销原因
		if (expires == 0)
		{
			osip_contact_t *contact = NULL;
			char tmp[128];

			osip_message_get_contact(regMsg, 0, &contact);
			{
				sprintf(tmp, "<sip:%s@%s:%s>;expires=0",
						contact->url->username, contact->url->host,
						contact->url->port);
			}
			//osip_contact_free(contact);
			//reset contact header
			osip_list_remove(&regMsg->contacts, 0);
			osip_message_set_contact(regMsg, tmp);
			osip_message_set_header(regMsg, "Logout-Reason", "logout");
		}
	}
	// 发送注册消息
	ret = eXosip_register_send_register(m_pSipCtx, m_nRegisterId, regMsg);
	if (ret != OSIP_SUCCESS)
	{
		m_nRegisterId = 0;
	}
	eXosip_unlock(m_pSipCtx);
	return ret;

}
