#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <string.h>
#define  maxsize 1000
#define  process 521

//���ַ����ṹ�� 
struct scores
{
	int Chinese;//���� 
	int Math;//��ѧ 
	int English;//Ӣ�� 
	int total;//�ܷ� 
	int aver;//ƽ���� 
};
//����ѧ���Ļ�����Ϣ�ṹ�� 
struct student
{
	char num[10];//ѧ�� 
	char name[12];//���� 
	char sex[8];//�Ա� 
	int age;//���� 
	struct scores fenshu;//���� 
	char hobby[20];//���� 
};

//�༶ѧ����������ṹ�� 
 
struct students
{
	struct student* NUM [maxsize];//���ѧ����Ϣ������ 
	int length;//��ǰ�İ༶ѧ�������� 
};
//���ز˵��ṹ��
struct  laststep 
{
	struct students* NUM [process];//��Ų������̵����� 
	int length;//��ǰ�Ĳ�������
	int i;//�ж��Ƿ�ִ�з��ز����ı�־
	int current_index;//ʼ�պ�length����ͬ����ֻ�е�ִ�з��ز���ʱ�����ٺ�length����ͬ����
	                  //��������֮ǰ�Ĳ�����Χ�ڷ��أ������ص�ǰ�ķ��ز��� 
	int index;//��ǰ������ִ�еķ��ز������±�λ�� 
 }; 
//��ʼ���༶��Ϣ
students* ChuShiHua(students *first)
{
	first->length=0;
	printf("�༶��Ϣ��ʼ���ɹ���\n");
	return first;
 }
 //��ʼ�����ؼ�¼��Ϣ
 laststep* ChuShiHua_laststep(laststep *record)
 {
 	record->index=0;
 	record->length=0;
 	printf("��ʼ�����ؼ�¼��Ϣ�ɹ���\n"); 
 	return record;
  } 
 /*�������� 
 
 */ 
void save(students *first);
void  record_method(laststep* record,students *first);
void printall(students * first); 
void  logo(students *first); 
 
 //��first�����ݸ��Ƶ���¼��
 void first_to_record(laststep* record,students *first)
 {
    record->NUM[record->length]=(students*)malloc(sizeof(students));
    record->NUM[record->length]->length=first->length;//������first��ǰ��������ͬ 
 	for(int i=0;i<first->length;i++)
 	{
 		record->NUM[record->length]->NUM[i]=(student*)malloc(sizeof(student));//�ǵ�Ҫ�����Ӧ��ѧ���ռ� 
 		strcpy(record->NUM[record->length]->NUM[i]->num,first->NUM[i]->num);//�ַ����鲻��ֱ���á�=����ֵ��Ҫͨ������strcpy��ֵ���мǣ����� 
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
 //����¼�е����ݷ��뵽first��ȡ
 void  record_to_first(laststep* record,students *first)
 {
 	first->length=record->NUM[record->index]->length;//������first��ǰ��������ͬ 
 	for(int i=0;i<first->length;i++)
 	{
 		first->NUM[i]=(student*)malloc(sizeof(student));//�ǵ�Ҫ�����Ӧ��ѧ���ռ� 
 		strcpy(first->NUM[i]->num,record->NUM[record->index]->NUM[i]->num);//�ַ����鲻��ֱ���á�=����ֵ��Ҫͨ������strcpy��ֵ���мǣ����� 
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
 
 //��¼�������裬�����ݸ��µĵط���Ҫʹ��һ�£������ݼ�¼����������ʹ�õ��ǣ�����һ����ͬ�Ľṹ�壬���Ƶ�ǰ״̬��
 //��Ϣ������������ݣ�ɾ�����ݣ��������ݣ��������ݶ�Ҫ��¼����
 /*�ڼ��볷�˹���ʱ���󲿷ֵķ���Ҫ����laststep*record�Ĳ�����ͬʱ�ڵ�����Щ�����ĵط���ҲҪ����������мǣ����Լ��ͷ����������
 ���˱ȽϾõ�ʱ�� 
 */
 void  record_method(laststep* record,students *first)
 {
 	first_to_record(record,first);
 	record->length++;
 	printf("������%d�����裡\n",record->length);
 	
  } 
  //��һ��
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
			printf("������˵ļ��ޣ�\n");
			return;
		}
		record->index--;
		//first=record->NUM[record->index];//���ܵ����Ľ�ָ�븳ֵ����Ϊ��ֵ��λ�ö���first��first�����ݱ��ˣ����Ƶ�����Ҳ��ͬ���䶯�����Է��ز���������ݶ���һ����
		record_to_first(record,first);
		//Ҫ�����������Ҫ�����ݸ��ƣ���������Ƿ��������������ʧ���˵ģ��мǣ����� 
		//printf("%d\n",first);
		//printf("%d\n",record->NUM[record->index]);
		save(first);
		printall(first);
		
		//record_method(record,first);//��ע�͵Ļ����������˵Ĺ���Ҳ��¼���ڣ�ע�ͺ�ֻ��¼���������Ĳ������� 
		
   } 
   //��һ��
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
			printf("����ǰ���ļ��ޣ�\n");
			return;
		}
		record->index++;
		//first=record->NUM[record->index];
		record_to_first(record,first);
		save(first);
		printall(first);
		
	} 
 
