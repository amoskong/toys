/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：serve.cpp
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 
#include <QtNetwork>
#include "serve.h"

Serve::Serve()
{
	msgmng = new MsgMng;
        //监听UDP数据包，如果有数据包抵达调用receiveessag槽进行处理
        udpSocket = new QUdpSocket(this);
        udpSocket->bind(IPMSG_DEFAULT_PORT);
        qDebug()<<"Port:"<<IPMSG_DEFAULT_PORT;

        //tcpSocket = new QTcpSocket(this);
        //tcpSocket->bind(IPMSG_DEFAULT_PORT);
        connect(udpSocket, SIGNAL(readyRead()), this, SLOT(receiveUdp()));                                                            
        //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(service->receiveTcp()));   
        //broadcast(IPMSG_BR_ENTRY, NULL);
	broadcast(6291457, NULL);
}

void Serve::broadcast(unsigned long command, QString extend)
{
	MsgMng *msg = new MsgMng;
	msg->command = command;
	msg->extend = extend;
        qDebug()<<"Username:"<<msg->username;
        /*qDebug()<<"Hostname:"<<msg->hostname;
        qDebug()<<"Version:"<<msg->version;
        qDebug()<<"Packetno:"<<msg->packetno;
        qDebug()<<"Command:"<<msg->command;
        qDebug()<<"Extend:"<<msg->extend;*/

	QByteArray datagram;
	datagram.append(QString("%1:%2:%3:%4:%5:%6")
			.arg(msg->version)
			.arg(msg->packetno)
			.arg(msg->username)
			.arg(msg->hostname)
			.arg(msg->command)
			.arg(msg->extend));
	qDebug()<<"Broadcast:"<<datagram;
	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
			QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);
	qDebug()<<QHostAddress::Broadcast;
}

