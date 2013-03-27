/***************************************************************
 *
 * Copyright (c) 2008 西安邮电学院Linux兴趣小组
 * 文件名称：ipmsg.h
 * 摘    要：
 * 当前版本：
 * 作    者：
 * 完成日期：
 *
***************************************************************/ 

#ifndef IPMSG_H
#define IPMSG_H
#include <QtNetwork>                                                                                                                           
#include <QTime>
#include <QtGui>
//IP Messenger 通信协议V1.2定义

//宏
#define GET_MODE(command)	(command & 0x000000ffUL)
#define GET_OPT(command)	(command & 0xffffff00UL)

//首部
#define IPMSG_VERSION			0x0001
#define IPMSG_DEFAULT_PORT		0x0979

//命令
#define IPMSG_NOOPERATION		0x00000000UL

#define IPMSG_BR_ENTRY			0x00000001UL
#define IPMSG_BR_EXIT			0x00000002UL
#define IPMSG_ANSENTRY			0x00000003UL
#define IPMSG_BR_ABSENCE		0x00000004UL

#define IPMSG_BR_ISGETLIST		0x00000010UL
#define IPMSG_OKGETLIST			0x00000011UL
#define IPMSG_GETLIST			0x00000012UL
#define IPMSG_ANSLIST			0x00000013UL
#define IPMSG_BR_ISGETLIST2		0x00000018UL

#define IPMSG_SENDMSG			0x00000020UL
#define IPMSG_RECVMSG			0x00000021UL
#define IPMSG_READMSG			0x00000030UL
#define IPMSG_DELMSG			0x00000031UL
#define IPMSG_ANSREADMSG		0x00000032UL

#define IPMSG_GETINFO			0x00000040UL
#define IPMSG_SENDINFO			0x00000041UL

#define IPMSG_GETABSENCEINFO		0x00000050UL
#define IPMSG_SENDABSENCEINFO		0x00000051UL

#define IPMSG_GETFILEDATA		0x00000060UL
#define IPMSG_RELEASEFILES		0x00000061UL
#define IPMSG_GETDIRFILES		0x00000062UL

#define IPMSG_GETPUBKEY			0x00000072UL
#define IPMSG_ANSPUBKEY			0x00000073UL

//所有命令选项
#define IPMSG_ABSENCEOPT		0x00000100UL
#define IPMSG_SERVEROPT			0x00000200UL
#define IPMSG_DIALUPOPT			0x00010000UL
#define IPMSG_FILEATTACHOPT		0x00200000UL
#define IPMSG_ENCRYPTOPT		0x00400000UL
#define IPMSG_UTF8OPT			0x00800000UL

//发送命令选项
#define IPMSG_SENDCHECKOPT		0x00000100UL
#define IPMSG_SECRETOPT			0x00000200UL
#define IPMSG_BROADCASTOPT		0x00000400UL
#define IPMSG_MULTICASTOPT		0x00000800UL
#define IPMSG_NOPOPUPOPT		0x00001000UL
#define IPMSG_AUTORETOPT		0x00002000UL
#define IPMSG_RETRYOPT			0x00004000UL
#define IPMSG_PASSWORDOPT		0x00008000UL
#define IPMSG_NOLOGOPT			0x00020000UL
#define IPMSG_NEWMUTIOPT		0x00040000UL
#define IPMSG_NOADDLISTOPT		0x00080000UL
#define IPMSG_READCHECKOPT		0x00100000UL
#define IPMSG_SECRETEXOPT		(IPMSG_READCHECKOPT|IPMSG_SECRETOPT)
#define IPMSG_NO_REPLY_OPTS   		(IPMSG_BROADCASTOPT|IPMSG_AUTORETOPT)

//加密命令的加密标志
#define IPMSG_RSA_512			0x00000001UL
#define IPMSG_RSA_1024			0x00000002UL
#define IPMSG_RSA_2048			0x00000004UL
#define IPMSG_RC2_40			0x00001000UL
#define IPMSG_RC2_128			0x00004000UL
#define IPMSG_RC2_256			0x00008000UL
#define IPMSG_BLOWFISH_128		0x00020000UL
#define IPMSG_BLOWFISH_256		0x00040000UL
#define IPMSG_SIGN_MD5			0x10000000UL
#define IPMSG_SIGN_SHA1			0x20000000UL

//与Win贝塔版本的兼容
#define IPMSG_RC2_40OLD			0x00000010UL	// for beta1-4 only
#define IPMSG_RC2_128OLD		0x00000040UL	// for beta1-4 only
#define IPMSG_BLOWFISH_128OLD		0x00000400UL	// for beta1-4 only
#define IPMSG_RC2_40ALL			(IPMSG_RC2_40|IPMSG_RC2_40OLD)
#define IPMSG_RC2_128ALL		(IPMSG_RC2_128|IPMSG_RC2_128OLD)
#define IPMSG_BLOWFISH_128ALL		(IPMSG_BLOWFISH_128|IPMSG_BLOWFISH_128OLD)

