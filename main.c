#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "getOrder.h"
#include "proses.h"
#include "printing.h"
#define DATA_SIZE 1000
#include<conio.h>



int main1() {
    print_start();
    while (1) {
        char *order = get_order_func();
        print_doing(2);
        proses(order);
        char str[2];

            printf("will you continue orders?(y/n)\n");
            scanf("%s", str);
            print();
            if (strcmp(str, "n") == 0)
                break;
            else if (strcmp(str, "y") == 0)
                continue;
    }return 0;
}
int main() {
    char *type = get_type();
    if (strcmp(type, "-find") == 0) {
        if (getchar() == '\n')
            printf("%s", type);
        else {
            type =get_type();
            printf("%s", type);
        }
    }
}