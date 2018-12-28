#include "lib.h"
#include <time.h>
 
int main()
{
	int cnt = 0;
	while(1){
		set(cnt++);
		usleep(1000000);
	}
	return 0;
}

