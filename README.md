# StudentManagerSystem（学生管理系统）
## 一，项目简介
  #### 该项目是一个学生管理系统，主要使用C语言编写，在DEVC++上运行，源码中有两个文件：StudentManager.cpp和StudentManager.exe。
  #### 前者需要在DEVC++上运行，可以看到源码，运行时需要编译；后者是一个可执行文件，不依赖在DEVC++上运行，直接双击即可，但是看不到源码。
  #### 如何在DEVC++上编译执行请在浏览器上输入该地址：<https://blog.csdn.net/WeiMengXuan/article/details/78554447>。
  #### 该系统代码只有一个类，因此代码数量多达2000行，其实里面的代码很多是可以复用的，如果复用了代码量将减少到原来的五分之一左右。
  #### 读者可以自行将我的源码进行分解成多个类，也可以自己重构代码，将代码复用写的更通用，期间会遇到一些困难，但是成功了，对于读者的实力将有很大的提升。
## 二，项目运行部署
---
 - 1.如果需要查看源代码请自行下载DEVC++，然后直接将StudentManager.cpp导入即可，也可以直接双击StudentManager.cpp，它会自动在DEVC++中打开，   不过前提是你自己的电脑上已经安装了DEVC++的软件。
 - 2.如果不需要查看源代码，则可以直接双击StudentManager.exe可执行文件，直接运行。
