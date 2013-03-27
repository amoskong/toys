/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：mainWindow.cpp
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 

#include <stdlib.h>
#include "mainWindow.h"
#include <QHostInfo>
#include <QDebug>

//初始化登录窗口
MainWindow::MainWindow()
{
	initWindow();
	//initServer();
	usercount = 0;
	initUp();
  	connect(service, SIGNAL(addUser(MsgMng *)) , this, SLOT(addUserList(MsgMng *)));

  	connect(service, SIGNAL(msgBrExit(MsgMng *)) , this, SLOT(delUserList(MsgMng *)));
}

void MainWindow::initServer()
{

	/*//监听UDP数据包，如果有数据包抵达调用receiveessag槽进行处理
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(IPMSG_DEFAULT_PORT);
	qDebug()<<"Port:"<<IPMSG_DEFAULT_PORT;

	//tcpSocket = new QTcpSocket(this);
	//tcpSocket->bind(IPMSG_DEFAULT_PORT);
	//connect(udpSocket, SIGNAL(readyRead()), , SLOT(receiveUdp()));
	//connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(service->receiveTcp()));	
	service->broadcast(IPMSG_BR_ENTRY, NULL);*/
}
void MainWindow::initUp()
{

	//hostStringList = new QStringList();
	service=new Serve;
/*	hostStringList = new QStringList();
	//监听UDP数据包，如果有数据包抵达调用receiveessag槽进行处理
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(IPMSG_DEFAULT_PORT);
	//tcpSocket = new QTcpSocket(this);
	//tcpSocket->bind(IPMSG_DEFAULT_PORT);
	//connect(udpSocket, SIGNAL(readyRead()), this, SLOT(recvUdp()));
	//connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(service->receiveTcp()));   
	//service->broadcast(IPMSG_BR_ENTRY, NULL); */

}

void MainWindow::exit()
{
	/*MsgMng *msg = new MsgMng;
        msg->command = IPMSG_BR_EXIT;
        msg->extend="";
	service->broadcast(6291458, NULL);
        //接受信号，执行退出
	 event->accept();*/

}

//根据sublist显示用户到列表
void MainWindow::showuserlist()
{
	userListWidget->clear();
	//void removeItemWidget ( QListWidgetItem * item )
	qDebug()<<"UserCount:"<<usercount;

	foreach(QString str, sublist)
	{
		qDebug()<<"User:"<<str;
		//QStringList s=str.split(":"); 
		//QStringList s=str.split(":"); 
		//userListWidgetItem = new QListWidgetItem(QIcon(":/data/QQ.png"),s.at(1),userListWidget);
		if (str.endsWith("*"))
			userListWidgetItem = new QListWidgetItem(QIcon(":/data/openimage.png"), str, userListWidget);
		else
			userListWidgetItem = new QListWidgetItem(QIcon(":/data/ipmsg.png"), str, userListWidget);
		//userListWidgetItem = new QListWidgetItem(QIcon(":/data/QQ.png"),u.toString,userListWidget);
	}
}

void MainWindow::addSub(QListWidgetItem *u)
{
	//QHostAddress addr=QHostAddress::LocalHost;
	//QHostAddress addr=u.text();
	qDebug()<<"u->text:"<<u->text();
	/*QStringList s=(u->text()).split(":"); 
	QHostAddress addr=(QHostAddress)s.at(0);
	qDebug()<<"s.at(0) address:"<<s.at(0);*/
	QString str=u->text();
	qDebug()<<"str:"<<str;
	if(subislist[str]!=1)
	{
		sub = new SubWindow(service, u->text());
  		connect(sub , SIGNAL(delSub(QString)) , this, SLOT(delSub(QString)));
		sub->show();
		subislist[str]=1;
	}
}

//关闭子窗口
void MainWindow::delSub(QString str)
{

	qDebug()<<"MainWindow::delSub(QString str)";
	subislist[str]=0;

}

