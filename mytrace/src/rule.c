#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
 
 
#define buf_MAX 512
#define rule_MAX 10
#define thread_MAX 500


struct conf{
char name[100];/* 规则名称 */
int line;/* 匹配条数 */
char rule[10][buf_MAX];
}conf[rule_MAX];

struct thr{
	char logfile[50];/*日志名*/
	char fpath[100];/*日志路径*/
	char pid[10];/*PID*/
	FILE *lfp;/*日志文件*/
	FILE *cmdf;/*PID和cmdline*/
	char cmd_buf[512];
	char s_log[buf_MAX];/*日志记录*/
}thr[thread_MAX];



int treatment(char *cmd,char *pidd,char *rule_name)
{
printf("CMD=%s     pid=%s\t !!!!!!!!%s\n\n",cmd,pidd,rule_name);
}


		
int get_log(thr)
		struct thr *thr;
{
	
	int line,n,k;
	sprintf(thr[0].fpath,"log/%s",thr[0].logfile);
	for(n=0;n<rule_MAX,conf[n].rule[0][0]!='\0';n++)
	{	
		k=0;
		thr[0].lfp=fopen(thr[0].fpath,"r");	
		for(line=0;line<10;line++)
		{
			if(conf[n].rule[line][0]=='\0')
				break;
			while(!feof(thr[0].lfp))/*判断读完*/
			{
			
				fgets(thr[0].s_log,buf_MAX,thr[0].lfp);
				if(strstr(thr[0].s_log,conf[n].rule[line])!=NULL)
				{
					k++;
					break;
				}
			}
			if(k==conf[n].line)/*当k与匹配行数相等时，为病毒行为*/
			{
				thr[0].cmdf=fopen("./cmd.txt","r");
			
				strncpy(thr[0].pid,thr[0].logfile,strlen(thr[0].logfile)-4);
				while(!feof(thr[0].cmdf))
				{
					fgets(thr[0].cmd_buf,buf_MAX,thr[0].cmdf);
					if(strstr(thr[0].cmd_buf,thr[0].pid)!=NULL)
						//printf("\tCMD=%s",thr[0].cmd_buf+strlen(thr[0].pid)+1);
						break;						
				}
				treatment(thr[0].cmd_buf+strlen(thr[0].pid)+1,thr[0].pid,conf[n].name);			
				fclose(thr[0].cmdf);
				break;
			}
		
		
		}	
		if(k!=conf[n].line)
			fclose(thr[0].lfp);
	}	
	
}

int get_rule()/*从配置文件读取规则*/
{
	int i,j,k;
	
	int line,n;
	FILE *rfp;
	char buf[buf_MAX];
	if((rfp=fopen("rule.conf","r"))==NULL)
	{
		printf("打开配置文件错误!\n");
		exit(-1);
	}
	
	for(n=0;n<rule_MAX,!feof(rfp);)
	{
		fgets(buf,buf_MAX,rfp);		
		if(buf[0]=='#'||buf[0]==' '||buf[0]=='\n')/*注释行或空格或空白行*/
			continue;
		if(buf[0]=='{')/*"{"规则开始*/
		{
			for(line=0;line<10;)
			{
				fgets(buf,buf_MAX,rfp);
				if(buf[0]=='#'||buf[0]==' '||buf[0]=='\n')/*注释行或空格或空白行*/
					continue;
				if(buf[0]=='N'&&buf[1]=='A'&&buf[2]=='M'&&buf[3]=='E'&&buf[4]==':')
				{/*规则名称*/
					strncpy(conf[n].name,buf+5,100);
					continue;
				}
				if(buf[0]=='L'&&buf[1]=='I'&&buf[2]=='N'&&buf[3]=='E'&&buf[4]==':')
				{/*匹配条数*/
					conf[n].line=atoi(buf+5);
					continue;
				}
				if(buf[0]=='}')/*"}"规则结束*/
					break;
				strncpy(conf[n].rule[line],buf,buf_MAX);/*读取匹配行*/
				conf[n].rule[line][strlen(conf[n].rule[line])-1]='\0';/*去掉串尾'\n'*/
				line++;
			}
		}
		n++;/*下一组规则*/
	}
	fclose(rfp);	

}
 main()
{
	pthread_t id[thread_MAX];
	int t,i,ret;
	struct stat st; /*文件属性*/
	size_t fsize;/*文件大小*/
	char filepath[100];
	int len;		
	get_rule();
	
	
	struct dirent *ptr; 
	DIR *dir;	


	while(1)
	{	
	t=0;
	dir = opendir("log");
	while((ptr = readdir(dir))!= NULL)
	{	
		if (!(isdigit(ptr->d_name[0]))) //判断是否为数字
			continue;
									
		len=strlen(ptr->d_name);
		if(ptr->d_name[len-1]!='.'&&ptr->d_name[len-1]!='l'&&ptr->d_name[len-1]!='o'&&ptr->d_name[len-1]!='g') /*文件名应以.log结尾*/
			continue;
		sprintf(filepath,"log/%s",ptr->d_name);	
		stat(filepath,&st);
		fsize=st.st_size;/*获取文件大小*/
		if(fsize==0)
			continue;												
		strcpy(thr[t].logfile,ptr->d_name);
		t++;								
	}
	
	closedir(dir);

				
	for (i=0;i<t;i++)   /*启动线程,t为需启动的线程数 */
	{	
		ret=pthread_create(&id[i],NULL,(void *) get_log,thr+i);
		if(ret!=0){
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
		
	for (i=0;i<t;i++) 
	{
		pthread_join(id[i],NULL);/*stop thread*/
	}
	sleep(10);
	
	}


	printf("end!!!\n");
	
		
}

