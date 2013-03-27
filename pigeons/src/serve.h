/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：serve.h
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 

#include <QtGui>
#include <QtNetwork>
#include <QDebug>
#include "ipmsg.h"

class Serve : public QObject
{
	Q_OBJECT
public slots:

	void broadcast(unsigned long command, QString extend);
	void sendUdp(MsgMng *);
	void sendTcp(MsgMng *, QString);
	void receiveUdp();
	void receiveTcp();
signals:
	void msgBrExit(MsgMng *msg);
	void msgSendMsg(MsgMng *msg);
	void addUser(MsgMng *msg);
public:
	MsgMng *msgmng;
	QUdpSocket *udpSocket;	
	Serve();
	void	msgBrEntry(MsgMng *msg);

	void	msgAnsEntry(MsgMng *msg);
	void	msgBrAbsence(MsgMng *msg);

	void	msgRecvMsg(MsgMng *msg);
	void	msgReadMsg(MsgMng *msg);
	void	msgBrIsGetList(MsgMng *msg);
	void	msgOkGetList(MsgMng *msg);
	void	msgGetList(MsgMng *msg);
	void	msgAnsList(MsgMng *msg);
	void	msgGetInfo(MsgMng *msg);
	void	msgSendInfo(MsgMng *msg);
	void	msgGetPubKey(MsgMng *msg);
	void	msgAnsPubKey(MsgMng *msg);
	void	msgGetAbsenceInfo(MsgMng *msg);
	void	msgSendAbsenceInfo(MsgMng *msg);
	void	msgReleaseFiles(MsgMng *msg);
	void	msgInfoSub(MsgMng *msg);

private:


};
