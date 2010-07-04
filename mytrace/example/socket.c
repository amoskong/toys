#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
main()
{
	int sock_fd;	
	struct sockaddr_in server_addr; 
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(9527);/*服务器要监听的端口*/
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);/*监听所有IP地址的请求*/
	if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) <0) 
	{
		fprintf(stderr,"socket error:%s\n",strerror(errno));
		exit(1);
	}
	if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) <0) 
	{
		fprintf(stderr,"bind error:%s\n",strerror(errno));
		exit(1);
	}
	if (listen(sock_fd,4) <0) 
	{
		fprintf(stderr,"Listen error:%s\n",strerror(errno));
		exit(1);
	}
	printf("listening......\n");
	sleep(20);
} 

