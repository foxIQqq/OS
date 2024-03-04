#include <cstdlib>
#include <iostream>
#include <dlfcn.h>

int main(){
    int num_of_lib;
    std::cout << "Enter num of library: ";
    std::cin >> num_of_lib;
    if(num_of_lib != 1 && num_of_lib != 2){
        std::cout << "Error library\n";
        exit(1);
    }
    --num_of_lib;
    int command;
    const char* libs[] = {"libd1.so", "libd2.so"};
    void* library_handle;
    library_handle = dlopen(libs[num_of_lib], RTLD_LAZY);
    if(!library_handle){
        std::cout << "Error in dlopen\n";
        exit(1);
    }

    float (*Square)(float A, float B);
    char* (*translation)(long x);

    Square = (float(*)(float, float))dlsym(library_handle, "Square");
    translation = (char*(*)(long x))dlsym(library_handle, "translation");

    std::cout << "Enter command 1, 2 or 3\n";
    while(std::cin >> command) {
        switch (command) {
            default:
                std::cout << "Wrong command\n";
                break;
            case 0:
                exit(0);
            case 3:
                dlclose(library_handle);
                num_of_lib = (num_of_lib + 1) % 2;
                library_handle = dlopen(libs[num_of_lib], RTLD_LAZY);
                if(!library_handle){
                    std::cout << "Error in dlopen\n";
                    exit(1);
                }
                Square = (float(*)(float, float))dlsym(library_handle, "Square");
                translation = (char*(*)(long x))dlsym(library_handle, "translation");
                std::cout << "Change contract\n";
                break;
            case 1:
                std::cout << "Enter lengths A and B: ";
                float A, B;
                std::cin >> A >> B;
                std::cout << "Square is " << Square(A, B) << std::endl;
                break;
            case 2:
                long x;
                std::cout << "Enter decimal number: ";
                std::cin >> x;
                char* memory = translation(x);
                if(num_of_lib + 1 == 1) {
                    std::cout << "Binary number is " << memory << std::endl;
                }
                else if (num_of_lib + 1 == 2){
                    std::cout << "Ternary number is " << memory << std::endl;
                }
                free(memory);
                break;
        }
    }
    dlclose(library_handle);
}