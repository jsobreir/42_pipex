#include "pipex.h"

int main(int argc, char **argv, char *envp)
{
	printf("%s\n", get_path(argv[1]));
}