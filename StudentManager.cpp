#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <string.h>
#define  maxsize 1000
#define  process 521

//各种分数结构体 
struct scores
{
	int Chinese;//语文 
	int Math;//数学 
	int English;//英语 
	int total;//总分 
	int aver;//平均分 
};
//单个学生的基本信息结构体 
struct student
{
	char num[10];//学号 
	char name[12];//姓名 
	char sex[8];//性别 
	int age;//年龄 
	struct scores fenshu;//分数 
	char hobby[20];//爱好 
};

//班级学生基本情况结构体 
 
struct students
{
	struct student* NUM [maxsize];//存放学生信息的数组 
	int length;//当前的班级学生的人数 
};
//返回菜单结构体
struct  laststep 
{
	struct students* NUM [process];//存放操作过程的数组 
	int length;//当前的操作步数
	int i;//判断是否执行返回操作的标志
	int current_index;//始终和length保持同步，只有当执行返回操作时，不再和length保持同步，
	                  //作用是在之前的操作范围内返回，不返回当前的返回操作 
	int index;//当前的正在执行的返回操作的下标位置 
 }; 
//初始化班级信息
students* ChuShiHua(students *first)
{
	first->length=0;
	printf("班级信息初始化成功！\n");
	return first;
 }
 //初始化返回记录信息
 laststep* ChuShiHua_laststep(laststep *record)
 {
 	record->index=0;
 	record->length=0;
 	printf("初始化返回记录信息成功！\n"); 
 	return record;
  } 
 /*声明函数 
 
 */ 
void save(students *first);
void  record_method(laststep* record,students *first);
void printall(students * first); 
void  logo(students *first); 
 
 //将first的内容复制到记录中
 void first_to_record(laststep* record,students *first)
 {
    record->NUM[record->length]=(students*)malloc(sizeof(students));
    record->NUM[record->length]->length=first->length;//保持与first当前的人数相同 
 	for(int i=0;i<first->length;i++)
 	{
 		record->NUM[record->length]->NUM[i]=(student*)malloc(sizeof(student));//记得要申请对应的学生空间 
 		strcpy(record->NUM[record->length]->NUM[i]->num,first->NUM[i]->num);//字符数组不能直接用“=”赋值，要通过方法strcpy赋值，切记！！！ 
 		strcpy(record->NUM[record->length]->NUM[i]->name,first->NUM[i]->name);
		strcpy(record->NUM[record->length]->NUM[i]->sex,first->NUM[i]->sex);
		record->NUM[record->length]->NUM[i]->age=first->NUM[i]->age;
		record->NUM[record->length]->NUM[i]->fenshu.Chinese=first->NUM[i]->fenshu.Chinese;
		record->NUM[record->length]->NUM[i]->fenshu.Math=first->NUM[i]->fenshu.Math;
		record->NUM[record->length]->NUM[i]->fenshu.English=first->NUM[i]->fenshu.English;  
		record->NUM[record->length]->NUM[i]->fenshu.total=first->NUM[i]->fenshu.total;
		record->NUM[record->length]->NUM[i]->fenshu.aver=first->NUM[i]->fenshu.aver;
		strcpy(record->NUM[record->length]->NUM[i]->hobby,first->NUM[i]->hobby);
	 }
 	
  } 
 //将记录中的内容放入到first中取
 void  record_to_first(laststep* record,students *first)
 {
 	first->length=record->NUM[record->index]->length;//保持与first当前的人数相同 
 	for(int i=0;i<first->length;i++)
 	{
 		first->NUM[i]=(student*)malloc(sizeof(student));//记得要申请对应的学生空间 
 		strcpy(first->NUM[i]->num,record->NUM[record->index]->NUM[i]->num);//字符数组不能直接用“=”赋值，要通过方法strcpy赋值，切记！！！ 
 		strcpy(first->NUM[i]->name,record->NUM[record->index]->NUM[i]->name);
		strcpy(first->NUM[i]->sex,record->NUM[record->index]->NUM[i]->sex);
		first->NUM[i]->age=record->NUM[record->index]->NUM[i]->age;
		first->NUM[i]->fenshu.Chinese=record->NUM[record->index]->NUM[i]->fenshu.Chinese;
		first->NUM[i]->fenshu.Math=record->NUM[record->index]->NUM[i]->fenshu.Math;
		first->NUM[i]->fenshu.English=record->NUM[record->index]->NUM[i]->fenshu.English;  
		first->NUM[i]->fenshu.total=record->NUM[record->index]->NUM[i]->fenshu.total;
		first->NUM[i]->fenshu.aver=record->NUM[record->index]->NUM[i]->fenshu.aver;
		strcpy(first->NUM[i]->hobby,record->NUM[record->index]->NUM[i]->hobby);
	 }
  } 
 
 //记录操作步骤，有数据更新的地方都要使用一下，把数据记录下来，这里使用的是，定义一个相同的结构体，复制当前状态的
 //信息。比如加入数据，删除数据，更改数据，重排数据都要记录下来
 /*在加入撤退功能时，大部分的方法要加入laststep*record的参数，同时在调用这些方法的地方，也要加入参数，切记，你自己就犯了这个错误
 改了比较久的时间 
 */
 void  record_method(laststep* record,students *first)
 {
 	first_to_record(record,first);
 	record->length++;
 	printf("保存了%d个步骤！\n",record->length);
 	
  } 
  //上一步
  void last(laststep* record,students *first)
  {
  	   if(record->i==0)
  	   {
  	   	 record->current_index=record->length-1;
  	   	 record->index=record->current_index;
  	   	 record->i=1;
		 }
		if(record->index<=0)
		{
			printf("到达后退的极限！\n");
			return;
		}
		record->index--;
		//first=record->NUM[record->index];//不能单纯的将指针赋值，因为他值得位置都是first，first的内容变了，复制的内容也会同步变动，所以返回步骤里的内容都是一样的
		record_to_first(record,first);
		//要解决这个问题就要将内容复制，你这里就是犯了这个错误所以失败了的，切记！！！ 
		//printf("%d\n",first);
		//printf("%d\n",record->NUM[record->index]);
		save(first);
		printall(first);
		
		//record_method(record,first);//不注释的话，连带后退的过程也记录在内，注释后只记录其他真正的操作过程 
		
   } 
   //下一步
   void next(laststep* record,students *first)
   {
   	    if(record->i==0)
  	   {
  	   	 record->current_index=record->length-1;
  	   	 record->index=record->current_index;
  	   	 record->i=1;
		 }
		if(record->index>=record->current_index)
		{
			printf("到达前进的极限！\n");
			return;
		}
		record->index++;
		//first=record->NUM[record->index];
		record_to_first(record,first);
		save(first);
		printall(first);
		
	} 
 
