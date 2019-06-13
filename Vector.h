#pragma once
#include <iostream>

using namespace std;

template <class T>
class Vector {
private:
	T *mass;
	int Capacity;
	static int count, Size;
public:
	Vector() {
		Size = 0;
		Capacity = 10;
		mass = new T[Capacity];
		count++;
	}
	Vector(int _Size) {
		Size = Capacity = _Size;
		mass = new T[Size];
		count++;
	}
	Vector(Vector<T>& other_mass) {
		this->Capacity = other_mass.Capacity;
		this->Size = other_mass.Size;
		this->mass = new T[other_mass.Size];
		for (int i = 0; i < other_mass.Size; i++)
			this->mass[i] = other_mass.mass[i];
		count++;
	}

	int Counter()
	{
		return count;
	}

	bool isEmpty()
	{
		return Size == 0;
	}

	int Find(T value)
	{
		for (int i = 0; i < Size; i++)
			if (mass[i] == value)
				return i;
		return -1;
	}

	void push_back(T element) {
		if (Size < Capacity) {
			mass[Size++] = element;
		}
		else  if (Size >= Capacity) {
			Capacity += 5;
			T *buf = new T[Capacity];
			for (int i = 0; i < Size; i++) {
				buf[i] = mass[i];
			}
			delete[] mass;
			mass = buf;
			push_back(element);
		}
	}

	T& operator[](int i) {
		return mass[i];
	}

	int size() {
		return Size;
	}

	bool operator>(const Vector<T> &obj)
	{
		if (this->Size != obj.Size)
			return false;
		else
		{
			for (int i = 0; i < Size; i++)
				if (!(this->mass[i] > obj.mass[i]))
					return false;
			return true;
		}
	}

	bool operator==(const Vector<T> &obj)
	{
		if (this->Size != obj.Size)
			return false;
		else
		{
			for (int i = 0; i < Size; i++)
				if (!(this->mass[i] == obj.mass[i]))
					return false;
			return true;
		}
	}

	T pop_back()
	{
		T temp = mass[--Size];
		mass[Size] = 0;
		return temp;

	}

	Vector<T> operator+(Vector<T> &obj)
	{
		int max = this->Size > obj.size() ? this->Size : obj.size();
		Vector<T> newObj;
	    for (int i = 0; i < max; i++)
				newObj.push_back(this->mass[i] + obj.mass[i]);
		return newObj;
	}

	Vector<T>& operator=(Vector<T> &obj)
	{
		return Vector(obj);
	}


	void Sort()
	{
		for (int i = 1; i < Size; i++)
			for (int j = i; j > 0 && mass[j] > mass[j - 1]; j--)
				swap(mass[j], mass[j - 1]);
	}
	
	void ShakerSort()
	{
		int leftMark = 1;
		int rightMark = Size - 1;
		while (leftMark <= rightMark)
		{
			for (int i = rightMark; i >= leftMark; i--)
				if (mass[i - 1] > mass[i]) swap(mass[i], mass[i-1]);
			leftMark++;


			for (int i = leftMark; i <= rightMark; i++)
				if (mass[i - 1] > mass[i]) swap(mass[i], mass[i-1]);
			rightMark--;
		}
	}

	void CountingSort() {
		int counter = 0;
		T max = mass[0];
		T min = mass[0];
		for (int i = 0; i < this->Size; i++) {
			if (mass[i] > max) max = mass[i];
			if (mass[i] <min) min = mass[i];
		}
		T **mas = new T *[max - min];
		for (int i = 0; i <max - min; i++)
		{
			mas[i] = new T[1];
		}
		for (int i = 0, k = min; i <max - min; i++, k++) {
			mas[0][i] = k;
		}

		for (int i = 0; i < this->Size; i++)
			for (int j = 0; j < max - max; j++)
				if (mas[0][j] == mass[i])mas[1][j];
		

	}

