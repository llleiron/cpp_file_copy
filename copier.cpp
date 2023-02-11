#include <iostream>
#include <fstream>
#include <string>

inline bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void do_copy(std::string str_source, std::string str_target){
    std::string line;
    std::ifstream source{str_source};
    std::ofstream target{str_target};

    while(getline(source, line)){
        target << line << "\n";
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        perror("argument count");
        return 0;
    }
    if(!exists(argv[1])){
        perror("");
        return 0;
    }

    std::string flag = "yes";
    
    if(exists(argv[2])){
        std::cout << "Would you like to override the target file?: ";
        std::cin >> flag;
    }
    if(flag == "yes"){

        do_copy(argv[1], argv[2]);
    }
    else{
        std::cout << "You did not want to override the file" << "\n";
    }

    return 0;
}