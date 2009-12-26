#include "stdio.h"
#include "string.h"
#define N sizeof(struct book)/*N代表结构体的空间大小*/
int num3=0;/*num3用来记录文件中存储的书本的数目*/



/*结构体用于存储图书信息*/
struct book
{
  char sort[16];/*书的类别*/
  char name[16];/*书名*/
  char author[16];/*著者信息*/
  long numble;/*书号*/ 
  long numble2;/*借书人借书证号*/
  int lend;/*lend用来标记图书是否被借,1为被借, 0为未借，2为续借*/
  long time1;/*借书时间*/
  long time2;/*还书时间*/
  struct book *next;/*用于不同指针之间的连接*/
}*head;/*在这里定义一个名为head的结构体，且head为全局变量*/

/*输出函数*/ 
printfs(struct book *p1)/*它的功能就是将传入指针指向结构体的内容输出*/
{
   printf("  类别:%-11s  书名:%-11s  作者:%-11s  书号:%-ld\n被借人借书证号:%ld 已借:%d  借书日期:%ld  还书日期:%ld\n",p1->sort,p1->name,p1->author,p1->numble,p1->numble2,p1->lend,p1->time1,p1->time2);
}



/*读取模块*/
struct book *read(fp)/*从文件中读取数据，并赋值给申请的结构体空间中*/
{ 
   struct book *p1,*p2,*p3;
   FILE *fp2;

   fp2=fp;
   head=NULL;
   while(!feof(fp2))/*用来控制文件中的指针在文件末尾时结束执行while内的语句*/
   {  
     if(num3==0)
	 { 
	     head=p3=p2=p1=(struct book *)malloc(N);/*head,p1,p2指首结点*/
         fscanf(fp2,"%s%s%s%ld%ld%d%ld%ld ",p1->sort,p1->name,p1->author,&p1->numble,&p1->numble2,&p1->lend,&p1->time1,&p1->time2);
         printf("  类别:%-11s  书名:%-11s  作者:%-11s  书号:%-ld\n  被借人借书证号:%ld已借:%d  借书日期：%ld  还书日期:%ld\n\n",p1->sort,p1->name,p1->author,p1->numble,p1->numble2,p1->lend,p1->time1,p1->time2);
		 /*fp2为文件内部指针*/
 		 num3=1;/*num3的值在第一次执行完后变为1，以后执行else里的语句，这样head不变地指向申请的第一个地址*/
	 }
	 else
	 {
	     p1=(struct book *)malloc(N);/*head,p1,p2指首结点*/
         fscanf(fp2,"%s%s%s%ld%ld%d%ld%ld ",p1->sort,p1->name,p1->author,&p1->numble,&p1->numble2,&p1->lend,&p1->time1,&p1->time2);
     	 printf("  类别:%-11s  书名:%-11s  作者:%-11s  书号:%-ld\n  被借人借书证号:%ld已借:%d  借书日期：%ld  还书日期:%ld\n\n",p1->sort,p1->name,p1->author,p1->numble,p1->numble2,p1->lend,p1->time1,p1->time2);
		 p2->next=p1;
         p2=p1;
		 num3++;
	 }
   }
   p2->next=NULL;/*最后一个申请的地址的next指向空地址NULL*/

}
reads()
{   
    FILE *fp;
    if((fp=fopen("newbook.txt","rt"))==NULL)/*rb表示只读打开一个文本文件，只允许读数据*/
    {
       printf("\n不能打开此文件，按任意键退出!");
       getch();/*getch()函数可以时printf输出的内容停留在屏幕上*/
       exit(1);
    }
    read(fp);
    fclose(fp);/*读取完后关闭文件*/
	return fp;/*将文件指针返回，便于后边进行内容更新*/
}



