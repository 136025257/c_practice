#include <stdio.h>


//定义学生结构体
typedef struct{
    int id; //学号
    char name[20]; //姓名
    float score[3]; //0=语文、1=数学、2=英语
}student;


int main(void){
    /*student s = {2401001,"王明",{87,93,94}};
    printf("学生：%s,学号：%d,语文成绩：%.1f,数学成绩：%.1f,英语成绩：%.1f\n",
        s.name,s.id,s.score[0],s.score[1],s.score[2]);*/
    int i;
    printf("您要录入几位学生的信息：");
    scanf("%d",&i);
    student s[i];
    for(int a = 0; a < i; a++){
        printf("这是录入的第%d位同学\n",a+1);
        printf("姓名：");
        scanf("%s",s[a].name);
        printf("学号：");
        scanf("%d",&s[a].id);
        printf("语文成绩：");
        scanf("%f",&s[a].score[0]);
        printf("数学成绩：");
        scanf("%f",&s[a].score[1]);
        printf("英语成绩：");
        scanf("%f",&s[a].score[2]);
        if(a == i-1){printf("输入完成！\n");}
    }
    return 0;
}