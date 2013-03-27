/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：msgManage.cpp
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 

#include "ipmsg.h"

MsgMng::MsgMng(){
	username = QHostInfo::localHostName();
	hostname = QHostInfo::localHostName()+"*";  
	version = PIGEONS_VERSION;
	packetno = QDateTime::currentDateTime().toTime_t();//实际返回uint，有点不匹配

}
unsigned long MsgMng::getPacketno()
{
	return packetno;
}
QString MsgMng::getUsername()
{
	return username;
}
QString MsgMng::getHostname()
{
	return hostname;
}
QHostAddress MsgMng::getAddress()
{
	return address;
}
int MsgMng::getVersion()
{
	return version;
}
unsigned long MsgMng::getCommand()
{
	return command;
}
QString MsgMng::getExtend()
{
	return extend;
}
MsgMng* MsgMng::makeMng(QString username, QString hostname, unsigned long command, QString extend,QHostAddress addr)
{
	MsgMng *msg = new MsgMng;
	msg->username = username;
	msg->hostname = hostname;
	msg->command = command;
	msg->extend = extend;
	msg->address=addr;
	return msg;
}

void MsgMng::parseMsg(){}
