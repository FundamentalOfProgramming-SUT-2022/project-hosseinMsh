#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include<sys/stat.h>
#include<errno.h>
#define DATA_SIZE 1000
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define SIZE_OF_STR 100000
/// clipboard for to select and
char clipboard[SIZE_OF_STR];
///convert two str in new str
char* merge_to_str(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
///break two str from pos1 to pos2.
char* Break_str(const char *s1,int pos1,int pos2){
    char* str= calloc(SIZE_OF_STR,sizeof (char));
    for (int i = pos1; i < pos2; ++i) {
        str[i]=s1[i];
    }
    str[pos2]='\0';
    return str;
}
///read file to get all text in file in to str
char *readFile(char *filename) {
    FILE *f = fopen(filename, "rt");
    if(!f)
        printf("your file does not exist");
    assert(f);
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *) malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}
///pos address show where is location of order in file
int pos_address(const char* ary,const long long* pos){
    int line_num=1;
    int address=-1;
    for (int i = 0; i < strlen(ary); ++i) {
        if (ary[i] == '\n') {
            line_num++;
            if (line_num == pos[0]) {
                address=i+(int)pos[1];
                break;
            }
        }
    }
    return address;
}
int Check(char* address) {
    FILE *file = fopen(address, "r");

    if (file) {
        fclose(file);
        return 1;
    } else {
        return 0;
    }
}
int check_file_exist(char* address){
    FILE *file= fopen(address, "r");

    if (file)
    {
        fclose(file);
        return 1;
    }
    else
    {
        ANSI_COLOR_RED;
        printf("file doesn't exist");
        ANSI_COLOR_RESET;
        return 0;
    }
}
///create folder for "creat_file" func
void Create_folder(char* address){
    for (int i = 0; i < strlen(address); ++i) {
        if (address[i] == '/') {
                char dirname[i];
                strncpy(dirname , address , i + 1);
                dirname[i + 1] = '\0';
                mkdir(dirname);
        }
    }
}
///create file to make new file.
void Create_file(char* address) {
    if(Check(address)==1){
        ANSI_COLOR_RED;
        printf("your file existed\n");
        ANSI_COLOR_RESET;
        return;
    }
    Create_folder(address);
    if (access(address, F_OK) == 0)
        return;
    else {
        FILE *newfile = fopen(address, "w");
        fclose(newfile);
        ANSI_COLOR_GREEN;
        printf("File Created Successfully\n");
        ANSI_COLOR_RESET;
    }
}
///insert to add str in file in pos...
void Insert(char* address,char* str,long long * pos) {
    ANSI_COLOR_GREEN;
    printf("this is your order :");
    printf("\naddress=%s\nstr=%s\npos=%lld %lld\n",address,str,pos[0],pos[1]);
    ANSI_COLOR_RESET;
    char *str_file = readFile(address);
    unsigned long long int size_of_file = strlen(str_file);
    unsigned long long int size_of_str = strlen(str);
    char new_str[SIZE_OF_STR];

    int pos_file= pos_address(str_file,pos);
    int j=0;
    for (int i = 0; i < pos_file; ++i) {
        new_str[j]=str_file[i];
        j++;
    }
    for (int i = 0; i < strlen(str); ++i) {
        new_str[j] = str[i];
        j++;
    }
    for (int i = pos_file; i < size_of_file; ++i) {
        new_str[j]=str_file[i];
        j++;
    }
    new_str[j]='\0';
    printf("%s",new_str);
    FILE *file= fopen(address,"w");
    fprintf(file,"%s",new_str);
    fclose(file);
}
///cat,to show what in file.
void Cat (char* address) {
    printf("%s",address);
    if (check_file_exist(address) == 1) {
        char *str_in_file = readFile(address);
        printf("in your file:\n ");
        ANSI_COLOR_GREEN;
        printf("%s", str_in_file);
        ANSI_COLOR_RESET;
    }
}
///remove to del some str in file in pos...
void  Remove (char* address,const long long int* pos,int size,const char* flag) {
    ///get what in file
    char *str_in_file_first = readFile(address);
    char *str_remove = calloc(SIZE_OF_STR, sizeof(char));
    int add_pos = pos_address(str_in_file_first, pos);
    int j = 0;
    if (strcmp(flag, "-f") == 0) {
        for (int i = 0; i < add_pos; ++i) {
            str_remove[j] = str_in_file_first[i];
            j++;
        }
        for (int i = add_pos + size; i < strlen(str_in_file_first); ++i) {
            str_remove[j] = str_in_file_first[i];
            j++;
        }
    }
    if (strcmp(flag, "-b") == 0) {
        for (int i = 0; i < add_pos - size; ++i) {
            str_remove[j] = str_in_file_first[i];
            j++;
        }
        for (int i = add_pos; i < strlen(str_in_file_first); ++i) {
            str_remove[j] = str_in_file_first[i];
            j++;
        }
    }
    str_remove[j] = '\0';
    FILE *remove= fopen(address,"w");
    fprintf(remove,"%s",str_remove);
    fclose(remove);
}
///copy to clipboard
void Copy(char* address,const long long int* pos,int size,const char* flag) {
    char *all_str_in_file = readFile(address);
    int pos_add = pos_address(all_str_in_file, pos);
    if (pos_add == -1) {
        ANSI_COLOR_RED;
        printf("pos address is wrong");
        ANSI_COLOR_RESET;
        return;
    }
    int j = 0;
    if (flag[1] == 'b') {
        for (int i = pos_add - size; i < pos_add; ++i) {
            clipboard[j] = all_str_in_file[i];
            j++;
        }
    }
    if (flag[1] == 'f') {
        for (int i = pos_add; i < pos_add + size; ++i) {
            clipboard[j] = all_str_in_file[i];
            j++;
        }
        clipboard[j]='\0';
    }
}
///cut =copy to clipboard and remove it.
void Cut(char* address,const long long int* pos,int size,const char* flag){
    Copy(address,pos,size,flag);
    Remove(address,pos,size,flag);
}
///paste from clipboard to pos.
void Paste(char* address,const long long int* pos){
    char*all_in_file=readFile(address);
    int pos_add= pos_address(all_in_file,pos);
    char* str1=Break_str(all_in_file,0,pos_add);
    char* str2= Break_str(all_in_file,pos_add, (int)strlen(all_in_file));
    char* str_final= merge_to_str(merge_to_str(str1,clipboard),str2);
    FILE *paste=fopen(address,"w");
    fprintf(paste,"%s",str_final);
    fclose(paste);
}
///find and find_object
int str_finder(const char* full_str,const char* what_you_need_find) {
    int find_pos = -1;
    int j = 0;
    int end_str = (int) strlen(what_you_need_find);
    ///*str
    if (what_you_need_find[0] == '*') {
        for (int i = (int) strlen(full_str); i > 0; --i) {
            if (full_str[i] == what_you_need_find[j]) {
                j++;
                if (what_you_need_find[j] == '*') {
                    while (full_str[i] == ' ' || full_str[i] == '\n' || full_str[i] == '\0')
                        i--;
                    find_pos = i + 1;
                }
            }
        }
    }
    ///str*
    if (what_you_need_find[end_str-2] == '*') {
        printf("%s",what_you_need_find);
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == what_you_need_find[j]) {
                j++;
                if (what_you_need_find[j] == '*') {
                    find_pos = i + 3 - (int) strlen(what_you_need_find);
                }
              if(full_str[i+1] == what_you_need_find[j+1]){

                    if (full_str[i] != what_you_need_find[j]) {
                        j = 0;
                        continue;
                    }
                }
            }
        }
    }
        ///str

    else {
        j = 0;
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == what_you_need_find[j]) {
                j++;
                if (what_you_need_find[j] == '\0') {
                    find_pos = i + 1 - (int) strlen(what_you_need_find);
                }
            }
        }
    }
    return find_pos;
}
void Find(char* str,char* address){
    check_file_exist(address);
    char* str_all_file= readFile(address);
    int pos_str_looking= str_finder(str_all_file,str);
    printf("%d\n",pos_str_looking);
}
int Find_count(char* str,char* address){
    char* full_str= readFile(address);
    int num_find=0;
    int j=0;
    int end_str= (int) strlen(str);
    ///*str
    if(str[0]=='*') {
        for (int i = (int) strlen(full_str); i > 0; --i) {
            if (full_str[i] == str[j]) {
                j++;
                if (str[j] == '*') {
                    while (full_str[i] == ' ' || full_str[i] == '\n' || full_str[i] == '\0')
                        i--;
                    num_find ++;
                    continue;
                }
            }
        }
    }
    ///str*
    if(str[end_str]=='*'){
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == str[j]) {
                j++;
                if (str[j] == '*') {
//                    while (full_str[i]==' ' ||full_str[i]=='\n'||full_str[i]=='\0')
//                        i++;
                    num_find++;
                    continue;
                }
            }
        }
    }
        ///str
    else {
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == str[j]) {
                j++;
                if (str[j] == '\0') {
                    num_find ++;
                    continue;
                }
            }
        }
    }
    return num_find;
}
void Find_at(char* str,char* address, int at){}
void Find_byword(char* str,char* address){}
void Find_all(char* str,char* address){}
///replace and replace_object
void Replace(char* str1,char*str2,char*address) {
    int exist=check_file_exist(address);
    if(exist==0)
        return;
    char *all_file = readFile(address);
    int num_pos_start_str1 = str_finder(all_file, str1);
    int num_pos_end_str1;
    for (int i = num_pos_start_str1; i < (int) strlen(all_file); ++i) {
        if (all_file[i] == ' ' || all_file[i] == EOF || all_file[i] == '\n')
            num_pos_end_str1 = i;
    }
    char*brack= calloc(strlen(all_file)+ strlen(str2),sizeof (char ));
    int j=0;
    for (int i = 0; i < num_pos_start_str1; ++i) {
        brack[j]=all_file[i];
        j++;
    }
    for (int i = 0; i < strlen(str2); ++i) {
        if(str2[i]=='\0')
            break;
        brack[j]=str2[i];
        j++;
    }
    for (int i = num_pos_end_str1; i < strlen(all_file); ++i) {
        if(str2[i]=='\0')
            break;
        brack[j]=all_file[i];
        j++;
    }
    brack[j]='\0';
    FILE *replace=fopen(address,"rw");
    fprintf(replace,"%s",brack);
    fclose(replace);
}
void Replace_at(char* str1,char*str2,char*address,int at){}
void Replace_all(char* str1,char*str2,char*address){}

void Grep(char* str,char *address){
    if(check_file_exist(address)==0)
        return;
    char* str_file= readFile(address);
    int loc=str_finder(str_file,str);
    printf("%s%s",address,"-->");
    for (int i = loc; i < strlen(str_file); ++i) {
        if(str_file[i]=='\n')
            break;
        printf("%c",str_file[i]);
    }
}
//C
//L
void Undo(){}
void Closing_pairs(){}
void Text_comparator(){}
void Directory_tree(){}
void Arman(){}
void Help(){
    printf("%s","for create file write \"createfile -file <file name and address>\"");

}

