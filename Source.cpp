//���������� ������� � ����������� ������ ���������.
//������ � ����� �������� � ��������� � ������ AEROFLOT,
//���������� ��������� ���� :
//- �������� ������ ���������� �����;
//- ����� �����;
//- ��� ��������.
//������� �� ����� : ����� �����, ���������� � ����� ����������,
//�������� �������� ������� � ���������, ��������� � ����������.



//TODO()
//��������� ������� 
// 
// ����������,         DONE
//��������������,      DONE
// ��������,           DONE
// ������,             DONE
// ����������,         DONE
// ����������,		   DONE
// ���������� �� ����� DONE
// � �.�


#include <iostream>
#include <fstream>
#include <string>
#include<windows.h>
using namespace std;

int voc_size = -1;
string* vocab;

//// ��� ����������� ������ ������
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#define newDBG_NEW
//#endif
//#endif


//VOCAB
void get_vocab() {
	ifstream inp_file("D:\\in-outs\\aviakassa.com-slash-airplanes.txt");
	if (!inp_file.is_open()) {
		cout << "������ ��� �������� ����� �������..?\n" << endl;
	}

	if (inp_file.peek() == std::ifstream::traits_type::eof()) {
		cout << "������ �������\n" << endl;
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
	cout << "������� �������." << endl;
}
void print_vocab() {
	cout << "�������: " << endl;
	for (int i = 0; i < voc_size; i++)
		cout << vocab[i] << endl;
}

//STRUCTS
struct aflot {
	string where;
	int num;
	string type;

	aflot(string where, int num, string type);
	aflot();
	bool operator ==(aflot thing);
	void operator =(aflot thing);
};

aflot::aflot(string where, int num, string type) {
	this->where = where;
	this->num = num;
	this->type = type;
}
aflot::aflot() {
	this->where = "nowhere";
	this->num = 0;
	this->type = "no type";
};
bool aflot:: operator ==(aflot thing) {
	return (this->where == thing.where && this->num == thing.num && this->type == thing.type);
}
void aflot :: operator =(aflot thing) {
	this->num = thing.num;
	this->where = thing.where;
	this->type = thing.type;
}

struct LinearList {
	LinearList* next;
	aflot entry;

	LinearList* getTail();
	int getSize();
	LinearList* getIndex(int index);
	LinearList();
	void print();

};

LinearList* LinearList::getTail() {
	LinearList* tmp = this;
	while (tmp->next != NULL) tmp = tmp->next;
	return tmp;
}
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
	this->entry = aflot();
};
void LinearList::print() {
	LinearList* tmp = this;
	if (tmp == NULL) cout << "List empty." << endl;
	while (tmp != NULL) {
		cout << tmp->entry.where << " " << tmp->entry.num << " " << tmp->entry.type << " " << endl;
		tmp = tmp->next;
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
bool uniq_num(LinearList* head, int num) {
	LinearList* tmp = head;
	while (tmp != NULL) {
		if (tmp->entry.num == num) return false;
		tmp = tmp->next;
	}
	return true;
}
int inp_number() {
	int inpn;
	cin >> inpn;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\n�������� ������ ������ ��������� ������ �����. ������� ������: ";
		cin >> inpn;
	}
	return inpn;
}
string inp_type() {
	string inp;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cout << "������� ��� �������. ����� ������� ������ �����, ������� Enter: ";
	getline(cin, inp);
	while (!valid_type(inp)) {
		if (inp.empty()) {
			print_vocab();
		}
		else
			cout << "\n������ ���� ��� � �������.\n";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "������� ��� �������. ����� ������� ������ �����, ������� Enter: ";
		getline(cin, inp);
	}
	return inp;
}
string inp_where() {
	string inp;
	cout << "������� ����� ����������: ";
	cin >> inp;
	while (inp.find('/') != string::npos) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\n�������� ������ �� ������ ��������� ����� '/'.\n";
		cout << "������� ����� ����������: ";
		cin >> inp;
	}
	return inp;
}
aflot inp_entry(LinearList* head) {
	aflot new_e;
	string inp;

	cout << "������� ����� �����: ";
	int inpn = inp_number();

	while (!uniq_num(head, inpn)) {
		cout << "������ � ����� ������� ��� ����������.\n ������� ����� �����: ";
		inpn = inp_number();
	}
	new_e.num = inpn;

	cout << "������� ����� ����������: ";
	cin >> inp;
	while (inp.find('/') != string::npos) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\n�������� ������ �� ������ ��������� ����� '/'.\n" << "������� ����� ����������: ";
		cin >> inp;
	}
	new_e.where = inp;

	inp = inp_type();
	new_e.type = inp;
	return new_e;
}

