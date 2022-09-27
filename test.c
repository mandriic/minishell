#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char **test;
    test = malloc(1);
	free(test);
	 test = NULL;
	free(test);
	free(test);
	free(test);
	free(test);
	free(test);
	free(test);
	free(test);

}