//Queue
/*
Keyin datum into queue.
Keyin "Catch" to get the first data.
Keyin "Number" to print data size.
*/

#include<stdio.h>
#include<string>
#include <unistd.h> // sleep(100)

using namespace std;

class QueueApplication
{
public:
	struct LinkedList
	{
		string LinkedListData;
		LinkedList* LinkedListnode;
	};
	LinkedList *headNode,*lastNode;
	int DataNumber;
	QueueApplication();
	string Queue(string inputData);
	~QueueApplication();
};
QueueApplication::QueueApplication()
{
	headNode = NULL;
	lastNode = NULL;
	DataNumber = 0;
}
QueueApplication::~QueueApplication()
{
	lastNode = NULL;
	headNode = NULL;
	delete lastNode;
	delete headNode;
}
string QueueApplication::Queue(string inputData)
{
	string result;
	// Show the Data Number
	if (inputData == "Number")
	{
		if (headNode == NULL)
		{
			result = "There is no any Datum in the queue";
		}
		else
		{
			result = "";
			printf("There are %d data in the queue\n", DataNumber);
		}
		return result;
	}
	
	//
	if (inputData == "Catch")
	{
		if (headNode == NULL)
		{
			result = "There is no any Datum in the queue";
		}
		else
		{
			result = headNode->LinkedListData;
			headNode = headNode->LinkedListnode;
			--DataNumber;
			
		}
	}
	else
	{
		// Build new link-list
		LinkedList* current = NULL;
		current = new LinkedList;
		current->LinkedListData = inputData;
		if (headNode == NULL)
		{
			headNode = current;
		}
		else
		{
			lastNode->LinkedListnode = current;
		}
		lastNode = current;
		result = "Added Data '";
		result = result + current->LinkedListData;
		result = result+"' Successfully";
		++DataNumber;
	}
	return result;
}
int main()
{
	printf("Queue Example\n");
	QueueApplication A;
	char keyin[20];
	while (1)
	{
		scanf("%10s", keyin); // the maximium input is 10 charaters.
		printf("%s\n", A.Queue(keyin).c_str());
		usleep(100);
	}
	return 0;
}
