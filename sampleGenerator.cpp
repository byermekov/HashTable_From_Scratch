#include <iostream> 
#include <fstream>
#include <limits>
#include <random> 
#include <unordered_set> 
#include <cstdio>
#include <string>
#include <cmath>
#include <chrono>
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

/** 
 * It is bad data generator, as many un-inserted keys will be searched for or deleted from the hash table. 
*/
int main(int argc, char **argv)
{
    ofstream inputFile("input.txt"); // output into the input.txt 
    ofstream outputFile("output.txt"); // output into the output.txt
    const string OPTIONS[3] = {"search", "insert", "delete"};
    unsigned int seed = 114514;
    unsigned int numOperations = 100000; 
    unsigned int keyUpperBound = numeric_limits<int>::max(); 

    mt19937 rng(seed);
    uniform_int_distribution< unsigned int> valGen(0, keyUpperBound);
    discrete_distribution<unsigned int> optGen({40, 40, 20}); // generator for no. of {search, insert, delete}, 40% search, 40% insert, 20% delete. 

	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now(); //time measuring starts
	HashTable* myhashtable = new HashTable("hashByDivision");
    unordered_set<unsigned int> hashTable; // hash table to store the keys, just for output a correct answer.
    for (unsigned int i = 0; i < numOperations; i++)
    {
		cout << "waiting for Mismatch" << endl;
        unsigned int opt = optGen(rng); 
        unsigned int val = valGen(rng); 
        inputFile << OPTIONS[opt] << " " << val << endl;

        if (opt == 0) // search
        {
			if (hashTable.find(val) != hashTable.end()) {
				if (!myhashtable->hasKey(val))
					cout << "Mismatch " << val << endl;
			}
			else {
				if (myhashtable->hasKey(val)) {
					cout << "Mismatch" << val << endl;
				}
			}
            //    outputFile << val << " was found" << endl;
            //else
             //   outputFile << val << " does not exist" << endl;
        }
        else if (opt == 1) // insert
        {
            hashTable.insert(val); 
			myhashtable->insertKey(val);
        }
        else // delete
        {
            if (hashTable.find(val) != hashTable.end())
            {
                outputFile << val << " was deleted successfully" << endl;
                hashTable.erase(val);
            }
            else
                outputFile << val << " does not exist" << endl;
			
        }
    }
	auto end = std::chrono::high_resolution_clock::now(); //time measuring ends here
	std::chrono::duration<float> duration = end - start;
	cout << duration.count() << "s " << endl;
}