//添加用户到sublist
void MainWindow::addUserList(MsgMng *msg)
//void MainWindow::addUserList(QHostAddress addr,QString username)
{	
	//if(usercount<1){
	//if(msg->username == "ubuntu")
	QHostInfo info=QHostInfo::fromName("localhost");                                                                                       
        /*if( 0 && usercount<1 && info.addresses().indexOf(msg->address)){
		qDebug()<<"Don't Add Localhost to UserList";                       
        }
	else
	{*/
		qDebug()<<"AddUserList:"<<msg->address<<":"<<msg->username;
		//userListWidgetItem = new QListWidgetItem(QIcon(":/data/openimage.png"), msg->username, userListWidget);
		QString str;
		if (msg->hostname == msg->username+"*")
			str=msg->address.toString()+":"+msg->username+"*";
		else
			str=msg->address.toString()+":"+msg->username;
		qDebug()<<"AddUserList: msg->command:"<<msg->command;
		qDebug()<<"subislist[str1]:" << subislist[str];
		/*foreach((int i, subislist)
		{
			if(subislist[str]==0) //subWindows is not exist
			{
			//qDebug()<<"sublist.insert(usercount, str):"<<usercount<<"++"<<str;
			}
			else
			{	
			//	sub = new SubWindow(service,str);
				subislist.insert(str, 0);
			}
		}*/

		if(msg->command==288)
		{
			/*foreach(int i, subislist)
			{*/
				if(subislist[str]==0) //subWindows is not exist
				{
			//qDebug()<<"sublist.insert(usercount, str):"<<usercount<<"++"<<str;
					sub = new SubWindow(service,str);
  					connect(sub , SIGNAL(delSub(QString)) , this, SLOT(delSub(QString)));
					sub->show();
					subislist[str]=1;
				}
			//}
		}

		foreach(QString s, sublist)
			if(!s.compare(str))
				return ;

		qDebug()<<"sublist.insert(usercount, str):"<<usercount<<"++"<<str;
		sublist.insert(usercount, str);
		subislist.insert(str, 0);
		qDebug()<<"subislist[str2]:" << subislist[str];

		//sublist.insert(usercount, msg->address.toString());
		//sublist.insert(msg->address, msg->username+":"+usercount);

		//userstringlist << msg->username;
		//hostStringList << msg->address;
	//}
	//qDebug()<<"msg->address:"<<msg->address<<" LocalHost:"<< fromName("localhost");
	usercount++;
	showuserlist();

}

//把用户从列表删除
void MainWindow::delUserList(MsgMng *msg)
{
	QString str=msg->address.toString()+":"+msg->username;
	int i=0;
	foreach(QString s, sublist)
	{	
		qDebug()<<"i:"<<i;
		if(!s.compare(str))
		{
			sublist.remove(i);
			usercount--;
			qDebug()<<"sublist.remove(i):"<<str<<"++"<<i;
		}
		i++;
	}
	//qDebug()<<"sublist[str]:"<<sublist[str];
	/*sublist.remove(sublist.(str));
	sublist.remove(0);
	sublist.remove(1);
	sublist.remove(2);*/

	showuserlist();
	/*foreach(QString s, sublist)
		if(!s.compare(str))
			return ;*/
	qDebug()<<"delUserList()---------------";
}

/*
   void MainWindow::recvUdp()
   {
//service = new Serve(); 
//service->receiveUdp();
}

void MainWindow::recvTcp()
{
//service = new Serve();
//service->receiveTcp();
}
*/

void MainWindow::closeEvent(QCloseEvent *event)
{
	qDebug()<<"closeEvent()------------------------------------";
	MsgMng *msg = new MsgMng;
        msg->command = IPMSG_BR_EXIT;
        msg->extend="";
	service->broadcast(6291458, NULL);
	//service->broadcast(IPMSG_BR_EXIT, NULL);
	service->udpSocket->close();
	event->accept();
}

//关于Pigeons
void MainWindow::about()
{
	QMessageBox::information(this, tr("About"),tr("This project is on Linux+QT4 platform, which was used for transfer files on Internet, providing communication with IP MSG, FeiQ or other clients. It is written for KDE envirenment. This software is released under GPL lisence, for more details about the license, please see the content of file COPYING."));
}

