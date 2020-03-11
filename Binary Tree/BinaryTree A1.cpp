// Binary Tree A1
/*
1. How to Show Data
2. Be a Function
*/
#include <stdio.h>

struct DoubleLinkList
{
	DoubleLinkList* LeftNode;
	int value;
	DoubleLinkList* RightNode;
};
int main()
{
	printf("Binary Tree\n");
	int DataSize = 10;
	// Set Tree Point
	DoubleLinkList** TreePoint=new DoubleLinkList*[DataSize];
	for (int i(0); i << DataSize; i++)
	{
		TreePoint[i] = new DoubleLinkList;
	}
	
	//DoubleLinkList* Current = NULL;
	for (int i(0); i < DataSize; i++)
	{
		
		// Create a New DataNode
		DoubleLinkList* DataNode = new DoubleLinkList;
		DataNode->value = i;
		DataNode->LeftNode = NULL;
		DataNode->RightNode = NULL;
		//printf("%d\n", i);
		// Label 
		TreePoint[i] = DataNode;
		// Check Node Space
		if (i==0)
		{
			TreePoint[i] = DataNode;
			//printf("%d First\n", i);
		}
		else
		{
			for (int j(0); j < i; j++)
			{
				if (TreePoint[j]->LeftNode == NULL)
				{
					TreePoint[j]->LeftNode = DataNode;
					//printf("%d Left\n", j);
					break;
				}
				if (TreePoint[j]->RightNode == NULL)
				{
					TreePoint[j]->RightNode = DataNode;
					//printf("%d Right\n", j);
					break;
				}
			}
		}
		// fill up
		// Label
		
	}
	// Show Result
	/**/
	DoubleLinkList* NodeBuffer = new DoubleLinkList;
	for (int i(0); i < 3; i++)
	{
		NodeBuffer = TreePoint[i];
		printf("%d\n", TreePoint[i]->value);
		
		NodeBuffer = TreePoint[i]->LeftNode;
		printf("%d,", NodeBuffer->value);
		
		//printf("%d,", TreePoint[i]->value);
		NodeBuffer = TreePoint[i]->RightNode;
		printf("%d\n", NodeBuffer->value);
		printf("\n");
		/**/
	}
	
	return 0;
}
