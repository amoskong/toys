#include <sys/types.h>
#include <unistd.h>
 
 main()
{
	chown("/etc/passwd",501,501);
}


