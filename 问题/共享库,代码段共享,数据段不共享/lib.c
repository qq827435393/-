#include <stdio.h>
#include "lib.h"
 
static int a = 0;
 
void set(int v)
{
	a = v;
	printf("a = %d\n", a);
	return;
}
 
void get()
{
	printf("a = %d\n", a);
}
