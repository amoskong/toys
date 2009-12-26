/*计算Fibonacci数列第n项的程序 by孔建军*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main()
{
	int fd[2];
	int n,i=1;
	int error;
	printf("输出Fibonacci数列前n项，请输入n:");
	scanf("%d",&n);
	if(n>92){
	printf("数字n太大！\n");
	return 1;
	}
	if(n<=0){
	printf("输入有误！\n");
	return 1;
	}
	n++;
	long a[n+2];
	a[0]=0;
	a[1]=1;
	pid_t childpid=0,f;
	f=getpid();
	if(pipe(fd)==-1){
		perror("新建管道出错");
		return 1;
	}
	if((dup2(fd[0],STDIN_FILENO)==-1)||(dup2(fd[1],STDOUT_FILENO)==-1)){
		perror("管道连接出错");
		return 1;
	}
	if((close(fd[0])==-1)||(close(fd[1])==-1)){
		perror("关闭管道口出错");
		return 1;
	}
	for(i=1;i<n;i++){/*利用for语句创建进程环*/
		if(pipe(fd)==-1){
			perror("新建管道出错");
			return 1;
		}
		if((childpid=fork())==-1){
			perror("新建进程出错");
			return 1;
		}
		if(childpid>0)
			error=dup2(fd[1],STDOUT_FILENO);
		else if(!childpid)
			error=dup2(fd[0],STDIN_FILENO);
		if((close(fd[0])==-1)||(close(fd[1])==-1)){
			perror("关闭管道口出错");
			return 1;
		}
		if(f==getpid())	write(STDOUT_FILENO,a,sizeof(a));
		else if(childpid){
			read(STDIN_FILENO,a,sizeof(a));
			a[i]=a[i-2]+a[i-1];
			write(STDOUT_FILENO,a,sizeof(a));
			}
		if(childpid) break;
	}	
	if(childpid==0){/*最后一个进程计算最后一项，并将结果传递给第一个进程。*/
		read(STDIN_FILENO,a,sizeof(a));
		a[i]=a[i-2]+a[i-1];
		write(STDOUT_FILENO,a,sizeof(a));
		return 1;
	}
	else wait(NULL);
	if(f==getpid()){
		read(STDIN_FILENO,a,sizeof(a));
		for(i=1;i<n;i++) 
			fprintf(stderr,"%ld\t",a[i]);
		fprintf(stderr,"\n",NULL);
	}
	return 0;
}

