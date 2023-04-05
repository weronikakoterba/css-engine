#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"DoubleLinkedList.h"
using namespace std;


typedef enum {
	START,
	SELECTORS,
	SELSPACE,
	ATTRIBUTESNAME,
	ATTRIBUTESVALUE,
	COMMANDS,
	NEWBLOCK,
	SECTIONEND,
	SELECTORSEND,
	ATTSPACE
} Mode;


struct sections {
	DoubleLinkedList<attribute>* attr;
	DoubleLinkedList<char*>* sel;
};

char* copy(char* tmp) {
	char* result = new char[CSS_NAME];
	for (int i = 0; tmp[i - 1] != '\0'; i++) result[i] = tmp[i];
	return result;
}
char* copy(char* source, char* destination) {
	for (int i = 0; source[i - 1] != '\0'; i++) destination[i] = source[i];
	return destination;
}

int isLetter(char* tab) {
	if (atoi(tab) == 0) return 1;
	return 0;
}

void addSelectors(Mode& state, sections& section, DoubleLinkedList<char*>*& firstSel, char* tab,int i) {
	DoubleLinkedList<char*>* nodeSel;
	if (state == SECTIONEND || state == NEWBLOCK) {
		section.sel = new DoubleLinkedList<char*>(CSS_NAME);
		section.attr = new DoubleLinkedList<attribute>(1);
		firstSel = section.sel;
		section.sel->insertElement(copy(tab), firstSel);
	}
	else if (state != START) {
		nodeSel = section.sel->seekSelName(section.sel, tab);
		if (nodeSel == NULL) {
			firstSel = section.sel->addLast(section.sel);
			section.sel->insertElement(copy(tab), firstSel);
		}
		else section.sel->insertElement(copy(tab), nodeSel);	
	}
	else {
		section.sel->insertElement(copy(tab), firstSel);
	}

}

int countAllSel(DoubleLinkedList<sections>* first, char* tab) {
	int sum = 0;
	for (int i = 0; i < first->getSecNumber(first); i++) {
		sum += first->getElement(i).sel->countRepSel(first->getElement(i).sel, tab);
	}
	return sum;

}

int countAllAttr(DoubleLinkedList<sections>* first, char* tab) {
	int sum = 0;
	for (int i = 0; i < first->getSecNumber(first); i++) {
		sum += first->getElement(i).attr->countRepAttr(first->getElement(i).attr, tab);
	}
	return sum;

}



char* removeWhiteSpaces( char* tab, int i) {
	while (tab[i] <= ' ') {
		tab[i] = '\0';
		i--;
	}
	return tab;
}


void addAttributes(DoubleLinkedList<attribute>*& nodeAttr, sections& section, attribute& at, bool rep, DoubleLinkedList<attribute>*& firstAttr){
	nodeAttr = section.attr->seekAttrName(section.attr, at.name);
	if (nodeAttr == NULL) {
		if (rep != false) {
			section.attr->addLast(section.attr);
		}
		firstAttr = section.attr->getLast(section.attr);
		section.attr->insertAttr(at, firstAttr);
	}
	else section.attr->insertAttr(at, nodeAttr);
}

