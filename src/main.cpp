/*
 * main.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: cy
 */
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Log.h"
#include "SipUA.h"


using namespace std;
int main()
{
	boost::property_tree::ptree pt;
	SipUA* pSipUA= new SipUA();

	boost::property_tree::ini_parser::read_ini("./SipUA.ini", pt);  // 打开读文件
	pSipUA->SetGatewayParams(pt);

//	int debugFlag = pt.get<int>("Debug.flag");
//	if(debugFlag)
//	{
//		cout << "debug" << endl;
//		return 0;
//	}



	if (!init_log_environment("./Log.cnf")) {
		cout << "Failed to initialize log system." << endl;
		return -1;
	}




	pSipUA->eXosipInit();
	pSipUA->SendRegister(3000);//expire > 0 Reg ; expire = 0 log out;
	//事件用于等待
	eXosip_event_t* pEvent = NULL;
	int ret;
	while(true)
	{
		//等待事件 0的单位是秒，500是毫秒
		pEvent = pSipUA->eXosipEventWait();
		pSipUA->eXosipDefultAction(pEvent);
		//事件空继续等待
		if (NULL == pEvent)
		{
			continue;
		}
		ret = pSipUA->eXosipEventHandle(pEvent);
	}


	delete(pSipUA);
	return 0;
}



