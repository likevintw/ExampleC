//https://www.twblogs.net/a/5b81aca82b71772165adbbf9
#include <iostream>
#include <string>

using namespace std;

class Referenced
{
public:
	//
	Referenced(int* pi)
	{
		refCount = 1;
		p = pi;
	}

	//
	int ref()
	{
		return ++refCount;
	}

	//
	int unref()
	{
		return --refCount;
	}

	//
	int count()
	{
		return refCount;
	}

	//
	~Referenced()
	{
		cout << "delete referenced" << endl;
		delete p;
	}
private:
	int refCount;//
	int* p;//
};

//
//
class  Ref_ptr
{
public:

	//
	Ref_ptr(int* i) :ptr(new Referenced(i))
	{
	}

	//
	Ref_ptr(const Ref_ptr& rhs)
	{
		ptr = rhs.ptr;//
		ptr->ref();//
	}

	//
	Ref_ptr& operator=(const Ref_ptr& rhs)
	{
		if (&rhs == this)
			return *this;
		if (ptr->unref() == 0)//
		{
			cout << "delete Ref_ptr" << endl;
			delete ptr;
		}
		ptr = rhs.ptr;//
		ptr->ref();//
		return *this;
	}

	//
	~Ref_ptr()
	{
		if (ptr->unref() == 0)
		{
			cout << "delete Ref_ptr" << endl;
			delete ptr;
		}
	}
private:
	Referenced* ptr;
};

int main()
{
	//Referenced rd=new int(4);
	Ref_ptr r = new int(4);
	Ref_ptr r1 = new int(5);
	r = r1;

	//getchar();
	return 0;
}