void Serve::sendUdp(MsgMng *msg)
{
	//qDebug()<<"Username:"<<msgmng->msgbuf->username;
	//qDebug()<<"Hostname:"<<msgmng->msg->hostname;
	//msg->extend="This is broadcast message(There seems a bug if the message it too long)";
	
	//QString str=msg->address.toString()+":"+msg->username;
	//msg->address=getAddress(str);
	
	qDebug()<<"---sendUdp---";
	qDebug()<<"Username:"<<msg->username;
	qDebug()<<"Hostname:"<<msg->hostname;
	qDebug()<<"HostAddress:"<<msg->address;
	qDebug()<<"Version:"<<msg->version;
	qDebug()<<"Packetno:"<<msg->packetno;
	qDebug()<<"Command:"<<msg->command;
	qDebug()<<"Extend:"<<msg->extend;
	QHostInfo info=QHostInfo::fromName("localhost");
	//QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
	foreach(QHostAddress addr, info.addresses())
        {
		qDebug()<<"Localhost-Address:"<<addr;
	}

	if (!info.addresses().isEmpty()) {
		//qDebug()<<info.addresses().first();
		//if(msg->address==info.addresses().first()){
		qDebug()<<"info.addresses().indexOf(msg->address)= "<< info.addresses().indexOf(msg->address) ;
		//if(info.addresses().indexOf(msg->address)!=-1){
		//if(msg->address==QHostAddress("192.168.21.35")) {
		qDebug()<<"msg->address:"<<msg->address;
		qDebug()<<"msgmng->address:"<<msgmng->address;

		if(msg->address==msgmng->address) {
			//emit addUser(msg);
			emit msgSendMsg(msg);
			qDebug()<<"sendUdp---to localhost";
			return;
		}	
	}
	
	/*QByteArray datagram;
	datagram.append(QString("%1:%2:%3:%4:%5:%6")
			.arg(msg->version)
			.arg(msg->packetno)
			.arg(msg->username)
			.arg(msg->hostname)
			.arg(msg->command)
			.arg(msg->extend));  */
	QByteArray datagram;
	datagram.append(QString("%1:%2:")
			.arg(msg->version)
			.arg(msg->packetno));

	QByteArray data2 = (msg->username+":").toUtf8();
	QByteArray data3 = msg->hostname.toUtf8();

	QByteArray data4;
	data4.append(QString(":%1:")
			.arg(msg->command));
	QByteArray data5 = msg->extend.toUtf8();  
	datagram += data2;
	datagram += data3;
	datagram += data4;
	datagram += data5;

	/*QByteArray *datagram=new QByteArray;
	datagram->append(QString("%1:%2:%3:%4:%5:%6")
			.arg(msg->version)
			.arg(msg->packetno)
			.arg(msg->username)
			.arg(msg->hostname)
			.arg(msg->command)
			.arg(msg->extend));*/
	/*udpSocket = new QUdpSocket(this);
        udpSocket->bind(IPMSG_DEFAULT_PORT);*/

	qDebug()<<"SendUdp:"<<datagram;
	udpSocket->writeDatagram(datagram.data(), (qint64)datagram.size(),
	              msg->address, IPMSG_DEFAULT_PORT);
	              //QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);
}
void Serve::receiveUdp()
{
	qDebug()<<"Begin ReceiveUdp";
	while (udpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		QHostAddress addr;
		quint16 port;
		qDebug()<<"|=------------------------------------------------------------------------=|";
		datagram.resize(udpSocket->pendingDatagramSize());
		udpSocket->readDatagram(datagram.data(), datagram.size(), &addr, &port);
		qDebug()<<"Ip:Port "<<addr<<":"<<port;
		//msgmng->address=addr;
		//开始解码
		int receiveVersion = 1;							//保存解码数据包版本
		unsigned long receivePacketno = 0;   		//保存数据包的编号
		QString receiveUsername = NULL;				//保存解码后的数据包的用户昵称
		QString receiveHostname = NULL;				//保存解码数据包后的主机名
		unsigned long receiveCommand = 0;   		//保存命令字
		QString receiveExtend = NULL;     			//保存附加信息
		if(!datagram.isEmpty())
		{
			QList<QByteArray> list=datagram.split (':');
			QListIterator<QByteArray> i(list);
			for(	int j =0;i.hasNext();j++)
				switch(j)
				{
					case 0:receiveVersion = atoi(i.next());break;
					//case 1:receivePacketno = atoi(stringPacketno=i.next());break;
					case 1:receivePacketno = atoi(i.next());break;
					case 2:receiveUsername = i.next();break;
					case 3:receiveHostname = i.next();break;
					case 4:receiveCommand = atol(i.next());break;
					case 5:receiveExtend = i.next();break;
					default:break;
				}	
		}

		qDebug()<<"ReciveUdp:"<<datagram;
		qDebug()<<"Username:"<<receiveUsername;
		qDebug()<<"Command:"<<receiveCommand;
		qDebug()<<"Hostname:"<<receiveHostname;
		qDebug()<<"Version:"<<receiveVersion;
		qDebug()<<"Packetno:"<<receivePacketno;
		qDebug()<<"Extend:"<<receiveExtend;

		if(receiveUsername==QHostInfo::localHostName())
		{
			msgmng->address=addr;
		}
		unsigned long recvCmd;
		unsigned long recvOpt;
		recvCmd=GET_MODE(receiveCommand);
		qDebug()<<"recvCmd:"<<recvCmd;
		recvOpt=GET_OPT(receiveCommand);
		qDebug()<<"recvOpt:"<<recvOpt;

		MsgMng *msg;
		msg = msgmng->makeMng(receiveUsername, receiveHostname, receiveCommand, receiveExtend, addr);
		//msg = makeMsg(receiveFlag, receiveBag,receiveUserName,receiveHostName, receiveCmd, receiveExtend);

		QByteArray datagramm;
		MsgMng *m;
		m = msgmng->makeMng(receiveUsername, receiveHostname, receiveCommand, receiveExtend, addr);
		//qDebug()<<"receiveCommand :"<<receiveCommand;
		if(recvCmd==IPMSG_SENDMSG || receiveCommand==2097440 || recvCmd==0)
		{
			m->username=QHostInfo::localHostName();
			m->hostname=QHostInfo::localHostName()+"*";
			m->address=addr;
			m->command=33;
			//m->command=IPMSG_ANSENTRY;
			datagramm.append(QString("%1:%2:%3:%4:%5:%6")
				.arg(m->version)
				.arg(receivePacketno)
				.arg(m->username)
				.arg(m->hostname)
				.arg(m->command)
				.arg(receivePacketno));
			qDebug()<<"SSSSendUdp:"<<datagramm;
			udpSocket->writeDatagram(datagramm.data(), (qint64)datagramm.size(),msg->address, IPMSG_DEFAULT_PORT);
		}


		switch (recvCmd)
		{
			case IPMSG_BR_ENTRY:
				msgBrEntry(msg);
				break;

			case IPMSG_BR_EXIT:
				emit msgBrExit(msg);
				break;

			case IPMSG_ANSENTRY:
				msgAnsEntry(msg);
				break;

			case IPMSG_BR_ABSENCE:
				msgBrAbsence(msg);
				break;

			case IPMSG_SENDMSG:
				emit addUser(msg);
				emit msgSendMsg(msg);

			/*	//msg=msgmng->makeMng((QHostInfo::localHostName()),(QHostInfo::localHostName()), 33, (QString)receivePacketno, addr);
				msg->username=QHostInfo::localHostName();
				msg->hostname=QHostInfo::localHostName();
				msg->address=addr;
				msg->command=33;
				//msg->command=IPMSG_ANSENTRY;


				datagramm.append(QString("%1:%2:%3:%4:%5:%6")
					.arg(msg->version)
					.arg(receivePacketno)
					.arg(msg->username)
					.arg(msg->hostname)
					.arg(msg->command)
					.arg(receivePacketno));
				qDebug()<<"SSSSendUdp:"<<datagramm;
				udpSocket->writeDatagram(datagramm.data(), (qint64)datagramm.size(),msg->address, IPMSG_DEFAULT_PORT);*/
				break;

			case IPMSG_RECVMSG:
				msgRecvMsg(msg);
				break;

			case IPMSG_READMSG:
			case IPMSG_ANSREADMSG:
				msgReadMsg(msg);
				break;

			case IPMSG_BR_ISGETLIST2:
				msgBrIsGetList(msg);
				break;

			case IPMSG_OKGETLIST:
				msgOkGetList(msg);
				break;

			case IPMSG_GETLIST:
				msgGetList(msg);
				break;

			case IPMSG_ANSLIST:
				msgAnsList(msg);
				break;

			case IPMSG_GETINFO:
				msgGetInfo(msg);
				break;

			case IPMSG_SENDINFO:
				msgSendInfo(msg);
				break;

			case IPMSG_GETPUBKEY:
				msgGetPubKey(msg);
				break;

			case IPMSG_ANSPUBKEY:
				msgAnsPubKey(msg);
				break;

			case IPMSG_GETABSENCEINFO:
				msgGetAbsenceInfo(msg);
				break;

			case IPMSG_SENDABSENCEINFO:
				msgSendAbsenceInfo(msg);
				break;

			case IPMSG_RELEASEFILES:
				msgReleaseFiles(msg);
				break;
		}
	}	
}
void Serve::sendTcp(MsgMng *msg, QString file)
{
	(void)msg;
	(void)file;
	qDebug()<<"SendTcp file:"<<file;
	sendUdp(msg);
/*unsigned long sendCmd;
unsigned long sendOpt;
sendCmd=GET_MODE(sendCommand);
sendOpt=GET_OPT(sendCommand);


if(sendCmd==IPMSG_BR_ENTRY|sendCmd==IPMSG_BR_ABSENCE)
{
	QByteArray datagram;
	datagram.append("1:120:entry:rizi:1:0");
	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
			 QHostAddress::Broadcast, defaultPort);
	
}
	
if(sendCmd==IPMSG_BR_EXIT)
{
	QByteArray datagram;
	datagram.append("1:120:exit:rizi:2:0");
	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
			 QHostAddress::Broadcast, defaultPort);
	
}
if(sendCmd==IPMSG_ANSENTRY)
{
	QByteArray datagram;
	datagram.append("1:120:answer:rizi:3:0");
	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
			 QHostAddress::Broadcast, defaultPort);
	
}
if(sendCmd==IPMSG_SENDMSG)
{
	QByteArray datagram;
	datagram.append("1:120:message:rizi:32:success");
	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
			 QHostAddress::LocalHost, defaultPort);
	*/

}
void Serve::receiveTcp(){}
void Serve::msgBrEntry(MsgMng *msg)
{
	qDebug()<<"msgBrEntry address:"<<msg->address;
	qDebug()<<"["<<QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))<<"]  "<<msg->username<<"is online."; 
	msg->command=IPMSG_ANSENTRY;
	msg->extend="";
	emit addUser(msg);
	broadcast(msg->command, msg->extend);

	/*	//QSound::play("data/Global.wav");
	
			//显示新用户登录事件
	SubWindow::recordTextEdit->append( "\n[ " + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))
					+ tr(" ]  System information \n\t") + msg->hostSub.userName);
			
			//回送数据包
			sendUdp(IPMSG_ANSENTRY);
			
			//如果用户已经存在，那么不添加
			int count = 0;
			for(count = 0; count < hostStringList->size(); count ++)
			{
				if( (msg->hostSub.hostName == hostStringList->at(count)) &&
								 (msg->hostSub.userName == userListWidget->item(count)->text()) )
				{
					break;
				}
			}
			if(count >= hostStringList->size())
			{
				//hostStringList 保存用户的主机名，userListWidgetItem保存用户昵称，两者一一对应
				hostStringList->append(msg->hostSub.userName);
				userListWidgetItem = new QListWidgetItem(QIcon(":/data/QQ.png"),msg->hostSub.userName,userListWidget);
			}  */
}
/*void Serve::msgBrExit(MsgMng *msg)
{

			for( int count = 0; count < hostStringList->size(); count ++)
			{
				if( (msg->hostSub.hostName == hostStringList->at(count))
									&& (msg->hostSub.userName == userListWidget->item(count)->text()))
				{
					hostStringList->removeAt(count);
					userListWidget->takeItem(count);
					break;
				}
			}
			
			recordTextEdit->append( "\n[ " + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))
					+ tr(" ]  System information \n\t") + msg->hostSub.userName);
			
}*/
void Serve::msgAnsEntry(MsgMng *msg)
{
	emit addUser(msg);
	//emit addUser(msg->hostaddress);
	qDebug()<<"["<<QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))<<"]  "<<msg->username<<"Reply to broadcast  "<<msg->extend; 

}
void Serve::msgBrAbsence(MsgMng *msg){(void)(msg);}
/*void Serve::msgSendMsg(MsgMng *msg)
{	
	qDebug()<<"----msgsendmesssg----";
	qDebug()<<"Username:"<<msg->username;
	recordTextEdit->append("\n[" + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss")) 
			+ tr("]  ") +msg->username+("\n") +message); 
	qDebug()<<"["<<QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))<<"]  "<<msg->username<<"\n"<<msg->extend; 

	
}*/
void Serve::msgRecvMsg(MsgMng *msg){(void)(msg);}
void Serve::msgReadMsg(MsgMng *msg){(void)(msg);}
void Serve::msgBrIsGetList(MsgMng *msg){(void)(msg);}
void Serve::msgOkGetList(MsgMng *msg){(void)(msg);}
void Serve::msgGetList(MsgMng *msg){(void)(msg);}
void Serve::msgAnsList(MsgMng *msg){(void)(msg);}
void Serve::msgGetInfo(MsgMng *msg){(void)(msg);}
void Serve::msgSendInfo(MsgMng *msg){(void)(msg);}
void Serve::msgGetPubKey(MsgMng *msg){(void)(msg);}
void Serve::msgAnsPubKey(MsgMng *msg){(void)(msg);}
void Serve::msgGetAbsenceInfo(MsgMng *msg){(void)(msg);}
void Serve::msgSendAbsenceInfo(MsgMng *msg){(void)(msg);}
void Serve::msgReleaseFiles(MsgMng *msg){(void)(msg);}
void Serve::msgInfoSub(MsgMng *msg){(void)(msg);}


