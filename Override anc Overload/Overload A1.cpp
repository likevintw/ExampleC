/*****************
Class: constructor&deconstructor R1 20190208_0034

First constructor, last deconstructor

*****************/
#include <iostream> //cout and cin

using namespace std;

class DataType
{
public:
    void ShowDataType(int inputData);
    void ShowDataType(float inputData);
    void ShowDataType(char inputData);
};
void DataType::ShowDataType(int inputData)
{
    printf("Data Type is Interger\n");
}
void DataType::ShowDataType(float inputData)
{
    printf("Data Type is Float\n");
}
void DataType::ShowDataType(char inputData)
{
    printf("Data Type is Character\n");
}



int main()
{
    cout<<"Overload Example\n"<<endl;
    DataType test;
    char charData(55);
    float floatData(55);
    int intData(55);
    test.ShowDataType(charData);
    test.ShowDataType(floatData);
    test.ShowDataType(intData);

       return 0;
}
