/*******************

C++, Bubble Sorting With Array Example
20180709
A1

*******************/

#include <iostream>

using namespace std;


int *bubble_sortiong_with_array_example(int*data_sepuence,int data_number)
{
    int data_buffer(0),counter(0);
        while(1)
        {
            for(int i(0);i<data_number-1;i++)
            {
                if(data_sepuence[i]>data_sepuence[i+1])
                {
                    data_buffer=data_sepuence[i+1];
                    data_sepuence[i+1]=data_sepuence[i];
                    data_sepuence[i]=data_buffer;
                }
            }
            counter++;
            if(counter>=data_number)
                break;
        }
        return data_sepuence;
}


int main()
{
    cout << "Sorting with Array Processing" << endl;
    int data1[10]={5,8,7,4,1,9,4,6,3,0};
    int data_number=10;
    int *data_array= new int [data_number];

    //Print the values in the Array
    cout<<endl;
    cout<<"Original Data"<<endl;
    for(int i(0);i<data_number;i++)
    {
        data_array[i]=data1[i];
        cout<<data_array[i]<<endl;
    }

    //Sorting Algorithm
    data_array=bubble_sortiong_with_array_example(data_array,data_number);

    //Result Presentation
    cout<<endl;
    cout<<"The Result"<<endl;
    for(int i(0);i<data_number;i++)
    {
        cout<<data_array[i]<<endl;
    }

    return 0;
}
