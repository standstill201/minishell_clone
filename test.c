#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *temp = strdup("");
	free(temp);
}