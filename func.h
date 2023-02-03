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
    int line_num=0;
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

    Create_folder(address);
    if (access(address, F_OK) == 0)
        return;
    else {
        FILE *newfile = fopen(address, "w");
        fclose(newfile);
    }
}
///insert to add str in file in pos...
void Insert(char* address,char* str,long long * pos) {
    printf("\naddress=%s\nstr=%s\npos=%lld %lld\n",address,str,pos[0],pos[1]);
    char *str_file = readFile(address);
    remove(address);
    FILE *new_file = fopen(address, "a++");
    unsigned long long int size_of_file = strlen(str_file);
    unsigned long long int size_of_str = strlen(str);
    char new_str[SIZE_OF_STR];
    int i = 0, line_num = 0;
    char leftover[SIZE_OF_STR];
    while (1) {
        if (str_file[i] == '\n') {
            line_num++;
            if (line_num == pos[0]) {
                int l = 0;
                for (int j = i ; j < strlen(str_file); ++j) {
                    leftover [l]= str_file[i+l];
                    l++;
                }
                strncpy(new_str, str_file, i + pos[1] + 1);
                new_str[i + pos[1] + 1] = '\0';
                leftover[l + 1] = '\0';
            }
            break;
        }
        i++;
    }
    printf("left=%s\n",leftover);
    char *new_file_str = merge_to_str(new_str, str);
    char *new_file_str1 = merge_to_str(new_file_str, leftover);
    new_file_str[size_of_file + size_of_str + 1] = '\0';
    fprintf(new_file,"%s",new_file_str1);
    fclose(new_file);
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
    ///del file
    remove(address);
    char *str_before_pos_del= calloc(strlen(str_in_file_first),sizeof (char));
    char *str_after_pos_del= calloc(strlen(str_in_file_first),sizeof (char));
   ///creat file
    Create_file(address);
    FILE *remove = fopen(address, "a+");
    int line_num = 0;
    long long int pos_ary;
    for (long long int i = 0; i < strlen(str_in_file_first); ++i) {
        if (str_in_file_first[i] == '\n') {
            line_num++;
            if (line_num != pos[0])
                continue;
            pos_ary = i + pos[1];
        }
    }
///backward del
    if (flag[1] == 'b') {
        for (int i = 0; i < pos_ary-size; ++i) {
            str_before_pos_del[i]=str_in_file_first[i];
        }
        str_before_pos_del[pos_ary-size+1]='\0';
        int j=0;
        for (long long int i = pos_ary+1; i < strlen(str_in_file_first); ++i) {
            str_after_pos_del[j]=str_in_file_first[i];
            j++;
        }
        str_after_pos_del[j+1]='\0';
    }

    /// forward del
    else if (flag[1] == 'f') {
        for (int i = 0; i < pos_ary+size; ++i) {
            str_before_pos_del[i]=str_in_file_first[i];
        }
        str_before_pos_del[pos_ary+size+1]='\0';
        int j=0;
        for (long long int i = pos_ary+1; i < strlen(str_in_file_first); ++i) {
            str_after_pos_del[j]=str_in_file_first[i];
            j++;
        }
        str_after_pos_del[j+1]='\0';
    }
    /// now input in new file
    char* new_str_for_adding_to_file= merge_to_str(str_before_pos_del,str_after_pos_del);
    printf("%s\n%s",str_before_pos_del,str_after_pos_del);
    fprintf(remove,"%s",new_str_for_adding_to_file);
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
    FILE *paste=fopen(address,"wr");
    fprintf(paste,"%s",str_final);
    fclose(paste);
}
///find and find_object
int str_finder(const char* full_str,const char* what_you_need_find){
    int find_pos=-1;
    int j=0;
    int end_str= (int) strlen(what_you_need_find);
    ///*str
    if(what_you_need_find[0]=='*') {
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
    if(what_you_need_find[end_str]=='*'){
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == what_you_need_find[j]) {
                j++;
                if (what_you_need_find[j] == '*') {
//                    while (full_str[i]==' ' ||full_str[i]=='\n'||full_str[i]=='\0')
//                        i++;
                    find_pos = i - (int) strlen(what_you_need_find);
                }
            }
        }
    }
    ///str
    else {
        for (int i = 0; i < strlen(full_str); ++i) {
            if (full_str[i] == what_you_need_find[j]) {
                j++;
                if (what_you_need_find[j] == '\0') {
                    find_pos = i - (int) strlen(what_you_need_find);
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
    printf("%d",pos_str_looking);
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
void Replace(char* str1,char*str2,char*address){
    char* all_file= readFile(address);
    int num_pos_start_str1=str_finder(all_file,str1);
    int num_pos_end_str1;
    for (int i = num_pos_start_str1; i < (int) strlen(all_file); ++i) {
        if(all_file[i]==' '|| all_file[i]==EOF || all_file[i] == '\n')
        num_pos_end_str1=i;
    }

}
void Replace_at(char* str1,char*str2,char*address,int at){}
void Replace_all(char* str1,char*str2,char*address){}

void Grep(char* str,char *address){

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

