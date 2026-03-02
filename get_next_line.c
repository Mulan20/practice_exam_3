#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	//this is to find the c in the string and to return the position of that string
	int i = 0;
	//if there is nothing in the string, return NULL
	if (!s)
		return NULL;
	while (s[i] != '\0')
	{
		//until the end of the string
		if (s[i] == (char)c)
			return s + i;
		i++;
	}
	return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	//this is to copy the src to dest based on n size
	size_t i = 0; //counter
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest); //return the destination 
}

size_t	ft_strlen(char *s)
{
	//to get the length of the string
	size_t len = 0;
	if (!s)
		return 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	//this is to add the s2 string to s1 array of strings 
	size_t size1; //to get the length of s1
	char *temp; //to malloc the combination of s1 and s2
		    //if the string array is not empty, we will get the size of current index of string from that string array 
	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0; //else the size is zero
			   //
	temp = malloc(size1 + size2 + 1); 
	if (!temp) //if the malloc is not created successfully
		return 0; 
	if (*s1) //if there are text in s1, copy it to temp first
		ft_memcpy(temp, *s1, size1);
	//after that copy s2 to temp
	ft_memcpy(temp + size1, s2, size2);
	temp[size1 + size2] = '\0';

	free(*s1); //free the previous s1
	*s1 = temp; //copy the temp back to s1
	return (1); //for success
}

int 	str_append_str(char **s1, char *s2)
{
	//this is to append s2 to s1
	size_t size2 = ft_strlen(s2); //get the size of s2 first
	return str_append_mem(s1, s2, size2); //call another function to put s2 to s1 and create malloc 
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (!dest || !src) //if there is nothing in either destination or src
		return NULL;
	if (dest > src) //if the destination is greater than source
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];//copy from src to dest backward
		}
	}
	else if (dest < src)
	{
		for (i = 0; i < n; i++)
		{
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	return dest;
}

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = ""; //to store the buffer
	char *ret = NULL; //to return the line we read
	char *temp; //this is to point the new line character
	int read_ret; //this is to store how many we have read
		      //
	while (1) //to loop until EOF or new line is found
	{
		temp = ft_strchr(b, '\n'); //this will return the pointer to the new line 
		if (temp)
		{
			//if the newline is found we will try to copy that to ret
			//temp - b + 1 is because b would point the start of the static buffer so, if we minus that from temp or the new line pointer  we will get the middle and + 1 is for newline 
			if (!str_append_mem(&ret, b, temp - b + 1))
				return (free(ret), NULL); 
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1); //now, we will move the remaining data after newline to the start of the buffer and return the line from before
			return ret;
		}
		//if no new line is found , we will copy b to ret entirely 
		if (!str_append_str(&ret, b))
			return NULL:
//read data to b based on BUFFER_SIZE
		read_ret = read(fd, b, BUFFER_SIZE); 
		
		//if nth is read 
		if (read_ret <= 0)
		{
			b[0] = '\0'; //clear buffer
			if (ret && *ret) //if we have read before
				return ret;
			free (ret);
			return NULL;
		}

		b[read_ret] = '\0'; //we will null terminate the buffer until the point we have read 
	}
}
