#include "stdc++.h"
#include <fstream>
#include <conio.h>
#include <string>


using namespace std;

class Person {
private:
	int postalCode;
	string name; 
	string family;
	string strasse; 
	int hausnummer; 
	string city;
	

public:
	// Default Constractor
	Person()
	{
		postalCode = 0;
		name = "no name";
		family = "no family";
		strasse = "no name";
		hausnummer = 0;
		city = "no name";
	}

	void getPersonData()
	{
		cout << "Enter person name, family, strasse, postalCode, hausenummer and city : ";
		cin >> name;
		cin >> family;
		cin >> strasse;
		cin >> postalCode;
		cin >> hausnummer;
		cin >> city;
	}

	void showPersonData()
	{
		cout << "\n"
			<< "name " << name << " family " << family << '\n'
			<< strasse << " " << postalCode << " " << hausnummer << "\n"
			<< " city is " << city;
	}

	// CreateReadUpdateDelete
	int storePerson();
	void viewAllPersons();
	void searchPerson(string);
	void deletePerson(string);
	void updatePerson(string);
};

void Person::updatePerson(string n)
{
	fstream file;  //Neveshtan dar file

	file.open("myfile2.txt", ios::in | ios::out | ios::ate | ios::binary); //betunim dakhelesh input output service. Becharkh file ro peida kon
	file.seekg(0);
	file.read((char*)this, sizeof(*this)); //file ro bekhun

	while (!file.eof()) { // Ta zamani k file b akharesh nereside
		if (n == name) { //agar nE peida shod
			getPersonData(); //ke etelaat ro bgirim dobare

			file.seekp(file.tellp()); //dar file ta ghabl az un andaze(ghabl az n) boro
			file.write((char*)this, sizeof(*this));
		}

		file.read((char*)this, sizeof(*this));
	}

	file.close();
}

void Person::deletePerson(string n)
{
	ifstream fin;
	ofstream fout;

	fin.open("myfile2.txt", ios::app | ios::binary);
	if (!fin)
		cout << "\n File not found ";
	else {
		fout.open("tempfile.txt", ios::app | ios::binary);
		fin.read((char*)this, sizeof(*this));

		while (!fin.eof())
		{
			if (name != n)
				fout.write((char*)this, sizeof(*this));
			fin.read((char*)this, sizeof(*this));
		}

		fin.close();
		fout.close();
		remove("myfile2.txt");
		rename("tempfile.txt", "myfile2.txt");
	}
}

void Person::searchPerson(string n) {
	int counter = 0;
	ifstream fin;
	fin.open("myfile2.txt", ios::in | ios::binary);

	if (!fin)
		cout << "\nThis file dose not exiest\n";
	else {
		fin.read((char*)this, sizeof(*this));

		while (!fin.eof())
		{
			if (n == name)
			{
				showPersonData();
				counter++;
			}
			fin.read((char*)this, sizeof(*this));
		}
		if (counter == 0) {
			cout << "not found record";
		}
		fin.close();
	}
}

void Person::viewAllPersons()
{
	ifstream fin;

	fin.open("myfile2.txt", ios::in | ios::binary);
	if (!fin)
		cout << "file not found";
	else {
		fin.read((char*)this, sizeof(*this));
		while (!fin.eof())
		{
			showPersonData();
			fin.read((char*)this, sizeof(*this));
		}

		fin.close();
	}
}


int Person::storePerson()
{
	if (name == "" && family == "") {
		cout << "person data is not valid";
		return(0);
	}
	else
	{
		ofstream fout;

		fout.open("myfile2.txt", ios::app | ios::binary);

		fout.write((char*)this, sizeof(*this));
		fout.close();
		return(1);
 	}
}


int menu()
{
	int choice;
	cout << "\nPerson managment : "
		<< "\n1.insert new person "
		<< "\n2.view all persons"
		<< "\n3.search for person"
		<< "\n4.delete person"
		<< "\n5.update person"
		<< "\n6.Exit"
		<< "\nEnter your choice : ";
	cin >> choice;
	return(choice);
}

int main()
{
	Person person;
	string n;
	while (true)
	{
		system("cls");

		switch (menu()) {
		case 1:
			person.getPersonData();
			person.storePerson();
			cout << "\nperson Insert successfuly\n";
			break;
		case 2:
			person.viewAllPersons();
			break;
		case 3:
			cout << "\nEnter person name for search :";
			cin.ignore();
			cin >> n;
			person.searchPerson(n);
			break;
		case 4:
			cout << "\nEnter person name for delete :";
			cin.ignore();
			cin >> n;
			person.deletePerson(n);
			break;
		case 5:
			cout << "\nEnter person name for update :";
			cin.ignore();
			cin >> n;
			person.updatePerson(n);
			break;
		case 6:
			cout << "thanks for using my app";
			_getch();
			exit(0);
		default:
			cout << "invalid input";
		}
		_getch();
	}
}