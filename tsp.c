#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h> 
//float.h is where u will get ur float_max
//you will need to define a data structure for city as following

typedef struct {
	float x, y;
}	City;

//the following function is to calculate the distance between the two cities
//this is based on the equation to find the hypotenues of a right triangle
//
float cal_distance(City a, City b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf((dx * dx) + (dy * dy));
}

//this function is used to get the total distance between all the cities at once 
float cal_total_distance(City *cities, int *path, int n)
{
	float total = 0.0;
	int i;

	//this is to loop through all the cities in each path. 
	for (i = 0; i < n - 1; i++)
	{
		total += cal_distance(cities[path[i]], cities[path[i + 1]]);
	}

	//this is important because we will need to calculate the distance between the last city and the very first cit
	total += cal_distance(cities[path[n - 1]], cities[path[0]]);

	return total;
}

//this is to swap the path 
void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//this is to find the shortest available path of the cities 
void find_shortest_path(City *cities, int *path, int n, int pos, float *min_distance)
{
	if (pos == n)
	{
		float current_distance = cal_total_distance(cities, path, n);
		if (current_distance < *min_distance)
			*min_distance = current_distance;

		return;
	}

	for (int i = pos; i < n; i++)
	{
		swap(&path[pos], &path[i]);
		find_shortest_path(cities, path, n, pos + 1, min_distance);
		swap(&path[pos], &path[i]);
	}
}

int main(void)
{
	//we will never be testing with more than 11 cities 
	City cities[12];
	int n = 0; //this will store the number of cities 

	while (n < 11 && fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)
		n++;
	//if we didn't read anything 
	if (n < 2)
	{
		printf("0.00\n");
		return 0;
	}

	int path[12];
	//this is how we initialize the path from 0 to 11 
	for (int i = 0; i < n; i++)
		path[i] = i;

	//we will set the minimum distance to be the maximum float value 
	float min_distance = FLT_MAX;

	find_shortest_path(cities, path, n, 1, &min_distance);

	//we are getting the float value until the 2nd point meaning -> 
	//0.00
	printf("%2f\n", min_distance);
	return 0;
}
