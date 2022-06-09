#include <iostream>
#include <fstream>

using namespace std;

int main() {
		ifstream file ( "examples/simple.lic" );
		if (file.is_open()) 
			cout << file.rdbuf();
    return 0;
}
