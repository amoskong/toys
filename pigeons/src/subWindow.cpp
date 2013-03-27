#include "subWindow.h"

//构造函数，初始化登录窗口
SubWindow::SubWindow(Serve *ser, QString str)
{
	initialize();
	service = ser;
	msgmng = new MsgMng;

        QStringList s=str.split(":"); 
        qDebug()<<"s.at(0) address:"<<s.at(0);
	msgmng->username = s.at(1);
	msgmng->hostname = s.at(1);
	msgmng->address = (QHostAddress)s.at(0);
	connect(service, SIGNAL(msgSendMsg(MsgMng *)) , this, SLOT(showMessage(MsgMng *)));
}

void SubWindow::showMessage(MsgMng *msg)
{
	qDebug()<<"["<<QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss")<<"]  "<<msg->username<<":\n"<<msg->extend;
	recordTextEdit->append("[" + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))
		                                        + tr("]  ") +msg->username+" :");
	recordTextEdit->append(msg->extend);
}
	
//处理关闭事件
void SubWindow::closeEvent(QCloseEvent *event)
{
	//广播用户注销信息
	/*MsgMng *msg = new MsgMng;
	msg->command = IPMSG_BR_EXIT;
	msg->extend="";
	service->broadcast(6291458, NULL);*/

	QString str=msgmng->address.toString()+":"+msgmng->username;
	emit delSub(str);
	qDebug()<<"emit delSub(str)";
	//service->udpSocket->close();
	//接受信号，执行退出
	event->accept();
}

//发送消息
void SubWindow::sendMessage()
{	
	qDebug()<<"sendMessage():"<<msgmng->hostname<<":"<<msgmng->username;
	if(msgmng->hostname.endsWith("*"))
	        message = inputTextEdit->toHtml();
	else
		message = inputTextEdit->toPlainText();
	//char *m =  inputTextEdit->toPlainText();
	//message=message.toUtf8(); 
	//message = m->fromUtf8(m, -1);
	recordTextEdit->append("[" + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))
		                                        + tr("]  ") + (QHostInfo::localHostName()));
	recordTextEdit->append(message);
	//connect(fontComboBox, SIGNAL(activated(const QString &)),inputTextEdit, SLOT(setFontFamily(const QString &)));
	MsgMng *msg = new MsgMng;
	//msg->command=IPMSG_SENDMSG;
	msg->command=288;
	//msg->command=33;
	msg->extend=message;
	msg->address=msgmng->address;
	//QString str=msg->address.toString()+":"+msg->username;
	qDebug()<<"sendMessage() msgmng->address"<<msgmng->address;
	qDebug()<<"sendMessage() msg->address"<<msg->address;
	service->sendUdp(msg);
	qDebug()<<"End of sendUdp";
	//清除发送框
        inputTextEdit->clear();

}

//关于本程序
void SubWindow::about()
{
	QMessageBox::information(this, tr("About"),tr("This project is on Linux+QT4 platform, which was used for transfer files on Internet, providing communication with IP MSG, FeiQ or other clients. It is written for KDE envirenment. This software is released under GPL lisence, for more details about the license, please see the content of file COPYING."));
}

//激活发送按钮
void SubWindow::enabledSendButton()
{
	sendButton->setEnabled(true);
}

//设置字体颜色
void SubWindow::setFontColor()
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

//槽函数，打开图片文件
void SubWindow::openImage()
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
}

void SubWindow::sendFile()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Send File..."),
			"~", tr("Image-Files (*)"));
	//QFile::copy(image, QString("temp-image/") + QFileInfo(image).fileName());
	if (file.isEmpty())
	{
		qDebug()<<"file is empty";
		return;
	}

	recordTextEdit->append("[" + QDateTime::currentDateTime().toString(tr("yyyy-MM-dd  hh:mm:ss"))
		                                        + tr("]  ") + (QHostInfo::localHostName())+tr(":\n") +"Send File: "+file);
	//inputTextEdit->append("Send file: "+file);
	//inputTextEdit->append("Send file: "+QFileInfo(file).fileName());
	MsgMng *msg = new MsgMng;
	//msg->command=IPMSG_SENDMSG;
	msg->command=2097440;
	//msg->command=33;
	msg->extend=message;
	msg->address=msgmng->address;
	//QString str=msg->address.toString()+":"+msg->username;
	qDebug()<<"sendMessage() msgmng->address"<<msgmng->address;
	qDebug()<<"sendMessage() msg->address"<<msg->address;
	service->sendTcp(msg, file);
	qDebug()<<"End of sendTcp";


}
//槽函数，设置字体大小
void SubWindow::setFontSize(const QString &size)
{
	inputTextEdit->setFontPointSize(size.toFloat());
}

//槽函数，设置输入字体为粗体
void SubWindow::setBoldFont(bool flag)
{
	if(flag == true)
	{
		inputTextEdit->setFontWeight(QFont::Bold);
	}
	else
		inputTextEdit->setFontWeight(QFont::Normal);
}

//初始化聊天室界面和程序基本信息
void SubWindow::initialize()
{
	
	resize(620,600);
	setMinimumSize(620,600);
	setMaximumSize(620,600);
	setWindowTitle(tr("Pigeons by Xiyou-Linux-Group"));

	messageWindow = new QWidget(this);
	messageWindow->resize(620,600);
	messageWindow->setMinimumSize(620,600);
        messageWindow->setMaximumSize(620,600);
	
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
	connect(imageButton, SIGNAL(clicked()), this, SLOT(openImage()));
	
	//发送文件
	fileButton = new QToolButton(editToolBar);
	editToolBar->addWidget(fileButton);
	fileButton->setIcon(QIcon(":/data/file.png"));
	connect(fileButton, SIGNAL(clicked()), this, SLOT(sendFile()));

	//发送按钮
	sendButton = new QPushButton(tr("&Send"), messageWindow);
	sendButton->setEnabled(false);
	connect(inputTextEdit, SIGNAL(textChanged()), this, SLOT(enabledSendButton()));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

	//关于按钮
	aboutButton = new QPushButton(tr("&About"),messageWindow);
	connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));

	//用户昵称表
	//userListWidget = new QListWidget(messageWindow);
	//userListWidget->setMinimumSize(120,420);
	//userListWidget->setMaximumSize(180,600);

	//退出按钮
	quitButton = new QPushButton(tr("&Quit"),messageWindow);
	connect(quitButton,SIGNAL(clicked()), this, SLOT(close()));
			
	//布局
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(aboutButton);
	buttonLayout->addStretch(3);
	buttonLayout->addWidget(sendButton);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(quitButton);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(recordTextEdit);
	leftLayout->addWidget(editToolBar);
	leftLayout->addWidget(inputTextEdit);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addLayout(leftLayout,0,0);
	//mainLayout->addWidget(userListWidget,0,1);
	mainLayout->addLayout(buttonLayout,1,0,1,2);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	messageWindow->setLayout(mainLayout);
	messageWindow->show();
}

