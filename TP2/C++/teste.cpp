#include <iostream>

using namespace std;

int main()
{
	string origin, destination;
	string str = "12345";

	origin = str[1];
	destination = str[3];
	
	str.replace(1,1,destination);
	str.replace(3,1,origin);

	cout << str << endl;

	return 0;
}