//刷新用户列表
void MainWindow::refurbish()
{	
	service->broadcast(6291457, NULL);
	int i=0;
 	foreach(QString s, sublist)
        {
		sublist.remove(i);
		usercount--;
                i++;
        }

	showuserlist();
}

void MainWindow::enabledSendButton()
{
	sendButton->setEnabled(true);
}

//槽函数，打开图片文件
void MainWindow::openImage()
{
	//实现图像同步的策略为，先复制图像到自己和别人机器的 temp-image/ 下，然后在数据包中加入HTML的显示本地图像代码
	QString image = QFileDialog::getOpenFileName(this, tr("Open Image File..."),
			"temp-image/", tr("Image-Files (*.png *.gif *.bmp *.jpeg *.jpg)"));
	QFile::copy(image, QString("temp-image/") + QFileInfo(image).fileName());
	if (image.isEmpty())
	{
		return;
	}
	inputTextEdit->append("<img src='temp-image/" + QFileInfo(image).fileName() + "'  />");
	//广播图片	
	QByteArray datagram;
	QDataStream out(&datagram,QIODevice::WriteOnly);

	out << 4;

	out << QFileInfo(image).fileName();

	QImageReader imageReader(image);
	imageReader.setFormat(QFileInfo(image).suffix().toAscii());
	out <<  imageReader.read();

	udpSocket->writeDatagram(datagram.data(), qint64(datagram.size()),
				 QHostAddress::Broadcast, IPMSG_DEFAULT_PORT);
}

//设置字体颜色
void MainWindow::setFontColor()
{
	QColor col = QColorDialog::getColor(inputTextEdit->textColor(), this);
	if (!col.isValid())
	{
		return;
	}
	inputTextEdit->setTextColor(col);
	
	QPixmap pix(16, 16);
	pix.fill(col);
	colorButton->setIcon(pix);
}

//槽函数，设置字体大小
void MainWindow::setFontSize(const QString &size)
{
	inputTextEdit->setFontPointSize(size.toFloat());
}

//槽函数，设置输入字体为粗体
void MainWindow::setBoldFont(bool flag)
{
	if(flag == true)
	{
		inputTextEdit->setFontWeight(QFont::Bold);
	}
	else
		inputTextEdit->setFontWeight(QFont::Normal);
}

