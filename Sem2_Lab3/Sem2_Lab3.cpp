#include "Menu.h"
#include "Libs.h"
#include "Classes.h"

vector<UpperClothes> arr;
Cart cart;

template <class T> T enter() {
	T tmp;
	while (true) {
		cin >> tmp;
		if (cin.good()) {
			break;
		}
		cin.clear();
	}
}

void TermFunc() {
	cout << "Была вызвана функция завершения";
	exit(-1);
}

void addHoodie() {
	Hoodie* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "Введите название: ";
		cin >> name;
		cout << "Введите стоимость: ";
		cin >> cost;
		try {
			tmp = new Hoodie(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (...) {
			cout << "\n\nДанные введены неверно!\n";
			char sym;
			cout << "Повторить ввод? (y/n): ";
			cin >> sym;
			if (sym == 'n') break;
		}
	}
}

void addJaket() {
	Jaket* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "Введите название: ";
		cin >> name;
		cout << "Введите стоимость: ";
		cin >> cost;
		try {
			if (cost < 0) throw new CostErr(cost);
			tmp = new Jaket(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (CostErr* exeption) {
			exeption->what();
			char sym;
			cout << "Повторить ввод? (y/n): ";
			cin >> sym;
			if (sym == 'n') break;
		}
	}
}

void addParka() {
	Parka* tmp;
	string name;
	int cost;
	while (1) {
		system("cls");
		cout << "Введите название: ";
		cin >> name;
		cout << "Введите стоимость: ";
		cin >> cost;
		try {
			if (cost < 0) throw cost;
			tmp = new Parka(name, cost);
			arr.push_back(*tmp);
			break;
		}
		catch (int exeption) {
			cout << "\n\nДанные введены неверно (стоимость " << exeption << " < 0)\n";
			char sym;
			cout << "Повторить ввод? (y/n): ";
			cin >> sym;
			if (sym == 'n') break;
		}
	}
}

void ShowAll() {
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			cout << i + 1 << ") " << arr[i] << endl;
		}
	}
	catch (int) {
		cout << "Нет товаров!";
	}
}

void ShowHoodie() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isHoodie()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "Нет товаров!";
	}
	catch (bool) {
		cout << "Нет товаров данной категории!";
	}
}

void ShowJaket() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isJaket()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "Нет товаров!";
	}
	catch (bool) {
		cout << "Нет товаров данной категории!";
	}
}

void ShowParka() {
	int counter = 1;
	bool exist = false;
	try {
		if (arr.size() == 0) throw 1;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i].isParka()) {
				cout << counter << ") " << arr[i] << endl;
				counter++;
				exist = true;
			}
		}
		if (exist == false) throw false;
	}
	catch (int) {
		cout << "Нет товаров!";
	}
	catch (bool) {
		cout << "Нет товаров данной категории!";
	}
}

void SetCart() {
	while (1) {
		system("cls");
		ShowAll();

		int choise;
		cout << "Введите номер товара: ";
		cin >> choise;
		try {
			if (choise < 1 || choise > arr.size()) throw 1;
			cart.AddSome(&arr[choise - 1]);
			break;
		}
		catch (int) {
			cout << "\n\nТакого номера нет!";
			char sym;
			cout << "Повторить ввод? (y/n): ";
			cin >> sym;
			if (sym == 'n') break;
		}
	}
}

void ShowCart() {
	try {
		cart.ShowCart();
	}
	catch (int) {
		cout << "Корзина пуста\n\n";
		cout << "Итоговая стоимость: " << cart.GetTotalCost();
	}
}

int main() {
	Menu menu;
	set_terminate(TermFunc);

	menu.CreateMenu(3, "Добавить товар", "Просмотреть товары", "Корзина");
	{
		menu.sub[0].CreateMenu(3, "Худи", "Пуховик", "Парка");
		{
			menu.sub[0].function[0] = addHoodie;
			menu.sub[0].function[1] = addJaket;
			menu.sub[0].function[2] = addParka;
		}
		menu.sub[1].CreateMenu(4, "Худи", "Пуховики", "Парки", "Все");
		{
			menu.sub[1].function[0] = ShowHoodie;
			menu.sub[1].function[1] = ShowJaket;
			menu.sub[1].function[2] = ShowParka;
			menu.sub[1].function[3] = ShowAll;
		}
		menu.sub[2].CreateMenu(2, "Добавить в корзину", "Показать корзину");
		{
			menu.sub[2].function[0] = SetCart;
			menu.sub[2].function[1] = ShowCart;
		}
	}

	bool running = true;
	while (running)
	{
		menu.ShowMenu();
		menu.Navigation(&running);
	}
}