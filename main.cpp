#include <iostream>
#include "Service.h"

int main()
{
    std::ifstream myfile("test.txt");
    if (myfile.fail())
    {
        std::cout << "Error: Can't find the text file!" << std::endl;
    }
    else
    {
        InterpretC_relis(myfile);
    }
    return 0;
}