//��������,��������Ϣ�����ظ���ͬ������ѧ�Ų����ظ���
//���㷨ֻ�ǳ������жϣ�����û�һ��ʼ�����������ѧ��û���ظ�������ʵ�����������һ��ʼ��Ҫ����Ĳ�һ����Ҳ��������ɹ��� 
students* jiazaishuju(laststep* record,students *first)
{
	printf("�������㽫Ҫ�����ѧ���ţ�");
	char num2[10];
	scanf("%s",num2);
	for(int i=0;i<first->length;i++)
	{
		int ptr;
		ptr=strcmp(num2,first->NUM[i]->num);
		if(ptr==0)
		{
			printf("�������ѧ������ѧ�������ѧ�����ظ����,����ʧ�ܣ�\n");
			return NULL;
		}
	 } 
	first->NUM[first->length]=(student*)malloc(sizeof(student));
	printf("������ѧ���Ļ�����Ϣ��\n");
	printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t����\n");
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
	printf("��%d��ѧ������Ϣ������ϣ�\n",first->length);
	return first;
 } 
 students* jiazaishuju2(laststep* record,students *first)
 {
 	int i=1;
 	while(i==1)
 	{
 		jiazaishuju(record,first);
 		printf("�Ƿ��������ѧ����Ϣ1������  0��������   :");
 		scanf("%d",&i); 
	 }
 	
 	return first;
 }
 //��ӡȫ��ѧ����Ϣ 
 void printall(students * first)
 {
    printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 	for(int i=0;i<first->length;i++)
 	{
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	  }
	 printf("ȫ����Ϣ��ӡ��ɣ�\n");
 }
 
 
 //����ѧ��ɾ��ѧ����Ϣ
 void  delete_num(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ����ѧ�ţ�");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n>=2)
	 	{
	 		printf("����ѧ��%s����ͬ��%d������ȫ��ɾ����\n",num2,n);
		 }
	 }
	 if(n==0)
	 {
	 	 printf("����ѧ��ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  //����ɾ���м䲽�� 
   int   delete_name1(students *first,char name2[10],int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //��������ɾ��
  void  delete_name(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ����������");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("��������%s����ͬ��%d������ȫ��ɾ����\n",name2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("��������ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
 
  
  //�Ա�ɾ���м䲽�� 
   int   delete_sex1(students *first,char sex2[10],int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //�����Ա�ɾ��
  void  delete_sex(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ�����Ա�");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("�����Ա�%s����ͬ��%d������ȫ��ɾ����\n",sex2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("�����Ա�ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
   //����ɾ���м䲽�� 
   int   delete_age1(students *first,int &age,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //��������ɾ��
  void  delete_age(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ�������䣺");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("��������%d����ͬ��%d������ȫ��ɾ����\n",age2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("��������ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	record->i=0;
	record->current_index=record->length; 
  } 
  

  //���ķ���ɾ���м䲽�� 
   int   delete_Chinese1(students *first,int &Chinese,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //�������ķ���ɾ��
  void  delete_Chinese(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ�������ķ�����");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("�������ķ���%d����ͬ��%d������ȫ��ɾ����\n",Chinese2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("�������ķ���ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
   //��ѧ����ɾ���м䲽�� 
   int   delete_Math1(students *first,int &Math,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //������ѧ����ɾ��
  void  delete_Math(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ������ѧ������");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("������ѧ����%d����ͬ��%d������ȫ��ɾ����\n",Math2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("������ѧ����ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  //Ӣ�����ɾ���м䲽�� 
   int   delete_English1(students *first,int &English,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //����Ӣ�����ɾ��
  void  delete_English(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ����Ӣ�������");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("����Ӣ�����%d����ͬ��%d������ȫ��ɾ����\n",English2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("����Ӣ�����ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 

   //�ܷ�ɾ���м䲽�� 
   int   delete_total1(students *first,int &total,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //�����ܷ�ɾ��
  void  delete_total(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ�����ܷ֣�");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("�����ܷ�%d����ͬ��%d������ȫ��ɾ����\n",total2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("�����ܷ�ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
   //ƽ����ɾ���м䲽�� 
   int   delete_aver1(students *first,int &aver,int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //����ƽ����ɾ��
  void  delete_aver(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ����ƽ���֣�");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("����ƽ����%d����ͬ��%d������ȫ��ɾ����\n",aver2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("����ƽ����ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	record->i=0;
    record->current_index=record->length; 
  } 
   
  //����ɾ���м䲽�� 
   int   delete_hobby1(students *first,char hobby2[10],int &n)//��������ʱ�����ͺ��������͵��������͵ļǵ�ȡ��ַ���ţ����Լ�������Ϊû��ȡ��ַ���žͳԿ��ˣ������˽�������Сʱ�������� 
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
  //���հ���ɾ��
  void  delete_hobby(laststep* record,students * first)
 {
 	if(first->length==0)
 	{
 		printf("ѧ������Ϊ�㣬��ѧ����Ϣ��ɾ��ʧ�ܣ�\n");
 		return ;
	 }
	printf("��������Ҫɾ����ѧ���İ��ã�");
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
	 	printf("ɾ���ɹ���\n");
	 	if(n1>=2)
	 	{
	 		printf("���Ұ���%s����ͬ��%d������ȫ��ɾ����\n",hobby2,n1);
		 }
	 }
	 if(n1==0)
	 {
	 	 printf("���հ���ɾ��ʧ�ܣ�\n");
	     return;
	 }
	save(first);
	record_method( record,first);
	 record->i=0;
		record->current_index=record->length; 
  } 
  
  
 //����ѧ�Ų�ѯ
 void reserach_num(students * first)
 {
 	printf("��������Ҫ���ҵ�ѧ�ţ�");
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
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    return;
		 }
 		
	 }
	 printf("����ѧ�ò���ʧ�ܣ�\n");
	 return;
  } 
  //����������ѯ
  void reserach_name(students * first)
  {
  	printf("��������Ҫ���ҵ�������");
 	char name1[10];
 	scanf("%s",name1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->name,name1);
 		if(ptr==0)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s����ͬ��,����ͬ��������Ϊ%d����\n",name1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("������������ʧ�ܣ�\n");
	    return;
	 }
	 
   } 
   //���� �Ա����
   void reserach_sex(students * first)
  {
  	printf("��������Ҫ���ҵ��Ա�");
 	char sex1[10];
 	scanf("%s",sex1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->sex,sex1);
 		if(ptr==0)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s����ͬ�Ա�,����ͬ�Ա������Ϊ%d����\n",sex1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("�����Ա����ʧ�ܣ�\n");
	    return;
	 }
	 
   } 
   //�����������
   void reserach_age(students * first)
  {
  	printf("��������Ҫ���ҵ����䣺");
 	int age1;
 	scanf("%d",&age1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		
 		if(first->NUM[i]->age==age1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d����ͬ����,����ͬ���������Ϊ%d����\n",age1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("�����������ʧ�ܣ�\n");
	    return;
	 }
	 
   }  
   //�������ķ������� 
   void reserach_Chinese(students * first)
  {
  	printf("��������Ҫ���ҵ����ķ�����");
 	int Chinese1;
 	scanf("%d",&Chinese1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Chinese==Chinese1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d�ֳ���ͬ���ķ���,����ͬ���ķ���������Ϊ%d����\n",Chinese1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("�������ķ�������ʧ�ܣ�\n");
	    return;
	 }
	 
   }  
   //������ѧ�������� 
   void reserach_Math(students * first)
  {
  	printf("��������Ҫ���ҵ���ѧ������");
 	int Math1;
 	scanf("%d",&Math1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.Math==Math1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d�ֳ���ͬ������ѧ,����ͬ��ѧ����������Ϊ%d����\n",Math1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("������ѧ��������ʧ�ܣ�\n");
	    return;
	 }
	 
   }  
   // ����Ӣ���������
   void reserach_English(students * first)
  {
  	printf("��������Ҫ���ҵ�Ӣ�������");
 	int English1;
 	scanf("%d",&English1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.English==English1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d�ֳ���ͬӢ�����,����ͬӢ�����������Ϊ%d����\n",English1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("����Ӣ���������ʧ�ܣ�\n");
	    return;
	 }
	 
   }
   //�����ܷ������� 
   void reserach_total(students * first)
  {
  	printf("��������Ҫ���ҵ��ܷ�����");
 	int total1;
 	scanf("%d",&total1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.total==total1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d�ֳ���ͬ�ܷ���,����ͬ�ܷ���������Ϊ%d����\n",total1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("�����ܷ�������ʧ�ܣ�\n");
	    return;
	 }
	 
   }
   
   // ����ƽ���ֲ��� 
   void reserach_aver(students * first)
  {
  	printf("��������Ҫ���ҵ�ƽ���֣�");
 	int aver1;
 	scanf("%d",&aver1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		if(first->NUM[i]->fenshu.aver==aver1)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%d�ֳ���ͬƽ����,����ͬƽ���ֵ�����Ϊ%d����\n",aver1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("����ƽ���ֲ���ʧ�ܣ�\n");
	    return;
	 }
	 
   }
   //���հ��ò���
   void  reserach_hobby(students * first)
   {
   	   
   	   printf("��������Ҫ���ҵİ��ã�");
 	char hobby1[10];
 	scanf("%s",hobby1) ;
	 int n=0;
 	for(int i=0;i<first->length;i++)
 	{
 		int ptr;
 		
 		ptr=strcmp(first->NUM[i]->hobby,hobby1);
 		if(ptr==0)
 		{
 		printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
 		printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",first->NUM[i]->num,first->NUM[i]->name,first->NUM[i]->sex,
     	first->NUM[i]->age,first->NUM[i]->fenshu.Chinese,first->NUM[i]->fenshu.Math,first->NUM[i]->fenshu.English,
	    first->NUM[i]->fenshu.total,first->NUM[i]->fenshu.aver,first->NUM[i]->hobby);
	    n++;
	    //printf("%d\t",n); 
	    //printf("%d",i);
		 }
		 if(i+1>=first->length&&n>1)
	    {
	    	printf("%s����ͬ����,����ͬ���õ�����Ϊ%d����\n",hobby1,n);
	    	return;
		} 
		
 		
	 }
	 if(n==0)
	 {
	 	printf("���հ��ò���ʧ�ܣ�\n");
	    return;
	 }
   }
   //��ȡ��ǰ��ѧ������
   void gettotalnum(students * first)
   {
   	  
   	  printf("����ǰ��ѧ������Ϊ��%d\n",first->length);
	} 
	//�жϵ�ǰ�����Ƿ�Ϊ��
	void empty(students * first)
	{
		if(first->length==0)
		{
			printf("��ǰѧ������Ϊ�գ�\n");
		}
		else
		{
			printf("��ǰѧ��������Ϊ�գ�\n");
		}
	 } 
	 //����ѧ������
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
		 printf("������ɣ�\n");
	 }
	 //������������ 
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
		 printf("������ɣ�\n");
	 }
	 //�����Ա����� 
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
		 printf("������ɣ�\n");
	 }
	 //������������ 
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
		 printf("������ɣ�\n");
	 }
	 
	 //�������ķ������� 
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
		 printf("������ɣ�\n");
	 }
	 //������ѧ�������� 
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
		 printf("������ɣ�\n");
	 }
	 //����Ӣ��������� 
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
		 printf("������ɣ�\n");
	 }
	 //�����ܷ����� 
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
		 printf("������ɣ�\n");
	 }
	 //����ƽ�������� 
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
		 printf("������ɣ�\n");
	 }
	 //���հ������� 
	 
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
		 printf("������ɣ�\n");
	 }
	 //ͨ��ѧ���޸���Ϣ
	 void  alter_num2(laststep* record,students *first)
	 {
	printf("��������Ҫ�޸ĵ�ѧ�ţ�");
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
 	  	//  char *num3="���޸�״̬��";
 		//first->NUM[i]->num=;
 		strcpy(first->NUM[i]->num,num3);
 		//printf("%s\n",first->NUM[i]->num);
 		printf("ѧ���޸�Ϊ��\t"); 
 		scanf("%s",num2) ;
 		for(int j=0;j<first->length;j++)
 		{
 		int ptr;
 		ptr=strcmp(first->NUM[j]->num,num2);
 		    if(ptr==0)
 		    {
 			   printf("ѧ����Ϣ�������㽫Ҫ�޸ĵ�ѧ���ţ��޸�ʧ�ܣ���Ϣ�Զ��ع���\n");
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
	 	printf("����\t�Ա�\t����\t����\t��ѧ\tӢ��\t����\n");
		scanf("%s%s%d%d%d%d%s",first->NUM[i]->name,first->NUM[i]->sex,
		&(first->NUM[i]->age),&(first->NUM[i]->fenshu.Chinese),&(first->NUM[i]->fenshu.Math),&(first->NUM[i]->fenshu.English),
		first->NUM[i]->hobby);
		first->NUM[i]->fenshu.total=first->NUM[i]->fenshu.Chinese+first->NUM[i]->fenshu.Math+first->NUM[i]->fenshu.English;
		first->NUM[i]->fenshu.aver=first->NUM[i]->fenshu.total/3;
	    
	    printf("����ѧ���޸���Ϣ�ɹ����޸ĺ�ɹ���ĸ�����Ϣ��\n");
	    printf("ѧ��\t����\t�Ա�\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����\t����\n");
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
	 printf("ѧ����û���������ѧ�ţ��޸�ʧ�ܣ�\n");
	  } 
	 //ѧ���޸���Ϣѭ������
	 students* alter_num(laststep* record,students *first)
 {
 	int i=1;
 	while(i==1)
 	{
 		alter_num2(record,first);
 		printf("�Ƿ�����޸�ѧ����Ϣ1������  0��������   :");
 		scanf("%d",&i); 
	 }
 	
 	return first;
 } 
	 
	 //��������˵�
	 
	 void  sort_menu_scores(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.�������ķ�������^_^\n");
   	    	printf("          ^_*2.������ѧ��������^_*\n");
   	    	printf("          ^_&3.����Ӣ���������^_&\n");
   	    	printf("          ^_+4.�����ܷ�����^_+\n");
   	    	printf("          ^_$5.����ƽ��������^_$\n");	    
   	    	printf("          ^_<0.��������˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ���������˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  	    
	} 
	 //����˵�
	 void sort_menu(students *first)
	 {
	 	
	 	  int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.����ѧ������^_^\n");
   	    	printf("          ^_*2.������������^_*\n");
   	    	printf("          ^_&3.�����Ա�����^_&\n");
   	    	printf("          ^_+4.������������^_+\n");
   	    	printf("          ^_$5.���շ�������^_$\n");
			printf("          ^_@6.���հ�������^_@\n"); 	    
   	    	printf("          ^_<0.�������˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ��������˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  
	  } 
	 
	 
	 
	 
	 
	
	 //ɾ�������˵�
	 
	 void  delete_menu_scores(laststep*record,students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.�������ķ���ɾ��^_^\n");
   	    	printf("          ^_*2.������ѧ����ɾ��^_*\n");
   	    	printf("          ^_&3.����Ӣ�����ɾ��^_&\n");
   	    	printf("          ^_+4.�����ܷ�ɾ��^_+\n");
   	    	printf("          ^_$5.����ƽ����ɾ��^_$\n");	    
   	    	printf("          ^_<0.����ɾ���˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ�����ɾ���˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  	    
	} 
	 //ɾ���˵�
	 void delete_menu(laststep*record,students *first)
	 {
	 	
	 	  int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.����ѧ��ɾ��^_^\n");
   	    	printf("          ^_*2.��������ɾ��^_*\n");
   	    	printf("          ^_&3.�����Ա�ɾ��^_&\n");
   	    	printf("          ^_+4.��������ɾ��^_+\n");
   	    	printf("          ^_$5.���շ���ɾ��^_$\n");
			printf("          ^_@6.���հ���ɾ��^_@\n"); 	    
   	    	printf("          ^_<0.�������˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ��������˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  
	  } 
	 
	 
	 //�������Ҳ˵� 
	  void  reserach_menu_scores(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.�������ķ�������^_^\n");
   	    	printf("          ^_*2.������ѧ��������^_*\n");
   	    	printf("          ^_&3.����Ӣ���������^_&\n");
   	    	printf("          ^_+4.�����ֲܷ���^_+\n");
   	    	printf("          ^_$5.����ƽ���ֲ���^_$\n");	    
   	    	printf("          ^_<0.���ز��Ҳ˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ����ز��Ҳ˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  	    
	}
	 //���Ҳ˵� 
	 void  reserach_menu(students *first)
	{
		
   	    int i=1;
   	    while(i==1)
   	    {
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.����ѧ�Ų���^_^\n");
   	    	printf("          ^_*2.������������^_*\n");
   	    	printf("          ^_&3.�����Ա����^_&\n");
   	    	printf("          ^_+4.�����������^_+\n");
   	    	printf("          ^_$5.���շ�������^_$\n");
   	    	printf("          ^_@6.���հ��ò���^_@\n"); 	    
   	    	printf("          ^_<0.�������˵���^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("�Ѿ��������˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  	    
	}
	//��ȡ�ļ���ѧ��������
	int  logo_num(students *first)
	{
		FILE *fp2;
			if((fp2=fopen("total.txt","r"))==NULL)
		{
			printf("�ļ������ڣ�\n");
			exit(0);
		}
		int num=0;
		fscanf(fp2,"%d",&num);
		fclose(fp2);
		return num;
	 } 
		//��ʼ����ȡ�ļ�����
		//�ر�ע���ʽ�Ͷ�Ӧ���±꣬ͬʱע���Ƿ�Ҫ��ǰ��ȡ��ַ���� 
	void  logo(students *first)
	{
		FILE *fp;
		if((fp=fopen("student.txt","r"))==NULL)
		{
			printf("�ļ������ڣ�\n");
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
		 printf("��ȡ��ϣ�\n");
		 fclose(fp);
		
		
	 } 
	 //����ѧ��������
	 void save_num(students *first)
	 {
	 	FILE *fp;
	 	if((fp=fopen("total.txt","w"))==NULL)
		{
			printf("�ļ������ڣ�\n");
			exit(0);
		}
	 	fprintf(fp,"%d",first->length);
	 	fclose(fp);
	  } 
	 //����ѧ�����ݺ󣬰��ճ��������˳��󣬱������� 
	 void save(students *first)
	 {
	 	
	    FILE *fp;
	    if((fp=fopen("student.txt","w"))==NULL)
		{
			printf("�ļ������ڣ�\n");
			exit(0);
		}
		printf("ѧ��������%d\n",first->length);
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
		 printf("������ϣ�\n");
		 fclose(fp);
	 
	 }
	 
	 //���ز˵�
	 void  laststep_menu(laststep* record,students *first)
	 {
	 	int i=1;
	 	while(i==1)
	 	{
	 		printf("******************����һ��********************\n");
	 		printf("          ����~---1.��һ��-------��~          \n");
	 		printf("          ����~---2.��һ��-------��~          \n"); 
	 		printf("          ����~---0.������ҳ-----��~          \n");
	 		printf("**************HAPPY**NEW**YEAR****************\n");
	 		printf("��������Ĳ���ѡ��"); 
   	    	int select;
   	    	scanf("%d",&select);
			switch(select)
			{
			    case 1:last(record,first);
			 	break;
			 	case 2:next(record,first); 
			 	break;
			 	case 0:i=0;printf("�Ѿ��������˵���\n");
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
		 }
	  } 
	 //���˵� 
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
   	    	printf("******************����һ��********************\n");
   	    	printf("          ^_^1.��������^_^\n");
   	    	printf("          ^_*2.��ʽ���^_*\n");
   	    	printf("          ^_&3.ɾ���˵�^_&\n");
   	    	printf("          ^_+4.��ȡ����^_+\n");
   	    	printf("          ^_$5.�пղ���^_$\n");
   	    	printf("          ^_@6.���Ҳ˵�^_@\n"); 
			printf("          ^_#7.����˵�^_#\n"); 
			printf("          ^_!8.�޸���Ϣ^_!\n");
			printf("          ^_-9.���ز˵�^_-\n");  	    
   	    	printf("          ^_<0.�˳�����^_<\n");
   	    	printf("**************HAPPY**NEW**YEAR****************\n");
   	    	
   	    	printf("��������Ĳ���ѡ��"); 
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
			 	case 0:i=0;printf("��ӭ�´�ʹ�ã�\n"); 
			 	break;
			 	default:
			 	printf("�������������ѡ��\n");
			 } 
					 }  	    
	}	
int main()
{
	 menu(); 

 } 

















 