//初始化聊天室界面和程序基本信息
void MainWindow::initWindow()
{   
	resize(220,480);
        //setMinimumSize(220,480);
        //setMaximumSize(220,480);

        setWindowTitle(tr("Pigeons")); 
	messageWindow = new QWidget(this);
	messageWindow->resize(200,600);
   	//messageWindow->setMinimumSize(200,600);
	//messageWindow->setMaximumSize(200,600);
	//messageWindow->setWindowTitle(tr("localqq"));
	
	/*f(){
	recordTextEdit = new QTextEdit(messageWindow);
	recordTextEdit->setReadOnly(true);
	recordTextEdit->setMinimumSize(600,300);

	inputTextEdit = new QTextEdit(messageWindow);
	inputTextEdit->setMinimumSize(490,100);
	inputTextEdit->setMaximumSize(600,180); 

	editToolBar = new QToolBar(messageWindow);

	//编辑工具栏上的字体
	fontComboBox = new QComboBox(editToolBar);
	editToolBar->addWidget(fontComboBox);
	fontComboBox->setEditable(true);
	QFontDatabase fontDB;
	fontComboBox->addItems(fontDB.families());
	connect(fontComboBox, SIGNAL(activated(const QString &)),
	inputTextEdit, SLOT(setFontFamily(const QString &)));
	fontComboBox->setCurrentIndex(fontComboBox->findText(QApplication::font().family()));

	//编辑工具栏的字体大小
	sizeComboBox = new QComboBox(editToolBar);
	editToolBar->addWidget(sizeComboBox);
	sizeComboBox->setEditable(true);
	foreach(int size, fontDB.standardSizes())
		sizeComboBox->addItem(QString::number(size));
	connect(sizeComboBox, SIGNAL(activated(const QString &)),
		this, SLOT(setFontSize(const QString &)));
	sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(QApplication::font().pointSize())));

	//粗体
	boldButton = new QToolButton(editToolBar);
	editToolBar->addWidget(boldButton);
	boldButton->setCheckable(true);
	boldButton->setIcon(QIcon(":/data/textbold.png"));
	connect(boldButton, SIGNAL(toggled(bool)), this, SLOT(setBoldFont(bool)));

	//斜体
	italicButton = new QToolButton(editToolBar);
	editToolBar->addWidget(italicButton);
	italicButton->setCheckable(true);
	italicButton->setIcon(QIcon(":/data/textitalic.png"));
	connect(italicButton, SIGNAL(toggled(bool)), inputTextEdit, SLOT(setFontItalic(bool)));

	//下划线
	underlineButton = new QToolButton(editToolBar);
	editToolBar->addWidget(underlineButton);
	underlineButton->setCheckable(true);
	underlineButton->setIcon(QIcon(":/data/textunder.png"));
	connect(underlineButton, SIGNAL(toggled(bool)), inputTextEdit, SLOT(setFontUnderline(bool)));

	//颜色
	colorButton = new QToolButton(editToolBar);
	editToolBar->addWidget(colorButton);
	colorButton->setIcon(QIcon(":/data/textcolor.png"));
	connect(colorButton, SIGNAL(clicked()), this, SLOT(setFontColor()));

	//打开图片
	imageButton = new QToolButton(editToolBar);
	editToolBar->addWidget(imageButton);
	imageButton->setIcon(QIcon(":/data/openimage.png"));
	connect(imageButton, SIGNAL(clicked()), this, SLOT(openImage()));//


	//发送按钮
	sendButton = new QPushButton(tr("&Send"), messageWindow);
	sendButton->setEnabled(false);
	connect(inputTextEdit, SIGNAL(textChanged()), this, SLOT(enabledSendButton()));
	//connect(sendButton, SIGNAL(clicked()), this, SLOT(service->sendUdp()));// 
	} */

	//关于按钮
	aboutButton = new QPushButton(tr("&About"),messageWindow);
	connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));

	//刷新按钮
	refurbishButton = new QPushButton(tr("&Rrfurbish"),messageWindow);
	connect(refurbishButton, SIGNAL(clicked()), this, SLOT(refurbish()));

	//用户昵称表
	userListWidget = new QListWidget(messageWindow);
	showuserlist();
	userListWidget->setMinimumSize(190,430);
	userListWidget->setMaximumSize(200,600);
	connect(userListWidget, SIGNAL(itemDoubleClicked (QListWidgetItem*)),this,SLOT(addSub(QListWidgetItem *)));//


	//退出按钮
	quitButton = new QPushButton(tr("&Quit"),messageWindow);
	connect(quitButton,SIGNAL(clicked()), this, SLOT(close()));
			
	//布局
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(aboutButton);
	//buttonLayout->addStretch(3);
	//buttonLayout->addWidget(sendButton);
	//buttonLayout->addStretch(1);
	buttonLayout->addWidget(refurbishButton);
	buttonLayout->addWidget(quitButton);

//	QVBoxLayout *leftLayout = new QVBoxLayout;
	//leftLayout->addWidget(recordTextEdit);
	//leftLayout->addWidget(editToolBar);
	//leftLayout->addWidget(inputTextEdit);

	QGridLayout *mainLayout = new QGridLayout;
//	mainLayout->addLayout(leftLayout,0,0);
//	mainLayout->addWidget(userListWidget,0,1);
//	mainLayout->addLayout(buttonLayout,1,0,1,2);
//	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(userListWidget,0,0);
	mainLayout->addLayout(buttonLayout,1,0,1,2);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	
	messageWindow->setLayout(mainLayout);
	messageWindow->show();
}


