#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  Паттерн проектирования, объединяет объекты в древовидную структуру для представления иерархии от частного к целому.
 *  Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
	Паттерн определяет иерархию классов, которые могут состоять из примитивных и сложных объектов, упрощает архитектуру клиента,
 *  делает процесс добавления новых видов объекта более простым.
 *
 * Одна из целей паттерна компоновщик - избавить клиентов от необходимости знать, работают ли они с листовым или составным объектом.
 * Для достижения этой цели класс Component должен сделать как можно больше операций общими для классов Composite и Leaf.
 * Обычно класс Component предоставляет для этих операций реализации по умолчанию, а подклассы Composite и Leaf замещают их.
 *
 * Результаты:
 * - определяет иерархии классов, состоящие из примитивных и составных объектов.
 * - упрощает архитектуру клиента.
 * - облегчает добавление новых видов компонентов.
 * - способствует созданию общего дизайна
*/

/*
 Component
	- объявляет интерфейс для компонуемых объектов;
	- предоставляет подходящую реализацию операций по умолчанию, общую для всех классов;
	- объявляет интерфейс для доступа к потомкам и управления ими;
	- определяет интерфейс для доступа к родителю компонента в рекурсивной структуре и при необходимости реализует его.
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
 *  - определяет поведение компонентов, у которых есть потомки;
	- хранит компоненты-потомки;
	- реализует относящиеся к управлению потомками операции в интерфейсе класса Component;
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
	- представляет листовые узлы композиции и не имеет потомков;
	- определяет поведение примитивных объектов в композиции;
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
	// Клиент манипулирует объектами композиции через интерфейс Component.

	Component *root = new Composite("Reception");
	Component* CoffeeTable = new Composite("Coffee table");

	CoffeeTable->Add(new Leaf("10-20 magazines of the “computer world” type", 32));	
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
	Component* TenСomputerВesks = new Composite("Ten computer desks");	
	Component* ComputerOnEveryВesk = new Composite("Computer on every desk");	
		
	ComputerOnEveryВesk->Add(new Leaf("Processor 2.2GHz", 110));	
	ComputerOnEveryВesk->Add(new Leaf("80 GB hard drive", 97));	
	ComputerOnEveryВesk->Add(new Leaf("RAM 1024MB", 137));	
	TenСomputerВesks->Add(ComputerOnEveryВesk);	
	TenСomputerВesks->Add(new Leaf("Socket near each table", 2));				
	ComputerAudience->Add(TenСomputerВesks);

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


