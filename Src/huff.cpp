#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"huff.h"
unsigned min_rw_size=1;
unsigned char *read_buffer,*write_buffer;
// int encode_time=0;
// int decode_time=1;
// int MAX_TIME_DECODE_TIME;
// int MAX_TIME_ENCODE_TIME=4;
int main(int argc,char *argv[])
{   
    for(int i=10;i<11;i++)
    {
        min_rw_size=1<<i;
        read_buffer=(unsigned char*)malloc(sizeof(unsigned char)*min_rw_size);
        write_buffer=(unsigned char*)malloc(sizeof(unsigned char)*min_rw_size);

        get_encode_file_recursion("D:\\Chrome_Download\\高一物理必修2知识点全总结.doc","D:\\Chrome_Download\\output.huff",4);

        get_decode_file_recursion("D:\\Chrome_Download\\output.huff","D:\\Chrome_Download\\高一物理必修2知识点全总结.doc");
        // LARGE_INTEGER li;
        // LONGLONG start, end, freq;
        

//         QueryPerformanceFrequency(&li);
//         freq = li.QuadPart;

//         char output[1000]="D:\\Chrome_Download\\";
//         QueryPerformanceCounter(&li); 
//         start = li.QuadPart;
        
        


        



        // QueryPerformanceCounter(&li);
        // end = li.QuadPart;
        // double useTime =(end - start) / (double)freq;
        // int len=strlen("total encode time:");
        // char x[100]="";
        // x[0]='\n';
        // memset(&x[1],' ',20-1-len);
        // sprintf(&x[20-len],"total encode time:%.6f s",useTime);
        // printf("%s",x);
        // FILE*fp_time=fopen("./Test/time.txt","a");
        // fprintf(fp_time,"file_size=%10d\tmin_rw_size=%10dB",get_file_size(fopen(init_filepath,"rb")),min_rw_size);
        // fprintf(fp_time,"\t%.6f",useTime);
        
        

        // char *huff_filepath="D:\\Chrome_Download\\a.test.huff";
        // QueryPerformanceCounter(&li); 
        // start = li.QuadPart;



        // get_decode_file(huff_filepath,);




        // QueryPerformanceCounter(&li);
        // end = li.QuadPart;
        // useTime =(end - start) / (double)freq;
        // len=strlen("total decode time:");
        // char y[100]="";
        // y[0]='\n';
        // memset(&y[1],' ',20-1-len);
        // sprintf(&y[20-len],"total decode time:%.6f s",useTime);
        // printf("%s",y);
        
        // fprintf(fp_time,"\t%.6f\n",useTime);
        // fclose(fp_time);
        free(read_buffer);
        free(write_buffer);

    }

    return 0;
}

