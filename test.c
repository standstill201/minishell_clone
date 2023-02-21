#include <stdio.h>

char *return_chr(void)
{
	return (0);
}
int main(void)
{
	char *str = return_chr();
	printf("%p", str);
}