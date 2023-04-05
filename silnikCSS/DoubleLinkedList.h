#include <iostream>
using namespace std;

#define SIZE 8
#define CSS_NAME 110

struct attribute {
	char name[CSS_NAME];
	char value[CSS_NAME];
};

template< typename N>
class DoubleLinkedList {
	int size;
	int counter = NULL;
	N* array;
	DoubleLinkedList* prev = NULL;
	DoubleLinkedList* next = NULL;

public:
	DoubleLinkedList(int size) {
		this->size = size;
		array = new N[size];
	}
	N getArray() {
		return array;
	}
	attribute getArrayAttr() {
		return array;
	}

	N getElement(int index) {
		if (index >= size) {
			return next->getElement(index - size);
		}
		return array[index];
	}

	bool contain(int index) {
		if (index >= size) {
			next->contain(index - size);
		}
		else if (index >= counter) return false;
		return true;
	}

	N getElement(DoubleLinkedList* first, int index) {
		DoubleLinkedList<N>* tmp = first;
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		}
		return tmp->array[0];

	}

	DoubleLinkedList* findNode(int index) {
		if (index >= size) {
			return next->findNode(index - size);
		}
		return this;
	}

	bool contain(DoubleLinkedList* first, int index) {
		DoubleLinkedList<N>* tmp = first;
		for (int i = 0; i < index; i++) {
			if (tmp->next != NULL)
				tmp = tmp->next;
			else return false;
		}
		return true;

	}

	int getCounter() {
		return counter;
	}

	void print(DoubleLinkedList* next) {
		DoubleLinkedList<N>* tmp = next;
		while (tmp != NULL) {
			cout << tmp->counter << endl;
			for (int i = 0; i < tmp->counter; i++) {
				cout << tmp->array[i].attr << endl;
				cout << tmp->array[i].sel << endl;

			}
			tmp = tmp->next;
		}
	}

	void print2(DoubleLinkedList* next) {
		DoubleLinkedList<N>* tmp = next;
		while (tmp != NULL) {
			for (int i = 0; i < tmp->counter; i++)
				cout << tmp->array[i] << endl;
			tmp = tmp->next;
		}
	}

	void print3(DoubleLinkedList* next) {
		DoubleLinkedList<N>* tmp = next;
		while (tmp != NULL) {
			cout << tmp->array[0].name << " ";
			cout << tmp->array[0].value << endl;
			tmp = tmp->next;
		}
	}

	int getLen(DoubleLinkedList* first) {
		int cnt = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			cnt = cnt + tmp->counter;
			tmp = tmp->next;
		}
		return cnt;
	}
	int getSecNumber(DoubleLinkedList* first) {
		int cnt = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			cnt = cnt + tmp->counter;
			tmp = tmp->next;
		}
		return cnt;
	}
	DoubleLinkedList* getFirst(DoubleLinkedList* first) {
		if (first == NULL) return NULL;
		return first;
	}
	DoubleLinkedList* getLast(DoubleLinkedList* first) {
		if (first == NULL)return NULL;
		DoubleLinkedList<N>* tmp = first;
		while (tmp->next != NULL) tmp = tmp->next;
		return tmp;
	}
	DoubleLinkedList* addFirst(DoubleLinkedList* first) {
		DoubleLinkedList<N>* newNode = new DoubleLinkedList<N>();
		newNode->prev = NULL;
		newNode->next = first;
		if (first != NULL) {
			first->prev = newNode;
			return newNode;
		}
	}
	DoubleLinkedList* addLast(DoubleLinkedList* first) {
		DoubleLinkedList<N>* newNode = new DoubleLinkedList<N>(size);
		DoubleLinkedList<N>* last = getLast(first);
		newNode->prev = last;
		if (last == NULL) {
			return newNode;
		}
		last->next = newNode;
		return newNode;
	}

	DoubleLinkedList* removeNode(DoubleLinkedList* first, DoubleLinkedList* node) {
		if (node == NULL) {
			return first;
		}

		if (node->next != NULL) {
			node->next->prev = node->prev;
		}
		if (node->prev == NULL) {
			return node->next;
		}
		node->prev->next = node->next;
		return first;
	}

	void removeElement( int index) {// zawsze first
		DoubleLinkedList<N>* node;
		node = this;
		while(index >= size) {
			node = node->next;
			index -= size;
		}
		if (index == node->counter) {
			node->counter--;
		}
		else {
			for (int i = index; i<node->counter-1; i++) {
				N bufor = node->array[i];
				node->array[i] = node->array[i + 1];
				node->array[i + 1] = bufor;

			}
			node->counter--;
		}
		if (node->counter==0) {
			removeNode(this,node);
		}
	}



	DoubleLinkedList* seekAttrName(DoubleLinkedList* first, char* tab) {
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			if (strcmp(tab, tmp->array[0].name) == 0) return tmp;
			tmp = tmp->next;
		}
		return NULL;
	}

	DoubleLinkedList* seekSelName(DoubleLinkedList* first, char* tab) {
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
				if (strcmp(tab, tmp->array[0]) == 0) return tmp;
			tmp = tmp->next;
		}
		return NULL;
	}


	int SelInSection(DoubleLinkedList* first, int sectionNumber) {
		int count = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			if (count + tmp->counter >= sectionNumber) {
				return tmp->array[sectionNumber - count - 1].sel->getLen(tmp->array[sectionNumber - count - 1].sel);
			}
			else {
				tmp = tmp->next;
				count += SIZE;
			}
		}
		return -1;
	}

	int AttrInSection(DoubleLinkedList* first, int sectionNumber) {
		int count = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			if (count + tmp->counter >= sectionNumber) {
				return tmp->array[sectionNumber - count - 1].attr->getLen(tmp->array[sectionNumber - count - 1].attr);
			}
			else {
				tmp = tmp->next;
				count += SIZE;
			}

		}
		return -1;
	}
	//def FindNode(firstNode, dataPattern) :
	//	tmp = firstNode
	//	while tmp != None :
	//		if tmp.data == dataPattern :
	//			return tmp
	//			tmp = tmp.next
	//			return None
	//DoubleLinkedList findNode(DoubleLinkedList* first, char* data) {
	//	int count = 0;
	//	DoubleLinkedList<N>* tmp = first;
	//	while (tmp != first) {
	//		count++;
	//		if (tmp.array == data) {
	//			return tmp;
	//			tmp = tmp->next;
	//			return NULL;
	//		}
	//	}
	//}


	int findNode(DoubleLinkedList* first, char* data) {
		int index = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			if (strcmp(tmp->array->name, data) == 0) {
				return index;
				break;
			}
			else {
				index++;
				tmp = tmp->next;
			}

		}
		return -1;
	}
	char* value(char* attr, DoubleLinkedList* first) {
		DoubleLinkedList<attribute>* check = first->seekAttrName(first, attr);
		if (check != NULL) return check->array[0].value;
		return NULL;
	}

	char* findNodeFromEnd(DoubleLinkedList* last,char* sel, char* attr) {
		DoubleLinkedList<N>* tmp = last;
		while (tmp != NULL) {
			for (int i = tmp->counter-1; i >=0; i--) {
				tmp->array[i].sel->seekSelName(tmp->array[i].sel, sel);
				if (tmp->array[i].sel->seekSelName(tmp->array[i].sel, sel) != NULL) {
					char* result = tmp->array[i].attr->value(attr, tmp->array[i].attr);
					if (result != NULL)return result;
				}
			}
			tmp = tmp->prev;
		}
		return NULL;
	}

	int countRepSel(DoubleLinkedList* first, char* data) {
		int count = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
				if (strcmp(tmp->array[0], data) == 0) {
					count++;
			}
			tmp = tmp->next;

		}
		return count;
	}

	int countRepAttr(DoubleLinkedList* first, char* data) {
		int count = 0;
		DoubleLinkedList<N>* tmp = first;
		while (tmp != NULL) {
			if (strcmp(tmp->array[0].name, data) == 0) {
				count++;
			}
			tmp = tmp->next;
		}
		return count;
	}


	void insertSection(N section, DoubleLinkedList* first, DoubleLinkedList** last) {//node
		if (counter < SIZE) {
			array[counter] = section;
			counter++;
		}
		else {
			if (next != NULL) {
				next->insertSection(section, first,last);
			}
			else {
				DoubleLinkedList<N>* newLast = addLast(first);
				*last = newLast;
				newLast->insertSection(section, first,last);
			}
		}
	}

	void insertElement(N element, DoubleLinkedList* current) {//node
		current->array[0] = element;
		counter++;
	}
	void insertAttr(N element, DoubleLinkedList* current) {//node
		current->array[0] = element;
		current->counter = 1;
	}
	~DoubleLinkedList() {


	}

};

