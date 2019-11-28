#include"huff.h"
#include"aux_tool.h"
#include"dir.h"


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>


int main(int argc,char *argv[])
{   
    char helpmessage[1000]="\
Usage:huff <option> <target> ...\n\n\
common usage:\n\
    huff [-e | --encode] <src_dir | src_file> [destination_file | destination_file]\n\
    huff [-d | --decode] <src.huff> [destination_file]\n\
Options:\n\
    -h, --help\t\t help message.\n\
    -v, --version\tPrint version number of huff and exit.\n\
    -e, --encode\t encode file or directory into .huff.\n\
    -d, --decode\t decode .huff file into file or directory.\n\
    \
    ";

    char version_message[1000]="\
huff version 1.0.0 on win.\n\
    \
    ";

    char filepath[100]="";
    char output[100]="";
    if(argc==1){printf("%s\n",helpmessage);return 0;}
    for(int i=1;i<=argc-1;i++)
    {
        if(strcmp(argv[i],"-h")==0||strcmp(argv[i],"--help")==0)
        {
            printf("%s\n",helpmessage);
            return 0;
        }
        else if(strcmp(argv[i],"-v")==0||strcmp(argv[i],"--version")==0)
        {
            printf("%s\n",version_message);
            return 0;
        }
        else if(strcmp(argv[i],"-e")==0||strcmp(argv[i],"--encode")==0)
        {
            if(i==argc-1)
            {
                printf("lack of src file or directory.\n");
                return -1;
            }

            get_correct_path(argv[i+1],filepath);
            if(i+1!=argc-1)
            {
                // strcat(output,)
                int len=strlen(output);
                if(output[len-1]='\\'||output[len-1]=='/')
                output[len-1]='\0';
                get_correct_path(argv[i+2],output);
                printf("%s\n",output);
            }
            else
            {
                output[0]='.';
            }
            
            get_encode_file(filepath,output);
            return 0;
        }
        else if(strcmp(argv[i],"-d")==0||strcmp(argv[i],"--decode")==0)
        {
            // printf("%s\n",argv[i+1]);
            int len;
            if(i==argc-1)
            {
                printf("lack of src file or directory.\n");
                return -1;
            }
            char file[10]="";
            len=strlen(argv[i+1]);
            strcat(file,&argv[i+1][len-5]);
            // printf("%s\n",file);
            if(len<5||strcmp(".huff",file)!=0)
            {
                printf("src file is not .huff type\n");
                return -1;
            }
            if(i+1!=argc-1)
            {
                // strcat(output,)
                if(strcmp(output,".")==0||strcmp(output,"./")==0||strcmp(output,".\\")==0)
                {
                    output[0]='.';//默认情况 即当前文件夹
                }
                else
                {
                    int len=strlen(output);
                    if(output[len-1]='\\'||output[len-1]=='/')
                    output[len-1]='\0';
                    get_correct_path(argv[i+2],output);
                    printf("%s\n",output);
                }
                

            }
            else
            {
                output[0]='.';//默认情况 即当前文件夹
            }
            get_correct_path(argv[i+1],filepath);
            get_decode_file(filepath,output);
            return 0;
        }
        else
        {
            printf("input error\n%s\n",helpmessage);
        }
        

    }

    return 0;
}

void get_encode_file(char *filepath,char *output)
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
    strcpy(file_name,&filepath[i+1]);//获取文件夹名
    printf("directory encoding:%s\n",file_name);

    // char file_huff[100]="./";
    strcat(output,"/");
    strcat(output,file_name);
    strcat(output,".huff");//获取huff压缩文件名和路径
    printf("output file:%s\n",output);

    // FILE*fp=fopen(filepath,"rb");
    FILE*fp_huff=fopen(output,"wb");
    if(!fp_huff)
    {
        printf("%s  created failed. check the path.",output);
        exit(0);
    }
    if(!fp_huff)
    {
        printf("%s Create failed\n",output);
    }
    // printf("huff file:%s\n",file_huff);

    //陆续开始存储解压要用到的数据
    
    fwrite(&root,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);

    fwrite(&count,sizeof(int),1,fp_huff);
    extra_bytes+=sizeof(int);
    fwrite(Huff_tree,sizeof(Huff_node),2*count,fp_huff);//记录哈夫曼树
    extra_bytes+=sizeof(Huff_node)*2*count;

    char relative_path[1000]="/";
    int file_num=0;
   

    FILE*fp=fopen(filepath,"rb");//如果是单个文件
    if(fp)
    {
        printf("encodeing:%s\n",&filepath[1]);
        
        dir_visiting(fp,fp_huff,map,&filepath[1]);
        file_num++;
        fclose(fp);
    }
    else
    {
        dir_encoding(fp_huff,filepath,map,relative_path,&file_num);//这里默认使用了压缩文件夹
    }
    


    
    fwrite(&file_num,sizeof(file_num),1,fp_huff);//文件个数放最后写

    free(weight);
    free(Huff_tree);
    free(map);
    fclose(fp_huff);
}
void get_decode_file(char*filepath,char *output)//规定，解压后一定有一个根文件夹
{
    // printf("filepath:%s\n",filepath);

    FILE*fp_huff=fopen(filepath,"rb");
    if(!fp_huff)
    {
        printf("%s open failed.\n",filepath);
        exit(0);
    }
    char file_name[100]="";
    int i=strlen(filepath);
    for(;i>=0&&filepath[i]!='.';i--);
    int j=i;
    for(;filepath[j]!='\\'&&filepath[j]!='/';j--);

    strncpy(file_name,&filepath[j+1],i-1-j);
    printf("decoding:%s.huff\n",file_name);
    char init_file_path_name[1000]="";
    // printf("output:%s\n",output);
    strcpy(init_file_path_name,output);
    strcat(init_file_path_name,"/");
    strcat(init_file_path_name,file_name);//获取文件夹名

    // printf("dir:%s\n",init_file_path_name);
   
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
        // printf("读出路径:%s\n",relative_path);
        
        strcat(filepath_tmp,init_file_path_name);
        // printf("%s\n",filepath_tmp);
        strcat(filepath_tmp,relative_path);
        // printf("%s\n",filepath_tmp);
        FILE*fp_init=create_dir_file(filepath_tmp);
        if(!fp_init)
        {
            printf("%s created failed.\n",filepath_tmp);
            exit(0);
        }
        printf("decoding:%s\n",relative_path);
        if(!fp_init)
        {
            printf("%s create failed.\n",filepath_tmp);
            exit(0);
        }

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
    // int per=-1;
    // printf("\n");
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
    
    FILE*fp=fopen(filepath,"rb");//如果是单个文件
    if(fp)
    {
        // printf("encodeing:%s\n",&filepath[1]);
        unsigned char ch;
        fread(&ch,sizeof(ch),1,fp);
        while(feof(fp)==0)
        {
            (*weight)[ch]++;
            fread(&ch,sizeof(ch),1,fp);
        }
        fclose(fp);
        
    }
    else
    {
        dir_weighting(filepath,*weight,&total_bytes);//这里默认使用了压缩文件夹
    }
    
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



