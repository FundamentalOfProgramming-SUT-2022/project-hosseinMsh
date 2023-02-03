#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<unistd.h>
char* create_file="createfile";
char* insert="insertstr";
char* cat="cat";
char* remove_str="removetstr";
char* copystr="copystr";
char* cutstr="cutstr";
char* past="pastestr";
char* find="find";
char* replace="replace";
char* help="help";
char* grep="grep";
void error(int err_num){
    fprintf(stdout , "error" " : " "%d\n", err_num);
}
void proses(char* order) {
    ///creat file
    if (strcmp(order, create_file) == 0) {
        char *type = get_type();
        if (strcmp(type, "-file") == 0) {
            Create_file(get_Address());
            ANSI_COLOR_GREEN;
            printf("File Created Successfully\r");
            sleep(2);
            ANSI_COLOR_RESET;
        } else error(101);
    }
        ///insert
    else if (strcmp(order, insert) == 0) {
        printf("insert ro shenakt\n");
        char *type = get_type();
        if (strcmp(type, "-file") == 0) {
            char *address = get_Address();
            type = get_type();
            if (strcmp(type, "-str") == 0) {
                char *str = get_str();
                type = get_type();
                if (strcmp(type, "-pos") == 0) {
                    long long *pos = get_pos();
                    Insert(address, str, pos);
                    {
                        ANSI_COLOR_GREEN;
                        printf("your str is being inserted\r");
                        sleep(2);
                        ANSI_COLOR_RESET;
                    }
                } else {
                    ANSI_COLOR_RED;
                    printf("your dose not write correctly pos !!");
                    ANSI_COLOR_RESET;
                }
            } else {
                ANSI_COLOR_RED;
                printf("your dose not write correctly str order!!");
                ANSI_COLOR_RESET;
            }
        } else error(102);
    }
        ///cat
    else if ((strcmp(order, cat) == 0)) {
        char *type = get_type();
        if (strcmp(type, "-file") == 0)
            Cat(get_Address());
        else error(103);
    }
        ///remove
    else if (strcmp(order, remove_str) == 0) {
        char* type=get_type();
        if(strcmp(type,"-file")==0){
            char* address=get_Address();
            type=get_type();
            if(strcmp(type,"-pos")==0){
                long long int* pos=get_pos();
                type=get_type();
                if(strcmp(type,"-size")==0){
                    int size=get_size();
                    type=get_type();
                    if(strcmp(type,"-b")==0){
                        Remove(address,pos,size,type);
                    }
                    if(strcmp(type,"-f")==0){
                        Remove(address,pos,size,type);
                    }
                    else{ error(200);}
                } else{ error(202);}
            } else{ error(203);}
        } else{ error(204);}
    }//end remove
        ///copy
    else if(strcmp(order,copystr)==0){
        char* type=get_type();
        if(strcmp(type,"-file")==0){
            char* address=get_Address();
            type=get_type();
            if(strcmp(type,"-pos")==0){
                long long int* pos=get_pos();
                type=get_type();
                if(strcmp(type,"-size")==0){
                    int size=get_size();
                    type=get_type();
                    if(strcmp(type,"-b")==0){
                        Copy(address,pos,size,type);
                        printf("copy is successful");
                    }
                    if(strcmp(type,"-f")==0){
                        Copy(address,pos,size,type);
                        printf("copy is successful");
                    }
                    else{ error(300);}
                } else{ error(302);}
            } else{ error(303);}
        } else{ error(304);}
    }
        ///cut
    else if(strcmp(order,cutstr)==0){
        char* type=get_type();
        if(strcmp(type,"-file")==0){
            char* address=get_Address();
            type=get_type();
            if(strcmp(type,"-pos")==0){
                long long int* pos=get_pos();
                type=get_type();
                if(strcmp(type,"-size")==0){
                    int size=get_size();
                    type=get_type();
                    if(strcmp(type,"-b")==0){
                        Cut(address,pos,size,type);
                        printf("cut is successful");
                    }
                    if(strcmp(type,"-f")==0){
                        Cut(address,pos,size,type);
                        printf("copy is successful");
                    }
                    else{ error(400);}
                } else{ error(402);}
            } else{ error(403);}
        } else{ error(404);}
    }
        ///past
    else if(strcmp(order,past)==0){
        char* type=get_type();
        if(strcmp(type,"-file")==0) {
            char *address = get_Address();
            type = get_type();
            if (strcmp(type, "-pos") == 0) {
                long long int *pos = get_pos();
                Paste(address,pos);
                printf("past is successful");
            } else{ error(501);}
        }else { error(502);}
    }
        ///find
    else if(strcmp(order,find)==0){
        char* type=get_type();
        if(strcmp(type,"-str")==0){
            char* str=get_str();
            type=get_type();
            if(strcmp(type,"-file")==0){
                char* address=get_Address();
                if(getchar()=='\n'){
                    Find(str,address);
                }
                else{
                    type=get_type();
                    if(strcmp(type,"-count")==0){
                        Find_count(str,address);
                    }
                    if(strcmp(type,"-at")==0){
                        int at;
                        scanf_s("%d",&at);
                        Find_at(str,address,at);
                    }
                    if(strcmp(type,"-byword")==0){
                        Find_byword(str,address);
                    }
                    if(strcmp(type,"-all")==0){
                        Find_all(str,address);
                    } else
                        error(600);
                }
            } else
            error(601);
        } else
        error(602);
    }
        ///replace
    else if(strcmp(order,replace)==0) {
        char *type = get_type();
        if (strcmp(type, "-str") == 0) {
            char *str1 = get_str();
            type = get_type();
            if (strcmp(type, "-str") == 0) {
                char *str2 = get_str();
                type = get_type();
                if (strcmp(type, "-file") == 0) {
                    char *address = get_Address();
                    if (getchar() == '\n') {
                        Replace(str1, str2, address);
                    } else {
                        type = get_type();
                        if (strcmp(type, "-at") == 0) {
                            int at;
                            scanf_s("%d", &at);
                            Replace_at(str1, str2, address, at);
                        }
                        if (strcmp(type, "-all") == 0) {
                            Replace_all(str1, str2, address);
                        } else
                            error(700);
                    }
                } else
                    error(701);
            } else
                error(702);
        } else
        error(703);
    }
        ///grep
    else if(strcmp(order,grep)==0){
        char*type=get_type();
        if(strcmp(type,"-str")==0){
            char*str=get_str();
            type=get_type();
            if(strcmp(type,"-file")==0) {
                char *address=get_Address();
                Grep(str,address);
            }
            else{ error(801);}
        }
        if(strcmp(type,"-c")==0){
            type=get_type();
            if(strcmp(type,"-str")==0){
                char*str=get_str();
                type=get_type();
                if(strcmp(type,"-file")==0) {
                    char *address=get_Address();
                    Grep(str,address);
                }
                else{ error(801);}
            }
        }
        if(strcmp(type,"l")==0){
            type=get_type();
            if(strcmp(type,"-str")==0){
                char*str=get_str();
                type=get_type();
                if(strcmp(type,"-file")==0) {
                    char *address=get_Address();
                    Grep(str,address);
                }
                else{ error(801);}
            }
        }
        else{ error(800);}
    }

        ///help
    else if (strcmp(order, help) == 0) {
        Help();
    } else {
        printf("%s", "your order is wrong!\n");
    }
}
