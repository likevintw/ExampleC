#include <stdio.h>
class A
{
public:
    A()
    {
        printf("A\n");
    }
    ~A()
    {
        printf("~A\n");
    }
};
class B:  public  A
{
public:
    B()
    {
        printf("B\n");
    }
    ~B()
    {
        printf("~B\n");
    }
};
class C:  public  A
{
public:
    C()
    {
        printf("C\n");
    }
    ~C()
    {
        printf("~C\n");
    }
};
class D:  public  B, public  C
{
public:
    D()
    {
        printf("D\n");
    }
    ~D()
    {
        printf("~D\n");
    }
};
int main()
{
    D D;
    return 0;
}

