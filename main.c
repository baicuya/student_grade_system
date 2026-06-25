#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 32

typedef struct {
    int id;
    char name[NAME_LEN];
    double chinese;
    double math;
    double english;
    double total;
    double average;
} Student;

static Student students[MAX_STUDENTS];
static int student_count = 0;

static void clear_input(void);
static int read_int(const char *prompt);
static double read_score(const char *prompt);
static void read_name(char *name, size_t size);
static void update_score(Student *student);
static int find_index_by_id(int id);
static void print_student_header(void);
static void print_student(const Student *student);
static void input_scores(void);
static void output_scores(void);
static void query_score(void);
static void statistics_scores(void);
static void insert_score(void);
static void delete_score(void);
static void modify_score(void);
static void sort_scores(void);
static void show_menu(void);

int main(void) {
    int choice;

    do {
        show_menu();
        choice = read_int("请选择功能: ");

        switch (choice) {
            case 1:
                input_scores();
                break;
            case 2:
                output_scores();
                break;
            case 3:
                query_score();
                break;
            case 4:
                statistics_scores();
                break;
            case 5:
                insert_score();
                break;
            case 6:
                delete_score();
                break;
            case 7:
                modify_score();
                break;
            case 8:
                sort_scores();
                break;
            case 0:
                printf("已退出系统。\n");
                break;
            default:
                printf("输入错误，请重新选择。\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

static void clear_input(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int read_int(const char *prompt) {
    int value;

    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clear_input();
            return value;
        }
        printf("输入无效，请输入整数。\n");
        clear_input();
    }
}

static double read_score(const char *prompt) {
    double value;

    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && value >= 0.0 && value <= 100.0) {
            clear_input();
            return value;
        }
        printf("输入无效，请输入 0 到 100 之间的成绩。\n");
        clear_input();
    }
}

static void read_name(char *name, size_t size) {
    while (1) {
        printf("姓名: ");
        if (fgets(name, (int)size, stdin) == NULL) {
            name[0] = '\0';
            return;
        }

        name[strcspn(name, "\n")] = '\0';
        if (strlen(name) > 0) {
            return;
        }

        printf("姓名不能为空。\n");
    }
}

static void update_score(Student *student) {
    student->total = student->chinese + student->math + student->english;
    student->average = student->total / 3.0;
}

static int find_index_by_id(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void print_student_header(void) {
    printf("%-10s %-12s %8s %8s %8s %8s %8s\n",
           "学号", "姓名", "语文", "数学", "英语", "总分", "平均分");
}

static void print_student(const Student *student) {
    printf("%-10d %-12s %8.2f %8.2f %8.2f %8.2f %8.2f\n",
           student->id,
           student->name,
           student->chinese,
           student->math,
           student->english,
           student->total,
           student->average);
}

static void input_scores(void) {
    int count;

    printf("\n== 成绩输入 ==\n");
    count = read_int("请输入要录入的学生人数: ");
    if (count < 0 || count > MAX_STUDENTS) {
        printf("人数应在 0 到 %d 之间。\n", MAX_STUDENTS);
        return;
    }

    student_count = 0;
    for (int i = 0; i < count; i++) {
        Student student;

        printf("\n第 %d 个学生:\n", i + 1);
        student.id = read_int("学号: ");
        if (find_index_by_id(student.id) != -1) {
            printf("该学号已存在，请重新录入当前学生。\n");
            i--;
            continue;
        }

        read_name(student.name, sizeof(student.name));
        student.chinese = read_score("语文成绩: ");
        student.math = read_score("数学成绩: ");
        student.english = read_score("英语成绩: ");
        update_score(&student);

        students[student_count++] = student;
    }

    printf("成绩录入完成，共 %d 条记录。\n", student_count);
}

static void output_scores(void) {
    printf("\n== 成绩输出 ==\n");
    if (student_count == 0) {
        printf("暂无学生成绩记录。\n");
        return;
    }

    print_student_header();
    for (int i = 0; i < student_count; i++) {
        print_student(&students[i]);
    }
}

static void query_score(void) {
    int id;
    int index;

    printf("\n== 成绩查询 ==\n");
    id = read_int("请输入要查询的学号: ");
    index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到学号为 %d 的学生。\n", id);
        return;
    }

    print_student_header();
    print_student(&students[index]);
}

static void statistics_scores(void) {
    double total_chinese = 0.0;
    double total_math = 0.0;
    double total_english = 0.0;
    int pass_count = 0;
    int excellent_count = 0;

    printf("\n== 成绩统计 ==\n");
    if (student_count == 0) {
        printf("暂无学生成绩记录。\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        total_chinese += students[i].chinese;
        total_math += students[i].math;
        total_english += students[i].english;
        if (students[i].average >= 60.0) {
            pass_count++;
        }
        if (students[i].average >= 90.0) {
            excellent_count++;
        }
    }

    printf("学生总人数: %d\n", student_count);
    printf("语文平均分: %.2f\n", total_chinese / student_count);
    printf("数学平均分: %.2f\n", total_math / student_count);
    printf("英语平均分: %.2f\n", total_english / student_count);
    printf("总平均分: %.2f\n",
           (total_chinese + total_math + total_english) / (student_count * 3.0));
    printf("平均分及格人数: %d\n", pass_count);
    printf("平均分优秀人数: %d\n", excellent_count);
    printf("及格率: %.2f%%\n", pass_count * 100.0 / student_count);
    printf("优秀率: %.2f%%\n", excellent_count * 100.0 / student_count);
}

static void insert_score(void) {
    Student student;

    printf("\n== 成绩插入 ==\n");
    if (student_count >= MAX_STUDENTS) {
        printf("记录已满，最多保存 %d 名学生。\n", MAX_STUDENTS);
        return;
    }

    student.id = read_int("学号: ");
    if (find_index_by_id(student.id) != -1) {
        printf("该学号已存在，不能重复插入。\n");
        return;
    }

    read_name(student.name, sizeof(student.name));
    student.chinese = read_score("语文成绩: ");
    student.math = read_score("数学成绩: ");
    student.english = read_score("英语成绩: ");
    update_score(&student);

    students[student_count++] = student;
    printf("插入成功。\n");
}

static void delete_score(void) {
    int id;
    int index;

    printf("\n== 成绩删除 ==\n");
    id = read_int("请输入要删除的学号: ");
    index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到学号为 %d 的学生。\n", id);
        return;
    }

    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("删除成功。\n");
}

static void modify_score(void) {
    int id;
    int index;

    printf("\n== 成绩修改 ==\n");
    id = read_int("请输入要修改的学号: ");
    index = find_index_by_id(id);
    if (index == -1) {
        printf("未找到学号为 %d 的学生。\n", id);
        return;
    }

    read_name(students[index].name, sizeof(students[index].name));
    students[index].chinese = read_score("语文成绩: ");
    students[index].math = read_score("数学成绩: ");
    students[index].english = read_score("英语成绩: ");
    update_score(&students[index]);

    printf("修改成功。\n");
}

static void sort_scores(void) {
    int choice;

    printf("\n== 成绩排序 ==\n");
    if (student_count == 0) {
        printf("暂无学生成绩记录。\n");
        return;
    }

    printf("1. 按总分降序\n");
    printf("2. 按平均分降序\n");
    printf("3. 按学号升序\n");
    choice = read_int("请选择排序方式: ");
    if (choice < 1 || choice > 3) {
        printf("排序方式无效。\n");
        return;
    }

    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - 1 - i; j++) {
            int need_swap = 0;

            if (choice == 1 && students[j].total < students[j + 1].total) {
                need_swap = 1;
            } else if (choice == 2 && students[j].average < students[j + 1].average) {
                need_swap = 1;
            } else if (choice == 3 && students[j].id > students[j + 1].id) {
                need_swap = 1;
            }

            if (need_swap) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("排序完成，当前成绩表如下:\n");
    output_scores();
}

static void show_menu(void) {
    printf("\n========== 学生成绩管理系统 ==========\n");
    printf("1. 成绩输入\n");
    printf("2. 成绩输出\n");
    printf("3. 成绩查询\n");
    printf("4. 成绩统计\n");
    printf("5. 成绩插入\n");
    printf("6. 成绩删除\n");
    printf("7. 成绩修改\n");
    printf("8. 成绩排序\n");
    printf("0. 退出系统\n");
    printf("=====================================\n");
}
