#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <string.h>
#include <string>

void do_copy(int source, int target){
    char buffer[1024];
    ssize_t bytes;
    while((bytes = read(source, buffer, 1024)) != 0)
    {
        lseek(target, 0, SEEK_END);
        write(target, buffer, bytes);
    }

    close(source);
    close(target);
    std::cout << "Copied successfully";
}

int main(int argc, char** argv)
{
    if(argc < 2){
        perror("arguments count error!");
        return 1;
    }

    int source = open(argv[1], O_RDONLY, 0666);

    if(source < 0){
        perror("Openning the file failed");
        return 1;
    }

    int target{};

    if(argc > 2){
        printf("%s", "Would you like to override the file? \n");

        std::string temp;
        std::cin >> temp;

        while(temp != "Yes" || temp != "No"){
            if(temp == "No"){
                target = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            }
            else if(temp == "Yes"){
                target = open(argv[2], O_WRONLY, 0666);
            }
            else{
                std::cout << "not normal answer, try again: ";
                std::cin >> temp;
            }
        }
    }
    else{
        const char* filename = "Target";
        target = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }

    if(target < 0){
        perror("Can't open the file");
        return 1;
    }

    do_copy(source, target);
    return 0;
}
