#include <stdio.h>
#include <stdlib.h>

const char *file_name = "stu_data.txt";

typedef struct Stu {
    char name[20];
    int age;
    int class;
    double height;
} Stu;

#define MAX_N 10000
Stu stu_arr[MAX_N + 5];
int stu_cnt = 0;

enum NO_TYPE {
    LIST = 1,
    ADD,
    MODIFY,
    DELETE,
    QUIT
};

int usage();
void read_from_file();
void write_to_file();
void list_stu();
void add_a_stu();
void modify_stu();
void delete_stu();

int main() {
    read_from_file();
    while (1) {
        int no = usage();
        switch (no) {
            case LIST: {
                list_stu();
            } break;
            case ADD: {
                add_a_stu();
            } break;
            case MODIFY: {
                modify_stu();
            } break;
            case DELETE: {
                delete_stu();
            } break;
            case QUIT: exit(0);
        }
    }
    return 0;
}

int usage() {
    int no;
    do {
        printf("%d:学生信息\n", LIST);
        printf("%d:添加学生信息\n", ADD);
        printf("%d:修改学生信息\n", MODIFY);
        printf("%d:删除学生信息\n", DELETE);
        printf("%d:退出\n", QUIT);
        printf("mysql > ");
        scanf("%d", &no);
    } while (no < 1 || no > 5);
    return no;
}

void read_from_file() {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) return;
    stu_cnt = 0;
    while (fscanf(fp, "%19s", stu_arr[stu_cnt].name) != EOF) {
        fscanf(fp, "%d%d%lf",
            &stu_arr[stu_cnt].age,
            &stu_arr[stu_cnt].class,
            &stu_arr[stu_cnt].height
        );
        stu_cnt++;
    }
    fclose(fp);
}

void write_to_file() {
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to save data!\n");
        return;
    }
    for (int i = 0; i < stu_cnt; i++) {
        fprintf(fp, "%s %d %d %.2lf\n",
            stu_arr[i].name,
            stu_arr[i].age,
            stu_arr[i].class,
            stu_arr[i].height
        );
    }
    fclose(fp);
}

void list_stu() {
    int len = printf("%4s|%10s|%4s|%6s|%7s",
        "id", "name", "age","class", "height"
    );
    printf("\n");
    for (int i = 0; i < len; i++) printf("=");
    printf("\n");
    for (int i = 0; i < stu_cnt; i++) {
        printf("%4d|%10.10s|%4d|%6d|%7.2f|\n", 
            i, stu_arr[i].name, stu_arr[i].age,
            stu_arr[i].class, stu_arr[i].height
        );
    }
}

void add_a_stu() {
    if (stu_cnt >= MAX_N) {
        printf("学生数量已达上限！\n");
        return;
    }
    Stu s;
    printf("添加学生（姓名 年龄 班级 身高）：\n");
    printf("mysql > ");
    scanf("%19s%d%d%lf", s.name, &s.age, &s.class, &s.height);
    stu_arr[stu_cnt++] = s;
    write_to_file();
    printf("添加成功！\n");
}

void modify_stu() {
    int id;
    printf("请输入要修改的学生ID：");
    scanf("%d", &id);
    if (id < 0 || id >= stu_cnt) {
        printf("无效ID！\n");
        return;
    }
    Stu s;
    printf("请输入新数据（姓名 年龄 班级 身高）：\n");
    printf("mysql > ");
    scanf("%19s%d%d%lf", s.name, &s.age, &s.class, &s.height);
    stu_arr[id] = s;
    write_to_file();
    printf("修改成功！\n");
}

void delete_stu() {
    int id;
    printf("请输入要删除的学生ID：");
    scanf("%d", &id);
    if (id < 0 || id >= stu_cnt) {
        printf("无效ID！\n");
        return;
    }
    for (int i = id; i < stu_cnt - 1; i++) {
        stu_arr[i] = stu_arr[i + 1];
    }
    stu_cnt--;
    write_to_file();
    printf("删除成功！\n");
}