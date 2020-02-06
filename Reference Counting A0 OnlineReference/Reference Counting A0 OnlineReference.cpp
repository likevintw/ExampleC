#include <iostream>
#include <string>

using namespace std;

class Referenced 
{
public:
	//初始化這個類，引用計數設爲1，並且將p指向傳入的地址
	Referenced(int * pi)
	{
		refCount=1;
		p=pi;
	}

	//引用計數加1
	int ref()
	{
		return ++refCount;
	}	

	//引用計數減1
	int unref()
	{
		return --refCount;
	}

	//返回引用計數
	int count()
	{
		return refCount;
	}

	//析構函數，釋放掉內存
	~Referenced()
	{
		cout<<"delete referenced"<<endl;
		delete p;
	}
private:
	int refCount;//引用計數，表示有多少個變量引用這塊內存
	int * p;//真實的指針
};

//對指針進行管理的類，持有一個Referenced類的指針ptr，根據ptr中的
//引用計數來判斷是否調用delete來刪除掉這個指針ptr
class  Ref_ptr
{
public:

	//使用int*指針初始化ptr，注意必須要放在初始化列表中
	Ref_ptr(int * i):ptr(new Referenced(i))
	{
	}

	//拷貝構造函數，又有一個變量指向了這塊內存
	Ref_ptr(const Ref_ptr & rhs)
	{
		ptr=rhs.ptr;//將右操作數的引用計數對象賦值給左操作數
		ptr->ref();//將它們的應用計數加1
	}

	//賦值操作符，右操作數的引用計數要減1，左操作數的引用計數要加1
	Ref_ptr & operator=(const Ref_ptr & rhs)
	{
		if(&rhs==this)
			return *this;
		if(ptr->unref()==0)//賦值操作符，首先將當前類的引用計數減1
		{
			cout<<"delete Ref_ptr"<<endl;
			delete ptr;
		}
		ptr=rhs.ptr;//將右操作數的引用計數賦值給當前對象
		ptr->ref();//引用計數加1
		return *this;
	}

	//析構函數，引用計數要減1，如果減爲0，刪除這塊內存
	~Ref_ptr()
	{
		if(ptr->unref()==0)
		{
			cout<<"delete Ref_ptr"<<endl;
			delete ptr;
		}
	}
private:
	Referenced * ptr;
};

int main()
{
	//Referenced rd=new int(4);
	Ref_ptr r=new int(4);
	Ref_ptr r1=new int(5);
	r=r1;

	getchar();
	return 0;
}