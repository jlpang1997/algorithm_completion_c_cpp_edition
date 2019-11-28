#include"aux_tool.h"

#include<string.h>
#include<direct.h>
#include<io.h>
void print_progress(int n,char *title)
{
    int new_n=n*30/100;
    char x[200]={'\0'};
    x[0]='\r';
    int len=strlen(title);
    int len_for_title=20;

    memset(&x[1],' ',len_for_title-len-1);
    sprintf(&x[len_for_title-len],"%s%3d%%[",title,n);
    memset(&x[len_for_title+5],'>',new_n);
    memset(&x[len_for_title+5+new_n],'_',30-new_n);

    strcat(x,"]");
    printf("%s",x);
}
FILE* create_dir_file(char *relative_path)//输入格式"./test/
{
    // printf("%s\n",relative_path);
    int len=strlen(relative_path);
    int j=len;
    for(j=len;relative_path[j]!='/'&&relative_path[j]!='\\';j--);

    char dir_path[1000]="";
    for(int i=2;i<j;)//从2开始跳过前面的"./".\"//检查目录是否存在
    {
        
        while(relative_path[i]!='\\'&&relative_path[i]!='/')i++;
        strncpy(dir_path,relative_path,i);
        // printf("%s\n",dir_path);
        if(_access(dir_path,0)==-1)
        {
            _mkdir(dir_path);
        }
        else
            i++;
        
    }
    FILE*fp=fopen(relative_path,"wb");
    return fp;
}
long get_file_size(FILE*fp)
{
    fseek(fp,0,SEEK_SET);
    long size=0;
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    rewind(fp);
    return size;
}

void my_itoa(unsigned char ch,char num_str[9],int len)
{
    unsigned char num=1<<(len-1);
    for(int i=0;i<len;i++)
    {
        num_str[i]=ch/num+'0';
        ch%=num;
        num/=2;
    }

}
unsigned char my_atoi(char num_str[],int len)
{
    unsigned char result=0;
    for(int i=0;i<len;i++)
    {
        result+=(num_str[i]-'0')*(1<<(len-1-i));
    }
    return result;
}

int get_file_num(char *path)
{
    int file_num=0;
    long hFile = 0;
    struct _finddata_t fileInfo;
    char filepath_name[1000]="";
    strcat(filepath_name,path);
    strcat(filepath_name,"\\*");
    if ((hFile = _findfirst(filepath_name, &fileInfo)) == -1) {
        return file_num;
    }
    int len=strlen(filepath_name);
    filepath_name[len-1]='\0';
    do {
        
        if(strcmp(".",fileInfo.name)==0||strcmp("..",fileInfo.name)==0)
            continue;
        if(fileInfo.attrib&_A_SUBDIR)
        {
            int len=strlen(filepath_name);
            strcat(filepath_name,fileInfo.name);
            file_num+=get_file_num(filepath_name);
            filepath_name[len]='\0';
        }
        else 
        {
            file_num++;
        }
        
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return file_num;
}

void get_correct_path(char *input,char *output)
{
    int len=strlen(input);
    if(input[len-1]=='\\'||input[len-1]=='/')input[len-1]='\0';
    if(input[0]=='.')
    {
        strcpy(output,input);

        return ;
    }
    if(input[0]=='\\'||input[0]=='/')
    {
        output[0]='.';
        strcat(output,input);
        return ;
    }
    else if(input[0]!='.')
    {
        strcat(output,"./");
        strcat(output,input);
        return ;
    }
}


