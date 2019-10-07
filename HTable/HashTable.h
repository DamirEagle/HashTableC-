#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#define MAX_SIZE 256

using namespace std;
struct info
{
	string phone;
	string firstName;
	string secondName;
	string fatherName;
	string mail;
	string company;
	string prof;
	friend ostream & operator << (ostream &stream, const info&I)
	{
		stream << I.firstName << " " << I.secondName << " " << I.fatherName << " " << I.phone << " " << I.mail << " " << I.company << " " << I.prof << endl;
		return stream;
	}
};

template<typename T, typename K>
struct record
{
	int key;
	list<info> values;
};

template<typename T, typename K>
class HashTable
{
private:
	vector<record<T, K> > _table;
public:
	class Iterator
	{
	public:
		Iterator(T* curr);
		Iterator& operator ==(const Iterator& I);
		Iterator& operator ++();
		T operator *();
		T* operator ->();
	private:
		T* current;
	};
	HashTable();
	unsigned int Hashing(string Key)const;
	HashTable &Add(T Key, struct info&data);
	void remove(T Key);
	void removeAll();
	void reduct(T searchString);
	friend ostream &operator << <T, K>(ostream& stream, const HashTable<T, K>&HT);
	void LoadFromFile(string fileName);
	void SaveToFile(string fileName);
	info operator[](string person);
	info find(T searchString);
};

template<typename T, typename K>
HashTable<T, K>::Iterator::Iterator(T* curr) :current(curr) {}

template<typename T, typename K>
typename HashTable<T, K>::Iterator& HashTable<T, K>::Iterator::operator++()
{
	++current;
	return *this;
}

template<typename T, typename K>
T HashTable<T, K>::Iterator:: operator *()
{
	return *current;
}

template<typename T, typename K>
T* HashTable<T, K>::Iterator:: operator ->()
{
	return current;
}


template<typename T, typename K>
HashTable<T, K>::HashTable()
{
	_table.resize(MAX_SIZE);
}

template<typename T, typename K>
unsigned int HashTable<T, K>::Hashing(string key)const
{
	unsigned int hash, i;
	for (hash = i = 0; i < key.length(); ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash % MAX_SIZE;
}

template<typename T, typename K>
HashTable<T, K> &HashTable<T, K>::Add(T Key, struct info&data)
{
	int hKey;
	hKey = Hashing(Key);
	_table[hKey].values.push_back(data);
	_table[hKey].key = hKey;
	return *this;
}


template<typename T, typename K>
info HashTable<T, K>::operator[](string person)
{
	unsigned int ht = Hashing(person);
	for (auto it = _table[ht].values.begin(); it != _table[ht].values.end(); it++)
	{
		if (it->phone == person)
			return(*it);
	}
	cout << "Not found";
	info tmp;
	return tmp;
}

template<typename T, typename K>
void HashTable<T, K>::LoadFromFile(string fileName)
{
	removeAll();
	ifstream fin(fileName);
	if (!fin.is_open())
	{
		cout << "Open file error." << endl;
		getchar();
		return;
	}
	for (auto it = _table.begin(); it != _table.end(); it++)
	{
		info book;
		while (fin >> book.firstName >> book.secondName >> book.fatherName >> book.phone >> book.mail >> book.company >> book.prof)
		{
			this->Add(book.phone, book);
		}
	}
	fin.close();
}



template<typename T, typename K>
void HashTable<T, K>::remove(T Key)
{
	int hKey = Hashing(Key);
	for (auto it = _table.begin(); it != _table.end(); it++)
	{
		if (it->key == hKey)
		{
			for (auto il = it->values.begin(); il != it->values.end(); il++)
			{
				il->firstName = "";
				il->secondName = "";
				il->fatherName = "";
				il->phone = "";
				il->mail = "";
				il->company = "";
				il->prof = "";
				return;
			}
		}
	}
	return;
}

template<typename T, typename K>
void HashTable<T, K>::removeAll()
{
	for (auto it = _table.begin(); it != _table.end(); it++)
	{
		if (it->key != 0)
			*it = record<T, K>();
	}
	return;
}

template<typename T, typename K>
info HashTable<T, K>::find(T searchString)
{
	for (auto it = _table.begin(); it != _table.end(); it++)
	{
		for (auto il : (*it).values)
		{
			if (il.firstName == searchString || il.secondName == searchString || il.fatherName == searchString || il.phone == searchString || il.company == searchString || il.prof == searchString || il.mail == searchString)
				return (il);
		}
	}
	info struc;
	return struc;
}

template<typename T, typename K>
void HashTable<T, K>::reduct(T searchString)
{
	for (auto it = _table.begin(); it != _table.end(); it++)
	{
		for (auto il : (*it).values)
		{
			if (il.firstName == searchString || il.secondName == searchString || il.fatherName == searchString || il.phone == searchString || il.company == searchString || il.prof == searchString || il.mail == searchString)
			{
				this->remove(il.phone);
				cout << "Input new data" << endl;
				info book;
				while (cin >> book.firstName >> book.secondName >> book.fatherName >> book.phone >> book.mail >> book.company >> book.prof)
				{
					this->Add(book.phone, book);
					break;
				}
			}
		}
	}
}

template<typename T, typename K>
ostream &operator << (ostream &stream, const HashTable<T, K>&HS)
{
	for (auto it = HS._table.begin(); it != HS._table.end(); it++)
	{
		if (it->key != 0)
		{
			for (auto it1 = it->values.begin(); it1 != it->values.end(); it1++)
			{
				stream << it1->firstName << " " << it1->secondName << " " << it1->fatherName << " " << it1->phone << " " << it1->mail << " " << it1->company << " " << it1->prof << endl;
			}
		}
	}
	return stream;
}