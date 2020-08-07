#include<iostream>
#include"vector.h"
using namespace std;

int main(){
	Vector a = Vector();
	try{
		cout << a[0] << '\n';
	}
	catch(exception& e){
		cout << "woups" << '\n';
	}
	a.push_back(12);
	cout << a[0] << '\n';
	Vector b = Vector(a);
	cout << b[0] << '\n';
	Vector c = Vector{1,3,4};
	cout << c[2] << '\n';
	c = b;
	cout << c[0] << '\n';
	c[0] = 5;
	cout << c[0] << '\n';
	cout << b[0] << '\n';

	cout << "Size, empty, clear \n";
	cout << a.size() << '\n';
	a.empty() ? cout << "yes \n" : cout << "no \n";
	a.clear();
	cout << a.size() << '\n';
	a.empty() ? cout << "yes \n" : cout << "no \n";

	cout << "Pop back and [] \n";
	Vector d = Vector{5,6,7,8};
	d.pop_back();
	try{
		cout << d[3] << '\n';
	}
	catch(exception e){
		cout << "woups2" << '\n';
	}

	return 0;
}