#include "Libs.h"

void enterNum(int* num) {
	*num = 0;

	int counter = 0;

	while (counter < 9) {
		char butt = _getch();
		if (butt > 47 && butt < 58) {
			*num = (*num * 10) + (butt - 48);
			printf("%c", butt);
			counter++;
		}
		else if (butt == 8 && counter != 0) {
			*num /= 10;
			if (*num == 1) {
				*num = 0;
			}
			putchar('\b');
			printf(" ");
			putchar('\b');
			if (counter > 0) counter--;
		}
		else if (butt == 13) {
			break;
		}
	}
	printf("\n");
}

class CostErr {
	int ErrCode;
public:
	CostErr() : ErrCode(0) {}
	CostErr(int num) : ErrCode(num) {}
	void what() { cout << "\n\nДанные введены неверно!\n"; }
};

class UpperClothes {
	int cost;
	string name;
	string _class;
	int productClass;
public:
	UpperClothes() : cost(0), productClass(0) {}

	void SetCost(int num) { cost = num; }
	int GetCost() { return cost; }

	void SetName(string _name) { name = _name; }
	string GetName() { return name; }

	void SetProdClass(int num) {
		productClass = num;
		if (num == 1) _class = "Худи";
		else if (num == 2) _class = "Пуховик";
		else if (num == 3) _class = "Парка";
	}
	bool isHoodie() {
		if (productClass == 1) return true;
		else return false;
	}
	bool isJaket() {
		if (productClass == 2) return true;
		else return false;
	}
	bool isParka() {
		if (productClass == 3) return true;
		else return false;
	}

	friend ostream& operator<<(ostream& stream, UpperClothes& obj) {
		cout << obj._class << " " << obj.GetName() << " " << obj.GetCost() << "$" << endl;
		return stream;
	}
};

class Hoodie : public UpperClothes {
public:
	Hoodie(string name, int cost) { SetProdClass(1); SetName(name); if (cost < 0) throw 1; SetCost(cost); }
	~Hoodie() { cout << "Данные введены неверно!"; }
};

class Jaket : public UpperClothes {
public:
	Jaket(string name, int cost) { SetProdClass(2); SetName(name); SetCost(cost); }
};

class Parka : public UpperClothes {
public:
	Parka(string name, int cost) { SetProdClass(3); SetName(name); SetCost(cost); }
};

class Cart {
	vector<UpperClothes> cart;
	int totalCost = 0;
public:
	Cart() : cart(NULL) {}
	void AddSome(UpperClothes* obj) {
		cart.push_back(*obj);
		totalCost += obj->GetCost();
	}
	void ShowCart() {
		if (cart.size() == 0) throw 1;
		for (int i = 0; i < cart.size(); i++) {
			cout << i + 1 << ") " << cart[i] << endl;
		}
		cout << "Итоговая стоимость: " << totalCost;
	}
	int GetTotalCost() { return totalCost; }
};