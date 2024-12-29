#include<iostream>
#include<string>
#include<vector>
#include<initializer_list>
using namespace std;

template<class T>
void getValue(string prompt, T& value)
{
	cout << prompt;
	cin >> value;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Error... try again" << endl;
		cout << prompt;
		cin >> value;
	}
	string endLine;
	getline(cin, endLine);
}

template<>
inline void getValue<string>(string prompt, string& value)
{
	cout << prompt;
	getline(cin, value);
}


template<class T>
class Array
{
	size_t currentSize = 0;
	size_t maxSize = 0;
	size_t grow = 1;
	T* data;

public:
	Array(const initializer_list<T>& list) : Array(list.size())
	{
		int i = 0;
		for (auto& t : list)
		{
			data[i] = t;
		}
	}
	Array() : data{ nullptr } {}
	Array(size_t size) :Array(size, 1) {}
	Array(size_t size, size_t g) : data{ new T[size]() }, maxSize{ size }, currentSize{ size }, grow{ g } {}
	size_t GetSize()
	{
		return maxSize;
	}

	void SetSize(size_t size)
	{
		if (size > maxSize)
		{
			T* t = new T[size]();
			for (int i = 0; i < currentSize; i++)
			{
				t[i] = data[i];
			}
			delete data;
			data = t;
			maxSize = size;
			currentSize = size;
		}
		else
		{
			currentSize = size;
		}
	}
	void SetGrow(size_t g = 1)
	{
		grow = g;
	}
	size_t GetUpperBound()
	{
		return currentSize;
	}
	bool IsEmpty()
	{
		return currentSize == 0 ? true : false;
	}
	void FreeExtra()
	{
		T* t = new T[currentSize]();
		for (int i = 0; i < currentSize; i++)
		{
			t[i] = data[i];
		}
		delete data;
		data = t;
		maxSize = currentSize;
	}

	void RemoveAll()
	{
		delete data;
		data = nullptr;
		maxSize = 0;
		currentSize = 0;
	}

	T GetAt(size_t i)
	{
		if (i < currentSize)
			return data[i];
		else
			return 0;
	}

	void SetAt(size_t i, T v)
	{
		if (i < currentSize)
			data[i] = v;
	}

	void Add(T e)
	{
		if (currentSize == maxSize)
			maxSize++;
		currentSize++;
		data[currentSize] = e;
	}

	void Append(Array a2)
	{
		currentSize += a2.currentSize;
		if (maxSize < currentSize)
			maxSize = currentSize;
		for (int i = currentSize - a2.currentSize + 1; i < currentSize + 1; i++)
		{
			data[i] = a2.data[i - currentSize + a2.currentSize - 1];
		}
	}

	Array operator=(Array a2)
	{
		bool isEqual = true;
		for (int i = 0; i < ((currentSize > a2.currentSize) ? currentSize : a2.currentSize); i++)
		{
			if (data[i] != a2.data[i])
			{
				isEqual = false;
			}
		}
		return isEqual;
	}

	T* Getdata()
	{
		return *data;
	}

	void InsertAt(size_t index, Array d2)
	{
		for (int i = index; i < d2.currentSize; i++)
		{
			data[i] = d2.data[i - index];
		}
	}

	void RemoveAt(size_t index, int n)
	{
		for (int i = index; i <= n; i++)
		{
			data[i] = data[i + n];
		}
		currentSize -= n;
	}
};

int main()
{
	return 0;
}