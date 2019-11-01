/*
20190218_1954 data form txt to 2D array
*/

#include <iostream>
#include <fstream>

using namespace std;

#define input_txt "Data1.txt"


int main()
{
    cout << "Read/Write Text File" << endl;

    /**/
    unsigned int data_number(100);
    short **training_data= new short *[data_number];
    for(int i(0);i<data_number;i++)
    {
        training_data[i] = new short [6];
    }
    int read_data_buffer(0);

    /*1. Reading the data*/
    //Check the text file, if it is not exit, show the warming information
    ifstream txt_file(input_txt,ios::in);
    if(!txt_file)
    {
        cout<<endl;
        cout<<"Export_file is opened fail"<<endl;
        cout<<endl;
    }

    //Reading data from text
    for(int i(0),j(0);;)
    {
        txt_file>>read_data_buffer;
        cout<<"The data is "<<read_data_buffer<<endl;
        cout<<"i "<<i<<" j "<<j<<endl;
        training_data[i][j]=read_data_buffer;
        if(j==5)
        {
            j=0;
            i++;
        }
        else
        {
            j++;
        }
        if(txt_file.eof())
        {
            cout<<"Reading text file is over"<<endl;
            break;
        }
    }

    //Show the data
    cout<<"Show the Data"<<endl;
    for(unsigned int i(0);i<data_number;i++)
    {
        for(int j(0);j<6;j++)
        {
            cout<<training_data[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<< "End"<<endl;
    return 0;
}
