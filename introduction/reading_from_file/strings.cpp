#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::cout;

int main() {
    
    // initialize string
    string a("1 2 3");
    
    int n; // any integer

    // Create istringstream object
    istringstream my_stream(a);

    // Testing to see if hte stream was successful
    while (my_stream) {
        my_stream >> n;
        if (my_stream) {
            cout << "That stream was successful: " << n << "\n";
        }
        else cout << "That stream was not successful! " << "\n"; 
    }
    return 0;
}

// int main() 
// {
//     string b("1,2,3");

//     istringstream my_stream(b);

//     char c;
//     int n;

//     while (my_stream >> n >> c) {
//       cout << "That stream was successful:" << n << " " << c << "\n";
//     }
//     cout << "The stream has failed." << "\n";
// }