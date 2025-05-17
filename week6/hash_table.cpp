#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

vector<Company> readCompanyList(string file_name) {
	ifstream fin(file_name);
	vector<Company> com;
	string info;
	if (!fin.is_open()) {
		cout << "Cannot open file.\n";
		return {};
	}
	getline(fin, info);
	while (getline(fin, info)) {
		Company company;
		stringstream ss(info);

		getline(ss, company.name, '|');
		getline(ss, company.profit_tax, '|');
		getline(ss, company.address);

		com.push_back(company);

	}
	fin.close();
	return com;
}

long long hashString(string company_name) {
	long long hash = 0;
	long long p = 1;
	string s;
	int len = company_name.length();
	if (len > 20) {
		s = company_name.substr(len - 20);
	}
	else {
		s = company_name;
	}
	for (int i = 0; i < s.length(); i++) {
		hash += ((long long)s[i] * p) % 2000;
		p = (p* 31) % 2000;
	}
	return hash%2000;
}

struct HashTable {
	Company* table[2000];
	HashTable() {
		for (int i = 0; i < 2000; i++) {
			table[i] = nullptr;
		}
	}
};

HashTable* createHashTable(vector<Company> list_company) {
	HashTable* hash_table = new HashTable();
	for (int i = 0; i < list_company.size(); i++) {
		long long pos = hashString(list_company[i].name);
		long long temp = pos;

		while (hash_table->table[pos] != nullptr) {
			pos = (pos + 1) % 2000;
			if (pos == temp) {
				cout << "Full.\n";
				break;
			}
		}

		if (hash_table->table[pos] == nullptr) {
			hash_table->table[pos] = new Company(list_company[i]);
		}
	}
	return hash_table;
}

void insert(HashTable* hash_table, Company company) {
	long long pos = hashString(company.name);
	long long temp = pos;
	while (hash_table->table[pos] != nullptr) {

		pos = (pos + 1) % 2000;
		if (pos == temp) {
			cout << "Full\n";
			return;
		}
	}

	if (hash_table->table[pos] == nullptr) {
		hash_table->table[pos] = new Company(company);
	}
}

Company* search(HashTable* hash_table, string company_name) {
	long long pos = hashString(company_name);
	long long temp = pos;

	while (hash_table->table[pos] != nullptr) {
		if (hash_table->table[pos] -> name == company_name) {
			return hash_table->table[pos];
		}
		pos = (pos + 1) % 2000;
		if (pos == temp) {
			break;
		}
	}
	return nullptr;
}

void process(string info_file, string input_file, string output_file) {
	ifstream fin(input_file);
	ofstream fout(output_file);
	if (!fin.is_open() || !fout.is_open()) {
		cout << "Cannot open file.\n";
		return;
	}

	vector<Company> list_company = readCompanyList(info_file);
	HashTable* hash_table;
	hash_table = createHashTable(list_company);
	string company;
	Company* com = nullptr;
	while (getline(fin, company)) {
		com = search(hash_table, company);
		if (com == nullptr) fout << "NULL" << endl;
		else {
			fout << com->name << "|" << com->profit_tax << "|" << com->address << endl;
		}
	}

	for (int i = 0; i < 2000; i++) {
		delete hash_table->table[i];
	}
	delete hash_table;
	fin.close();
	fout.close();
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		return 1;
	}
	string info_file = argv[1];
	string input_file = argv[2];
	string output_file = argv[3];

	process(info_file, input_file, output_file);
	return 0;

}

