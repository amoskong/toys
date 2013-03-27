/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：main.cpp
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 

#include <QApplication>
#include "mainWindow.h"

int main( int argc, char *argv[])
{
	Q_INIT_RESOURCE(resource);

	QApplication app( argc, argv);

	//加载翻译文件
	QTranslator translator;
	translator.load(":/data/zh_CN");
	app.installTranslator(&translator);
	
	MainWindow mainwindow;
	mainwindow.show();

	return app.exec();
}
