#include"huff.h"
#include<stdio.h>
#include<string.h>


void get_encode_file_recursion(char*init_filepath,char *huff_dir_file3,int MAX_TIME_ENCODE_TIME)
{
// char *init_filepath="D:\\Chrome_Download\\a.test.downloading";
        int cur_state=0;
        int next_state=0;
        int encode_time=MAX_TIME_ENCODE_TIME;

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

        while(encode_time>0)
        {
            cur_state=next_state;
            if(cur_state==0)
            {
                if(encode_time==1)
                {
                    get_encode_file(init_filepath,huff_dir_file3,MAX_TIME_ENCODE_TIME);
                    next_state=3;
                    encode_time--;
                }
                else
                {
                    get_encode_file(init_filepath,huff_dir_file1,MAX_TIME_ENCODE_TIME);
                    next_state=1;
                    encode_time--;
                }
            }
            else if(cur_state==1)    
            {
                if(encode_time==1)
                {
                    get_encode_file(huff_dir_file1,huff_dir_file3,MAX_TIME_ENCODE_TIME);
                    next_state=3;
                    encode_time--;
                }
                else
                {
                    get_encode_file(huff_dir_file1,huff_dir_file2,MAX_TIME_ENCODE_TIME);
                    next_state=2;
                    encode_time--;
                }

            }
            else if(cur_state==2)    
            {
                if(encode_time==1)
                {
                    get_encode_file(huff_dir_file2,huff_dir_file3,MAX_TIME_ENCODE_TIME);
                    next_state=3;
                    encode_time--;
                }
                else
                {
                    get_encode_file(huff_dir_file2,huff_dir_file1,MAX_TIME_ENCODE_TIME);
                    next_state=1;
                    encode_time--;
                }
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
                }
                else
                {
                    get_decode_file(init_dir_file2,init_dir_file1,MAX_TIME_DECODE_TIME);
                    next_state=1;
                    decode_time--;
                }

            }
            else if(cur_state==1)    
            {
                if(decode_time==1)
                {
                    get_decode_file(init_dir_file1,init_dir_file0,MAX_TIME_DECODE_TIME);
                    next_state=0;
                    decode_time--;
                }
                else
                {
                    get_decode_file(init_dir_file1,init_dir_file2,MAX_TIME_DECODE_TIME);
                    next_state=2;
                    decode_time--;
                }
            }
        }  
}