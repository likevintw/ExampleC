/*
Vector example R1
*/

#include <iostream>
#include <vector> //for vector
using namespace std;
int main()
{
	cout << "Vector Example" << endl;
	vector <int> v1(10, 1); //std::vector <int> v1;
	cout << "v1.size(): " << v1.size() << endl;
	for (int i(0); i < v1.size(); i++)
	{
		v1[i] = i;
	}
	//The first method to present values
	for (int i(0); i < v1.size(); i++)
	{
		cout << v1[i] << endl;
	}
	//The second method to present values
	for (int i(0); i < v1.size(); i++)
	{
		cout << v1.at(i) << endl;
	}
}

/*
vec.push_back() - 新增元素至 vector 的尾端，必要時會進行記憶體配置。
vec.pop_back() - 刪除 vector 最尾端的元素。
vec.insert() - 插入一個或多個元素至 vector 內的任意位置。
vec.erase() - 刪除 vector 中一個或多個元素。
vec.clear() - 清空所有元素。
vec.empty() - 如果 vector 內部為空，則傳回 true 值。
vec.size() - 取得 vector 目前持有的元素個數。
vec.resize() - 改變 vector 目前持有的元素個數。
vec.capacity() - 取得 vector 目前可容納的最大元素個數。這個方法與記憶體的配置有關，它通常只會增加，不會因為元素被刪減而隨之減少。
重新配置／重設長度
vec.reserve() - 如有必要，可改變 vector 的容量大小（配置更多的記憶體）。在眾多的 STL 實做，容量只能增加，不可以減少。
*/

