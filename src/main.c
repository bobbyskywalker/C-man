#include "../headers/pacman.h"

int main(int argc, char **argv) {
    (void) argv;
    if(argc > 1)
    {
        printf("valid execution: name of the program");
        return 1;
    }
    print_menu();
    return 0;
}
