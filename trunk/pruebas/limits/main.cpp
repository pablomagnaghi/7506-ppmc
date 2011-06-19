#include <limits>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	cout << "bytes size_t: " << sizeof(size_t) << endl;
	cout << "max size_t: " << numeric_limits<size_t>::max() << endl;

        cout << "bytes streampos: " << sizeof(streampos) << endl;
        cout << "max streampos: " << numeric_limits<streampos>::max() << endl;

}
