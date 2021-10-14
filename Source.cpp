#include <iostream>
#include <string>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
bool l = 0, s = 0;
struct Diary {
	string Theme, Other;
	Diary* pr;
	Diary* ch;
};
Diary* head = NULL;
Diary* tail = NULL;
int sizo = 0;
void Add(Diary* adr, string th, string tx) {
	Diary* new_el = new Diary;
	new_el->Theme = th;
	new_el->Other = tx;

	if (adr == head && !l && s) {
		head = new_el;
		new_el->ch = adr;
		adr->pr = new_el;
		new_el->pr = NULL;
	}
	else if (adr == tail) {
		tail = new_el;
		adr->ch = new_el;
		new_el->ch = NULL;
		new_el->pr = adr;
	}
	else {
		Diary* temp = adr->ch;
		new_el->pr = adr;
		new_el->ch = temp;
		temp->pr = new_el;
		adr->ch = new_el;
	}
	sizo++;
}
Diary* Poz(int pos) {
	Diary* a;
	int siz;
	if (pos > sizo / 2 + sizo % 2) {
		a = tail;
		siz = sizo + 1;
		while (siz != pos) {
			siz--;
			a = a->pr;
		}
	}
	else {
		a = head;
		siz = 1;
		while (siz != pos) {
			a = a->ch;
			siz++;
		}
	}
	return(a);
}
void Pull() {
	Diary* a = head;
	for (int i = 0; i < sizo; ++i) {
		cout << i + 1 << ':' << endl << a->Theme << endl << a->Other << endl;
		a = a->ch;
	}
}
void Cl(Diary* adr) {
	Diary* pred, * chiled;
	if (adr == head)head = head->ch;
	if (adr == tail)tail = tail->pr;
	pred = adr->pr;
	chiled = adr->ch;
	if (pred != NULL)pred->ch = chiled;
	if (chiled != NULL)chiled->pr = pred;
	free(adr);
	sizo--;
}
int main() {
	setlocale(LC_ALL, "Rus");
	bool f = true;
	string tx, th;
	cout << "Welcome to the Diary" << endl << endl;
	//for (int i = 0; i < 500000000; ++i);
	while (f) {
		system("cls");
		cout << "0 - Add an entry" << endl;
		cout << "1 - Output all entries" << endl;
		cout << "2 - Delete an entry by number" << endl;
		cout << "3 - Burn the diary" << endl;
		cout << "I choose: ";
		char c;
		cin >> c;
		switch (c) {
		case'0':
			system("cls");
			cout << "Enter a subject: ";
			cin >> th;
			cout << "Enter the text: ";
			cin >> tx;
			if (sizo == 0) {
				Diary* m = new Diary;
				head = m;
				head->pr = NULL;
				tail = m;
				tail->ch = NULL;
				m->Theme = th;
				m->Other = tx;
				sizo++;
			}
			else {
				int k;
				cout << "At which position to create a record?(1-" << sizo + 1 << "): ";
				cin >> k;
				if (k == sizo + 1)l = true;
				else l = false;
				if (k == 1)s = true;
				else s = false;
				Add(Poz(k), th, tx);
				//if (k == 1)head = head->pr;
				//if (k == sizo - 1)tail = tail->ch;
			}
			break;
		case'1':
			Pull();
			char s;
			cout << "Enter any key to continue ";
			cin >> s;
			break;
		case'2':
			system("cls");
			cout << "Which record to delete?(1-" << sizo << "): ";
			int k;
			cin >> k;
			Cl(Poz(k));
			break;
		case '3':
			f = 0;
			break;
		}
	}
}