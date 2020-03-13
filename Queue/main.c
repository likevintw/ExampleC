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
	string Keyword_catch;
	string Keyword_exit;
	string Keyword_number;
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
	Keyword_catch = "catch";
	Keyword_exit = "exit";
	Keyword_number = "number";
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
	if (inputData == Keyword_number.c_str())
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
	if (inputData == Keyword_catch.c_str())
	{
		if (headNode == NULL)
		{
			result = "There is no any Datum in the queue";
		}
		else
		{
			LinkedList* BufferNode;
			BufferNode = headNode;
			headNode = headNode->LinkedListnode;
			result = BufferNode->LinkedListData;
			BufferNode = NULL;
			delete BufferNode;
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
		//scanf("%10s", keyin); // the maximium input is 10 charaters.
		scanf("%s", keyin); // the maximium input is 10 charaters.
		if (!A.Keyword_exit.find(keyin))
		{
			printf("Queue End\n");
			break;
		}
		else
		{
			printf("%s\n", A.Queue(keyin).c_str());
		}
		usleep(100);
	}
	return 0;
}