/*保存模块*/
save()
{
	FILE *fp;
    struct book *p1;
    if((fp=fopen("newbook.txt","wt"))==NULL)/*wt表示只打开或着建立一个文件，只允许写数据*/
    {
       printf("\n不能打开此文件，按任意键退出!");
       getch();
       exit(1);
    }

	p1=head;     
	while(p1!=NULL)/*保存内存中结构体中的内容到文件，p11=NULL时p1指向结构体的尾部，此时结束保存*/
	{
		fprintf(fp,"%s %s %s %ld %ld %d %ld %ld ",p1->sort,p1->name,p1->author,p1->numble,p1->numble2,p1->lend,p1->time1,p1->time2);
       /* printf("  类别:%-11s  书名:%-11s  作者:%-11s  书号:%-ld\n被借人借书证号:%ld  已借:%d  借书日期:%ld  还书日期:%ld\n",p1->sort,p1->name,p1->author,p1->numble,p1->numble2,p1->lend,p1->time1,p1->time2);*/
		p1=p1->next;/*每次赋值完后，将指针后移一次*/

	}  
    
	fclose(fp);/*保存完文件关闭文件*/
}





/*新书入库模块*/
struct book *creat()
{  struct book *p1,*p2,*p3,*head2;
   int i,j,k,a=0;/*a用来标记输入类别是否符合图书类别中的一个*/
   char sorts[][16]={"leader","literature","foreignlang","computer","math","magazine","other"};
   printf("请输入入库书本数量:");/*输入需要入库新书的数量*/
   scanf("%d",&k);
   head2=NULL;/*先定义结构体为空*/
   if(k>0)/*当输入为0时,不需申请空间,直接返回空指针*/
   {
      head2=p2=p1=(struct book *)malloc(N);/*head,p1,p2指首结点*/
      printf("请输入第1本书的类别(社科:leader  文艺:literature  外语:foreignlang\n计算机:computer  数学:math  杂志:magazine  其他:other)、书名、作者、书号\n");
      scanf("%s%s%s%ld",p1->sort,p1->name,p1->author,&p1->numble);
   	  p1->numble2=0;/*新书入库时没有必要进行借书证、借书日期、还书日期的输入，所以系统默认为0，表示该书未被借*/
	  p1->lend=0;
	  p1->time1=0;
	  p1->time2=0;
	 
/*下面的for循环用来控制输入的图书类别在合法范围（社科:leader  文艺:literature  外语:foreignlang\n计算机:computer  数学:math  杂志:magazine  其他:other）内*/
      for(;a!=1;)
          {
              for(i=0;i<7;i++)
                 if(!strcmp(sorts[i],p1->sort))
        		 {
                   a=1;
                   break;  
            	 }   
                 if(a!=1)  
        		 {
                   printf("您输入类别(社科:leader  文艺:literature  外语:foreignlang\n计算机:computer  数学:math  杂志:magazine  其他:other)有误!!\n请重新输入类别:\n");       
                   scanf("%s",p1->sort);
        		 }
          } 
      for(i=1;i<k;i++)
      {  
          printf("请输入第%d本书的类别、书名、作者、书号\n",i+1);
          p1=(struct book *)malloc(N);/*p1指向新申请的结点*/
          scanf("%s%s%s%ld",p1->sort,p1->name,p1->author,&p1->numble);
          p1->numble2=0;
	      p1->lend=0;
	      p1->time1=0;
	      p1->time2=0;
          a=0;/*将a还原为初始值0，以便对输入的图书类别进行检查*/
          /*下面的for循环用来控制输入的图书类别在合法范围（社科:leader  文艺:literature  外语:foreignlang\n计算机:computer  数学:math  杂志:magazine  其他:other）内*/
		  for(;a!=1;)
          {
              for(j=0;j<7;j++)
                 if(!strcmp(sorts[j],p1->sort))
        		 {
                   a=1;
                   break;  
            	 }   
                 if(a!=1)  /*当输入的类别不属于合法范围内时，提示用户输入正确图书的类别*/
        		 {
                   printf("您输入类别(社科:leader  文艺:literature  外语:foreignlang\n计算机:computer  数学:math  杂志:magazine  其他:other)有误!!\n请重新输入类别:\n");       
                   scanf("%s",p1->sort);
        		 }
          } 
          p2->next=p1;
          p2=p1;
      }   
      p2->next=NULL;/*最后一次申请的空间，指向NULL*/
   }
   if(head==NULL)
	   head=head2;
   p3=head;
   while(p3->next!=NULL)/*将存储文件原来信息的结构体与存储新录入图书的结构体连接在一起*/
   {
       p3=p3->next; 
   }
   p3->next=head2;
   return head;/*将存储图书信息的结构体的头指针返回*/
}




