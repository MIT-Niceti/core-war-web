#include "Compiler.hh"
#include <iostream>
#include <string>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Usage: " << av[0] << " <input_file> <output_file>" << std::endl << std::endl;
        return (-1);
    }

    std::string input(av[1]), output(av[2]);

    Compiler compiler(input, output);

    return compiler.run() ? 0 : -1;
}
