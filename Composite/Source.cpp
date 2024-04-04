#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  ������� ��������������, ���������� ������� � ����������� ��������� ��� ������������� �������� �� �������� � ������.
 *  ��������� �������� ������������ ���������� �������������� � ��������� �������.
	������� ���������� �������� �������, ������� ����� �������� �� ����������� � ������� ��������, �������� ����������� �������,
 *  ������ ������� ���������� ����� ����� ������� ����� �������.
 *
 * ���� �� ����� �������� ����������� - �������� �������� �� ������������� �����, �������� �� ��� � �������� ��� ��������� ��������.
 * ��� ���������� ���� ���� ����� Component ������ ������� ��� ����� ������ �������� ������ ��� ������� Composite � Leaf.
 * ������ ����� Component ������������� ��� ���� �������� ���������� �� ���������, � ��������� Composite � Leaf �������� ��.
 *
 * ����������:
 * - ���������� �������� �������, ��������� �� ����������� � ��������� ��������.
 * - �������� ����������� �������.
 * - ��������� ���������� ����� ����� �����������.
 * - ������������ �������� ������ �������
*/

/*
 Component
	- ��������� ��������� ��� ����������� ��������;
	- ������������� ���������� ���������� �������� �� ���������, ����� ��� ���� �������;
	- ��������� ��������� ��� ������� � �������� � ���������� ���;
	- ���������� ��������� ��� ������� � �������� ���������� � ����������� ��������� � ��� ������������� ��������� ���.
 */

class Component abstract
{
protected:
	string name;
	int price;	
public: 
	Component(string name)
	{
		this->name = name;
	}
	Component(string name, int price)		
	{
		this->name = name;
		this->price = price;	
	}


	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  void Display(int depth) abstract;
};

/*
 * Composite
 *  - ���������� ��������� �����������, � ������� ���� �������;
	- ������ ����������-�������;
	- ��������� ����������� � ���������� ��������� �������� � ���������� ������ Component;
*/

class Composite : public Component
{
	vector<Component*> components;

public:
	Composite(string name):Component(name){	}
	Composite(string name, int price) :Component(name, price) {	}		

	void Add(Component * component) override
	{
		components.push_back(component);
	}
	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << endl;	

		for(Component *component : components)
		{
			component->Display(depth + 2);
		}
	}
};
/*
 * Leaf
	- ������������ �������� ���� ���������� � �� ����� ��������;
	- ���������� ��������� ����������� �������� � ����������;
 */
class Leaf : public Component
{
public:
	Leaf(string name, int price): Component(name, price){}

	void Add(Component *c) override
	{
		cout << "Cannot add to file\n";
	}
	void Remove(Component *c) override
	{
		cout << "Cannot remove from file\n";
	}
	void Display(int depth) override
	{
		string s(depth, '-');
		cout << s + name << " - " << price << "$" << endl;	
	}
};

int main()
{
	// ������ ������������ ��������� ���������� ����� ��������� Component.

	Component *root = new Composite("Reception");
	Component* CoffeeTable = new Composite("Coffee table");

	CoffeeTable->Add(new Leaf("10-20 magazines of the �computer world� type", 32));	
	root->Add(CoffeeTable);	
	root->Add(new Leaf("Soft sofa", 47));	

	Component* SecretaryDesk = new Composite("Secretary desk");	
	Component* Computer = new Composite("Computer");

	Computer->Add(new Leaf("Having a large hard drive is important", 80));	
	SecretaryDesk->Add(Computer);
	SecretaryDesk->Add(new Leaf("Office tools", 127));		
	root->Add(SecretaryDesk);	
	root->Add(new Leaf("Cooler with warm and cold water", 3));	

	root->Display(1);
	cout << "\n\n";

	Component* firstAudience = new Composite("First Audience");	
	firstAudience->Add(new Leaf("10 tables", 150));	
	firstAudience->Add(new Leaf("Board", 30));	

	Component* TeachersTable = new Composite("Teacher's table");	
	TeachersTable->Add(new Leaf("Computer", 200));	
	firstAudience->Add(TeachersTable);	
	firstAudience->Add(new Leaf("Posters of great mathematicians", 10));	

	firstAudience->Display(1);	
	cout << "\n\n";

	Component* SecondAudience = new Composite("Second audience");
	Component* TwentyTables = new Composite("twenty tables");

	TwentyTables->Add(new Leaf("Black tables", 50));		
	SecondAudience->Add(TwentyTables);	
	SecondAudience->Add(new Leaf("Board", 50));
	SecondAudience->Add(new Leaf("Soft sofa", 87));			

	SecondAudience->Display(1);	
	cout << "\n\n";
		
	Component* ComputerAudience = new Composite("Computer audience");	
	Component* Ten�omputer�esks = new Composite("Ten computer desks");	
	Component* ComputerOnEvery�esk = new Composite("Computer on every desk");	
		
	ComputerOnEvery�esk->Add(new Leaf("Processor 2.2GHz", 110));	
	ComputerOnEvery�esk->Add(new Leaf("80 GB hard drive", 97));	
	ComputerOnEvery�esk->Add(new Leaf("RAM 1024MB", 137));	
	Ten�omputer�esks->Add(ComputerOnEvery�esk);	
	Ten�omputer�esks->Add(new Leaf("Socket near each table", 2));				
	ComputerAudience->Add(Ten�omputer�esks);

	Component* Board = new Composite("Board");
	Board->Add(new Leaf("Set of colorful markers", 5));	
	ComputerAudience->Add(Board);	

	ComputerAudience->Display(1);	
	cout << "\n\n";

	Component* DiningRoom = new Composite("Dining room");
	DiningRoom->Add(new Leaf("Coffee machine", 24));	
	Component* Table = new Composite("Table");	
	Table->Add(new Leaf("chair", 7));	
	DiningRoom->Add(Table);	
	DiningRoom->Add(new Leaf("Fridge", 100));
	DiningRoom->Add(new Leaf("Wash basin", 99));	


	DiningRoom->Display(1);	


	//root->Remove(leaf);
	//root->Display(1);

	//cout << "\n\n";
	//comp2->Remove(comp3);
	//root->Display(1);

	system("pause");
}


