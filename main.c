#include "codexion.h"


int	main(int argc, char **str)
{
	arguments_t	*args;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		exit(1);
	}
	args = parsing(str + 1);
	printf("%d\n", args->burnout_time);
    free(args);
	return (0);
}