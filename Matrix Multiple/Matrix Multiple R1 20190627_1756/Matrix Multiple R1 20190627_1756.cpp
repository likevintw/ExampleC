

//Matrix Multiple R1 20190627_1756
/**/
#include <fstream> //printf


/*
output=AB
input:
matrixA_m
matrixA_n
matrixB_m
matrixB_n
matrixA
matrixB
*/
class matrixMultiple
{
public:
	int matrixA_m, matrixA_n, matrixB_m,matrixB_n ;
	float** matrixA, ** matrixB,** matrixOut;
	matrixMultiple();
	void matrixMultiple_initial();
	void matrixMultiple_main();
	void matrixMultiple_showOutput();
};
matrixMultiple::matrixMultiple()
{
	matrixA_n = 1;
	matrixA_m = 1;
	matrixB_n = 1;
	matrixB_m = 1;
}
void matrixMultiple::matrixMultiple_initial()
{
	if (matrixA_n!= matrixB_m)
	{
		printf("matrixA_m=%d\n", matrixA_m);
		printf("matrixA_n=%d\n", matrixA_n);
		printf("matrixB_m=%d\n", matrixB_m);
		printf("matrixB_n=%d\n", matrixB_n);
		printf("The Matrix dimensions are wrong, please check it.\n");
	}
	else
	{
		printf("matrixA_m=%d\n", matrixA_m);
		printf("matrixA_n=%d\n", matrixA_n);
		printf("matrixB_m=%d\n", matrixB_m);
		printf("matrixB_n=%d\n", matrixB_n);

		//Set A
		matrixA = new float* [matrixA_m];
		for (int i(0); i < matrixA_m; i++)
		{
			matrixA[i] = new float [matrixA_n];
		}
		//Set B
		matrixB = new float* [matrixB_m];
		for (int i(0); i < matrixB_m; i++)
		{
			matrixB[i] = new float[matrixB_n];
		}
		
		//Set O[utput
		matrixOut = new float* [matrixB_n];
		for (int i(0); i < matrixA_m; i++)
		{
			matrixOut[i] = new float[matrixB_n];
		}
		
		
	}
	
}
void matrixMultiple::matrixMultiple_main()
{
	float b(0);
	//output
	for (int i(0); i < matrixA_m; i++)
	{
		for (int j(0); j < matrixB_n; j++)
		{
			for (int k(0); k < matrixA_n; k++)
			{
				b = b + matrixA[i][k] * matrixB[k][j];
				//printf("%d %d %d\n", i, j, k);
				//printf("%f", matrixA[i][k]);
			}
			matrixOut[i][j] = b;
			b = 0;
		}
	}
}
void matrixMultiple::matrixMultiple_showOutput()
{
	for (int i(0); i < matrixA_m; i++)
	{
		for (int j(0); j < matrixB_n; j++)
		{
			printf("%f  ", matrixOut[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	//define
	class matrixMultiple case1;
	case1.matrixA_m = 5; //A[m][n]
	case1.matrixA_n = 3;
	case1.matrixB_m = 3; //B[m][n]
	case1.matrixB_n = 6;
	case1.matrixMultiple_initial();
	//set input A
	printf("\n");
	for (unsigned int i(0); i < case1.matrixA_m; i++)
	{
		for (int j(0); j < case1.matrixA_n; j++)
		{
			case1.matrixA[i][j]=j+i;
			printf("%f  ", case1.matrixA[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//Set input B
	for (unsigned int i(0); i < case1.matrixB_m; i++)
	{
		for (int j(0); j < case1.matrixB_n; j++)
		{
			case1.matrixB[i][j] = i;
			printf("%f  ", case1.matrixB[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//Algorithm
	case1.matrixMultiple_main();
	//Show the result
	case1.matrixMultiple_showOutput();
	
	return 0;
}


