#include <iostream>
using namespace std;

int main() {
	string name = "Alice";
	cout << "Original: " << name << endl;

	name.append(" Wonderland");
	cout << "Updated: " << name << endl;

	cout << "Length: " << name.length() << endl;
	return 0;
}