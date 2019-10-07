#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "HashTable.h"

using namespace std;

int main()
{
	HashTable<string, string> ht;
	ht.LoadFromFile("save.txt");
	ofstream fileout;
	string choose = "";
	string finddata;
	while (true)
	{
		cout << "Chose action:" << endl << "1 : Viev all" << endl << "2 : Add" << endl << "3 : Delete" << endl << "4 : Edit" << endl << "5 : Find" << endl << "6 : Save" << endl << "7 : Load" << endl << "n : Search Name" << endl << "l : Search Lastname" << endl << "f : Search Fathername" << endl << "m : Search Mail" << endl << "c : Search Company" << endl << "o : Search Prof" << endl << "p : Search Phone" << endl << "0 : Exit" << endl;
		cin >> choose;
		cout << endl;
		if (choose.length() != 1)
		{
			continue;
		}
		info book;
		string fileName;
		switch (choose[0])
		{
		case '1':
			cout << ht;
			break;
		case '2':
			cout << "Input data" << endl;
			while (cin >> book.firstName >> book.secondName >> book.fatherName >> book.phone >> book.mail >> book.company >> book.prof)
			{
				ht.Add(book.phone, book);
				break;
			}
			break;
		case '3':
			cout << "Input phone number: ";
			cin >> book.phone;
			ht.remove(book.phone);
			break;
		case '4':
			cout << "Input file name: ";
			cin >> fileName;
			ht.LoadFromFile(fileName);
			break;
		case '5':
			cout << "Input data: ";
			cin >> finddata;
			cout << ht.find(finddata);
			break;
		case '6':
			cout << "Input file name: ";
			fileName = "save.txt";
			fileout.open(fileName);
			if (!fileout.is_open())
			{
				cout << "Error. File is not correct." << endl;
				getchar();
				return 0;
			}
			fileout << ht;
			fileout.close();
			break;
		case '7':
			cout << "Input file name" << endl;
			cin >> fileName;
			ht.LoadFromFile(fileName);
			break;
		case 'n':
			cout << "Input data: ";
			cin >> book.firstName;
			cout << ht.find(book.firstName);
			break;
		case 'l':
			cout << "Input data: ";
			cin >> book.secondName;
			cout << ht.find(book.secondName);
			break;
		case 'f':
			cout << "Input data: ";
			cin >> book.fatherName;
			cout << ht.find(book.fatherName);
			break;
		case 'c':
			cout << "Input data: ";
			cin >> book.company;
			cout << ht.find(book.company);
			break;
		case 'o':
			cout << "Input data: ";
			cin >> book.prof;
			cout << ht.find(book.prof);
			break;
		case 'p':
			cout << "Input data: ";
			cin >> book.phone;
			cout << ht.find(book.phone);
			break;
		case 'm':
			cout << "Input data: ";
			cin >> book.mail;
			cout << ht.find(book.mail);
			break;
		case '0':
			fileout.open("save.txt");
			fileout << ht;
			fileout.close();
			return 0;
		default:
			cout << "Bad choose" << endl;
			break;
		}
		cout << endl;
	}
	getchar();
	return 0;
}