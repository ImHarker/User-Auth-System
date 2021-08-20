#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "SHA256.h"

using namespace std;
string sha(string str);
int main() {
	ifstream is;
	ofstream os;
	string pwd = "";
	string pwdcheck = "";
	string username;
	int salt;
	cout << "Username: ";
	cin >> username;

	is.open("./Users/" + username);

	if (!is) {
		cout << "Registering a new user: " + username << endl;
		do {
			if (pwd != pwdcheck) cout << "Passwords do not match!\n";
			cout << "Enter your password: ";
			cin >> pwd;
			cout << "Repeat your password: ";
			cin >> pwdcheck;
		} while (pwd != pwdcheck);
		is.open("./Users/" + username);
		salt = time(0);
		os << salt << endl;
		os << sha(pwd + to_string(salt));
		os.close();
	} else {
		do {
			cout << "Enter your password: ";
			cin >> pwd;
			is >> salt >> pwdcheck;
			if (sha(pwd + to_string(salt)) != pwdcheck) {
				cout << "Wrong password!\n";
			} else {
				cout << "Successfully logged in!";
			}
		} while (sha(pwd + to_string(salt)) != pwdcheck);
		is.close();
	}

	return 0;
}

string sha(string str) {
	SHA256 sha;
	sha.update(str);
	uint8_t* digest = sha.digest();

	return SHA256::toString(digest);

	delete[] digest;
}
