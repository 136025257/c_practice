#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_student 100

//定义学生结构体
typedef struct{
    int id;                          //学号
    char name[20];                   //姓名
    float score[3];                  //0=语文、1=数学、2=英语
}student;

int save_file(student *s,int count); //保存数据
int load_file(student *s);           //读取数据

int main(void)
{
    int choice;                      //定义选项
    student s[max_student];          //定义结构体数组，存储学生信息
    int count = 0;                   //初始化
    count = load_file(s);            //加载学生信息，并传递出总信息数
    while(1)
    {
        printf("===== 学生成绩管理 =====\n");
        printf("1. 录入学生\n");
        printf("2. 显示全部\n");
        printf("0. 退出\n");
        printf("请选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                while (count < max_student)
                {
                    printf("这是录入的第%d位同学\n",count + 1 );
                    printf("姓名：");
                    scanf("%19s",s[count].name);//此处name是指针本身的值——地址，故不用写取址符&
                    printf("学号：");
                    scanf("%d",&s[count].id);
                    printf("语文成绩：");
                    scanf("%f",&s[count].score[0]);
                    printf("数学成绩：");
                    scanf("%f",&s[count].score[1]);
                    printf("英语成绩：");
                    scanf("%f",&s[count].score[2]);
                    count += 1;
                    printf("继续录入吗？(y/n)：");
                    char c;
                    scanf(" %c", &c);//%c前置空格，跳过缓存区的残留 
                    if (c == 'n' || c == 'N')
                    {
                        break;
                    }

                }
                save_file(s , count);
                printf("输入完成！，共录入%d位。\n",count);
                break;
            }

            case 2:
            {
                if (count == 0)
                    {
                        printf("还没有数据。\n");
                        break;
                    }
                for(int i = 0 ;i < count; i++)
                    {
                        printf("第%d位同学：%s，学号：%d，语文成绩：%.1f，数学成绩：%.1f，英语成绩：%.1f\n",
                                i + 1,s[i].name,s[i].id,
                                s[i].score[0],s[i].score[1],s[i].score[2]);
                    }
                break;
            }

            case 0:
            {
                printf("\n成功退出\n");
                return 0;
            }

            default:
                // 上面case 1、0都没匹配上，就跑这里
                printf("输入选项不存在，请重新输入！\n");
                break;
        }
    }
    return 0;
}

//保存数据
int save_file(student *s,int count)
    {
        FILE *fp = fopen("Student.bin","wb");//"wb":写 + 二进制，会清空原有内容
        if (fp == NULL)                      //判空
        {
            perror("保存失败");               //perror 会顺带打印具体原因
            return -1;
        }
        //fwrite(地址(数据从哪开始),字符数(每个元素多大),写几个，文件指针)；
        //返回值：成功读写到的块数量
        fwrite(&count, sizeof(int), 1, fp); //<count>头，文件里有多少条学生信息
        fwrite(s,sizeof(student),count,fp); //存储学生信息
        fclose(fp);
        return 0;
        
    }

//读取数据,成功返回总数
int load_file(student *s)
    {
        FILE *fp = fopen("Student.bin","rb");
        if(fp == NULL)
        {
            return 0;
        }
        int count = 0;
        fread(&count,sizeof(int),1,fp);
        printf("文件里有 %d 条记录\n", count);         //会自动停在第 5 个字节
        if (count < 0) count = 0;                    //防错误
        if (count > max_student) count = max_student;//越界保护
        fread(s,sizeof(student),count,fp);           //继续读取学生信息
        fclose(fp);                                  //释放文件
        return count;
    }