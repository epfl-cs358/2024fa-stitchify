#include <iostream>
#include <fstream>

int main() {
    const std::string filename = "commands.txt";
    std::ofstream commandFile(filename);

    if (commandFile.is_open()) {
        int number_rows = 0;
        std::cin>>number_rows;
        for(int i=1; i<= number_rows; i++)
        {
            commandFile<<"s1 45\n";
            commandFile<<"s2 45\n";
            for(int step = 1; step <= 3; step ++)
            {
                commandFile<<"n 100\n";
            }
        }
        commandFile.close();
        std::cout << "File '" << filename << "' created successfully with commands." << std::endl;
    } else {
        std::cerr << "Error: Unable to create the file '" << filename << "'." << std::endl;
        return 1;
    }

    return 0;
}
