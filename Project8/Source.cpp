#include<iostream>
#include<fstream>
#include<Windows.h>
using namespace std;
class Student {
	char* name;
	int age;
	int size;
	int* marks;
	float avgMark;

	void SetAverageMark() {
		int sum = 0;
		for (int i = 0; i < size; i++)
			sum += marks[i];
		avgMark = float(sum) / size;
	}
public:
	Student(const char* name = "No name", int age = 0):age(0), avgMark(0), size(0){
		this->name = nullptr;
		marks = nullptr;
		setName(name);
		setAge(age);
	}
	void AddMark(int mark) {
		if (mark < 1 || mark>12) {
			cout << "Incorrect mark.";
			return;
		}
		int* newMarks = new int[++size];
		for (int i = 0; i < size - 1; i++)
			newMarks[i] = marks[i];
		newMarks[size - 1] = mark;
		delete[]marks;
		marks = newMarks;
		SetAverageMark();
	}

	void print()const {
		cout << "Name: " << name << endl << "Age: " << age << endl;
		cout << "Marks: ( ";
		for (int i = 0; i < size; i++)
			cout << marks[i] << " ";
		cout<< ")\nAverage mark: " << avgMark << endl;
	}
	void setAge(int age) {
		if (age >=0 && age <=100)
		this->age = age;
	}
	void setName(const char* name) {
		delete[]this->name;
			this->name = new char[strlen(name) + 1];
			strcpy_s(this->name, strlen(name) + 1, name);
	}
	void setMark(int indexMark, int mark) {
		if (mark < 1 || mark>12) {
			cout << "Incorrect mark.\n";
			return;
		}
		if (indexMark<0 || indexMark>size-1) {
			cout << "Incorrect mark index.\n";
			return;
		}
		marks[indexMark] = mark;
		SetAverageMark();
	}
	int getMark(int indexMark)const {
		if (indexMark >= 0 && indexMark < size)
			return marks[indexMark];
		else
			return 0;
	}
	int getAge()const{
		return age;
	}
	float getAvgMark()const{
		return avgMark;
	}
	const char* getName()const {
		return name;
	}
		void Save()const {
			ofstream fout;
			fout.open("Student.txt");
			bool isOpen = fout.is_open();
			if (isOpen == false) {
				system("cls");
				cout << "The file couldn't be opened.\n";
				Sleep(2500);
				return;
			}
			fout << name << endl << age << endl << size << endl;
			for (int i = 0; i < size; i++)
				fout << marks[i] << endl;
			fout << avgMark;
			fout.close();
		}
		void Load() {
			ifstream fin;
			fin.open("Student.txt");
			bool isOpen = fin.is_open();
			if (isOpen == false) {
				system("cls");
				cout << "The file couldn't be opened.\n";
				Sleep(2500);
				return;
			}
			char Name[60];
			fin.getline(Name, 60);
			setName(Name);
			fin >> age;
			fin >> size;
			delete[]marks;
			marks = new int[size];
			for (int i = 0; i < size; i++)
				fin >> marks[i];
			fin >> avgMark;
			fin.close();
		}
	~Student() {
		delete[]name;
		delete[]marks;
	}
};


int main() {
	Student st1("Karyna", 19),st2;
	cout << "First student:\n";
	st1.print();
	cout << "\nAdd first mark:\n";
	st1.AddMark(12);
	st1.print();
	cout << "\nSave first student.\n";
	st1.Save();
	cout << "\nAdd secons mark:\n";
	st1.AddMark(11);
	st1.print();
	cout << "\nSet mark:\n";
	st1.setMark(1,9);
	st1.print();
	cout << "\nSecond student:\n";
	st2.print();
	cout << "\nLoad student in second student.\n";
	st2.Load();
	st2.print();
	cout << "\nAdd mark to second student.\n";
	st2.AddMark(10);
	st2.print();
	return 0;
}