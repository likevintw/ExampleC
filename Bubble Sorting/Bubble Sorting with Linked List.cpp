/*
Bubble Sorting with Linked List
201901091849
A1

*/
#include <iostream>

using namespace std;


struct data_linked
{
    int value;
    data_linked *node;
};

int main()
{
       cout<<"Bubble Sorting with Linked list"<<endl;

       short input_data[10]={3,5,6,8,10,4,5,4,8,4};
       //short output_data[10];

       //show the original data sequence
       cout<<"Original Data Sequence"<<endl;
       for(int i(0);i<10;i++)
       {
              cout<<"Data "<<i+1<<" = "<<input_data[i]<<endl;
       }

    data_linked *first_node=NULL,*previous_node = nullptr,*current_node;
       data_linked *input_node;

       for(int i(0);i<10;i++)
       {
              input_node= new data_linked;
              input_node->node=NULL;
              input_node->value=input_data[i];
              if(first_node==NULL)
              {
                     first_node=input_node;
              }
              else
              {
                     current_node=first_node;
                     while(1)
                     {
                            if(input_node->value<first_node->value)//input value < first value
                            {
                                   input_node->node=first_node;
                                   first_node=input_node;
                                   break;
                            }
                            if(input_node->value<current_node->value)//
                            {
                                   input_node->node=current_node;
                                   previous_node->node=input_node;
                                   break;
                            }
                            if(current_node->node==NULL)//input value >= all of the values in linked list
                            {
                                   current_node->node=input_node;
                                   break;
                            }
                            previous_node=current_node;
                            current_node=current_node->node;
                     }

              }
       }

    //Show the data which in the link list
    cout<<endl;
    cout<<"Show the data in the linked list"<<endl;
    current_node=first_node;
    while(1)
    {
        cout<<current_node->value<<endl;
        current_node=current_node->node;
        if(!current_node)
            break;
    }

    return 0;

}
