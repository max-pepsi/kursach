//Предметная область – «Расписание рейсов самолетов».
//Данные о рейсе хранятся в структуре с именем AEROFLOT,
//содержащей следующие поля :
//- название пункта назначения рейса;
//- номер рейса;
//- тип самолета.
//Задание на поиск : найти рейсы, вылетающие в пункт назначения,
//название которого совпало с названием, введенным с клавиатуры.



//TODO()
//отдельные функции 
// 
// добавления,         DONE
//редактирования,      DONE
// удаления,           DONE
// поиска,             DONE
// сортировки,         DONE
// сохранения,		   DONE
// считывания из файла DONE
// и т.д


/*
ИСПРАВИТЬ
+ при вводе пункта назначения с пробелом вводится только первое слово
+ тип самолёта не case-insensetive (принудительный ввод типа самолёта все заглавные?) +
+ при выводе добавить названия полей и индексы. сделать с setw()

+ при удалении, поиске и сортировке в пустом списке должо выводиться, что он пустой (до ввода данных)
+ так как номер уникален, реализовать удаление по номеру (по индексу можно оставить)

+ разрешить смену номера со своего на свой
+ после "запись с таким номером уже существует" нет предложения ввести новый номер

+ удаление и редактирование после сортировки сломано
+ происходит удаление записи с индексом -1

сортировка сортирует большие буквы последними
+(сделать принудительный ввод пункта назначения с заглавной буквы)



+ тестовые примеры из failed storage.txt должны выдавать неверную запись
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include<windows.h>
using namespace std;

int voc_size = -1;
string* vocab;


//VOCAB
void get_vocab() {
	ifstream inp_file("D:\\in-outs\\aviakassa.com-slash-airplanes.txt");
	if (!inp_file.is_open()) {
		cout << "Ошибка при открытии файла словаря\n" << endl;
	}

	if (inp_file.peek() == std::ifstream::traits_type::eof()) {
		cout << "Пустой словарь\n" << endl;
	}
	int n = 0;
	string str;
	while (!inp_file.eof()) {
		getline(inp_file, str);
		if (!str.empty()) n++;
	}
	string* voc = new string[n];
	inp_file.clear();
	inp_file.seekg(0);
	for (int i = 0; i < n; i++) {
		getline(inp_file, str);
		if (!str.empty()) voc[i] = str;
	}
	vocab = voc;
	inp_file.close();
	voc_size = n;
	cout << "Словарь обновлён." << endl;
}
void print_vocab() {
	cout << "Словарь: " << endl;
	for (int i = 0; i < voc_size; i++)
		cout << vocab[i] << endl;
}

//STRUCTS
struct AEROFLOT {
	string destination;
	int num;
	string type;

	AEROFLOT(string destination, int num, string type);
	AEROFLOT();
	bool operator ==(AEROFLOT thing);
	void operator =(AEROFLOT thing);
};

AEROFLOT::AEROFLOT(string destination, int num, string type) {
	this->destination = destination;
	this->num = num;
	this->type = type;
}
AEROFLOT::AEROFLOT() {
	this->destination = "nowhere";
	this->num = 0;
	this->type = "no type";
};
bool AEROFLOT:: operator ==(AEROFLOT thing) {
	return (this->destination == thing.destination && this->num == thing.num && this->type == thing.type);
}
void AEROFLOT :: operator =(AEROFLOT thing) {
	this->num = thing.num;
	this->destination = thing.destination;
	this->type = thing.type;
}

struct LinearList {
	LinearList* next;
	AEROFLOT entry;

	int getSize();
	LinearList* getIndex(int index);
	LinearList();
	void print();
};

int LinearList::getSize() {
	if (this == NULL) return 0;
	int s = 1;
	LinearList* tmp = this;
	while (tmp->next != NULL) { tmp = tmp->next; s++; }
	return s;
}
LinearList* LinearList::getIndex(int index) {
	LinearList* tmp = this;
	for (int i = 0; i < index; i++) {
		if (tmp->next != NULL) tmp = tmp->next;
		else return NULL;
	}
	return tmp;
}
LinearList::LinearList() {
	this->next = NULL;
	this->entry = AEROFLOT();
};
void LinearList::print() {
	LinearList* tmp = this;
	int i = 0;
	if (tmp == NULL) { cout << "Пустой список." << endl; return; }
	cout << " №    рейс      тип    пункт назначения" << endl;
	cout << "----------------------------------------" << endl;
	while (tmp != NULL) {
		cout << "[" << i << "] ";
		cout << setw(5) << tmp->entry.num << " ";
		cout << setw(10) << tmp->entry.type << "   ";
		cout << tmp->entry.destination << endl;
		tmp = tmp->next;
		i++;
	}
}

//CHECKS
bool valid_type(string type) {
	if (type.empty()) return false;
	for (int i = 0; i < voc_size; i++) {
		if (vocab[i] == type) return true;
	}
	return false;
}
void to_upper(string& s) {
	for (int i = 0; i < s.size(); i++) {
		(s[i] = toupper(s[i]));
	}
}
void to_uplow(string& s) {
	if (s.size() == 0) return;
	
	s[0] = toupper(s[0]);
	for (int i = 1; i < s.size(); i++) {
		(s[i] = tolower(s[i]));
	}
}
bool uniq_num(LinearList* head, int num) {
	LinearList* tmp = head;
	while (tmp != NULL) {
		if (tmp->entry.num == num) return false;
		tmp = tmp->next;
	}
	return true;
}
int inp_number() {
	int inpn = -1;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> inpn;
	while (cin.fail() || inpn < 0) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введённая строка должна содержать положительное число. Введите заново: ";
		cin >> inpn;
	}
	return inpn;
}
string inp_type() {
	string inp;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cout << "Введите тип самолёта. Чтобы вывести список типов, нажмите Enter: ";
	getline(cin, inp);
	to_upper(inp);
	while (!valid_type(inp)) {
		if (inp.empty()) {
			print_vocab();
		}
		else
			cout << "Такого типа нет в словаре.\n";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введите тип самолёта. Чтобы вывести список типов, нажмите Enter: ";
		getline(cin, inp);
		to_upper(inp);
	}
	return inp;
}
string inp_destination() {
	string inp;
	cout << "Введите пункт назначения: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, inp);
	while (inp.find('/') != string::npos) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Название пункта не должно содержать знака '/'.\n";
		cout << "Введите пункт назначения: ";
		getline(cin, inp);
	}
	to_uplow(inp);
	return inp;
}
AEROFLOT inp_entry(LinearList* head) {
	AEROFLOT new_e;
	string inp;

	cout << "Введите номер рейса: ";
	int inpn = inp_number();
	while (!uniq_num(head, inpn)) {
		cout << "Запись с таким номером уже существует.\nВведите номер рейса: ";
		inpn = inp_number();
	}
	new_e.num = inpn;

	inp = inp_type();
	new_e.type = inp;

	inp = inp_destination();
	new_e.destination = inp;

	return new_e;
}
bool my_str_compare(string s1, string s2) {
	if (s1.size() != s2.size()) return false;
	for (int i = 0; i < s1.size(); i++) {
		if (tolower(s1[i]) != tolower(s2[i])) return false;
	}
	return true;
}


//SORTS AND SEARCH
LinearList* merge_by(LinearList* one, LinearList* two, int by_what) {
	LinearList* result = NULL;

	//Base cases
	if (one == NULL)
		return (two);
	else if (two == NULL)
		return (one);

	bool condition = false;
	switch (by_what) {
	case 1:
		condition = one->entry.num < two->entry.num;
		break;
	case 2:
		condition = one->entry.type.compare(two->entry.type) < 0;
		break;
	case 3:
		condition = one->entry.destination.compare(two->entry.destination) < 0;
		break;
	}

	// Pick either a or b, and recur
	if (condition) {
		result = one;
		result->next = merge_by(one->next, two, by_what);
	}
	else {
		result = two;
		result->next = merge_by(one, two->next, by_what);
	}

	return (result);
}
void sort_by(LinearList* &h, int n, int by_what) {
	if (n < 2) return;
	//base case and one head??
	LinearList* one = h;
	LinearList* two = h->getIndex(n / 2);
	one->getIndex((n / 2) - 1)->next = NULL;

	sort_by(one, n / 2, by_what);
	sort_by(two, n - n / 2, by_what);

	h = merge_by(one, two, by_what);
}
void sort_start(LinearList*& head) {
	if (head == NULL) {
		cout << "Пустой список." << endl;
		return;
	}
	if (head->next == NULL) {
		cout << "Список отсортирован." << endl;
		return;
	}
	int by_what = -1;
	cout << "Введите чтобы отсортировать: 1 по номеру рейса; 2 по типу самолёта; 3 по пункту назначения." << endl;
	cin >> by_what;
	while (cin.fail() || (by_what < 1) || (by_what > 3)) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Ошибка ввода, выберите действие: " << endl;
		cin >> by_what;
	}
	sort_by(head, head->getSize() , by_what);
	cout << "Список отсортирован." << endl;
}
bool search(LinearList*& h) { // 1 where, 2 num, 3 type
	if (h == NULL) {
		cout << "Пустой список." << endl;
		return true;
	}
	LinearList* tmp = h;
	int by_what;
	bool found = false;
	cout << "Выберите поле поиска: 1 для номера рейса, 2 для типа, 3 для пункта назначения." << endl;
	cin >> by_what;
	while (cin.fail() || (by_what < 1) || (by_what > 3)) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Ошибка ввода, выберите действие: "; cin >> by_what;
	}
	string anything;
	int num = 0;
	//input + checks
	switch (by_what) {
	case 1:
		num = inp_number();
		break;
	case 2:
		anything = inp_type();
		break;
	case 3:
		anything = inp_destination();
		break;
	}
	//search & print
	int i = 0;

	while (tmp != NULL) {
		if (by_what == 1 && tmp->entry.num == num) {
			cout << " №    рейс      тип    пункт назначения" << endl;
			cout << "----------------------------------------" << endl;
			cout << "[" << i << "] ";
			cout << setw(5) << tmp->entry.num << " ";
			cout << setw(10) << tmp->entry.type << "   ";
			cout << tmp->entry.destination << endl;
			return true;
		}
		if (by_what == 2 && tmp->entry.type == anything || by_what == 3 && tmp->entry.destination == anything) {
			if (!found) {
				cout << " №    рейс      тип    пункт назначения" << endl;
				cout << "----------------------------------------" << endl;
				found = true;
			}
			cout << "[" << i << "] ";
			cout << setw(5) << tmp->entry.num << " ";
			cout << setw(10) << tmp->entry.type << "   ";
			cout << tmp->entry.destination << endl;
		}
		tmp = tmp->next;
		i++;
	}
	return found;
}

//MANIPULATION
void edit(LinearList*& head){
	if (head == NULL) {
		cout << "Пустой список." << endl;
		return;
	}
	cout << "Введите индекс записи для редактирования (с 0): ";
	int index = inp_number();
	LinearList* tmp = head->getIndex(index);
	if (tmp == NULL) {
		cout << "Записи под таким индексом нет." << endl;
		return;
	}
	int what_to;
	string inp;
	cout << "Запись "  << tmp->entry.num << " " << tmp->entry.type << " " << tmp->entry.destination << " " << endl;
	cout << "Введите чтобы изменить: 1 для номера рейса; 2 типа самолёта; 3 пункта назначения." << endl;
	cin >> what_to;
	while (cin.fail() || (what_to < 1) || (what_to > 3)) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Ошибка ввода, выберите действие: "; cin >> what_to;
	}
	switch (what_to) {
	case 1:
		cout << "Новый номер рейса: ";
		what_to = inp_number();
		if (what_to == tmp->entry.num) break;
		while (!uniq_num(head, what_to)) {
			cout << "Запись с таким номером уже существует.\nНовый номер рейса: ";
			what_to = inp_number();
			if (what_to == tmp->entry.num) break;
		}
		tmp->entry.num = what_to;
		break;
	case 2:
		inp = inp_type();
		tmp->entry.type = inp;
		break;
	case 3:
		inp = inp_destination();
		tmp->entry.destination = inp;
		break;
	}
	cout << "Успешно!" << endl;
	return;
}
void AddListElem(AEROFLOT elem, LinearList*& head) {
	LinearList* newCell = new LinearList;
	newCell->entry = elem;
	newCell->next = NULL;
	if (head == NULL) head = newCell;
	else {
		LinearList* tmp = head;
		while (tmp->next != NULL) { 
			tmp = tmp->next;
			if (tmp->entry == newCell->entry) return;
		}
		tmp->next = newCell;
	}
}
void DeleteIndex(LinearList*& head) {
	if (head == NULL) {
		cout << "Пустой список." << endl;
		return;
	}
	cout << "Введите индекс записи для удаления (с 0): ";
	int index = inp_number();
	if (index >= head->getSize()) {
		cout << "Записи с таким индексом нет в списке." << endl;
		return;
	}
	if (index == 0) { // item is in head: change head to next or nullify head
		if (head->next) {
			LinearList* temp = head;
			head = head->next;
			delete temp;
		}
		else head = NULL;
		cout << "Запись удалена." << endl;
		return;
	}
	else {
		LinearList* tempPrev = head->getIndex(index - 1);
		LinearList* temp = tempPrev->next;
		tempPrev->next = temp->next;
		delete temp;
		cout << "Запись удалена." << endl;
		return;

	}
}
void DeleteNumber(LinearList*& head) {
	if (head == NULL) {
		cout << "Пустой список." << endl;
		return;
	}
	cout << "Введите номер рейса для удаления: ";
	int number = inp_number();
	if (number == head->entry.num) { // item is in head: change head to next or nullify head
		if (head->next) {
			LinearList* temp = head;
			head = head->next;
			delete temp;
		}
		else head = NULL;
		cout << "Запись удалена." << endl;
		return;
	}
	LinearList* tempPrev = head;
	LinearList* temp = tempPrev->next;
	while (temp != NULL) {
		if (temp->entry.num == number) {
			tempPrev->next = temp->next;
			delete temp;
			cout << "Запись удалена." << endl;
			return;
		}
		else {
			tempPrev = tempPrev->next;
			temp = temp->next;
		}
	}
	cout << "Записи с таким номером нет." << endl;
	return;
}

//DELETE
void clear(LinearList*& head) {
	if (head == NULL) return;
	if (head->next) clear(head->next);
	delete head;
}

//FILE
bool fstore(LinearList* head) {
	ofstream out_file("D:\\in-outs\\out storage.txt");
	if (!out_file.is_open()) {
		cout << "Ошибка при открытии файла..?" << endl;
		return false;
	}
	LinearList* tmp = head;
	while (tmp != NULL) {
		out_file << tmp->entry.num << "/" << tmp->entry.type << "/" << tmp->entry.destination << "/" << endl;
		tmp = tmp->next;
	}
	out_file.close();
	return true;
}
bool fget(LinearList*& head) {
	ifstream inp_file("D:\\in-outs\\storage.txt");
	if (!inp_file.is_open()) {
		cout << "Ошибка при открытии файла..?" << endl;
		return false;
	}
	clear(head);
	head = NULL;
	string inp_line;
	while (!inp_file.eof()) {
		AEROFLOT new_entry;
		getline(inp_file, inp_line);
		string str = inp_line;
		if (str.empty()) continue;
		int pos = 0;
		string part; 

		int i = 0;
		bool wrong = false;
		while ((pos = str.find('/')) != string::npos)
		{
			if (i > 2) {
				wrong = true;
				break;
			}
			part = str.substr(0, pos); 
			auto it = part.begin();
			switch (i)
			{
			case 0:
				while (it != part.end() && isdigit(*it)) ++it;
				if (part.empty() || it != part.end()) {
					wrong = true;
					break;
				}
				if (!uniq_num(head, stoi(part))) {
					wrong = true;
					break;
				}
				new_entry.num = stoi(part);
				break;
			case 1:to_upper(part);
				if (!valid_type(part)) {
					wrong = true;
					break;
				}
				new_entry.type = part;
				break;
			case 2:
				to_uplow(part);
				new_entry.destination = part;
				break;
			}
			if (wrong) break;
			i++;
			str.erase(0, pos + 1);  // erase() function store the current positon and move to next part
		}
		if (i < 2 || wrong) {
			cout << "Запись \"" << inp_line << "\" имеет неверный формат." << endl;
			continue;
		}
		AddListElem(new_entry, head);
	}
	inp_file.close();
	return true;
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	get_vocab();
	int inpn;
	LinearList* list = NULL;

	int menu_state = 0;
	while (menu_state == 0) {
		cout << "1 - Добавить запись" << endl;
		cout << "2 - Удалить запись по индексу" << endl;
		cout << "3 - Удалить запись по номеру рейса" << endl;
		cout << "4 - Отредактировать запись по индексу" << endl;
		cout << "5 - Найти запись" << endl;
		cout << "6 - Вывести список на экран" << endl;
		cout << "7 - Сохранить список в файл" << endl;
		cout << "8 - Загрузить список из файла" << endl;
		cout << "9 - Отсортировать список" << endl;
		cout << "10 - Выход" << endl;

		cin >> menu_state;
		if (menu_state == 1) {
			AddListElem(inp_entry(list), list);
			cout << "Запись добавлена." << endl;
			menu_state = 0;
		}
		else if (menu_state == 2) { //по индексу
			DeleteIndex(list);
			menu_state = 0;
		}
		else if (menu_state == 3) { //по номеру
			DeleteNumber(list);
			menu_state = 0;
		}
		else if (menu_state == 4) {
			edit(list);
			menu_state = 0;
		}
		else if (menu_state == 5) {
			if (!search(list)) cout << "Таких записей нет." << endl;
			menu_state = 0;
		}
		else if (menu_state == 6) {
			list->print();
			menu_state = 0;
		}
		else if (menu_state == 7) {
			if (fstore(list)) cout << "Успешно!" << endl;
			menu_state = 0;
		}
		else if (menu_state == 8) {
			LinearList* new_l = NULL;
			if (fget(new_l)) {
				list = new_l;
				cout << "Успешно!" << endl;
			}
			menu_state = 0;
		}
		else if (menu_state == 9) {
			sort_start(list);
			menu_state = 0;
		}
		else if (menu_state == 10) {
			break;
		}
		else {
			cout << "Неверный ввод." << endl;
			menu_state = 0;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	}

	clear(list);
	delete[] vocab;

	return 0;
}
