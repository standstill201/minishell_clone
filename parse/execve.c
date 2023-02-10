// make example of execve

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	// char *argv2[] = {"echo", "$?", NULL};
	// char *envp2[] = {NULL};
	// execve("/bin/echo", argv2, envp);
	// print envp
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}


	return (0);
}
