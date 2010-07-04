 /*gcc -lpthread -o test test15.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define MAX_PID 500



struct pid_i{
		pid_t pid;
		char strace_buf[100];	/* strace指令 */
}pid_i[MAX_PID];
	

void get_syscall(pid_i)
		struct pid_i *pid_i;
{
	
	memset(pid_i[0].strace_buf,0,100);
		
	sprintf(pid_i[0].strace_buf,"/usr/bin/strace -o log/%d.log -p %d 2>/dev/null",pid_i[0].pid,pid_i[0].pid);
	/*"/usr/bin/strace -o log/[<pid>].log -p [<pid>]"*/	
	system(pid_i[0].strace_buf);
	pthread_exit(0);	
	
}

	int main(int argc, char *argv[])
{
	pthread_t id[MAX_PID];
	int j,k=0,low,high,ret,m,n;
	pid_t pid_n;
	struct stat st; /*文件属性*/
	size_t fsize;/*文件大小*/
	char cmd_file[100];
	char buf[1024];	
	char cmdline[1024];
	char pid_cmd[1024];	
	DIR *dir;
	struct dirent *ptr; 
	FILE *cmdf;	

	int fp;

	dir = opendir("/proc");
	cmdf=fopen("cmd.txt","w");
	while((ptr = readdir(dir))!= NULL)
	{		
		pid_n=atol(ptr->d_name);
		if ((!(isdigit(ptr->d_name[0]))) || getpid()==pid_n ) //判断是否为数字或自己
			continue;
		pid_i[k].pid=pid_n;
		k++;		
		
		
		
		
		memset(buf,0,1024);  
		memset(cmdline,0,1024);
		sprintf(cmd_file,"/proc/%d/cmdline",pid_n);
		fp=open(cmd_file, O_RDONLY);
		read(fp,buf,1024);/*从/proc/[<PID>]/cmdline下读取进程的指令*/
		close(fp);

		for(m=0;m<1024;m++) /*删除cmdline中的'\0'*/
		{
			if(buf[m]=='\0')
			{
				buf[m]=' ';
				if(buf[m+1]=='\0')
					break;
			}
		}
			
		sprintf(pid_cmd,"%d\t%s\n",pid_n,buf);		
		fputs(pid_cmd,cmdf);/*将进程的PID和命令写入cmd.txt，供行为监控程序使用*/
								
	}
	
	fclose(cmdf);
	

	
	
		
	for (j=0;j<k;j++)/*启动线程,k为需启动的线程数*/
	{	
		ret=pthread_create(&id[j],NULL,(void *) get_syscall,pid_i+j);
		if(ret!=0){
			printf ("Create pthread error!\n");
			exit (1);
		}
	}
	closedir(dir);

	
	while(1)/*监控新进程的产生*/
	{	
		sleep(1);	
			
		high=k-1;	
		dir = opendir("/proc");	
		while((ptr = readdir(dir))!= NULL)
		{
			pid_n=atol(ptr->d_name);
			if ((!(isdigit(ptr->d_name[0]))) || getpid()==pid_n ) //判断是否为数字或自己
				continue;
								
			memset(buf,0,1024);  
			memset(cmdline,0,1024);
			sprintf(cmd_file,"/proc/%d/cmdline",pid_n);

			fp=open(cmd_file, O_RDONLY);
			read(fp,buf,1024);/*从/proc/[<PID>]/cmdline下读取进程的指令*/
			close(fp);

			for(m=0;m<1024;m++) /*删除cmdline中的'\0'*/
			{
				if(buf[m]=='\0')
				{
					buf[m]=' ';
					if(buf[m+1]=='\0')
						break;
				}
			}
			if(strstr(buf,"strace")!=NULL)  /*不监视strace进程*/
				continue;
			if(strstr(buf,"cmd.txt")!=NULL)  /*不监视保存cmd.txt进程*/
				continue;
							

			for(low=0;low<=high;low++)         /*找到新pid*/
				if(pid_n==pid_i[low].pid)
					break;
			if(low>high)
			{
				pid_i[k].pid=pid_n;	
				
				sprintf(pid_cmd,"%d\t%s\n",pid_n,buf);								
				cmdf=fopen("cmd.txt","a");
				fputs(pid_cmd,cmdf);
				fclose(cmdf);
				ret=pthread_create(&id[k],NULL,(void *) get_syscall,pid_i+k);  /*启动新线程跟踪新PID*/
				if(ret!=0){
					printf ("Create pthread error!\n");
					exit (1);
				}								
				k++;
			}
		}	
		closedir(dir);

		
	}
	return (0);
	
	
	
	

}