void get_encode_file(char *filepath,char *output,int MAX_TIME_ENCODE_TIME)
{
    int extra_bytes=0;
    long *weight;
    int count;
    get_weight_from_file(filepath,&weight,&count);

    Huff_node*Huff_tree;
    char **map;
    int root;
    huff_encode(weight,count,&Huff_tree,&map,&root);

    FILE*fp=fopen(filepath,"rb");
    FILE*fp_huff=fopen(output,"wb");
    printf("\ninput:\t%s\noutput:\t%s\n",filepath,output);
    if(!fp||!fp_huff)
    {
        printf("file open failed.\n");
        exit(0);
    }
    //陆续开始存储解压要用到的数据
    fwrite(&MAX_TIME_ENCODE_TIME,sizeof(MAX_TIME_ENCODE_TIME),1,fp_huff);
    extra_bytes+=sizeof(MAX_TIME_ENCODE_TIME);

    int init_end=0;
    // fseek(fp_huff,sizeof(int)+sizeof(long),SEEK_SET);//留出给init_end和totalbytes的空间
    fwrite(&init_end,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);

    long total_bytes=0;
    fwrite(&total_bytes,sizeof(long),1,fp_huff);
    extra_bytes+=sizeof(long);

    fwrite(&root,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);

    fwrite(&count,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);
    fwrite(Huff_tree,sizeof(Huff_node),2*count,fp_huff);//记录哈夫曼树
    extra_bytes+=sizeof(Huff_node)*2*count;

    
    long cur_total_bytes=-1;
    int per=-1;
    printf("\n");
    unsigned char ch;
    
    int bit_n=0;
    char byte[9]="";

    long size=get_file_size(fp);
    long read_num=size/min_rw_size;
    unsigned last_size=size%min_rw_size;
    unsigned cur_write_count=0;
    for(long k=0;k<read_num;k++)
    {
        fread(read_buffer,1,min_rw_size,fp);
        for(int j=0;j<min_rw_size;j++)
        {
            ch=read_buffer[j];
            // (*weight)[ch]++;
            cur_total_bytes++;
            if(((100*(double)cur_total_bytes)/size)>per)
                print_progress(++per,"encoding:");
            
            int code_n=strlen(map[ch]);
            for(int i=0;i<code_n;i++)
            {
                byte[bit_n++]=map[ch][i];
                if(bit_n==8)
                {
                    unsigned char new_byte=my_atoi(byte,8);
                    // fputc(new_byte,fp_huff);
                    write_buffer[cur_write_count++]=new_byte;
                    if(cur_write_count==min_rw_size)
                    {
                        fwrite(write_buffer,1,min_rw_size,fp_huff);
                        cur_write_count=0;
                    }
                    total_bytes++;
                    bit_n=0;
                }
            }
        }
    }
    if(last_size)
    {
        fread(read_buffer,1,last_size,fp);
        for(int j=0;j<last_size;j++)
        {
            ch=read_buffer[j];
            // (*weight)[ch]++;
            cur_total_bytes++;
            if(((100*(double)cur_total_bytes)/size)>per)
                print_progress(++per,"encoding:");
            
            int code_n=strlen(map[ch]);
            for(int i=0;i<code_n;i++)
            {
                byte[bit_n++]=map[ch][i];
                if(bit_n==8)
                {
                    unsigned char new_byte=my_atoi(byte,8);
                    // fputc(new_byte,fp_huff);
                    write_buffer[cur_write_count++]=new_byte;
                    if(cur_write_count==min_rw_size)
                    {
                        fwrite(write_buffer,1,min_rw_size,fp_huff);
                        cur_write_count=0;
                    }
                    total_bytes++;
                    bit_n=0;
                }
            }
        }

    }

    init_end=bit_n;
    if(bit_n!=0)
    {
        for(int i=bit_n;i<8;i++)
        {
            byte[i]='0';
        }
        unsigned char new_byte=my_atoi(byte,8);
        // fputc(new_byte,fp_huff);
        write_buffer[cur_write_count++]=new_byte;
        if(cur_write_count==min_rw_size)
        {
            fwrite(write_buffer,1,min_rw_size,fp_huff);
            cur_write_count=0;
        }
        (total_bytes)++;
        bit_n=0;
    }
    if(cur_write_count)
        fwrite(write_buffer,1,cur_write_count,fp_huff);
    if(fseek(fp_huff,sizeof(MAX_TIME_ENCODE_TIME),0)!=0)
        printf("返回失败\n");//定位回到开头
    fwrite(&init_end,sizeof(int),1,fp_huff);
    fwrite(&total_bytes,sizeof(long),1,fp_huff);
    printf("\n");
    int len=strlen("reduction ratio:");
    char x[100]="";
    x[0]='\n';
    memset(&x[1],' ',20-1-len);
    total_bytes+=extra_bytes;
    double ratio=(100*(double)(size-total_bytes)/size);
    sprintf(&x[20-len],"reduction ratio:%.2f%%",ratio);
    printf("%s\n\n",x);
    FILE*fp_result=fopen("./Test/result.txt","a");
    // fprintf(fp_result,"one byte\t%s%s\t%.2fKB\t%.2fKB\t%.2f%%\n",file_name,file_type,(double)size/1024,(double)total_bytes/1024,ratio);
    fclose(fp_result);
    fclose(fp_huff);
    fclose(fp);
}
void get_decode_file(char*filepath,char *output,int MAX_TIME_DECODE_TIME)
{
    printf("\ninput:\t%s\noutput:\t%s\n",filepath,output);
    FILE*fp_huff=fopen(filepath,"rb");
    if(!fp_huff)
    {
        printf("%s open failed.\n",filepath);
        exit(0);
    }
    FILE*fp_init=fopen(output,"wb");
    if(!fp_init)
    {
        printf("%s open failed.\n",output);
        exit(0);
    }

    fread(&MAX_TIME_DECODE_TIME,sizeof(MAX_TIME_DECODE_TIME),1,fp_huff);
    fseek(fp_huff,sizeof(MAX_TIME_DECODE_TIME),0);

    int init_end;
    fread(&init_end,sizeof(int),1,fp_huff);

    int total_bytes;
    fread(&total_bytes,sizeof(long),1,fp_huff);

    int root;
    fread(&root,sizeof(int),1,fp_huff);

    int count;
    fread(&count,sizeof(int),1,fp_huff);

    Huff_node*Huff_tree=(Huff_node*)malloc(sizeof(Huff_node)*(2*count));
    fread(Huff_tree,sizeof(Huff_node),count*2,fp_huff);

    int per=-1;
    printf("\n");

    unsigned char ch;
    int cur_total=0;
    unsigned p=root;

    long cur_total_bytes=0;
    // long size=get_file_size(fp_huff);
    long read_num=total_bytes/min_rw_size;
    unsigned last_size=total_bytes%min_rw_size;
    unsigned cur_write_count=0;
    for(long k=0;k<read_num;k++)
    {
        fread(read_buffer,1,min_rw_size,fp_huff);
        for(int j=0;j<min_rw_size;j++)
        {
            ch=read_buffer[j];
            // (*weight)[ch]++;
            if(100*(double)cur_total/total_bytes>per)
                print_progress(++per,"decoding:");
            cur_total++;
            char byte_str[9]="";
            my_itoa(ch,byte_str);
            int flag=(cur_total==total_bytes&&init_end)?init_end:8;
            for(int i=0;i<flag;i++)
            {
                if(byte_str[i]=='0')
                    p=Huff_tree[p].lchild;
                else
                    p=Huff_tree[p].rchild;
                if(p<=count)
                {
                    // fprintf(fp_init,"%c",(unsigned char)p-1);
                    write_buffer[cur_write_count++]=(unsigned char)p-1;
                    if(cur_write_count==min_rw_size)
                    {
                        fwrite(write_buffer,1,min_rw_size,fp_init);
                        cur_write_count=0;
                    }
                    byte_str[i]='\0';
                    // printf("%d:%s ",p-1,byte_str);
                    p=root;
                }
            }
        }
    }
    if(last_size)
    {
        fread(read_buffer,1,last_size,fp_huff);
        for(int j=0;j<last_size;j++)
        {
            ch=read_buffer[j];
            if(100*(double)cur_total/total_bytes>per)
                print_progress(++per,"decoding:");
            cur_total++;
            char byte_str[9]="";
            my_itoa(ch,byte_str);
            int flag=(cur_total==total_bytes&&init_end)?init_end:8;
            for(int i=0;i<flag;i++)
            {
                if(byte_str[i]=='0')
                    p=Huff_tree[p].lchild;
                else
                    p=Huff_tree[p].rchild;
                if(p<=count)
                {
                    // fprintf(fp_init,"%c",(unsigned char)p-1);
                    write_buffer[cur_write_count++]=(unsigned char)p-1;
                    if(cur_write_count==min_rw_size)
                    {
                        fwrite(write_buffer,1,min_rw_size,fp_init);
                        cur_write_count=0;
                    }
                    byte_str[i]='\0';
                    // printf("%d:%s ",p-1,byte_str);
                    p=root;
                }
            }
        }
    }
    if(cur_write_count)
        fwrite(write_buffer,1,cur_write_count,fp_init);

    fclose(fp_huff);
    fclose(fp_init);
}





