#include"huff.h"
#include"aux_tool.h"
#include"dir.h"


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>


int main(int argc,char *argv[])
{   
    LARGE_INTEGER li;
    LONGLONG start, end, freq;
    char *init_filepath="C:\\Users\\庞进林\\Pictures\\求实小学";
    // // char *init_filepath="C:\\Users\\庞进林\\source\\huff\\test.txt";
    // char *init_filepath="C:\\Users\\庞进林\\Music\\Music\\薛之谦 - 丑八怪+演员.flac";

    // QueryPerformanceFrequency(&li);
    // freq = li.QuadPart;

    // QueryPerformanceCounter(&li); 
    // start = li.QuadPart;
    get_encode_file(init_filepath);
    // QueryPerformanceCounter(&li);
    // end = li.QuadPart;
    // double useTime =(end - start) / (double)freq;
    // int len=strlen("total encode time:");
    // char x[100]="";
    // x[0]='\n';
    // memset(&x[1],' ',20-1-len);
    // sprintf(&x[20-len],"total encode time:%.6f s",useTime);
    // printf("%s",x);
    
    
    

    char *huff_filepath="./Test/求实小学.huff";
    // QueryPerformanceCounter(&li); 
    // start = li.QuadPart;
    get_decode_file(huff_filepath);
    // QueryPerformanceCounter(&li);
    // end = li.QuadPart;
    // useTime =(end - start) / (double)freq;
    // len=strlen("total decode time:");
    // char y[100]="";
    // y[0]='\n';
    // memset(&y[1],' ',20-1-len);
    // sprintf(&y[20-len],"total decode time:%.6f s",useTime);
    // printf("%s",y);
    
    return 0;
}

void get_encode_file(char *filepath)
{
    int extra_bytes=0;
    long *weight;
    int count;
    get_weight(filepath,&weight,&count);

    Huff_node*Huff_tree;
    char **map;
    int root;
    huff_encode(weight,count,&Huff_tree,&map,&root);
 

    int i=strlen(filepath);
    for(;filepath[i]!='\\'&&filepath[i]!='/';i--);
    char file_name[100]="";
    strcpy(file_name,&filepath[i+1]);//获取文件名

    char file_huff[100]="./Test/";
    strcat(file_huff,file_name);
    strcat(file_huff,".huff");//获取huff压缩文件名和路径
    // printf("%s\n",file_huff);

    // FILE*fp=fopen(filepath,"rb");
    FILE*fp_huff=fopen(file_huff,"wb");

    //陆续开始存储解压要用到的数据
    
    fwrite(&root,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);

    fwrite(&count,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);
    fwrite(Huff_tree,sizeof(Huff_node),2*count,fp_huff);//记录哈夫曼树
    extra_bytes+=sizeof(Huff_node)*2*count;

    char relative_path[1000]="/";
    int file_num=0;
    dir_encoding(fp_huff,filepath,map,relative_path,&file_num);
    fwrite(&file_num,sizeof(file_num),1,fp_huff);//文件个数放最后写

    free(weight);
    free(Huff_tree);
    free(map);
    fclose(fp_huff);
}
void get_decode_file(char*filepath)
{

    FILE*fp_huff=fopen(filepath,"rb");

    int i=strlen(filepath);
    for(;i>=0&&filepath[i]!='.';i--);
    int j=i;
    for(;filepath[j]!='\\'&&filepath[j]!='/';j--);
    char file_name[100]="";
    strncpy(file_name,&filepath[j+1],i-1-j);
    char init_file_path_name[1000]="./Test/";
    strcat(init_file_path_name,file_name);//获取文件名

   
    int file_num;
    fseek(fp_huff,-sizeof(file_num),2);
    fread(&file_num,sizeof(file_num),1,fp_huff);

    fseek(fp_huff,0,0);
    int root;
    fread(&root,sizeof(root),1,fp_huff);

    int count;
    fread(&count,sizeof(count),1,fp_huff);

    Huff_node*Huff_tree=(Huff_node*)malloc(sizeof(Huff_node)*count*2);
    fread(Huff_tree,sizeof(Huff_node),count*2,fp_huff);

    for(int i=0;i<file_num;i++)
    {
        char filepath_tmp[1000]="";
        char relative_path[1000]="";
        int len;
        fread(&len,sizeof(len),1,fp_huff);
        fread(relative_path,sizeof(char),len,fp_huff);
        relative_path[len-1]='\0';
        // printf("读出路径:%s %d\n",relative_path,len);
        
        strcat(filepath_tmp,init_file_path_name);
        // printf("%s\n",filepath_tmp);
        strcat(filepath_tmp,relative_path);
        // printf("%s\n",filepath_tmp);
        FILE*fp_init=create_dir_file(filepath_tmp);

        int init_end;
        fread(&init_end,sizeof(init_end),1,fp_huff);

        long total_bytes;
        fread(&total_bytes,sizeof(total_bytes),1,fp_huff);


        unsigned p=root;
        for(long j=0;j<total_bytes;j++)
        {
            unsigned char ch=fgetc(fp_huff);
            char byte_str[9]="";
            my_itoa(ch,byte_str,8);
            int flag=(j==(total_bytes-1)&&init_end)?init_end:8;
            for(int i=0;i<flag;i++)
            {
                if(byte_str[i]=='0')
                    p=Huff_tree[p].lchild;
                else
                    p=Huff_tree[p].rchild;
                if(p<=count)
                {
                    p--;//这是哈夫曼树的问题
                    fwrite(&p,sizeof(unsigned char),1,fp_init);
                    // printf("%c",p);
                    p=root;
                }
            }
        }
        fclose(fp_init);
        // printf("\n");
    }

    fclose(fp_huff);
    free(Huff_tree);
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
        // if(100*(i-count)/(count-1)>per)
        //     print_progress(++per,"Tree-Building:");
        int min1,min2;
        get_min((*Huff_tree),i,min1,min2);
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

void get_weight( char *filepath,long **weight,int *count)
{
    

    *count=256;
    *weight=(long *)malloc(sizeof(long)*(*count));
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
    long total_bytes=0;
    dir_weighting(filepath,*weight,&total_bytes);
    return;
    
}

void get_min(Huff_node*Huff_tree,int i ,int &min1,int &min2)
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


void print_map(char *map[],int count)
{
    for(int i=0;i<count;i++)
        printf("%3d:%s\n",i,map[i]);
}



