// Reading from a file

// C++ uses std::ifstream object to handle input file streams

#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream my_file;
    my_file.open("/home/raxit/cppnd/res/demo.txt");
    if (my_file) {
        std::cout << "The file stream is created" << "\n";
        std::string line;
        while (getline(my_file, line))
            std::cout << line << "\n";
    }
}