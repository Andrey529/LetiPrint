#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid count of command line arguments." << std::endl;
        std::cerr << "Parameter list: <program name> <path for file that will be print>" << std::endl;
    }

    std::cout << "Path for printed file: " << argv[1] << std::endl;

    std::string command("lp -d HP-LaserJet-1018 ");
    command += argv[1];
    std::system(command.c_str());
}