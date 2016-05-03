#include "Compiler.hh"
#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "No input file specified" << std::endl;
        return (-1);
    }

    Compiler compiler((std::string(av[1])));

    compiler.run();
    return (0);
}