/*清除库存模块*/
clean()
{  
     long num;/*定义一个长整型变量，用于存储输入的书号，并与文件中的书号相比较，从而得出要删除的书指针*/
     struct book *p,*p0;
     if(head==NULL) return 0;
     printf("请输入要删除的书号：");
     scanf("%ld",&num);
     p0=head;
     if(p0->numble==num)
	 {
        head=p->next;
        free(p0);
        return 1;
	 }
     p=p0->next;
     while(p!=NULL)
	 {
       if(p->numble==num)
	   {
          p0->next=p->next;
          free(p);
          return 1;
	   }
       p0=p;
       p=p->next;
	 }
  return 0;
}





/*权限验证模块*/
validate()
{  
   int b=0,i;
   char password[16],passwords[16];
   FILE *fp;
   if((fp=fopen("passwords.txt","rt"))==NULL)/*先从文本文件中读出系统的密码*/
   {
       printf("\n不能打开此文件，按任意键退出!");
       getch();
       exit(1);
    }
   fscanf(fp,"%s",&passwords);/*要求用户输入密码*/    
   fclose(fp);
   printf("\n请输入密码:");
   scanf("%s",&password);
   for(i=0;i<3;i++)
   {
       
       if(strcmp(password,passwords))/*将用户输入的密码与存储在文本文件中的系统密码核对，相同时执行管理操作*/
       {printf("您输入密码有误!!\n");
        if(i==2)/*输入三次时，警告用户，并退出输入*/
            printf("本系统受法律保护，请不要恶意更改!!!");	   	   
        if(i<2)
        {printf("请重新输入:\n");
         scanf("%s",&password);
    	}
       }
       else
       {printf("您已经成功登陆!\n");/*输入正确时，提示用户成功登陆！*/
       b=1;
       break;
       }
   }
   if(b==1)
   return(b);
}


    




/*密码设定模块*/
passwords()
{
	char passwords[16],passwordss[16];
	FILE *fp1;
    if((fp1=fopen("passwords.txt","wt"))==NULL)/*先从文本文件中读出系统的密码*/
	{
      printf("\n不能打开此文件，按任意键退出!");
      getch();
      exit(0);
	}
  loop4:printf("\t请输入新密码：");/*提示用户输入新密码*/
  scanf("%s",&passwords);
  printf("\t请再次输入新密码：");/*提示用户再次输入新密码*/
  scanf("%s",&passwordss);
  if(strcmp(passwords,passwordss))/*对用户两次输入密码进行核对，两次输入不一致时，提示用户重新设定密码*/
  {printf("您两次输入密码不一致!请重新设定!\n");
  goto loop4;
  }
  else
  {fprintf(fp1,"%s",passwords);
   printf("恭喜您!密码设定成功!\n");/*设定密码成功后，对用户进行提示*/
   fclose(fp1);
  }
}





/*按书号查询*/
num_find(long num)/*num为调用文件时传入的书号*/
{ 
	struct book *p;
     p=head;
     while(p!=NULL)
	 {
        if(p->numble==num) return p;
        p=p->next;
	 }
    return NULL;
}



name_finds()
{
    
     char name[16];
	 struct book *p;
     printf("请输入要查找的书名：");/*提示用户输入要查找的书名*/
     scanf("%s",&name);
	 p=head;
     while(p!=NULL)
	 {
        if(!strcmp(p->name,name)) return p;
        p=p->next;
	    
	 }
     
     return NULL;
}



/*按作者查询*/
author_find()
{
     char author[16];
	 struct book *p;
     printf("请输入要查找的作者：");/*提示用户输入要查找的作者*/
     scanf("%s",&author);
	 p=head;
     while(p!=NULL)
	 {
        if(!strcmp(p->author,author)) return p;
        p=p->next;
	    
	 }
     
     return NULL;
}




