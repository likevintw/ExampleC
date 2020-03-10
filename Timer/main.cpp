
// Timer, 
// gettimeofday() is much batter than clock()
#include <stdio.h> //printf
#include <unistd.h> //usleep, sleep
#include <time.h> // clock()
#include<sys/time.h> //gettimeofday()

void delay(int delayTime)
{
	for (int i(0); i < delayTime; ++i)
	{
		for (int j(0); j < 10000; ++j)
		{

		}
	}
}
void Example_clock(int delayTime)
{
	clock_t t1;
	t1 = clock();  //Time of Start
	sleep(2); // clock() will be stop when in the sleep
	delay(delayTime);
	t1 = clock()- t1;  //Time of End
	printf("%lf Second\n", t1 / (double)(CLOCKS_PER_SEC));
}
void Example_gettimeofday(int delayTime)
{
	// timer, start
	// uSec=1*10^-1 s
	struct timeval tv, tv2;
	gettimeofday(&tv, NULL);
	double diff;
	sleep(delayTime);
	//timer, end
	gettimeofday(&tv2, NULL);
	diff = (tv2.tv_sec - tv.tv_sec) * 1000000 + (tv2.tv_usec - tv.tv_usec);
	printf("Runtime = %f ms\n", diff / 1000);
}
int main()
{
	Example_clock(100);
	Example_gettimeofday(3);
	return 0;
}
