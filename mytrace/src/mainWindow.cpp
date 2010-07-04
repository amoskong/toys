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

#include <stdlib.h>
#include "mainWindow.h"
#include <QDebug>
#include <QProcess>
#include <QTime>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/user.h>
#include <sys/syscall.h> /* For SYS_write etc */
#include <asm/ptrace.h>/*define ORIG_EAX 11*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>


//初始化窗口
MainWindow::MainWindow()
{
	pid_t p;
	initWindow();
	if((p=fork())<0)
		printf("foooooooooooooooooooooooooooooooooooork fail!\n");
	else if(p==0)	
		system("./trace");
	/*if((p=fork())<0)
	  printf("foooooooooooooooooooooooooooooooooooork fail!\n");
	  else if(p==0)	//test();
	  system("./rule");*/

	QTimer *timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(refurbish()));
	timer->start(3000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	system("killall strace");
	system("killall trace");
	system("killall rule");
	qDebug()<<"closeEvent()------------------------------------";
	event->accept();
}

//关于
void MainWindow::about()
{
	QMessageBox::information(this, tr("About"),tr("This project is on Linux+QT4 platform, which was used for listen of processes on system. It is written for KDE envirenment. This software is released under GPL lisence, for more details about the license, please see the content of file COPYING."));
	/*recordTextEdit->append("This project is on Linux+QT4 platform, which was used for listen of processes on system. It is written for KDE envirenment. This software is released under GPL lisence, for more details about the license, please see the content of file COPYING.");*/

}


//刷新
void MainWindow::refurbish()
{

	pidListWidget->clear();
	pidListWidgetItem = new QListWidgetItem(QIcon(":/blank.png"), tr("NAME\t\t\t\t")+tr("PID\tSYSCALL"), pidListWidget);
	pidListWidgetItem->setBackground(Qt::cyan);
	int flag_color=1;

	FILE * fp;
	FILE *fp3;
	char line3[123];
	int i=0;
	DIR *dir;
	char logname[30]="";
	struct stat st; /*文件属性*/
	size_t fsize;/*文件大小*/
	char p_name[128]="";
	char pid[10]="";
	char pid2[200]="";
	struct dirent *ptr;

	dir = opendir("log/");
	while((ptr = readdir(dir))!= NULL)
	{ 
		if(!strcmp(ptr->d_name,"..") || !strcmp(ptr->d_name,"."))
			continue;
		memset(logname, 0, sizeof(logname));
		strcat(logname,"log/");
		strcat(logname,ptr->d_name);

		stat(logname,&st);
		fsize=st.st_size;/*获取文件大小*/
		if(fsize==0)
			continue;

		fp = fopen(logname, "r");
		if (fp == NULL){
			printf("Fp =================================================== NULL\n");
			break;			
		}
		i=0;	
		fseek(fp,-150L,SEEK_END);
		while(i<150 && fgetc(fp)!='\n' && !feof(fp)) i++;
		i=0;
		int flag=0;
		memset(line3, 0, sizeof(line3));
		while(i<150 && (line3[i]=fgetc(fp))!='\n' && !feof(fp)){ if(line3[i]!=' ') flag=1; if(flag==1) i++;}
		line3[i]='\0';
		if((i+48)=='0'){  
			memset(line3, 0, sizeof(line3));
			fseek(fp,0L,SEEK_SET);
			while(i<50 && (line3[i]=fgetc(fp))!='\n' && !feof(fp)){ if(line3[i]!=' ') flag=1; if(flag==1) i++;}
			line3[i]='\0';
		}

		memset(pid, 0, sizeof(pid));
		strcat(pid,ptr->d_name);
		strcpy(strstr(pid,".log"),"");
		if((fp3=fopen("cmd.txt","r"))==NULL){
			printf("Fp =================================================== NULL\n");
			break;	
		}

		do{
			i=0;
			while(i<128 && (pid2[i]=fgetc(fp3))!='\n') i++;
			pid2[i]='\0';	
			i=0;
			while(pid2[i]!='\t'&& pid2[i]!='\0') i++;
			int j,k;
			j=k=i+1;

			i=0;
			memset(p_name, 0, sizeof(p_name));
			while(pid2[k]!='\0'){
				p_name[i]=pid2[k];
				i++;k++;
			}
			pid2[j-1]='\0';
			p_name[i-1]='\0';
			int Len=46;
			while(i<Len){
				p_name[i-1]='_';i++;
			}
			p_name[Len]='\0';

		}while(strcmp(pid2,pid) && !feof(fp3));
		pidListWidgetItem = new QListWidgetItem(QIcon(":/pid.png"),p_name+tr("\t")+pid+tr("\t")+line3, pidListWidget);
		if(flag_color==1){
//			pidListWidgetItem->setBackground(Qt::cyan);
			pidListWidgetItem->setBackground(Qt::lightGray);
			flag_color=0;
		}
		else
			flag_color=1;

		fclose(fp3);
		fclose(fp);
		fp=fp3=NULL;
	}

	closedir(dir);
	dir=NULL;
	printf("---\n");
	fflush(stdout);
	return ;
}

//初始化界面和程序基本信息
void MainWindow::initWindow()
{   
	resize(920,720);
	//setMinimumSize(220,480);
	//setMaximumSize(220,480);

	setWindowTitle(tr("Listen to Processes")); 
	messageWindow = new QWidget(this);
	messageWindow->resize(670,910);
	//messageWindow->setMinimumSize(200,600);
	//messageWindow->setMaximumSize(200,600);

	//关于按钮
	aboutButton = new QPushButton(tr("&About"),messageWindow);
	connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));

	//刷新按钮
	refurbishButton = new QPushButton(tr("&Refurbish"),messageWindow);
	connect(refurbishButton, SIGNAL(clicked()), this, SLOT(refurbish()));

	pidListWidget = new QListWidget(messageWindow);
	pidListWidget->setMinimumSize(900,670);
	pidListWidget->setMaximumSize(900,670);

	//退出按钮
	quitButton = new QPushButton(tr("&Quit"),messageWindow);
	connect(quitButton,SIGNAL(clicked()), this, SLOT(close()));

	//布局
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(aboutButton);
	buttonLayout->addWidget(refurbishButton);
	buttonLayout->addWidget(quitButton);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(pidListWidget,0,0);
	mainLayout->addLayout(buttonLayout,1,0,1,2);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	messageWindow->setLayout(mainLayout);
	messageWindow->show();
}