/*按书名和作者查询*/
name_author()
{
     char author[16];
	 char name[16];
	 struct book *p;
     printf("请输入要查找的书名和作者:");/*提示用户输入要查找的书名和作者*/
     scanf("%s%s",&name,&author);
	 p=head;
     while(p!=NULL)
	 {
        if(!strcmp(p->author,author)&&!strcmp(p->name,name)) return p;
        p=p->next;
	    
	 }
     return NULL;
}




/*借书模块*/
lend()
{
    long num1,num2;
	struct book *p;
    printf("请输入书号：");/*提示用户输入要借书的书号*/
	scanf("%ld",&num1);
    p=num_find(num1);
	if(p->lend==1)/*判断所输书号的书是否被借走*/
		printf("此书已被借走!");/*提示用户此书被续借*/
	else
	{
	  p->lend=1;
	  printf("请输入借书证号码:");/*提示用户输入借书证号*/
	  scanf("%ld",&num2);
	  printf("请输入借书日期:");/*提示用户输入借书日期*/
	  scanf("%ld",&p->time1);
	  printf("请输入还书日期:");/*提示用户输入还书日期*/
	  scanf("%ld",&p->time2);

	  p->numble2=num2;
	  printf("您借书成功!\n");
	
	}

}



/*统计同一作者书的数量*/
author_book()
{
     char author[16];
	 struct book *p;
     int i=0;
	 printf("请输入要统计的作者：");/*提示用户输入要统计的作者*/
     scanf("%s",&author);
	 p=head;
     while(p!=NULL)
	 {
        if(!strcmp(p->author,author))  i++;
        p=p->next;
	   
	 }
     
     printf("%d",i);
}




/*统计书名相同书的数量*/
name_book()
{
     char name[16];
	 struct book *p;
     int i=0;
	 printf("请输入要统计的书名：");/*提示用户输入要统计的书名*/
     scanf("%s",&name);
	 p=head;
     while(p!=NULL)
	 {
        if(!strcmp(p->name,name))  i++;
        p=p->next;
	    
	 }
     
     printf("%d",i);
}


/*统计某学生的借书*/
lend_book()
{
     long num2;
	 struct book *p;
     int i=0;
	 printf("请输入要统计学生的借书证号:");/*提示用户输入要统计的学生的借书证号*/
     scanf("%ld",&num2);
	 p=head;
	 printf("您借的书:");
     while(p!=NULL)
	 {
        if(p->numble2==num2) 
		{
		    i++;
			printf("%s  ",p->name);/*将用户所借的书输出到屏幕上*/
        }  
		p=p->next;/*移动指针*/
		
	 }
     
     printf("共借%d本书。",i);/*将用户所借的书的数量输出*/
}



/*还书模块*/
get_back()
{
   long num1,num2;
	struct book *p;
    printf("请输入书号：");/*提示用户输入要还的书的书号*/
	scanf("%ld",&num1);
    p=num_find(num1);
	p->numble2=0;
	p->lend=0;
	p->time1=0;
    p->time2=0;
	 
	printf("您还书成功！\n");/*提示用户还书成功*/


}



/*续借模块*/
go_on()
{
    long num1,num2;
	struct book *p;
    printf("请输入书号：");/*提示用户输入要要续借的书的书号*/
	scanf("%ld",&num1);
    p=num_find(num1);
	
	
	if(p->lend==2)/*判断所输书号的书是否被续借过*/
		printf("你已经续借过了!操作不成功\n");
	else
	{
		p->lend=2;
	    printf("请输入还书日期:");/*提示用户输入新的还书日期*/
	    scanf("%ld",&p->time2);
	    printf("您续借成功！\n");/*提示用户续借成功*/
	
	} 

}