//SORTS AND SEARCH
LinearList* merge_by(LinearList* one, LinearList* two, int by_what) {
	LinearList* result = NULL;

	/* Base cases */
	if (one == NULL)
		return (two);
	else if (two == NULL)
		return (one);

	bool condition = false;
	switch (by_what) {
	case 1:
		condition = one->entry.where.compare(two->entry.where) < 0;
		break;
	case 2:
		condition = one->entry.num < two->entry.num;
		break;
	case 3:
		condition = one->entry.type.compare(two->entry.type) < 0;
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
	//base case and one head??
	if (n == 1) return;
	LinearList* one = h;
	LinearList* two = h->getIndex(n / 2);
	one->getIndex((n / 2) - 1)->next = NULL;

	sort_by(one, n / 2, by_what);
	sort_by(two, n - n / 2, by_what);

	h = merge_by(one, two, by_what);
}
bool search(LinearList*& h) { // 1 where, 2 num, 3 type
	LinearList* tmp = h;
	int by_what;
	bool found = false;
	cout << "�������� ���� ������: 1 ��� ������ ����������, 2 ��� ������, 3 ��� ����: ";
	cin >> by_what;
	while (cin.fail() || (by_what < 1) || (by_what > 3)) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "������ �����, �������� ��������: "; cin >> by_what;
	}
	string anything;
	int num;
	//input + checks
	switch (by_what) {
	case 1:
		anything = inp_where();
		break;
	case 2:
		num = inp_number();
		break;
	case 3:
		anything = inp_type();
		break;
	}
	//search & print
	int i = 0;
	while (tmp != NULL) {
		switch (by_what) {
		case 1:
			if (tmp->entry.where == anything) {
				cout << "[" << i << "] " << tmp->entry.where << " " << tmp->entry.num << " " << tmp->entry.type << " " << endl;
				found = true;
			}
			break;
		case 2:
			if (tmp->entry.num == num) {
				cout << "[" << i << "] " << tmp->entry.where << " " << tmp->entry.num << " " << tmp->entry.type << " " << endl;
				return true;
			}
			break;
		case 3:
			if (tmp->entry.type == anything) {
				cout << "[" << i << "] " << tmp->entry.where << " " << tmp->entry.num << " " << tmp->entry.type << " " << endl;
				found = true;
			}
			break;
		}

		tmp = tmp->next;
		i++;
	}
	return found;
}

