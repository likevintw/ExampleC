

#include <stdio.h>
#include <stdlib.h>
typedef struct rec
	{
    		int i;
    		float PI;
    		char A;
	}RECORD;
void example_record()
{
	RECORD *ptr_one;
	ptr_one = (RECORD *) malloc (sizeof(RECORD));
	(*ptr_one).i = 10;
	(*ptr_one).PI = 3.14;
	(*ptr_one).A = 'a';

	printf("First value: %d\n",(*ptr_one).i);
	printf("Second value: %f\n", (*ptr_one).PI);
	printf("Third value: %c\n", (*ptr_one).A);

	free(ptr_one);
}

void example_basic()
{
	int size = 10;
    int *int_pointer = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++) 
	{
		int_pointer[i] = i;
        printf("int_pointer[%d] = %d\n", i, *(int_pointer+i));
    }

    free(int_pointer);
}

int main()
{
	//example_record();
	example_basic();
	return 0;
}
