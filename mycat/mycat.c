//mycat命令

#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
const struct option long_options[]={//长选项转换
    {"help",0,NULL,'h'}, 
    {"version",0,NULL,'k'}, 
    {NULL,0,NULL,0} 
};

int main(int argc,char **argv)
{
   FILE *fp;//定义文件指针
      char a[1],a1[90];//用于暂时存放从文件中读取的字符数据
      int b1,b2=1,b3=0,i=0,line=1,line2=1;
   int bb=0,EE=0,nn=0,ss=0,TT=0,vv=0; 
   if(argc==0)
       return 1; 
   if(argc==1)
   for(;;){
       scanf("%s",a);
       puts(a);
   }
   while((b1=getopt_long(argc,argv,"AbeEnstTuvh",long_options,NULL))!= -1)
       switch(b2++,b1){ 
       case 'k':printf(" mycat(GUN coreutils)5.99\nCopyright (C)2006 Free Software Foundation,Inc.\n这是自由软件。您可以按照GUN GPL协议< http://www.gnu.org/licenses/gp1/html>的条款再发布此软件的副本，但我们无法保证相关法律不对这一情形进行限制。\n\n由China Xi'an Instatute of Post & Communication 孔建军编写。\n");return 1; 
       case 'A':vv=1;EE=1;TT=1;break;//等价于 -vET 
       case 'b':bb=1;break;//对非空输出行编号
              case 'e':vv=1;EE=1;break;//等价于 -vE
       case 'E':EE=1;break;//在每行结束处显示 $
       case 'n':nn=1;break;//对输出的所有行编号
              case 's':ss=1;break;//不输出多行空行 
              case 't':vv=1;TT=1;break;//与 -vT 
       case 'T':TT=1;break;//等价将跳格字符显示为 ^I
       case 'u':;break;//(被忽略)
       case 'v':vv=1;break;//使用 ^ 和 M- 引用，除了 LFD 和 TAB 之外
              case 'h':printf("用法： mycat [选项] [文件]...\n将[文件]或标准输入组合输出到标准输出。\n\n  -A, --show-all           等价于 -vET\n\n  -b, --number-nonblank    对非空输出行编号\n  -e                       等价于 -vE\n  -E, --show-ends          在每行结束处显示 $\n  -n, --number             对输出的所有行编号\n  -s, --squeeze-blank      不输出多行空行\n  -t                       与 -vT 等价\n  -T, --show-tabs          将跳格字符显示为 ^I\n  -u                       (被忽略)\n  -v, --show-nonprinting   使用 ^ 和 M- 引用，除了 LFD 和 TAB 之外\n      --help     显示此帮助信息并退出\n      --version  输出版本信息并退出\n\n如果[文件]缺省，或者[文件]为 - ，则读取标准输入。\n\n示例：\n  cat f - g  先输出 f 的内容，然后输出标准输入的内容，最后输出 g 的内容。\n  mycat        将标准输入的内容复制到标准输出。\n\n请向 < bug-coreutils@gnu.org> 报告错误。\n"); 
              return 1;//显示此帮助信息并离开
              default:break;
    } 
    if((fp=fopen(*(argv+b2),"rb"))==NULL){
        printf("\nCan't open %s!\n",*(argv+b2)); 
        return 1;
        } 
    while(!feof(fp)){        //指针到达文件结尾前都执行循环    
                fscanf(fp,"%c",&a1[i]); 
    i++;
    }
    i=0;
    while(a1[i]!=(int)NULL){
        if(a1[i]!='\n'&&i==0&&(bb==1||nn==1))//按选项在第一行头输出行号1 
            printf("     1  ");        
        if(a1[i]=='\n'){ 
            line++;
            line2++;
        }
        if(bb==1&&a1[i]=='\n'&&a1[i+1]=='\n') 
            line2--; 
        if(a1[i]=='\t'&&TT==1) //将跳格字符显示为 ^I 
            printf("^I"); 
        else{ 
            if(ss==1&&a1[i]=='\n'&&a1[i+1]=='\n'){    //压缩多空行为一 
                                for(;a1[i+1]=='\n';i++); 
                    if(EE==1&&a1[i-1]=='\n') printf("$");
                printf("\n"); 
            }        
            if(EE==1&&a1[i]=='\n')   printf("$"); 
            if(vv==0)    printf("%c",a1[i]); 
            else{
                if(a[i]<32) printf("^%c",a[i]+64); 
                else{
                     if(a[i]<127)    printf("%c",a[i]); 
                     else{
                          if(a[i]==127)  printf("^?");
                          else   printf("M-%c",a[i]-128); 
                       } 
                  }  
            }
            if(nn==1&&a1[i]=='\n'&&a1[i+1]!=(int)NULL) 
                 printf("     %d  ",line);
            if(a1[i]=='\n'&&bb==1&&a1[i+1]!=(int)NULL&&a1[i+1]!='\n') 
                 printf("     %d  ",line2);     
        }
        i++;
    }
    fclose(fp);
    return 0;