---
## 三，项目详解
  
 - ###  项目结构
 
	![在这里插入图片描述](https://img-blog.csdnimg.cn/20191012124143682.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4MTcwNTI2,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191012124230355.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4MTcwNTI2,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20191012124254884.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4MTcwNTI2,size_16,color_FFFFFF,t_70)

 - ###  项目功能
	-  1.学生信息的基本的增，删，查，改。
	- 2.根据学生的学号，年龄，性别，爱好，各门成绩的排序展示。
	- 3.对数据的格式输出。
	- 4.对数据的永久保存，使用的是文件保存的形式，还未用到数据库。
	- 5.对学生人数的判空和人数的获取。
	- 6.记录用户操作的保存，可以进行回撤和前进。
	- 7.为了预防断电等情况的发生，使得用户操作的记录没有执行写入文件，每次执行了修改文件的操作时，都将会写文件保存起来，也就是实时写入文件。
 - ###  项目结构体讲解
	

```c
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
```

 - ###  项目文件读取与写入
	

```c
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
```
对文件操作不熟悉的话可以参考项目里的文件：c语言操作文件的说明
 - ###  项目方法详解
 	
 

```c
 	//通过学号修改信息
	 void  alter_num2(laststep* record,students *first)
	 //学号修改信息循环步骤
	 students* alter_num(laststep* record,students *first)
	 //初始化班级信息
students* ChuShiHua(students *first)
	//初始化返回记录信息
 laststep* ChuShiHua_laststep(laststep *record)
	//按照年龄删除
  void  delete_age(laststep* record,students * first)
	//年龄删除中间步骤 
   int   delete_age1(students *first,int &age,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！
	//按照平均分删除
  void  delete_aver(laststep* record,students * first)
	//平均分删除中间步骤 
   int   delete_aver1(students *first,int &aver,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
	//按照语文分数删除
  void  delete_Chinese(laststep* record,students * first)
	//语文分数删除中间步骤 
   int   delete_Chinese1(students *first,int &Chinese,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
   //按照英语分数删除
  void  delete_English(laststep* record,students * first)
	 
  //英语分数删除中间步骤 
   int   delete_English1(students *first,int &English,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  //按照爱好删除
  void  delete_hobby(laststep* record,students * first)
	//爱好删除中间步骤 
   int   delete_hobby1(students *first,char hobby2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
 //按照数学分数删除
  void  delete_Math(laststep* record,students * first)
//数学分数删除中间步骤 
   int   delete_Math1(students *first,int &Math,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  //删除菜单
	 void delete_menu(laststep*record,students *first)
//删除分数菜单
	 void  delete_menu_scores(laststep*record,students *first)
//按照姓名删除
  void  delete_name(laststep* record,students * first)
//姓名删除中间步骤 
   int   delete_name1(students *first,char name2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  //按照学号删除学生信息
 void  delete_num(laststep* record,students * first)
//按照性别删除
  void  delete_sex(laststep* record,students * first)
//性别删除中间步骤 
   int   delete_sex1(students *first,char sex2[10],int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
  //按照总分删除
  void  delete_total(laststep* record,students * first) 
 //总分删除中间步骤 
   int   delete_total1(students *first,int &total,int &n)//传参数的时候整型和类似整型的其他类型的记得取地址符号，你自己就是因为没有取地址符号就吃亏了，调试了将近两个小时！！！！ 
 //判断当前人数是否为空
	void empty(students * first)
//将first的内容复制到记录中
 void first_to_record(laststep* record,students *first)
//获取当前的学生人数
   void gettotalnum(students * first)
//加载数据,其他的信息可以重复相同，但是学号不能重复！
//此算法只是初步的判断，如果用户一开始输入想输入的学号没有重复，但是实际上输入的与一开始将要输入的不一样，也可能输入成功！ 
students* jiazaishuju(laststep* record,students *first)
//加载数据中间步骤 
 students* jiazaishuju2(laststep* record,students *first)
//上一步
  void last(laststep* record,students *first)
//返回菜单
	 void  laststep_menu(laststep* record,students *first)
//初始化读取文件内容
		//特别注意格式和对应的下标，同时注意是否要在前面取地址符号 
	void  logo(students *first)
//读取文件里学生的人数
	int  logo_num(students *first)
	//程序入口
int main()
//主菜单 
   void  menu()
//下一步
   void next(laststep* record,students *first)
//打印全部学生信息 
 void printall(students * first)
//记录操作步骤，有数据更新的地方都要使用一下，把数据记录下来，这里使用的是，定义一个相同的结构体，复制当前状态的
 //信息。比如加入数据，删除数据，更改数据，重排数据都要记录下来
 /*在加入撤退功能时，大部分的方法要加入laststep*record的参数，同时在调用这些方法的地方，也要加入参数，切记，你自己就犯了这个错误
 改了比较久的时间 
 */
 void  record_method(laststep* record,students *first)
//将记录中的内容放入到first中取
 void  record_to_first(laststep* record,students *first)
//按照年龄查找
   void reserach_age(students * first)
 // 按照平均分查找 
   void reserach_aver(students * first)
 //按照语文分数查找 
   void reserach_Chinese(students * first)
// 按照英语分数查找
   void reserach_English(students * first)
//按照爱好查找
   void  reserach_hobby(students * first)
//按照数学分数查找 
   void reserach_Math(students * first)
 //查找菜单 
	 void  reserach_menu(students *first)
//分数查找菜单 
	  void  reserach_menu_scores(students *first)
 //按照姓名查询
  void reserach_name(students * first)
//按照学号查询
 void reserach_num(students * first)
//按照 性别查找
   void reserach_sex(students * first)
//按照总分数查找 
   void reserach_total(students * first)
 //加载学生数据后，按照程序正常退出后，保存数据 
	 void save(students *first)
//保存学生的人数
	 void save_num(students *first)
//按照年龄排序 
	 void sort_age(students *first) 
//按照平均分排序 
	 void sort_aver(students *first) 
 //按照语文分数排序 
	 void sort_Chinese(students *first) 
//按照英语分数排序 
	 void sort_English(students *first) 
//按照爱好排序 
	  void sort_hobby(students *first) 
 //按照数学分数排序 
	 void sort_Math(students *first) 
//排序菜单
	 void sort_menu(students *first)
 //分数排序菜单
	 void  sort_menu_scores(students *first)
 //按照姓名排序 
	  void sort_name(students *first) 
//按照学号排序
	 void sort_num(students *first) 
//按照性别排序 
	 void sort_sex(students *first) 
//按照总分排序 
	 void sort_total(students *first) 

```

## 四，效果展示
## 五，技术囊括
## 六，问题详解
## 七，问题反馈
## 八，工作进程
