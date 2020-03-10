//++i, i++ Example A1

#include<iostream>

int main() {
	int A = 2;
	int B = 2;
	A++;
	B++;
	printf("A=%d  B=%d \n", A, B);
	int C = A++; // copy A to C, then do A=A+1
	int D = ++B; // Do A=A+1, then copy A to C
	printf("C=%d  D=%d \n", C, D);
	printf("A=%d  B=%d \n", A, B);
	int E = (A++) + (++A); // 4+6
	int F = (++B) + (B++); // 5+5
	printf("E=%d  F=%d \n", E, F);
	return 0;
}