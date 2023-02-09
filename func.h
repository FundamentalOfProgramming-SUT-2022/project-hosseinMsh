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
        printf("pos address is wrong\n");
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
int *str_finder(const char* full_str,const char* what_you_need_find) {
    int *find_pos= calloc(20,sizeof (int));
    int k = 1;
    int size_str_need_find = (int) strlen(what_you_need_find) - 2;
    int size_full_str = (int) strlen(full_str);
    ///*str
    if (what_you_need_find[0] == '*') {
        int flag=0;
        for (int i = size_full_str; i > 0; --i) {
            for (int j = size_str_need_find; j > 0; --j) {
                flag=1;
                if(full_str[i+j]!= what_you_need_find[j]) {
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                for (int j = i; j > 0; --j) {
                    if(full_str[j]=='\n' || full_str[j]==' ')
                        break;
                    find_pos[k]=j-size_str_need_find-2;
                }
                k++;
            }
        }

    }
    ///str*
    if (what_you_need_find[size_str_need_find] == '*') {
        int flag=0;
        for (int i = 0; i < size_full_str; ++i) {
            for (int j = 0; j < size_str_need_find; ++j) {
                flag=1;
                if(full_str[j+i]!= what_you_need_find[j]) {
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                find_pos[k]=i;
                k++;
            }
        }
    }
    ///str

    else {
        int flag=0;
        for (int i = 0; i < size_full_str; ++i) {
            for (int j = 0; j < size_str_need_find; ++j) {
                flag=1;
                if(full_str[j+i]!= what_you_need_find[j]) {
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                find_pos[k]=i;
                k++;
            }
        }
    }
    find_pos[0]=k-1;
    return find_pos;
}
void Find(char* str,char* address){
    check_file_exist(address);
    char* str_all_file= readFile(address);
    int *pos_str_looking= str_finder(str_all_file,str);
    printf("%d\n",pos_str_looking[1]);
}
int Find_count(char* str,char* address){
    check_file_exist(address);
    char*full_str= readFile(address);
    int *pos_looking= str_finder(full_str,str);
    return pos_looking[0];
}
int Find_at(char* str,char* address, int at){
    check_file_exist(address);
    char* str_all_file= readFile(address);
    int *pos_str_looking= str_finder(str_all_file,str);
    if(at>pos_str_looking[0]){
        ANSI_COLOR_RED;
        printf("at num not existed");
        ANSI_COLOR_RESET;
        return -1;
    }
    return pos_str_looking[at];
}
int Find_byword(char* str,char* address){
    char* string = readFile(address);
    int num=1;
    int pos= Find_at(str,address,1);
    for (int i = 0; i < pos; ++i) {
        if(string[i]==' ')
            num++;
    }
    return num;
}
char* Find_all(char* str,char* address){
    check_file_exist(address);
    char*full_str= readFile(address);
    int *pos_looking= str_finder(full_str,str);
    char* all= calloc(30,sizeof (char));
    int j=0;
    for (int i = 1; i <= pos_looking[0]; ++i) {
        printf("%d,",pos_looking[i]);
        all[j]=pos_looking[i];
        j++;
        all[j]=',';
        j++;
    }
    printf("\n");
    all[j-1]='\0';
    return all;
}
///replace and replace_object
char* Replace(char* str1,char*str2,char*address) {
    int pos=Find_at(str1,address,1);
    char *file_str= readFile(address);
    char *new_str= calloc(SIZE_OF_STR,sizeof (char));
    int j=0;
    for (int i = 0; i < pos; ++i) {
        new_str[j]=file_str[i];
        j++;
    }
    for (int i = 0; i < strlen(str2); ++i) {
        new_str[j]= str2[i];
        j++;
    }
    for (int i = pos+ (int)strlen(str1)-1; i < strlen(file_str); ++i) {
        new_str[j]= file_str[i];
        j++;
    }
    new_str[j]='\0';
    printf("%s",new_str);
    return new_str;
}
void Replace_at(char* str1,char*str2,char*address,int at){}
void Replace_all(char* str1,char*str2,char*address){}

void Grep(char* str,char *address){
    if(check_file_exist(address)==0)
        return;
    char* str_file= readFile(address);
    int *loc=str_finder(str_file,str);
    printf("%s%s",address,"-->");
    for (int i = loc[1]; i < strlen(str_file); ++i) {
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