/*按书号从小到大排序*/
num1_()
{
   struct book *q,*s,*p,*t=NULL;
   int i,j,n;
   p=q=s=head;
   n=num3;

   for(i=0;i<n;i++)
   {

      for(j=i;j<n;j++)
      {
        if(q->numble>p->numble)
           q=p;
           p=p->next;
      }
      *t=*s;
      *s=*q;
      *q=*t;
      t->next=s->next;
      s->next=q->next;
      q->next=t->next;
      s=s->next;
      q=p=s;
   }

}




  face()/*功能选取界面模块*/
{ 
    int a,b;/*a是用来记录用户所选模块的参数*/
	FILE *fp;
    do
    {  

       fp=reads(); /*每次运行时都先将文件里的图书信息读到内存里*/ 
	   printf("%d",num3);
       printf("\n\n\n\n*******************************图书管理系统************************************\n\n\n\n");
       printf("\t\t\t1.资料管理(新书入库和清除库存)\n\n\t\t\t2.信息查询(书本信息查询.统计和借阅信息排序)\n\n\t\t\t3.借书\n\n\t\t\t4.还书\n\n\t\t\t5.续借\n\n\t\t\t0.退出系统\n");
       printf("\n\n备注：进入图书管理界面后，输入9设定密码！！初始密码为computer\n\n\n\n\n\t请输入(0-5):");
       scanf("%d",&a);
       /*clrscr();*/
  loop:switch(a)/*switch函数的运用，使用户进入自己所选的模块进行具体的操作*/
       {
          case 1:if(validate()==1)/*密码验证可以使重要资料的管理更具安全性*/
        		 {  
                     printf("您已进入资料管理模块！1.新书入库  2.清除库存\n");
                     printf("请输入1-2:");
                     scanf("%d",&b);
                     switch(b)
        			 {
                        case 1:creat();
							   break;
                        case 2:clean();
							   break;
                        		 
        			 }
                 }
                 break;/*当用户输入1时，进入资料管理模块，break用来跳出switch*/
          case 2:printf("您已进入信息查询.统计模块!\n\t1.书本信息查询.统计\t2.按书号从小到大排序\t\n");
                 printf("\t请输入(1-2):");
                 scanf("%d",&b);
           loop2:switch(b)
        		 { 
                    case 1:printf("您已进入书本信息查询.统计模块\n\t1.按书名查询       2.按作者查询        3.按书名和作者查询\n  4.统计同一作者的书\t5.统计同一书名的书\t6.统计某学生借书\n");
						   printf("请输入1-6：");
						   scanf("%d",&b);
						   switch(b)
						   {
						       case 1:printfs(name_finds(fp));break;/*执行按书名查找函数后将返回的指针指向结构体里的内容输出*/
						       case 2:printfs(author_find(fp));break;/*执行按作者查找函数后将返回的指针指向结构体里的内容输出*/
						       case 3:printfs(name_author(fp));break;/*执行按书名和作者查找函数后将返回的指针指向结构体里的内容输出*/
						       case 4:author_book();break;/*统计同一作者的书*/
						       case 5:name_book();break;/*统计同一书名的书*/
						       case 6:lend_book();break;/*统计某学生借书*/
						    
						   }
					      break;
                    case 2:num1_();/*按书号从小到大排序*/
					      break;
                    default:printf("输入错误!请重新输入:");scanf("%d",&b);goto loop2;/*当输入的数字不属于1-2时，提示输入错误，并要求重新输入*/
        		 }
                 break;
          case 3:printf("您已进入借书模块");
			     lend();
				 break;
          case 4:printf("您已进入还书模块");
			     get_back();
				 break;
          case 5:printf("您已进入续借模块");
			     go_on();
				 break;
          case 9:passwords();/*设定密码模块*/
          case 0:break;
          default:printf("输入错误！请重新输入:\n");scanf("%d",&a);goto loop;/*当输入的数字不属于0—9时，提示输入错误，并要求重新输入*/
       }
       getch();/*getch()函数可以时printf输出的内容停留在屏幕上*/
       save();/*每次更新完资料后，都对数据进行储存*/
	   num3=0;/*每次操作后将num3恢复为0便于下次操作时对文件中书本数量的记录*/
    }while(a!=0);/*运行程序后，只有输入a时退出系统*/
   
	reads();/*退出系统时将最后保存的数据输出到屏幕*/

}


void main()
{   
	
    face();/*这是一个界面函数，对系统的所有操作都在此函数中进行*/
	
}
