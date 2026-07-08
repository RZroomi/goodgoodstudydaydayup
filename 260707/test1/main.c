#include "stdio.h"
#include "a.h"
#include "b.h"
#include "c.h"

int main(void)
{
#ifdef DEBUG
	printf("DEBUG!!!!!");
#endif

	printf("%d+%d=%d",b(),c(),20);
	return 0;

}
