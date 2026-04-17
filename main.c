#include "codexion.h"




int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder *coders;
	t_dongle *dongles;
	int i;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	i = 0;
	coders = malloc(args->num_coders * sizeof(t_coder));
	if (!coders)
	{
		free(args);
		return(1);
	}
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!dongles)
	{
		free(coders);
		free(args);
		return(1);
	}
	while (i < args->num_coders)
	{
		
	}
	
    free(args);
	return (0);
}
