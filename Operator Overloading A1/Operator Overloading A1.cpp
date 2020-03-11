
// Operator Overloading A1
/*
201912191128 A1 Reference
*/
#include <iostream>
using namespace std;


class Point2D 
{
private:
	int _x;
	int _y;
public:
	Point2D();
	Point2D(int, int);
	int x() { return _x; }
	int y() { return _y; }
	Point2D operator+(const Point2D&); // Overload +
	Point2D operator-(const Point2D&); // Overload -
	Point2D& operator++(); // Overload ++p
	Point2D operator++(int); // Overload p++
	Point2D& operator--(); // Overload --p 
	Point2D operator--(int); // Overload p--

};

Point2D::Point2D() {
	_x = 0;
	_y = 0;
}

Point2D::Point2D(int x, int y) {
	_x = x;
	_y = y;
}

Point2D Point2D::operator+(const Point2D& p) {
	Point2D tmp(_x + p._x, _y + p._y);
	return tmp;
}

Point2D Point2D::operator-(const Point2D & p) {
	Point2D tmp(_x - p._x, _y - p._y);
	return tmp;
}

Point2D& Point2D::operator++() {
	_x++;
	_y++;

	return *this;
}

Point2D Point2D::operator++(int) {
	Point2D tmp(_x, _y);
	_x++;
	_y++;

	return tmp;
}

Point2D& Point2D::operator--() {
	_x--;
	_y--;

	return *this;
}

Point2D Point2D::operator--(int) {
	Point2D tmp(_x, _y);
	_x--;
	_y--;

	return tmp;
}

int main() {
	Point2D p1(5, 5);
	Point2D p2(10, 10);
	Point2D p3;

	p3 = p1 + p2;
	cout << "p3(x, y) = ("
		<< p3.x() << ", " << p3.y()
		<< ")" << endl;

	p3 = p2 - p1;
	cout << "p3(x, y) = ("
		<< p3.x() << ", " << p3.y()
		<< ")" << endl;

	p3 = ++p1;
	cout << "p3(x, y) = ("
		<< p3.x() << ", " << p3.y()
		<< ")" << endl;

	return 0;
}