//附加信息中的文件类型
#define IPMSG_FILE_REGULAR		0x00000001UL
#define IPMSG_FILE_DIR			0x00000002UL
#define IPMSG_FILE_RETPARENT		0x00000003UL	// return parent directory
#define IPMSG_FILE_SYMLINK		0x00000004UL
#define IPMSG_FILE_CDEV			0x00000005UL	// for UNIX
#define IPMSG_FILE_BDEV			0x00000006UL	// for UNIX
#define IPMSG_FILE_FIFO			0x00000007UL	// for UNIX
#define IPMSG_FILE_RESFORK		0x00000010UL	// for Mac

//附加信息中的文件属性选项
#define IPMSG_FILE_RONLYOPT		0x00000100UL
#define IPMSG_FILE_HIDDENOPT		0x00001000UL
#define IPMSG_FILE_EXHIDDENOPT		0x00002000UL	// for MacOS X
#define IPMSG_FILE_ARCHIVEOPT		0x00004000UL
#define IPMSG_FILE_SYSTEMOPT		0x00008000UL

//附加信息中的扩展文件类型
#define IPMSG_FILE_UID			0x00000001UL
#define IPMSG_FILE_USERNAME		0x00000002UL	// uid by string
#define IPMSG_FILE_GID			0x00000003UL
#define IPMSG_FILE_GROUPNAME		0x00000004UL	// gid by string
#define IPMSG_FILE_PERM			0x00000010UL	// for UNIX
#define IPMSG_FILE_MAJORNO		0x00000011UL	// for UNIX devfile
#define IPMSG_FILE_MINORNO		0x00000012UL	// for UNIX devfile
#define IPMSG_FILE_CTIME		0x00000013UL	// for UNIX
#define IPMSG_FILE_MTIME		0x00000014UL
#define IPMSG_FILE_ATIME		0x00000015UL
#define IPMSG_FILE_CREATETIME		0x00000016UL
#define IPMSG_FILE_CREATOR		0x00000020UL	// for Mac
#define IPMSG_FILE_FILETYPE		0x00000021UL	// for Mac
#define IPMSG_FILE_FINDERINFO		0x00000022UL	// for Mac
#define IPMSG_FILE_ACL			0x00000030UL
#define IPMSG_FILE_ALIASFNAME		0x00000040UL	// alias fname
#define IPMSG_FILE_UNICODEFNAME 	0x00000041UL	// UNICODE fname

#define FILELIST_SEPARATOR	'\a'
#define HOSTLIST_SEPARATOR	'\a'
#define HOSTLIST_DUMMY		"\b"
#define HLIST_ENTRY_SEPARATOR	':'

//肥鸽子的协议
//#define PIGEONS_VERSION		0x0100
#define PIGEONS_VERSION		0x0001

//一般定义
#define MAX_SOCKBUF		65536
#define MAX_UDPBUF		16384
#define MAX_CRYPTLEN		((MAX_UDPBUF - MAX_BUF) / 2)
#define MAX_BUF			1024
#define MAX_NAMEBUF		50
#define MAX_LANGBUF		10
#define MAX_LISTBUF		(MAX_NAMEBUF * 3 + 50)
#define MAX_ANSLIST		100

#define HS_TOOLS		"HSTools"
#define IP_MSG			"IPMsg"
#define NO_NAME			"no_name"
#define URL_STR			"://"
#define MAILTO_STR		"mailto:"
#define MSG_STR			"msg"

#define DEFAULT_PRIORITY	10
#define PRIORITY_OFFSET		10
#define DEFAULT_PRIORITYMAX	5

class MsgMng{
	public:
		QString username;
		QString hostname;
		int version;
		unsigned long packetno;
		unsigned long command;
		QString extend;
		QHostAddress address;
		//quint32 address;
		int portNo;
		MsgMng();
		/*	username = QHostInfo::localHostName();
			hostname = QHostInfo::localHostName();  
			version = PIGEONS_VERSION;
			packetno = QDateTime::currentDateTime().toTime_t();//实际返回uint，有点不匹配 */
		MsgMng* makeMng(QString username, QString hostname, unsigned long command, QString extend, QHostAddress addr);
	private:
		unsigned long getPacketno();
		QString getUsername();
		QString getHostname();
		QHostAddress getAddress();
		int getVersion();
		unsigned long getCommand();
		QString getExtend();

		void parseMsg();
};

class CfgAllDialog {
	private :
		bool absenceOpt;
		bool serverOpt;
		bool dialupOpt;
		bool fileattchOpt;
		bool encryOpt;
		bool utf8Opt;

		//CfgAllDialog();
		//~CfgAllDialog();
		void changeCfgAll();
};

class CfgSendDialog {
	private :
		bool sendcheckOpt;
		bool secretOpt;
		bool broadcastOpt;
		bool multicastOpt;
		bool nopopuptOpt;
		bool autoretOpt;
		bool retryOpt;
		bool passwordOpt;
		bool nologOpt;
		bool newmutiOpt;
		bool noaddlistOpt;
		bool readcheckOpt;
		bool secretexOpt;

		//CfgSendDialog();
		//~CfgSendDialog();
		void changCfgSend();

};

#endif