int main() {// pousuwac new, same atrybuty nie dzia³aja,komendy usuwanie

	bool rep = false;
	Mode state = START;
	DoubleLinkedList<sections>* first = new DoubleLinkedList<sections>(SIZE);
	DoubleLinkedList<sections>* last = first;

	sections section;
	section.sel = new DoubleLinkedList<char*>(CSS_NAME);
	section.attr = new DoubleLinkedList<attribute>(1);

	attribute at;
	char tab[CSS_NAME];
	int i = 0;

	DoubleLinkedList<char*>* nodeSel;
	DoubleLinkedList<attribute>* nodeAttr;

	while (cin.peek() != EOF) {
		char input = getchar();
		DoubleLinkedList<char*>* firstSel = section.sel->getLast(section.sel);
		DoubleLinkedList<attribute>* firstAttr;
		tab[i] = input;
		if (tab[i] > ' ' || state == ATTRIBUTESVALUE || (( state==START || state==NEWBLOCK || state==SECTIONEND || state==SELECTORS) && tab[i] != '\n' && tab[i]!='\t')) i++;
		else continue;
		if (state == ATTSPACE) state = ATTRIBUTESVALUE;
		if (state == SELSPACE) state = SELECTORS;
		switch (input) {
		case ',':
			if (state == ATTRIBUTESVALUE || state == COMMANDS) break;
			tab[i - 1] = '\0';
			addSelectors(state, section, firstSel, removeWhiteSpaces(tab, i-1),i-1);
			state = SELSPACE;
			i = 0;
			break;
		case '{':
			rep = false;
			if (state == COMMANDS)break;
			tab[i - 1] = '\0';
			addSelectors(state, section, firstSel, removeWhiteSpaces(tab, i-1),i-1);
			state = SELECTORSEND;
			i = 0;
			break;
		case '}':
			if (state == COMMANDS)break;
			if (state == ATTRIBUTESVALUE) {
				tab[i - 1] = '\0';
				copy(tab, at.value);
				addAttributes(nodeAttr, section, at, rep, firstAttr);
				i = 0;
				rep = false;
			}
			first->insertSection(section, first,&last);
			state = SECTIONEND;
			i = 0;
			break;
		case ';':
			if (state == COMMANDS)break;
			state = ATTRIBUTESNAME;
			tab[i - 1] = '\0';
			copy(tab, at.value);
			addAttributes(nodeAttr, section, at, rep, firstAttr);
			i = 0;
			rep = true;
			break;
		case ':':
			if (state == COMMANDS || state == START || state == SELECTORS || state == SECTIONEND)break;
			state = ATTSPACE;
			tab[i - 1] = '\0';
			copy(tab, at.name);
			i = 0;
			break;
		case '?':
			tab[i - 1] = '\0';
			if (state == COMMANDS) {
				if (i < 2 || tab[i - 2] != ',') {
					/*cout << section.sel->getLen(section.sel) << endl;

					cout << first->getLen(first) << endl;
					section.sel->print2(section.sel);*/
					//section.attr->print3(section.attr);
					cout << "? == " << first->getSecNumber(first) << endl;
					//section.sel->print2(section.sel);
					//cout << section.attr->getLen(section.attr) << endl;
					//section.attr->print3(section.attr);
					//first->print(first);
				}
			}
			else {
				char second = getchar();
				char third = getchar();
				char fourth = getchar();
				if (second == '?' && third == '?' && fourth == '?') {
					state = COMMANDS;
				}
			}
			i = 0;
			break;
		case '*':
			if (state == COMMANDS) {
				tab[i - 1] = '\0';
				char second = getchar();
				char third = getchar();
				char fourth = getchar();
				if (second == '*' && third == '*' && fourth == '*' && state == COMMANDS) state = NEWBLOCK;
				i = 0;
			}
			break;
		case 'E':
			if (state == COMMANDS) {
				if (i >= 2 && tab[i - 2] == ',') {
					tab[i - 2] = '\0';
					char* sel = copy(tab);
					char letter = getchar();
					if (letter == ',') {
						i = 0;
						char nextletter = getchar();
						if ((nextletter >= 'a' && nextletter <= 'z') || (nextletter >= 'A' && nextletter <= 'Z')) {
							tab[i] = nextletter;
							i++;
							while (true) {
								char a = getchar();
								if (a == '\n') break;
								tab[i] = a;
								i++;
							}
							tab[i] = '\0';
							if (first->findNodeFromEnd(last, sel, tab) != NULL) 
							cout << sel<<",E," <<tab<<" == " << first->findNodeFromEnd(last, sel, tab)<<endl;
						}
					}
				}
				i = 0;
			}
			break;
		case 'S':
			if (state == COMMANDS) {
				tab[i - 1] = '\0';
				if (i >= 2 && tab[i - 2] == ',') {
					tab[i - 2] = '\0';
					int check = isLetter(tab);
					if (check == 0) {
						int sectionNumber = atoi(tab);
						char letter = getchar();
						if (letter == ',') {
							i = 0;
							char nextletter = getchar();
							if (nextletter >= '0' && nextletter <= '9') {
								tab[i] = nextletter;
								i++;
								while (getchar() != '\n') {
									tab[i] = getchar();
									i++;
								}
								tab[i] = '\0';
								int selectorNumber = atoi(tab);
								if ((first->contain(sectionNumber - 1) == false) || (first->getElement(sectionNumber - 1).sel->contain(first->getElement(sectionNumber - 1).sel,selectorNumber - 1) == false)) {
									i = 0;
									break;
								}
								cout << sectionNumber << ",S," << selectorNumber << " == " << first->getElement(sectionNumber - 1).sel->getElement(first->getElement(sectionNumber - 1).sel,selectorNumber - 1) << endl;
							}
							else if (nextletter == '?') {
								if (first->SelInSection(first, atoi(tab)) == -1) {
									i = 0;
									break;
								}
								cout << atoi(tab) << ",S,? == " << first->SelInSection(first, atoi(tab)) << endl;
							}
						}
					}
					else {
						char letter = getchar();
						char nextletter = getchar();
						if (letter == ',' && nextletter == '?') {
							cout << tab << ",S,? == " << countAllSel(first, tab) << endl;
						}
					}
				}
				i = 0;
			}
			break;
		case 'A':
			if (state == COMMANDS) {
				tab[i - 1] = '\0';
				if (i >= 2 && tab[i - 2] == ',') {
					tab[i - 2] = '\0';
					int check = isLetter(tab);
					if (check == 0) {
						int sectionNumber = atoi(tab);
						char letter = getchar();
						if (letter == ',') {
							i = 0;
							char nextletter = getchar();
							if ((nextletter >= 'a' && nextletter <= 'z') || (nextletter >= 'A' && nextletter <= 'Z')) {
								tab[i] = nextletter;
								i++;
								while (true) {
									char a = getchar();
									if (a == '\n') break;
									tab[i] = a;
									i++;
								}
								tab[i] = '\0';
								if ((first->contain(sectionNumber - 1) == false) || first->getElement(sectionNumber - 1).attr->findNode(first->getElement(sectionNumber - 1).attr, tab) == -1) {
									i = 0;
									break;
								}
								int attributeNumber = first->getElement(sectionNumber - 1).attr->findNode(first->getElement(sectionNumber - 1).attr, tab);
								cout << sectionNumber << ",A," << tab << " == " << first->getElement(sectionNumber - 1).attr->getElement(first->getElement(sectionNumber - 1).attr,attributeNumber).value << endl;
							}
							else if (nextletter == '?') {
								if (first->AttrInSection(first, atoi(tab)) == -1) {
									i = 0;
									break;
								}
								cout << atoi(tab) << ",A,? == " << first->AttrInSection(first, atoi(tab)) << endl;
							}
						}
					}
					else {
						char letter = getchar();
						char nextletter = getchar();
						if (letter == ',' && nextletter == '?') {
							cout << tab << ",A,? == " << countAllAttr(first, tab) << endl;
						}
					}
				}
				i = 0;
			}
			break;
		case 'D':
			if (state == COMMANDS) {
				tab[i - 1] = '\0';
				if (i >= 2 && tab[i - 2] == ',') {
					tab[i - 2] = '\0';
					int sectionNumber = atoi(tab);
					char letter = getchar();
					if (letter == ',') {
						i = 0;
						char nextletter = getchar();
						if (nextletter == '*') {
							first->removeElement(sectionNumber - 1);
							cout << sectionNumber<<",D,* == deleted"<<endl;
						}
						if ((nextletter >= 'a' && nextletter <= 'z') || (nextletter >= 'A' && nextletter <= 'Z')) {
							tab[i] = nextletter;
							i++;
							while (true) {
								char a = getchar();
								if (a == '\n') break;
								tab[i] = a;
								i++;
							}
							tab[i] = '\0';
							sections currentSection = first->getElement(sectionNumber - 1);
							int attributeNumber = currentSection.attr->findNode(first->getElement(sectionNumber - 1).attr, tab);
							currentSection.attr->removeElement(attributeNumber);
							if (currentSection.attr->getLen(currentSection.attr) == 0) {
								first->removeElement(sectionNumber - 1);
							}
							cout << sectionNumber << ",D," << tab << " == deleted"<<endl;	
						}
					}
				}
				i = 0;
			}
			break;

		}
	}
}