void huff_encode(long weight[],int count,Huff_node**Huff_tree,char ***map,int *root)//weight[10]=20 表示第11种类型有20个,weight . map 下标都从0开始
{
    *Huff_tree=(Huff_node*)malloc(sizeof(Huff_node)*(2*count));
    if(!(*Huff_tree))
    {
        printf("malloc failed\n");
        exit(0);
    }
    for(int i=1;i<=count;i++)
    {
        (*Huff_tree)[i].w=weight[i-1];
        (*Huff_tree)[i].lchild=0;
        (*Huff_tree)[i].rchild=0;
        (*Huff_tree)[i].parent=0;
    }
    for(int i=count+1;i<2*count;i++) 
    {
        (*Huff_tree)[i].w=0;
        (*Huff_tree)[i].lchild=0;
        (*Huff_tree)[i].rchild=0;
        (*Huff_tree)[i].parent=0;
    }
    int i;
    int per=-1;
    printf("\n");
    for(i=count+1;i<count*2;i++)
    {
        if(100*(i-count)/(count-1)>per)
            print_progress(++per,"Tree-Building:");
        int min1,min2;
        getmin((*Huff_tree),i,min1,min2);
        if(min1&&!min2)break;
        (*Huff_tree)[i].w=(*Huff_tree)[min1].w+(*Huff_tree)[min2].w;
        (*Huff_tree)[i].lchild=min1;
        (*Huff_tree)[i].rchild=min2;


        (*Huff_tree)[min1].parent=i;
        (*Huff_tree)[min2].parent=i;
    }
    *root=i-1;
    *map=(char **)malloc(sizeof(char *)*count);
    get_huffcode(*Huff_tree,count,*map);
}

