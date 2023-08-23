#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;



class Entry {
public:
	int key;
	Entry* next;
	Entry() {
		this->key = -1;
		this->next = NULL;
	}
	Entry(int k) {
		this->key = k;
	}

	void addNode(Entry* node) {
		Entry* copyNode = this;
		while (copyNode->next != NULL) {
			copyNode = copyNode->next;
		}
		copyNode->next = node;
	}

	void removeNode(int key) {
		Entry* copyNode = this;
		Entry* nextNode = copyNode->next;;
		while (nextNode->key != key) {
			nextNode = nextNode->next;
			copyNode = copyNode->next;
		}
		copyNode->next = nextNode->next;

	}

	void printData() {
		if (this->next == NULL) {
			printf("Empty list\n");
		}
		Entry* copyNode = this;
		while (copyNode != NULL) {
			cout << copyNode->key << " ";
			copyNode = copyNode->next;
		}
	}
	bool nodeExists(int key) {
		bool exists = false;
		Entry* copyNode = this;
		while (copyNode != NULL) {
			if (copyNode->key == key) {
				exists = true;
				break;
			}
			copyNode = copyNode->next;
		}
		return exists;
	}

};

const int SIZE = 100000;

class HashTable {
private:
	Entry* array[SIZE];
	string hashFunc;
	double A = 0.543216789;
public:
	HashTable(string s) { //setting every entry NULL initially
		for (int i = 0; i < SIZE; i++) {
			array[i] = new Entry();
		}
		hashFunc = s;
	}
	int hashByDivision(int key) {
		return key % SIZE;
	}

	int hashByMultiplication(int key) {
		return floor(SIZE * (fmod(key * A, 1)));
	}

	int getHashingMethod(int k) {
		if (this->hashFunc == "hashByDivision")
			return hashByDivision(k);

		if (this->hashFunc == "hashByMultiplication")
			return hashByMultiplication(k);
		return -1;
	}
	void insertKey(int k) {
		int h = getHashingMethod(k);

		if (h == -1) {
			puts("Choose the correct type of hash function : (by divison or by multiplication)");
		}
		else {

			if (array[h]->key != -1 && array[h]->key != k) {
				Entry* newNode = new Entry(k);
				array[h]->addNode(newNode);
			}
			else {
				array[h] = new Entry(k);
			}
		}
	}
	void deleteKey(int k) {
		int h = getHashingMethod(k);

		if (h == -1) {
			puts("Choose the correct type of hash function : (by divison or by multiplication)");
		}
		else {

			if (array[h]->key != -1) {
				if (array[h]->key != k) {
					array[h]->removeNode(k);
				}
				else {
					array[h] = new Entry();
				}
				printf("%d was deleted successfully\n", k);

			}
			else {
				printf("%d does not exist\n", k);
			}
		}
	}
	bool hasKey(int k) {
		int h = getHashingMethod(k);

		if (h == -1) {
			puts("Choose the correct type of hash function : (by divison or by multiplication)");
			return false;
		}
		else {
			if (array[h]->key == -1) {
				return false;

			}
			else {
				if (array[h]->key != k) {
					if (array[h]->nodeExists(k)) {
						return true;

					}
					else {
						return false;

					}
				}
				else {
					return true;

				}
			}
		}
	}
	void searchKey(int k) {
		int h = getHashingMethod(k);
		if (h == -1) {
			puts("Choose the correct type of hash function : (by divison or by multiplication)");
		}
		else {

			if (this->hasKey(k)) {
				printf("%d was found\n", k);
			}
			else {
				printf("%d does not exist\n", k);
			}
		}
	}
};








int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	HashTable* hashtable = new HashTable("hashByDivision");
	string str;
	int key;
	cin >> str;
	do {
		cin >> key;
		if (str == "insert")
			hashtable->insertKey(key);
		if (str == "delete")
			hashtable->deleteKey(key);
		if (str == "search")
			hashtable->searchKey(key);
	} while (cin >> str);
	

	return 0;
}