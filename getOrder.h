#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define addresss "C:/Users/Sharif IA/Documents/GitHub/project-hosseinMsh"
char* get_order_func(){
    char * order= calloc(100,sizeof (char ));
    int i=0;
    while (1){
        scanf("%s",order);
        if(order[i]!='-')
            break;
        i++;
    }
    return order;
}



char* get_type(){
    char* type=calloc(100,sizeof (char ));
    int i=0;
    while (1){
        scanf("%s",type);
        if(type[i]!=' ')
            break;
        i++;
    }
    return type;
}

char* get_Address(){
    char* address=calloc(100,sizeof (char ));
    int i=0;
    while (1){
        scanf("%[^-]s",address);
        if(address[i]!='\n')
            break;
        if(address[i]!='-')
            break;
        i++;
    }
    char* Address = merge_to_str(addresss,address);
    return Address;
}
char* get_str(){
    char* str=calloc(10000,sizeof (char ));
        scanf("%[^-]s", str);
    return str;
}
int get_size(){
    int size;
    scanf("%d",&size);
    return size;
}
long long int* get_pos(){
    long long int* pos= calloc(2,sizeof (long long int));
    scanf("%lld:%lld",pos,(pos+1));
    return pos;
}