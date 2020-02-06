
//SQRT_R1_20190503

#include <fstream> printf


double sqrt_Iterative(double input_value)
{
    double result_value(0);
    double trial_value(1);
    double check_value(0);
    
    //int i = 1; // to avoid
    for(int i(0);;i++)
    {
        result_value = 0.5 * (trial_value + input_value / trial_value);
        check_value = result_value - trial_value;
        //printf("i=%d , result_value=%f\n", i, result_value); //check the each result
        //printf("i=%d , result_value=%f\n", i, check_value); // check the each delt_value
        if (check_value < 0)
        {
            check_value = -check_value;
        }
        //The acccuracy of reslut
        if (check_value<0.01) //the accuracy of result
        {
            printf("%.2lf , result_value=%f\n", input_value, result_value); // check the each delt_value
            return result_value;
            //break;
        }
        trial_value = result_value;
        //avoid the infinity loop
        /*
        if (i > 10)
        break;
        */
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
