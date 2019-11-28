#include"dir.h"
#include"aux_tool.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <io.h>
#include<direct.h>


void dir_visiting(FILE*fp,FILE*fp_huff,char **map,char *relative_path)
{
    long total_bytes=0;
    int init_end=0;
    long offset=0;
    int len=strlen(relative_path)+1;//把\0也写入
    fwrite(&len,sizeof(len),1,fp_huff);
    fwrite(relative_path,sizeof(char),len,fp_huff);
    // printf("写入路径:%s 长度:%d\n",relative_path,len);

    fwrite(&init_end,sizeof(int),1,fp_huff);
    fwrite(&total_bytes,sizeof(long),1,fp_huff);
    offset+=sizeof(int)+sizeof(long);
    unsigned char ch;
    fread(&ch,sizeof(ch),1,fp);
    int bit_n=0;
    char byte[9]="";
    while(feof(fp)==0)
    {

        int code_n=strlen(map[ch]);
        for(int i=0;i<code_n;i++)
        {
            byte[bit_n++]=map[ch][i];
            if(bit_n==8)
            {
                unsigned char new_byte=my_atoi(byte,8);
                fwrite(&new_byte,sizeof(new_byte),1,fp_huff);
                // printf("%d ",new_byte);
                total_bytes++;
                bit_n=0;
            }
        }            
        fread(&ch,sizeof(ch),1,fp);
    }
    init_end=bit_n;
    if(bit_n!=0)
    {
        for(int i=bit_n;i<8;i++)
        {
            byte[i]='0';
        }
        unsigned char new_byte=my_atoi(byte,8);
        fwrite(&new_byte,sizeof(new_byte),1,fp_huff);
        // printf("%d ",new_byte);
        total_bytes++;
        bit_n=0;
    }
    offset+=total_bytes;
    if(fseek(fp_huff,-(offset),1)!=0)
        printf("返回失败\n");//定位回去把字节数和end的写回去  
    fwrite(&init_end,sizeof(int),1,fp_huff);
    fwrite(&total_bytes,sizeof(long),1,fp_huff);
    if(fseek(fp_huff,total_bytes,1)!=0)
        printf("FILE RETURN ERROR\n");
    
}

void dir_encoding(FILE*fp_huff,char *path,char **map,char *relative_path,int *file_num)
{
    long hFile = 0;
    struct _finddata_t fileInfo;
    char filepath_name[1000]="";
    strcat(filepath_name,path);
    strcat(filepath_name,"\\*");
    if ((hFile = _findfirst(filepath_name, &fileInfo)) == -1) {
        return;
    }
    int len=strlen(filepath_name);
    filepath_name[len-1]='\0';
    do {
        
        if(strcmp(".",fileInfo.name)==0||strcmp("..",fileInfo.name)==0)
            continue;
        if(fileInfo.attrib&_A_SUBDIR)
        {
            int len_rel=strlen(relative_path);
            int len=strlen(filepath_name);
            strcat(filepath_name,fileInfo.name);
            strcat(relative_path,fileInfo.name);
            strcat(relative_path,"/");
            dir_encoding(fp_huff,filepath_name,map,relative_path,file_num);
            filepath_name[len]='\0';
            relative_path[len_rel]='\0';

        }
        else 
        {
            int len=strlen(filepath_name);
            strcat(filepath_name,fileInfo.name);
            // printf("%s\n",filepath_name);
            FILE*fp=fopen(filepath_name,"rb");
            if(!fp)
            {
                printf("%s file open failed\n",filepath_name);
                exit(0);
            }
            int len_rel=strlen(relative_path);
            strcat(relative_path,fileInfo.name);
            // printf("%s\n",relative_path);
            dir_visiting(fp,fp_huff,map,relative_path);
            (*file_num)++;
            fclose(fp);
            filepath_name[len]='\0';
            relative_path[len_rel]='\0';
        }
        
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return;   


}



void dir_weighting(char * path,long *weight,long *total_bytes)
{
    long hFile = 0;
    struct _finddata_t fileInfo;
    char filepath_name[1000]="";
    strcat(filepath_name,path);
    strcat(filepath_name,"\\*");
    if ((hFile = _findfirst(filepath_name, &fileInfo)) == -1) {
        return;
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
            dir_weighting(filepath_name,weight,total_bytes);
            filepath_name[len]='\0';
        }
        else 
        {
            int len=strlen(filepath_name);
            strcat(filepath_name,fileInfo.name);
            // printf("%d:%s\n",strlen(filepath_name),filepath_name);
            FILE*fp=fopen(filepath_name,"rb");
            if(!fp)
            {
                printf("%s file open failed\n",filepath_name);
                exit(0);
            }
            unsigned char ch;
            fread(&ch,sizeof(ch),1,fp);
            while(feof(fp)==0)
            {
                (*total_bytes)++;
                weight[ch]++;
                fread(&ch,sizeof(ch),1,fp);
            }
            fclose(fp);
            
            filepath_name[len]='\0';
        }
        
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return;
}



