// ENUMS

#include <iostream>

using namespace std;

int main() {
    
    // Create the enum Color with fixed values
    enum class Color {white, black, blue, red};

    // Create a color variable and set it to Color::blue
    Color my_color = Color::blue;

    // Test to see if my car is re
    if (my_color == Color::red) {
        cout << "The color of my car is red!" << "\n";
    } else {
        cout << "The color of my car is not Red!" << "\n";
    }
}