	void MergeSort() { 
		int lb = 0;
		int split = (this->Size - 1) / 2;
		int ub = this->Size - 1;
		
		long pos1 = lb;

		
		long pos2 = split + 1;

		
		long pos3 = 0;

		T *temp = new T[ub - lb + 1];

		
		while (pos1 <= split && pos2 <= ub) {
			if (mass[pos1] < mass[pos2])
				temp[pos3++] = mass[pos1++];
			else
				temp[pos3++] = mass[pos2++];
		}

		
		while (pos2 <= ub)    
			temp[pos3++] = mass[pos2++];
		while (pos1 <= split)  
			temp[pos3++] = mass[pos1++];

		
		for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
			mass[lb + pos3] = temp[pos3];

		
	}



	void QuickSort(int first=0, int last=Size-1)
	{
		if (first < last)
		{
			int left = first, right = last, middle = mass[(left + right) / 2];
			do
			{
				while (mass[left] > middle) left++;
				while (mass[right] < middle) right--;
				if (left <= right)
				{
					swap(mass[left], mass[right]);
					left++;
					right--;
				}
			} while (left <= right);
			QuickSort(first, right);
			QuickSort(left, last);
		}
	}


	void ShellsSort()
	{
		int j;
		T t;
		for (int k = Size / 2; k > 0; k /= 2)
			for (int i = k; i < Size; i++)
			{
				t = mass[i];
				for (j = i; j >= k; j -= k)
				{
					if (t < mass[j - k])
						mass[j] = mass[j - k];
					else
						break;
				}
				mass[j] = t;
			}
	}


	void SortSelection()
	{
		for (int i = 0; i < Size - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < Size; j++)
			{
				if (mass[j] < mass[min])
				{
					min = j;
				}
			}
			if (min != i) {
				swap(mass[i], mass[min]);
				min = i;
			}
		}
	}


	int BinarySearch(T value)
	{
		Sort();
		int tail = Size - 1, head = 0;

		while (head <= tail)
		{
			int mid = head + (tail - head) / 2;
			if (value < mass[mid]) { tail = mid - 1; }
			else if (value > mass[mid]) { head = mid + 1; }
			else return mid;
		}
		return -1;
	}

	 string BarrierSearchRight(T item) {
    this->array[n] = item;
    cout <<endl<< n<<endl;
    int i = 0;
    while (array[i] != item) {
      i++;
    }
    cout << i;
    if (i == n) { return "Wasn`t found"; }
    else return "Was find";
  }

  string BarrierSearchLeft(T item) {
    if (array[0]==item) return "Was find";
    T buf = array[0];
    array[0] = item;
    int i = n - 1;
    while (array[i] != item) {
      i--;
    }
    if (i == 0) { array[0] = buf; return "Wasn`t found"; }
    else { array[0] = buf; return "Was found"; }
  }


	int interpolationSearch(T toFind) {
		// Возвращает индекс элемента со значением toFind или -1, если такого элемента не существует
		Sort();
		int mid;
		int low = 0;
		int high = this->n - 1;

		while (mass[low] < toFind && mass[high] > toFind) {
			mid = low + ((toFind - mass[low]) * (high - low)) / (mass[high] - mass[low]);

			if (mass[mid] < toFind)
				low = mid + 1;
			else if (mass[mid] > toFind)
				high = mid - 1;
			else
				return 1;
		}

		if (mass[low] == toFind)
			return 1;
		if (mass[high] == toFind)
			return 1;

		return -1; // Not found
	}
	int Search_Gold(T var)
	{
		int i = 0, j = this->Size() - 1, m;
		while (i < j)
		{
			m = (i + j) / 2;
			if (var > this->mass[m])
				i = m + 1;
			else j = m;
		}
		if (this->mass[i] == var) return i;
		else return -1;
	}


	void resize(int _Size) {
		if (Size > _Size) 
		{
			Size = _Size;
			for (int i = Size; i < Capacity; i++)
				mass[i] = 0;
		}
		else 
		{
			Vector<T> bufmass(*this);
			delete[] this->mass;
			this->mass = new T[_Size];
			for (int i = 0; i < _Size; i++)
			{
				if (i >= Size)
					this->mass[i] = 0;
				else
					this->mass[i] = bufmass[i];
			}
			Size = Capacity = _Size;
	
		}
	}


	~Vector() {
		count--;
		delete[] mass;
	}

	
};

template<class T>
int Vector<T>::count=0;


template<class T>
int Vector<T>::Size;
