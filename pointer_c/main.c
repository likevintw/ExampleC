

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

void example_malloc_free()
{
	int size = 10;
    int *int_pointer = malloc(size * sizeof(int));
	if(int_pointer == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    for(int i = 0; i < size; i++) 
	{
		int_pointer[i] = i;
        printf("int_pointer[%d] = %d\n", i, *(int_pointer+i));
    }

    free(int_pointer);
}

void example_calloc_free()
{
	int n, i, *ptr, sum = 0;

    ptr = (int*) calloc(n, sizeof(int));
    if(ptr == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    for(i = 0; i < n; ++i)
    {
		ptr[i] = i;
		printf("%d\n", *(ptr + i));
    }
    free(ptr);
}

void example_realloc()
{
	int *ptr, i , n1, n2;
	n1 = 5;
	n2 = 10;

    ptr = (int*) malloc(n1 * sizeof(int));

    printf("Addresses of previously allocated memory: \n");
    for(i = 0; i < n1; ++i)
	{
		ptr[i] = i;
		printf("[%d]:%d, %p\n", i, ptr[i], ptr + i);
	}

    // rellocating the memory
    ptr = realloc(ptr, n2 * sizeof(int));

    printf("Addresses of newly allocated memory: \n");
    for(i = 0; i < n2; ++i)
	{
		ptr[i] = i;
		printf("[%d]:%d, %p\n", i, ptr[i], ptr + i);
	}
  
    free(ptr);
}

int main()
{
	//example_record();
	//example_malloc_free();
	//example_calloc_free();
	example_realloc();
	return 0;
}