void get_weight_from_file( char *filepath,long **weight,int *count)
{
    FILE*fp=fopen(filepath,"rb");
    if(!fp)
    {
        printf("%s file open failed\n",filepath);
        exit(0);
    }
    *count=256;
    *weight=(long *)malloc(sizeof(long)*256);
    if(!*weight)
    {
        printf("malloc failed\n");
        exit(0);
    }
    int i=0;
    for(i=0;i<*count;i++)
    {
        (*weight)[i]=0;
    }
    // memset(*weight,0,*count);
    long size=get_file_size(fp);

    

    int per=-1;
    printf("\n");
    long cur_totals=0;
    unsigned char ch;

    long read_num=size/min_rw_size;
    unsigned last_size=size%min_rw_size;
    for(long i=0;i<read_num;i++)
    {
        fread(read_buffer,1,min_rw_size,fp);
        for(int j=0;j<min_rw_size;j++)
        {
            cur_totals++;
            if(100*(double)cur_totals/size>per)
                print_progress(++per,"weight-getting:");
            ch=read_buffer[j];
            (*weight)[ch]++;
        }
    }
    if(last_size)
    {
        fread(read_buffer,1,last_size,fp);
        for(int j=0;j<last_size;j++)
        {
            cur_totals++;
            if(100*(double)cur_totals/size>per)
                print_progress(++per,"weight-getting:");
            ch=read_buffer[j];
            (*weight)[ch]++;
        }

    }
    // ch=fgetc(fp);
    
    // while(feof(fp)==0)
    // {
    //     cur_totals++;
    //     if(100*(double)cur_totals/size>per)
    //         print_progress(++per,"weight-getting:");
    //     // printf("%d\n",(*weight)[ch]);
    //     (*weight)[ch]++;
    //     // printf("%d\n",(*weight)[ch]);
    //     ch=fgetc(fp);
    // }
}
void get_huffcode(Huff_node*Huff_tree,int count,char **map)
{
    for(int i=0;i<count;i++)
    {
        if(Huff_tree[i+1].w)
        {
            int total_len=2*count;
            char *code=(char *)malloc(sizeof(char)*total_len);
            code[--total_len]='\0';
            for(int k=i+1;Huff_tree[k].parent;k=Huff_tree[k].parent)
            {
                if(k==Huff_tree[Huff_tree[k].parent].lchild)
                    code[--total_len]='0';
                else
                    code[--total_len]='1';
            }
            int map_code_len=2*count-total_len;
            map[i]=(char *)malloc(sizeof(char)*(map_code_len));
            map[i][map_code_len-1]='\0';
            strcpy(map[i],&code[total_len]);
        }
        else
        {
            map[i]=(char *)malloc(sizeof(char)*(1));
            map[i]="";
        }
        

    }
}




void format_filepath(char *filepath)
{
    int flag=1;
    for(int i=0;i<strlen(filepath);)
    {
        if(filepath[i]='\\'&&filepath[i+1]!='\\')
        {
            filepath[i]='/';  
            i+=2;
        }
        else if(filepath[i]='\\'&&filepath[i+1]=='\\')
            i+=2;
        else 
            i++;
    }
}



void get_decode_map(unsigned long**decode_map,char **map,int count)
{//len最长是count-1
    *decode_map=(unsigned long *)malloc(sizeof(unsigned  long)*(count));
    for(int i=0;i<count;i++)(*decode_map)[i]=-1;
    for(int i=0;i<count;i++)
    {
        unsigned long num;
        num=my_atoi(map[i],strlen(map[i]));
        int j;
        for(j=num%count;(*decode_map)[j]!=-1;j=(j+1)%count);
        *(decode_map)[j]=num;
    }
}
unsigned char search_by_decode_map(unsigned long*decode_map,int count,char code[])
{
    int code_len=strlen(code);
    unsigned long num;
    num=my_atoi(code,code_len);
    unsigned char j;
    for(j=num%count;decode_map[j]!=num;j=(j+1)%count);
    return j;
}
void my_itoa(unsigned char ch,char num_str[10])
{
    unsigned char num=128;
    for(int i=0;i<8;i++)
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
void print_map(char *map[],int count)
{
    for(int i=0;i<count;i++)
        printf("%3d:%s\n",i,map[i]);
}
void getmin(Huff_node*Huff_tree,int i ,int &min1,int &min2)
{
    min1=min2=0;
    for(int j=1;j<i;j++)
    {
        if(!Huff_tree[j].parent&&Huff_tree[j].w)
        {
            if(!min1)
                min1=j;
            else if(min1&&!min2)
            {
                if(Huff_tree[j].w<Huff_tree[min1].w)
                {
                    min2=min1;
                    min1=j;
                }
                else
                {
                    min2=j;
                }
            }
            else if(min1&&min2)
            {
                if(Huff_tree[j].w<Huff_tree[min1].w)
                {
                    min2=min1;
                    min1=j;
                }
                else if(Huff_tree[j].w<Huff_tree[min2].w)
                {
                    min2=j;
                }
            }

        }
    }
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