//MANIPULATION
void edit(LinearList*& tmp, LinearList* head){
	int what_to;
	string inp;
	cout << "������ "  << tmp->entry.where << " " << tmp->entry.num << " " << tmp->entry.type << " " << endl;
	cout << "����� �������� ����� ���������� ������� 1. ����� ����� 2. ��� ������� 3." << endl;
	cin >> what_to;
	while (cin.fail() || (what_to < 1) || (what_to > 3)) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "������ �����, �������� ��������: "; cin >> what_to;
	}
	switch (what_to) {
	case 1:
		inp = inp_where();
		tmp->entry.where = inp;
		break;
	case 2:
		cout << "����� ����� �����: ";
		what_to = inp_number();

		while (!uniq_num(head, what_to)) {
			cout << "\n������ � ����� ������� ��� ����������.\n";
			what_to = inp_number();
		}
		tmp->entry.num = what_to;
		break;
	case 3:
		inp = inp_type();
		tmp->entry.type = inp;
		break;
	}
	return;
}
void AddListElem(aflot elem, LinearList*& head) {
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
bool DeleteListItem(int index, LinearList*& head) {
	if (index == 0) { // item is in head: change head to next or nullify head
		if (head->next) {
			LinearList* temp = head->next;
			head->entry = head->next->entry;
			head->next = head->next->next;
			delete temp;
		}
		else head = NULL;
		return true;
	}
	else {
		LinearList* tempPrev = head->getIndex(index - 1);
		if (tempPrev == NULL) return false;
		LinearList* temp = tempPrev->next;
		if (temp == NULL) return false;
		tempPrev->next = temp->next;
		delete temp;
		return true;

	}
	return false;
}

//FILE
bool fstore(LinearList* head) {
	ofstream out_file("D:\\in-outs\\storage.txt");
	if (!out_file.is_open()) {
		cout << "������ ��� �������� �����..?\n" << endl;
		return false;
	}
	LinearList* tmp = head;
	while (tmp != NULL) {
		out_file << tmp->entry.num << "/" << tmp->entry.type << "/" << tmp->entry.where << "/" << endl;
		tmp = tmp->next;
	}
	out_file.close();
	return true;
}
bool fget(LinearList*& head) {
	ifstream inp_file("D:\\in-outs\\storage.txt");
	if (!inp_file.is_open()) {
		cout << "������ ��� �������� �����..?\n" << endl;
		return false;
	}
	string str;
	while (!inp_file.eof()) {
		aflot new_entry;
		getline(inp_file, str);
		if (str.empty()) continue;
		int pos = 0;
		string part; 

		int i = 0;
		while ((pos = str.find('/')) != string::npos)
		{
			if (i > 2) {
				cout << "������ " << str << " ����� �������� ������." << endl;
				break;
			}
			part = str.substr(0, pos); 
			auto it = part.begin();
			switch (i)
			{
			case 0:
				while (it != part.end() && isdigit(*it)) ++it;
				if (part.empty() || it != part.end()) {
					cout << "������ " << str << " ����� �������� ������." << endl;
					break;
				}
				new_entry.num = stoi(part);
				break;
			case 1:
				new_entry.type = part;
				break;
			case 2:
				new_entry.where = part;
				break;
			}
			i++;
			str.erase(0, pos + 1);  // erase() function store the current positon and move to next part
		}
		AddListElem(new_entry, head);
	}
	inp_file.close();
	return true;
}

//DELETE
void clear(LinearList*& head) {
	if (head->next) clear(head->next);
	delete head;
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
		cout << "������� 1, ����� �������� ������." << endl;
		cout << "������� 2, ����� ������� ������ �� �������." << endl;
		cout << "������� 3, ����� ��������������� ������ �� �������." << endl;
		cout << "������� 4, ����� ����� ������." << endl;
		cout << "������� 5, ����� ������� ������ �� �����." << endl;
		cout << "������� 6, ����� ��������� ������ � ����." << endl;
		cout << "������� 7, ����� ��������� ������ �� �����." << endl;
		cout << "������� 8, ����� ������������� ������." << endl;
		cout << "������� 9 ��� ������." << endl;

		cin >> menu_state;
		if (menu_state == 1) {
			AddListElem(inp_entry(list), list);
			cout << "������ ���������." << endl;
			menu_state = 0;
		}
		else if (menu_state == 2) { //�� �������
			cout << "������� ������ ������ ��� �������� (� 0): ";

			inpn = inp_number();
			if (DeleteListItem(inpn, list))
				cout << "������ �������." << endl;
			else
				cout << "������ ��� ����� �������� ���." << endl;
			menu_state = 0;
		}
		else if (menu_state == 3) {
			cout << "������� ������ ������ ��� �������������� (� 0): ";

			inpn = inp_number();
			LinearList* elem = list->getIndex(inpn);
			if (elem == NULL) {
				cout << "������ ��� ����� �������� ���." << endl;
				menu_state = 0;
				continue;
			}
			edit(elem, list);
			cout << "�������!" << endl;
			menu_state = 0;
		}
		else if (menu_state == 4) {
			if (!search(list)) cout << "����� ������� ���." << endl;
			menu_state = 0;
		}
		else if (menu_state == 5) {
			list->print();
			menu_state = 0;
		}
		else if (menu_state == 6) {
			if (fstore(list)) cout << "�������!" << endl;
			menu_state = 0;
		}
		else if (menu_state == 7) {
			LinearList* new_l = NULL;
			if (fget(new_l)) {
				list = new_l;
				cout << "�������!" << endl;
			}
			menu_state = 0;
		}
		else if (menu_state == 8) {
			cout << "����� ������������� �� ������ ���������� ������� 1. �� ������ ����� 2. �� ���� ������� 3." << endl;
			cin >> inpn;
			while (cin.fail() || (inpn < 1) || (inpn > 3)) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "������ �����, �������� ��������: " << endl;
				cin >> inpn;
			}
			sort_by(list, list->getSize(), inpn);
			cout << "������ ������������." << endl;
			menu_state = 0;
		}
		else if (menu_state == 9) {
			break;
		}
		else {
			cout << "�������� ����." << endl;
			menu_state = 0;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	}

	clear(list);
	delete[] vocab;

	//// ��� ����������� ������ ������
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	//_CrtDumpMemoryLeaks();

	return 0;
}
