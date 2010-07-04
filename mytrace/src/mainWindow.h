/***************************************************************
 *
 * Copyright (c) 2008
 * 文件名称：mainWindow.cpp
 * 摘    要：
 * 当前版本：V1.0
 * 作    者：
 * 完成日期：2008.8
 *
 ***************************************************************/ 

#include <QtGui>
#include <QDebug>

class MainWindow : public QWidget 
{
	Q_OBJECT
			
	public:
		MainWindow();
		//初始化聊天室
		void initWindow();	
		//聊天室窗口
		QWidget *messageWindow;
		//显示聊天记录的文本编辑框
		//QTextEdit *recordTextEdit;
		//输入文本编辑框
		//QTextEdit *inputTextEdit;

		QListWidget *pidListWidget;
		QListWidgetItem *pidListWidgetItem;
		//关于按钮
		QPushButton *aboutButton;

		QPushButton *refurbishButton;
		//退出按钮
		QPushButton *quitButton;
		
		//保存收发的消息
		QString message;
		//处理系统关闭事件
		void closeEvent(QCloseEvent *event);

	public slots:
		//关于
		void about();
		//刷新
		void refurbish();
	private slots:
		//void recvTcp();

};

