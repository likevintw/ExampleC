#include <iostream>

using namespace std;
int max_prime_num(int input_num)
{
    int N(0);
    int half_N(0);
    int counter_prime(0);
    int max_prime(0);
    N=input_num;
    for(int i(N);i>2;i--)
    {
        half_N=i/2;
        for(int j(2);j<half_N;j++)
        {
             if(i%j==0)
            {
                break;
            }
            if(j==half_N-1)
            {
                //cout << "The Maximum Prime which less "<<N<<" is "<<i<< endl;
                //cout << "Prime "<<i<< endl;
                //to show how many prime number less the entered number
                counter_prime++;
                if(max_prime==0)
                {
                    max_prime=i;
                }
            }
            //cout << "The number of Prime "<<counter_prime<< endl;
        }
    }
    return max_prime;
}
int main()
{
    int export_data(0);
    int keyin_num(0);
    cout<<"Please Enter a Real Number\n";
    cin>>keyin_num;
    cout<<"The Enter Number is "<<keyin_num<<endl;;
    export_data=max_prime_num(keyin_num);
    cout <<"The Maximum Prime Number is "<< export_data << endl;
    return 0;
}

