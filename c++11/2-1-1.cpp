#include <iostream>

using namespace std;

int main()
{
		cout << "standard clib:" << __STDC_HOSTED__ << endl;
		cout << "standard c:" << __STDC__ << endl;
		cout << "ios/iec" << __STDC_ISO_10646__ <<endl;
}