//加载数据,其他的信息可以重复相同，但是学号不能重复！
//此算法只是初步的判断，如果用户一开始输入想输入的学号没有重复，但是实际上输入的与一开始将要输入的不一样，也可能输入成功！ 
students* jiazaishuju(laststep* record,students *first)
{
	printf("请输入你将要输入的学生号：");
	char num2[10];
	scanf("%s",num2);
	for(int i=0;i<first->length;i++)
	{
		int ptr;
		ptr=strcmp(num2,first->NUM[i]->num);
		if(ptr==0)
		{
			printf("你输入的学生号与学生表里的学号有重复情况,输入失败！\n");
			return NULL;
		}
	 } 
	first->NUM[first->length]=(student*)malloc(sizeof(student));
	printf("请输入学生的基本信息：\n");
	printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t爱好\n");
	scanf("%s%s%s%d%d%d%d%s",first->NUM[first->length]->num,first->NUM[first->length]->name,first->NUM[first->length]->sex,
	&(first->NUM[first->length]->age),&(first->NUM[first->length]->fenshu.Chinese),&(first->NUM[first->length]->fenshu.Math),&(first->NUM[first->length]->fenshu.English),
	first->NUM[first->length]->hobby);
    first->NUM[first->length]->fenshu.total=first->NUM[first->length]->fenshu.Chinese+first->NUM[first->length]->fenshu.Math+first->NUM[first->length]->fenshu.English;
	first->NUM[first->length]->fenshu.aver=first->NUM[first->length]->fenshu.total/3;

	
	first->length++; 
	save(first);
	record_method( record,first);
	record->i=0;
	record->current_index=record->length; 
	printf("第%d个学生的信息输入完毕！\n",first->length);
	return first;
 } 
 students* jiazaishuju2(laststep* record,students *first)
 {
 	int i=1;
 	while(i==1)
 	{
 		jiazaishuju(record,first);
 		printf("是否继续输入学生信息1：继续  0：不继续   :");
 		scanf("%d",&i); 
	 }
 	
 	return first;
 }
 //打印全部学生信息 
 void printall(students * first)
 {
    printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 	for(int i=0;i<first->length;i++)
 	{
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	  }
	 printf("全部信息打印完成！\n");
 }
 
 
 //按照学号删除学生信息
 void  delete_num(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的学号：");
	char num2[10];
	int n=0;
 	scanf("%s",num2) ;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		ptr=strcmp(first->NUM[i]->num,num2);
 		if(ptr==0)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
			 }
 	    n++;
 	    first->length--;
	   
		 }
 		 
	 }
	 if(n>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n>=2)
	 	{
	 		printf("并且学号%s有相同的%d个，已全部删除！\n",num2,n);
		 }
	 }
	 if(n==0)
	 {
	 	 printf("按照学号删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  //姓名删除中间步骤 
   int   delete_name1(students *first,char name2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		ptr=strcmp(first->NUM[i]->name,name2);
 		if(ptr==0)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 //	printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照姓名删除
  void  delete_name(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的姓名：");
	char name2[10];
	//int n=0;
	int n1=0; 
 	scanf("%s",name2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_name1(first,name2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且姓名%s有相同的%d个，已全部删除！\n",name2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照姓名删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
 
  
  //性别删除中间步骤 
   int   delete_sex1(students *first,char sex2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		ptr=strcmp(first->NUM[i]->sex,sex2);
 		if(ptr==0)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 	//printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照性别删除
  void  delete_sex(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的性别：");
	char sex2[10];
	//int n=0;
	int n1=0; 
 	scanf("%s",sex2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_sex1(first,sex2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且性别%s有相同的%d个，已全部删除！\n",sex2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照性别删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
   //年龄删除中间步骤 
   int   delete_age1(students *first,int &age,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->age==age)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 	//printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照年龄删除
  void  delete_age(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的年龄：");
	int age2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&age2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_age1(first,age2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且年龄%d有相同的%d个，已全部删除！\n",age2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照年龄删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	record->i=0;
	record->current_index=record->length; 
  } 
  

  //语文分数删除中间步骤 
   int   delete_Chinese1(students *first,int &Chinese,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Chinese==Chinese)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 //	printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照语文分数删除
  void  delete_Chinese(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的语文分数：");
	int Chinese2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&Chinese2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_Chinese1(first,Chinese2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且语文分数%d有相同的%d个，已全部删除！\n",Chinese2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照语文分数删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
   //数学分数删除中间步骤 
   int   delete_Math1(students *first,int &Math,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Math==Math)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 //	printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照数学分数删除
  void  delete_Math(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的数学分数：");
	int Math2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&Math2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_Math1(first,Math2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且数学分数%d有相同的%d个，已全部删除！\n",Math2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照数学分数删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  //英语分数删除中间步骤 
   int   delete_English1(students *first,int &English,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.English==English)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 	//printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照英语分数删除
  void  delete_English(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的英语分数：");
	int English2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&English2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_English1(first,English2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且英语分数%d有相同的%d个，已全部删除！\n",English2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照英语分数删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 

   //总分删除中间步骤 
   int   delete_total1(students *first,int &total,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.total==total)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 //	printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照总分删除
  void  delete_total(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的总分：");
	int total2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&total2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_total1(first,total2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且总分%d有相同的%d个，已全部删除！\n",total2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照总分删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
   //平均分删除中间步骤 
   int   delete_aver1(students *first,int &aver,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.aver==aver)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 	//printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照平均分删除
  void  delete_aver(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的平均分：");
	int aver2;
	//int n=0;
	int n1=0; 
 	scanf("%d",&aver2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_total1(first,aver2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且平均分%d有相同的%d个，已全部删除！\n",aver2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照平均分删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	record->i=0;
    record->current_index=record->length; 
  } 
   
  //爱好删除中间步骤 
   int   delete_hobby1(students *first,char hobby2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  {
  
  	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		ptr=strcmp(first->NUM[i]->hobby,hobby2);
 		if(ptr==0)
 		{
 			for(int j=i;j<first->length;j++)
 			{
 				first->NUM[j]=first->NUM[j+1];
 				
			 
			 }
		
 	    n++;
 	    first->length--;
		 }
		 
 		
 		 
	 }
	 if(n>=1)
	 {
	 	//printf("n=%d\n",n);
	    return n;
	  } 
	  return NULL;
	 
  }
  //按照爱好删除
  void  delete_hobby(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("学生人数为零，无学生信息，删除失败！\n");
 		return ;
	 }
	printf("请输入你要删除的学生的爱好：");
	char hobby2[10];
	//int n=0;
	int n1=0; 
 	scanf("%s",hobby2) ;
	 int m=first->length;
	 while(m>0)
	 {
	 	n1=delete_name1(first,hobby2,n1);
	 	m--;
	 }
	 if(n1>=1)
	 {
	 	printf("删除成功！\n");
	 	if(n1>=2)
	 	{
	 		printf("并且爱好%s有相同的%d个，已全部删除！\n",hobby2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("按照爱好删除失败！\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
 //按照学号查询
 void reserach_num(students * first)
 {
 	printf("请输入你要查找的学号：");
 	char num1[10];
 	scanf("%s",num1) ;
 	for(int i=0;i<first->length;i++)
 	{
 		
 	//	printf("%s\t%s\n",first->NUM[i]->num,num1);
 		int ptr;
 		ptr=strcmp(first->NUM[i]->num,num1);
 	//	printf("%d",ptr);
 		if(ptr==0)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    return;
		 }
 		
	 }
	 printf("按照学好查找失败！\n");
	 return;
  } 
  //按照姓名查询
  void reserach_name(students * first)
  {
  	printf("请输入你要查找的姓名：");
 	char name1[10];
 	scanf("%s",name1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->name,name1);
 		if(ptr==0)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s出现同名,并且同名的人数为%d个！\n",name1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照姓名查找失败！\n");
	    return;
	 }
	 
   } 
   //按照 性别查找
   void reserach_sex(students * first)
  {
  	printf("请输入你要查找的性别：");
 	char sex1[10];
 	scanf("%s",sex1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->sex,sex1);
 		if(ptr==0)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s出现同性别,并且同性别的人数为%d个！\n",sex1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照性别查找失败！\n");
	    return;
	 }
	 
   } 
   //按照年龄查找
   void reserach_age(students * first)
  {
  	printf("请输入你要查找的年龄：");
 	int age1;
 	scanf("%d",&age1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		
 		if(first->NUM[i]->age==age1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d出现同年龄,并且同年龄的人数为%d个！\n",age1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照年龄查找失败！\n");
	    return;
	 }
	 
   }  
   //按照语文分数查找 
   void reserach_Chinese(students * first)
  {
  	printf("请输入你要查找的语文分数：");
 	int Chinese1;
 	scanf("%d",&Chinese1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Chinese==Chinese1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d分出现同语文分数,并且同语文分数的人数为%d个！\n",Chinese1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照语文分数查找失败！\n");
	    return;
	 }
	 
   }  
   //按照数学分数查找 
   void reserach_Math(students * first)
  {
  	printf("请输入你要查找的数学分数：");
 	int Math1;
 	scanf("%d",&Math1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Math==Math1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d分出现同分数数学,并且同数学分数的人数为%d个！\n",Math1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照数学分数查找失败！\n");
	    return;
	 }
	 
   }  
   // 按照英语分数查找
   void reserach_English(students * first)
  {
  	printf("请输入你要查找的英语分数：");
 	int English1;
 	scanf("%d",&English1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.English==English1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d分出现同英语分数,并且同英语分数的人数为%d个！\n",English1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照英语分数查找失败！\n");
	    return;
	 }
	 
   }
   //按照总分数查找 
   void reserach_total(students * first)
  {
  	printf("请输入你要查找的总分数：");
 	int total1;
 	scanf("%d",&total1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.total==total1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d分出现同总分数,并且同总分数的人数为%d个！\n",total1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照总分数查找失败！\n");
	    return;
	 }
	 
   }
   
   // 按照平均分查找 
   void reserach_aver(students * first)
  {
  	printf("请输入你要查找的平均分：");
 	int aver1;
 	scanf("%d",&aver1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.aver==aver1)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d分出现同平均分,并且同平均分的人数为%d个！\n",aver1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照平均分查找失败！\n");
	    return;
	 }
	 
   }
   //按照爱好查找
   void  reserach_hobby(students * first)
   {
   	   
   	   printf("请输入你要查找的爱好：");
 	char hobby1[10];
 	scanf("%s",hobby1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->hobby,hobby1);
 		if(ptr==0)
 		{
 		printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s出现同爱好,并且同爱好的人数为%d个！\n",hobby1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("按照爱好查找失败！\n");
	    return;
	 }
   }
   //获取当前的学生人数
   void gettotalnum(students * first)
   {
   	  
   	  printf("但当前的学生人数为：%d\n",first->length);
	} 
	//判断当前人数是否为空
	void empty(students * first)
	{
		if(first->length==0)
		{
			printf("当前学生人数为空！\n");
		}
		else
		{
			printf("当前学生人数不为空！\n");
		}
	 } 
	 //按照学号排序
	 void sort_num(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			int ptr;
	 			ptr=strcmp(first->NUM[j]->num,first->NUM[j+1]->num);
	 			if(ptr>0)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照姓名排序 
	  void sort_name(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			int ptr;
	 			ptr=strcmp(first->NUM[j]->name,first->NUM[j+1]->name);
	 			if(ptr>0)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照性别排序 
	 void sort_sex(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			int ptr;
	 			ptr=strcmp(first->NUM[j]->sex,first->NUM[j+1]->sex);
	 			if(ptr>0)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照年龄排序 
	 void sort_age(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->age>first->NUM[j+1]->age)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 
	 //按照语文分数排序 
	 void sort_Chinese(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->fenshu.Chinese>first->NUM[j+1]->fenshu.Chinese)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照数学分数排序 
	 void sort_Math(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->fenshu.Math>first->NUM[j+1]->fenshu.Math)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照英语分数排序 
	 void sort_English(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->fenshu.English>first->NUM[j+1]->fenshu.English)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照总分排序 
	 void sort_total(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->fenshu.total>first->NUM[j+1]->fenshu.total)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照平均分排序 
	 void sort_aver(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			if(first->NUM[j]->fenshu.aver>first->NUM[j+1]->fenshu.aver)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //按照爱好排序 
	 
	  void sort_hobby(students *first) 
	 {
	 	student *tem=(student*)malloc(sizeof(student));
	 	for(int i=0;i<first->length;i++)
	 	{
	 		
	 		for(int j=0;j<first->length-i-1;j++)
	 		{
	 			int ptr;
	 			ptr=strcmp(first->NUM[j]->hobby,first->NUM[j+1]->hobby);
	 			if(ptr>0)
	 			{
	 				tem=first->NUM[j];
	 				first->NUM[j]=first->NUM[j+1];
					first->NUM[j+1]=tem;  
				 }
			 }
		 }
		 printf("排序完成！\n");
	 }
	 //通过学号修改信息
	 void  alter_num2(laststep* record,students *first)
	 {
	printf("请输入你要修改的学号：");
 	char num1[10];
 	char num2[10];
 	int  n;
 	scanf("%s",num1) ;
 	
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		ptr=strcmp(first->NUM[i]->num,num1);
 		if(ptr==0)
 		{
 		n=i;
 	    char num3[10]={0};
 	  	//  char *num3="待修改状态！";
 		//first->NUM[i]->num=;
 		strcpy(first->NUM[i]->num,num3);
 		//printf("%s\n",first->NUM[i]->num);
 		printf("学号修改为：\t"); 
 		scanf("%s",num2) ;
 		for(int j=0;j<first->length;j++)
 		{
 		int ptr;
 		ptr=strcmp(first->NUM[j]->num,num2);
 		    if(ptr==0)
 		    {
 			   printf("学生信息中有与你将要修改的学生号，修改失败，信息自动回滚！\n");
 			   //first->NUM[n]->num=&num1;
 			   strcpy(first->NUM[n]->num,num1);
 			   //printf("%s\n",first->NUM[n]->num);
 			   return ;
		    }
		 }
		//first->NUM[i]->num=num2; 
		strcpy(first->NUM[i]->num,num2);
		//printf("%s\n",first->NUM[i]->num);
		printf("\n");
	 	printf("姓名\t性别\t年龄\t语文\t数学\t英语\t爱好\n");
		scanf("%s%s%d%d%d%d%s",first->NUM[i]->name,first->NUM[i]->sex,
		&(first->NUM[i]->age),&(first->NUM[i]->fenshu.Chinese),&(first->NUM[i]->fenshu.Math),&(first->NUM[i]->fenshu.English),
		first->NUM[i]->hobby);
		first->NUM[i]->fenshu.total=first->NUM[i]->fenshu.Chinese+first->NUM[i]->fenshu.Math+first->NUM[i]->fenshu.English;
		first->NUM[i]->fenshu.aver=first->NUM[i]->fenshu.total/3;
	    
	    printf("按照学号修改信息成功，修改后成功后的个人信息：\n");
	    printf("学号\t姓名\t性别\t年龄\t语文\t数学\t英语\t总分\t平均分\t爱好\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    save(first);
	    record_method( record,first);
	    record->i=0;
		record->current_index=record->length; 
	    return;
		 }
		 
 		
	 }
	 printf("学生表没有你输入的学号，修改失败！\n");
	  } 
	 //学号修改信息循环步骤
	 students* alter_num(laststep* record,students *first)
 {
 	int i=1;
 	while(i==1)
 	{
 		alter_num2(record,first);
 		printf("是否继续修改学生信息1：继续  0：不继续   :");
 		scanf("%d",&i); 
	 }
 	
 	return first;
 } 
	 
	 //分数排序菜单
	 
	 void  sort_menu_scores(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照语文分数排序^_^\n");
   	    	printf("          ^_*2.按照数学分数排序^_*\n");
   	    	printf("          ^_&3.按照英语分数排序^_&\n");
   	    	printf("          ^_+4.按照总分排序^_+\n");
   	    	printf("          ^_$5.按照平均分排序^_$\n");	    
   	    	printf("          ^_<0.返回排序菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:sort_Chinese(first);printall(first);
			 	break;
			 	case 2:sort_Math(first);printall(first);
			 	break;
			 	case 3:sort_English(first);printall(first);
			 	break;
			 	case 4:sort_total(first);printall(first);
			 	break;
			 	case 5:sort_aver(first);printall(first);
			 	break;
			 	case 0:i=0;printf("已经返回排序菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  	    
	} 
	 //排序菜单
	 void sort_menu(students *first)
	 {
	 	
	 	  int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照学号排序^_^\n");
   	    	printf("          ^_*2.按照姓名排序^_*\n");
   	    	printf("          ^_&3.按照性别排序^_&\n");
   	    	printf("          ^_+4.按照年龄排序^_+\n");
   	    	printf("          ^_$5.按照分数排序^_$\n");
			printf("          ^_@6.按照爱好排序^_@\n"); 	    
   	    	printf("          ^_<0.返回主菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:sort_num(first);printall(first);
			 	break;
			 	case 2:sort_name(first);printall(first);
			 	break;
			 	case 3:sort_sex(first);printall(first);
			 	break;
			 	case 4:sort_age(first);printall(first);
			 	break;
			 	case 5:sort_menu_scores(first);
			 	break;
			 	case 6:sort_hobby(first);printall(first);
			 	break;
			 	case 0:i=0;printf("已经返回主菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  
	  } 
	 
	 
	 
	 
	 
	
	 //删除分数菜单
	 
	 void  delete_menu_scores(laststep*record,students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照语文分数删除^_^\n");
   	    	printf("          ^_*2.按照数学分数删除^_*\n");
   	    	printf("          ^_&3.按照英语分数删除^_&\n");
   	    	printf("          ^_+4.按照总分删除^_+\n");
   	    	printf("          ^_$5.按照平均分删除^_$\n");	    
   	    	printf("          ^_<0.返回删除菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:delete_Chinese(record,first);
			 	break;
			 	case 2:delete_Math(record,first);
			 	break;
			 	case 3:delete_English(record,first);
			 	break;
			 	case 4:delete_total(record,first);
			 	break;
			 	case 5:delete_aver(record,first);
			 	break;
			 	case 0:i=0;printf("已经返回删除菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  	    
	} 
	 //删除菜单
	 void delete_menu(laststep*record,students *first)
	 {
	 	
	 	  int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照学号删除^_^\n");
   	    	printf("          ^_*2.按照姓名删除^_*\n");
   	    	printf("          ^_&3.按照性别删除^_&\n");
   	    	printf("          ^_+4.按照年龄删除^_+\n");
   	    	printf("          ^_$5.按照分数删除^_$\n");
			printf("          ^_@6.按照爱好删除^_@\n"); 	    
   	    	printf("          ^_<0.返回主菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:delete_num(record,first);
			 	break;
			 	case 2:delete_name(record,first);
			 	break;
			 	case 3:delete_sex(record,first);
			 	break;
			 	case 4:delete_age(record,first);
			 	break;
			 	case 5:delete_menu_scores(record,first);
			 	break;
			 	case 6:delete_hobby(record,first);
			 	break;
			 	case 0:i=0;printf("已经返回主菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  
	  } 
	 
	 
	 //分数查找菜单 
	  void  reserach_menu_scores(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照语文分数查找^_^\n");
   	    	printf("          ^_*2.按照数学分数查找^_*\n");
   	    	printf("          ^_&3.按照英语分数查找^_&\n");
   	    	printf("          ^_+4.按照总分查找^_+\n");
   	    	printf("          ^_$5.按照平均分查找^_$\n");	    
   	    	printf("          ^_<0.返回查找菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:reserach_Chinese(first);
			 	break;
			 	case 2:reserach_Math(first);
			 	break;
			 	case 3:reserach_English(first);
			 	break;
			 	case 4:reserach_total(first);
			 	break;
			 	case 5:reserach_aver(first);
			 	break;
			 	case 0:i=0;printf("已经返回查找菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  	    
	}
	 //查找菜单 
	 void  reserach_menu(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.按照学号查找^_^\n");
   	    	printf("          ^_*2.按照姓名查找^_*\n");
   	    	printf("          ^_&3.按照性别查找^_&\n");
   	    	printf("          ^_+4.按照年龄查找^_+\n");
   	    	printf("          ^_$5.按照分数查找^_$\n");
   	    	printf("          ^_@6.按照爱好查找^_@\n"); 	    
   	    	printf("          ^_<0.返回主菜单！^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:reserach_num(first);
			 	break;
			 	case 2:reserach_name(first);
			 	break;
			 	case 3:reserach_sex(first);
			 	break;
			 	case 4:reserach_age(first);
			 	break;
			 	case 5:reserach_menu_scores(first);
			 	break;
			 	case 6:reserach_hobby(first);
			 	break;
			 	case 0:i=0;printf("已经返回主菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  	    
	}
	//读取文件里学生的人数
	int  logo_num(students *first)
	{
		FILE *fp2;
			if((fp2=fopen("total.txt","r"))==NULL)
		{
			printf("文件不存在，\n");
			exit(0);
		}
		int num=0;
		fscanf(fp2,"%d",&num);
		fclose(fp2);
		return num;
	 } 
		//初始化读取文件内容
		//特别注意格式和对应的下标，同时注意是否要在前面取地址符号 
	void  logo(students *first)
	{
		FILE *fp;
		if((fp=fopen("student.txt","r"))==NULL)
		{
			printf("文件不存在，\n");
			exit(0);
		}
		int num=logo_num(first);
		for(int i=0;i<num;i++)
		{
			first->NUM[first->length]=(student*)malloc(sizeof(student));
		
		    fscanf(fp,"%s%s%s%d%d%d%d%d%d%s",first->NUM[first->length]->num,first->NUM[first->length]->name,first->NUM[first->length]->sex,
	        &(first->NUM[first->length]->age),&(first->NUM[first->length]->fenshu.Chinese),&(first->NUM[first->length]->fenshu.Math),&(first->NUM[first->length]->fenshu.English),
         	&(first->NUM[first->length]->fenshu.total),&(first->NUM[first->length]->fenshu.aver),first->NUM[first->length]->hobby);
			
			fprintf(stdout,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[first->length]->num,first->NUM[first->length]->name,first->NUM[first->length]->sex,
		    first->NUM[first->length]->age,first->NUM[first->length]->fenshu.Chinese,first->NUM[first->length]->fenshu.Math,first->NUM[first->length]->fenshu.English,
			first->NUM[first->length]->fenshu.total,first->NUM[first->length]->fenshu.aver,first->NUM[first->length]->hobby);
		   
		    
		    first->length++;
		 } 
		 printf("读取完毕！\n");
		 fclose(fp);
		
		
	 } 
	 //保存学生的人数
	 void save_num(students *first)
	 {
	 	FILE *fp;
	 	if((fp=fopen("total.txt","w"))==NULL)
		{
			printf("文件不存在，\n");
			exit(0);
		}
	 	fprintf(fp,"%d",first->length);
	 	fclose(fp);
	  } 
	 //加载学生数据后，按照程序正常退出后，保存数据 
	 void save(students *first)
	 {
	 	
	    FILE *fp;
	    if((fp=fopen("student.txt","w"))==NULL)
		{
			printf("文件不存在，\n");
			exit(0);
		}
		printf("学生人数：%d\n",first->length);
		for(int i=0;i<first->length;i++)
		{
			//first->NUM[i]=(student*)malloc(sizeof(student));
		
//		    fscanf(first->NUM[i],"%s%s%s%d%d%d%d%d%d%s",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
//	        &(first->NUM[i]->age),&(first->NUM[i]->fenshu.Chinese),&(first->NUM[i]->fenshu.Math),&(first->NUM[i]->fenshu.English),
//         	&(first->NUM[i]->fenshu.total),&(first->NUM[i]->fenshu.aver),first->NUM[i]->hobby);
			
			fprintf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
		    first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
			first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
			//fprintf(fp,"\n");
		 } 
		 save_num(first);
		 printf("保存完毕！\n");
		 fclose(fp);
	 
	 }
	 
	 //返回菜单
	 void  laststep_menu(laststep* record,students *first)
	 {
	 	int i=1;
	 	while(i==1)
	 	{
	 		printf("******************二零一八********************\n");
	 		printf("          阿喵~---1.上一步-------喵~          \n");
	 		printf("          阿喵~---2.下一步-------喵~          \n"); 
	 		printf("          阿喵~---0.返回主页-----喵~          \n");
	 		printf("**************HAPPY**NEW**YEAR****************\n");
	 		printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:last(record,first);
			 	break;
			 	case 2:next(record,first); 
			 	break;
			 	case 0:i=0;printf("已经返回主菜单！\n");
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
		 }
	  } 
	 //主菜单 
   void  menu()
	{
		students * first=(students*)malloc(sizeof(students));
		laststep *record=(laststep*)malloc(sizeof(laststep));
     	ChuShiHua(first);
     	ChuShiHua_laststep(record);
		logo(first);
		record_method(record,first);
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************二零一八********************\n");
   	    	printf("          ^_^1.加载数据^_^\n");
   	    	printf("          ^_*2.格式输出^_*\n");
   	    	printf("          ^_&3.删除菜单^_&\n");
   	    	printf("          ^_+4.获取人数^_+\n");
   	    	printf("          ^_$5.判空操作^_$\n");
   	    	printf("          ^_@6.查找菜单^_@\n"); 
			printf("          ^_#7.排序菜单^_#\n"); 
			printf("          ^_!8.修改信息^_!\n");
			printf("          ^_-9.返回菜单^_-\n");  	    
   	    	printf("          ^_<0.退出程序^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("请输入你的操作选择："); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:jiazaishuju2(record,first);
			 	break;
			 	case 2:printall(first);
			 	break;
			 	case 3:delete_menu(record,first);
			 	break;
			 	case 4:gettotalnum(first);
			 	break;sort_menu(first); 
			 	case 5:empty(first);
			 	break;
			 	case 6:reserach_menu(first);
			 	break;
			 	case 7:sort_menu(first);
			 	break;
			 	case 8:alter_num(record,first);
			 	break;
			 	case 9:laststep_menu(record,first);
			 	break;
			 	case 0:i=0;printf("欢迎下次使用！\n"); 
			 	break;
			 	default:
			 	printf("输入错误，请重新选择！\n");
			 } 
					 }  	    
	}	
int main()
{
	 menu(); 

 } 

















 

