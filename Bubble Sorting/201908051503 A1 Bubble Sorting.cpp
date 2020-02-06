
/*
Bubble Sorting 201908051503
*/

#include <iostream>

class bubbleSorting
{
public:
	int* input_array;
	int* output_array;
	int dataSize;
	struct linkList
	{
		int value;
		linkList* node;
	};
	
	linkList* input_node, * first_node, * current_node, * previous_node;
	bubbleSorting();
	void bubbleSortingInitial();
	void bubble_sorting();
};
bubbleSorting::bubbleSorting()
{
	dataSize = 10;
	input_array = NULL;
	output_array = NULL;
};
void bubbleSorting::bubbleSortingInitial()
{
	input_array = new int[dataSize];
	output_array = new int[dataSize];
};
void bubbleSorting::bubble_sorting()
{
	first_node = NULL;
	for (int i(0);i<dataSize; i++)
	{
		input_node = new linkList;
		input_node->value = input_array[i];
		input_node->node = NULL;
		if (first_node == NULL)
		{
			first_node = input_node;
		}
		else
		{
			current_node = first_node;
			while (1)
			{
				if (input_node->value < first_node->value)//input value < first value
				{
					input_node->node = first_node;
					first_node = input_node;
					break;
				}
				if (input_node->value < current_node->value)//
				{
					input_node->node = current_node;
					previous_node->node = input_node;
					break;
				}
				if (current_node->node == NULL)//input value >= all of the values in linked list
				{
					current_node->node = input_node;
					break;
				}
				previous_node = current_node;
				current_node = current_node->node;
			}
		}
	}
	//show the lined list
	//printf("Show the linked list with bubble sorting\n");
	current_node = first_node;
	int i(0);
	while (1)
	{
		//printf("%d\n", current_node->value);
		output_array[i] = current_node->value;
		//printf("%d\n", output_array[i]);
		i++;
		current_node = current_node->node;
		if (!current_node)
			break;
	}
};


int main()
{
	
	const short data_size(10);
	int data1[data_size] = { 5,8,4,2,2,12,1,4,6,4 };

	bubbleSorting project1;
	project1.dataSize = data_size; //determine the data size
	project1.bubbleSortingInitial(); //initial
	project1.input_array = data1; //input data
	project1.bubble_sorting(); //Bubble Sorting Algorithm

	//Print Result
	printf("Show The Bubble Sorting Result\n");
	for (int i(0); i < data_size; i++)
	{
		printf("%d\n", project1.output_array[i]);
	}

	return 0;

}