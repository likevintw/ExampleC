
//SQRT_R1_20190505

#include <fstream> //printf


double sqrt_Iterative(double input_value)
{
    double result_value(0);
    double trial_value(1);
    double check_value(0);
    
    //int i = 1; // to avoid
    for(int i(0);;i++)
    {
        result_value = 0.5 * (trial_value + input_value / trial_value); //iterative algorithm
        check_value = result_value - trial_value; //check the result and the latest value
        
        //Trun the negative value to be positive
        if (check_value < 0)
        {
            check_value = -check_value;
        }
        //The acccuracy of reslut
        if (check_value<0.01) //the accuracy of result
        {
            printf("Root Square %.2lf is %.2lf\n", input_value, result_value); // check the each delt_value
            return result_value;
            //break;
        }
        trial_value = result_value;
    }
}

int main()
{
    printf("SQRT_R1_20190503\n");
    /**/
    for (int i(2); i < 50; i++)
    {
        sqrt_Iterative(i);
    }
    return 0;
}
