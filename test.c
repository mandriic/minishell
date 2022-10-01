#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void rest(int *i)
{
	i[0]++;
}
int main()
{
	int i[10];
	char **test;
    test = malloc(sizeof(char*) * 10);
	test[0] = malloc(sizeof(char) * 19);
	i[1] = 1;
	test[0][i[1]] = 'c';
	printf("test %c\n", test[0][i[1]]);
	rest(i);
	printf("rest %d", i[0]);
	rest(i);
	printf("rest %d", i[0]);

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