/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：subWindow.h
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
#include "serve.h"

class SubWindow : public QDialog
{
	Q_OBJECT

	public:
		SubWindow(Serve *ser,QString str);
		Serve *service;
		MsgMng *msgmng;
	signals:
		void delSub(QString str);
	public slots:
		void showMessage(MsgMng *msg);
		//void showMessage(QString msg, QString user);
	private:
		QWidget *messageWindow;
		//处理系统关闭事件
		void closeEvent(QCloseEvent *event);
		//根据flag编码UDP数据包并发送之
		void writeData(int flag);

		//显示聊天记录的文本编辑框
		QTextEdit *recordTextEdit;
		//输入文本编辑框
		QTextEdit *inputTextEdit;
		QString message;
		//关于按钮和发送按钮
		QPushButton *aboutButton;
		QPushButton *sendButton;
		//右侧的用户列表，保存其他用户的登录昵称
		QListWidget *userListWidget;
		QListWidgetItem *userListWidgetItem;
		//退出按钮
		QPushButton *quitButton;
		//编辑inpuTextEdit的包括字体，颜色等行为的工具栏
		QToolBar *editToolBar;
		QComboBox *fontComboBox;
		QComboBox *sizeComboBox;
		QToolButton *boldButton;
		QToolButton *italicButton;
		QToolButton *underlineButton;
		QToolButton *colorButton;
		QToolButton *imageButton;
		QToolButton *fileButton;
	private slots:

		//初始化聊天室
		void initialize();
		//设置字体尺寸
		void setFontSize(const QString &);
		//设置粗体
		void setBoldFont(bool);
		//设置字体颜色
		void setFontColor();
		//打开图像文件
		void openImage();
		//选择发送文件
		void sendFile();
		//开启发送按钮
		void enabledSendButton();
		//关于
		void sendMessage();
		void about();
};
