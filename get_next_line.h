#ifndef GNL
# define GNL

#include <stdlib.h> //malloc, free, NULL
#include <stdio.h> //printf for testing only
#include <unistd.h> //read(), close()
#include <sys/types.h> //size_t, ssize_t
#include <fcntl.h> //open(), O_RDONLY

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char	*get_next_line(int fd);
#endif
