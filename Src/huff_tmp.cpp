#include"huff.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

double get_encode_file_recursion(char*init_filepath,char *huff_dir_file3)
{
// char *init_filepath="D:\\Chrome_Download\\a.test.downloading";
        int cur_state=0;
        int next_state=0;
        

        // int encode_time=MAX_TIME_ENCODE_TIME;
        int encode_time;
        int MAX_TIME_ENCODE_TIME=0;

        char huff_dir[100]="D:\\Chrome_Download\\";

        char huff_file1[100]="tmp1.huff";
        char huff_file2[100]="tmp2.huff";
        // char huff_file3[100]="output.huff";


        char huff_dir_file1[100]="";
        strcpy(huff_dir_file1,huff_dir);
        strcat(huff_dir_file1,huff_file1);

        char huff_dir_file2[100]="";
        strcpy(huff_dir_file2,huff_dir);
        strcat(huff_dir_file2,huff_file2);

        // char huff_dir_file3[100]="";
        // strcpy(huff_dir_file3,huff_dir);
        // strcat(huff_dir_file3,huff_file3);

        while(true)
        {
            MAX_TIME_ENCODE_TIME++;
            cur_state=next_state;
            if(cur_state==0)
            {
                if(get_encode_file(init_filepath,huff_dir_file1,MAX_TIME_ENCODE_TIME)>0.0001)
                {
                    next_state=1;
                }
                else
                {
                    // if(rename(huff_dir_file1,huff_dir_file3)!=0)
                    // {
                    //     printf("rename failed.\n");
                    //     exit(0);
                    //     // return ;
                    // }
                    file_copy(huff_dir_file1,huff_dir_file3);
                    if(remove(huff_dir_file1))
                    {
                        printf("%s\n",strerror(errno));
                        exit(0);
                    }
                    
                    next_state=3;
                }
                
            }
            else if(cur_state==1)    
            {
                if(get_encode_file(huff_dir_file1,huff_dir_file2,MAX_TIME_ENCODE_TIME)>0.0001)
                {
                    next_state=2;
                    if(remove(huff_dir_file1)!=0)
                    {
                        printf("%s\n",strerror(errno));
                        
                        // return -1;
                        exit(0);
                    }
                }
                else
                {
                    file_copy(huff_dir_file1,huff_dir_file3);
                    if(remove(huff_dir_file1))
                    {
                        printf("%s\n",strerror(errno));
                        exit(0);
                    }

                    if(remove(huff_dir_file2))
                    {
                        printf("%s\n",strerror(errno));
                        exit(0);
                    }

                        
                    next_state=3;
                }

        

            }
            else if(cur_state==2)    
            {
                if(get_encode_file(huff_dir_file2,huff_dir_file1,MAX_TIME_ENCODE_TIME)>0.0001)
                {
                    next_state=1;
                    if(remove(huff_dir_file2)!=0)
                    {
                        printf("remove failed.\n");
                        return -1;
                    }
                }
                else
                {
                    file_copy(huff_dir_file2,huff_dir_file3);
                    if(remove(huff_dir_file2))
                    {
                        printf("%s\n",strerror(errno));
                        exit(0);
                    }


                    next_state=3;
                    if(remove(huff_dir_file1)!=0)
                    {
                        printf("remove failed.\n");
                        return -1;
                    }
                }

            }
            else if(cur_state==3)
            {
                break;
            }
        }


}

void get_decode_file_recursion(char*huff_filepath,char *init_dir_file0)
{
        int MAX_TIME_DECODE_TIME;
        char init_dir[100]="D:\\Chrome_Download\\";

        char init_file1[100]="tmp1.init";
        char init_file2[100]="tmp2.init";

        char init_dir_file1[100]="";
        strcpy(init_dir_file1,init_dir);
        strcat(init_dir_file1,init_file1);

        char init_dir_file2[100]="";
        strcpy(init_dir_file2,init_dir);
        strcat(init_dir_file2,init_file2);

        FILE *fp_huff=fopen(huff_filepath,"rb");
        if(!fp_huff)
        {
            printf("%s open failed.\n",huff_filepath);
            // exit(0);
            return;
        }
        fread(&MAX_TIME_DECODE_TIME,sizeof(MAX_TIME_DECODE_TIME),1,fp_huff);
        fclose(fp_huff);
        // cur_state=3;
        int next_state=3;
        int cur_state;
        int decode_time;
        decode_time=MAX_TIME_DECODE_TIME;
        while(decode_time>0)
        {
            cur_state=next_state;
            if(cur_state==3)
            {
                if(decode_time==1)
                {
                    get_decode_file(huff_filepath,init_dir_file0,MAX_TIME_DECODE_TIME);
                    next_state=0;
                    decode_time--;
                }
                else
                {
                    get_decode_file(huff_filepath,init_dir_file2,MAX_TIME_DECODE_TIME);
                    next_state=2;
                    decode_time--;
                }
            }
            else if(cur_state==2)    
            {
                if(decode_time==1)
                {
                    get_decode_file(init_dir_file2,init_dir_file0,MAX_TIME_DECODE_TIME);
                    next_state=0;
                    decode_time--;
                    remove(init_dir_file2);
                }
                else
                {
                    get_decode_file(init_dir_file2,init_dir_file1,MAX_TIME_DECODE_TIME);
                    next_state=1;
                    decode_time--;
                    remove(init_dir_file2);
                }

            }
            else if(cur_state==1)    
            {
                if(decode_time==1)
                {
                    get_decode_file(init_dir_file1,init_dir_file0,MAX_TIME_DECODE_TIME);
                    next_state=0;
                    decode_time--;
                    remove(init_dir_file1);
                }
                else
                {
                    get_decode_file(init_dir_file1,init_dir_file2,MAX_TIME_DECODE_TIME);
                    next_state=2;
                    decode_time--;
                    remove(init_dir_file1);
                }
            }
            else if(cur_state==0)
            {
                 break;
            }
            
        }  
}

void file_copy(char *src,char *des)
{
    FILE*fp_src=fopen(src,"rb");
    if(!fp_src)
    {
        printf("%s open failed.\n",src);
        exit(0);
    }

    FILE*fp_des=fopen(des,"wb");
    if(!fp_des)
    {
        printf("%s open failed.\n",des);
        exit(0);
    }

    long size=get_file_size(fp_src);
    unsigned char *buffer=(unsigned char *)malloc(sizeof(unsigned char )*size);
    if(!buffer)
    {
        printf("malloc failed.\n");
        exit(0);
    }
    fread(buffer,1,size,fp_src);
    fwrite(buffer,1,size,fp_des);
    return ;




}