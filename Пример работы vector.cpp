// Пример работы vector.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include "Vector.h"

using namespace std;

void Input(Vector<int> &_MassVector);
void Output(Vector<int> &_MassVector);

int main()
{
	Vector<int> MassVector;
	int n;
	srand(unsigned(time(NULL)));
	setlocale(LC_ALL, "ru");
	cout << "Введите размер массива: ";
	cin >> n;
	MassVector.resize(n);
	Input(MassVector);
	Vector<int> a = MassVector;
	Vector<int> b = a + MassVector;
	Output(a);
	a.push_back(20);
	cout << endl;
	/*cout<<a.BinarySearch(20)<<endl;*/
	a.CountingSort();
	Output(a);
	
	//Vector<int> b = a + MassVector;
	//Output(b);

	system("pause");
    return 0;
}

void Input(Vector<int> &_MassVector)
{
	for (int i = 0; i < _MassVector.size(); i++) 
		_MassVector[i] = rand() % 100 - 50;
}

void Output(Vector<int> &_MassVector)
{
	for (int i = 0; i < _MassVector.size(); i++) 
		cout << _MassVector[i] << '\t';
}



