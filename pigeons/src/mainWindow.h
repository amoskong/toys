/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：mainWindow.h
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
#include "subWindow.h"

class MainWindow : public QWidget 
{
	Q_OBJECT
			
	public:
		MainWindow();
		//初始化聊天室
		void initWindow();
		//聊天室窗口
		void initUp();
		void exit();
		void showuserlist();
		QWidget *messageWindow;
		//显示聊天记录的文本编辑框
		QTextEdit *recordTextEdit;
		//输入文本编辑框
		QTextEdit *inputTextEdit;
		//关于按钮
		QPushButton *aboutButton;

		QPushButton *refurbishButton;
  		//发送按钮
		QPushButton *sendButton;
		//退出按钮
		QPushButton *quitButton;
		//右侧的用户列表，保存其他用户的登录昵称
		
		int usercount;
		//QStringList userstringlist;
		QListWidget *userListWidget;
		QListWidgetItem *userListWidgetItem;
		QMap <int, QString> sublist;//hostaddress, username:usercount
		QMap <QString, int> subislist;//
		//QMap <QHostAddress , QString> sublist;//hostaddress, username:usercount
		CfgAllDialog cfgall;
		Serve *service;

		//编辑inpuTextEdit的包括字体，颜色等行为的工具栏
		QToolBar *editToolBar;
		QComboBox *fontComboBox;
		QComboBox *sizeComboBox;
		QToolButton *boldButton;
		QToolButton *italicButton;
		QToolButton *underlineButton;
		QToolButton *colorButton;
		QToolButton *imageButton;

		//UDP连接用的socket
		QUdpSocket *udpSocket;
		QTcpSocket *tcpSocket;
		//保存收发的消息
		QString message;
		//保存当前聊天室用户列表的主机名（为扩展：下一版本用TCP实现单对单聊天，这个是连接的关键）
		//QStringList *hostStringList;
		//处理系统关闭事件
		void closeEvent(QCloseEvent *event);

	public slots:
 		//设置字体尺寸
		void setFontSize(const QString &);
		//设置粗体
		void setBoldFont(bool);
		//设置字体颜色
		void setFontColor();
		//打开图像文件
		void openImage();
		//开启发送按钮
		void enabledSendButton();
		//关于
		void about();
		//刷新
		void refurbish();
		void delSub(QString str);
	private:
		SubWindow *sub;

		QPushButton cfgAllButton;
	private slots:
		void initServer();
		void addSub(QListWidgetItem *u);

		void addUserList(MsgMng *msg);
		void delUserList(MsgMng *msg);
		//void recvUdp();
		//void recvTcp();

};

