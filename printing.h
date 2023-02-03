#include <stdio.h>
#include <time.h>
#include<unistd.h>


void print();
void print_doing(int time){
    printf("\033[22;31m%s\t3\033[0m\r","Your order is being processed in");
    sleep(time);
    printf("\033[22;31m%s\t2\033[0m\r","Your order is being processed in");
    sleep(time);
    printf("\033[22;31m%s\t1\033[0m\r","Your order is being processed in");
    sleep(time);
    printf("\033[22;32m%s\t0\033[0m\r","Your order is being processed in");
    sleep(time);
    print();
}
void print_start(){
    printf("\033[22;31m%s\t3\033[0m\r","Your code is going to work at");
    sleep(1);
    printf("\033[22;31m%s\t2\033[0m\r","Your code is going to work at");
    sleep(1);
    printf("\033[22;31m%s\t1\033[0m\r","Your code is going to work at");
    sleep(1);
    printf("\033[22;32m%s\t0\033[0m\r","Your code is going to work at");
    sleep(1);
    print();
}
void print () {
    printf("\r                    "
           "                             "
           "                            "
           "             \r");
}
