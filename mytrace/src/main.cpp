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

#include <QApplication>
#include "mainWindow.h"

int main( int argc, char *argv[])
{
	Q_INIT_RESOURCE(resource);
	QApplication app( argc, argv);

	MainWindow mainwindow;
	mainwindow.show();

	return app.exec();
}
