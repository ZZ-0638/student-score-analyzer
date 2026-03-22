#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // 用于 rand()
#include <time.h>     // 用于 time()

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float score;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// 清空输入缓冲区（可选，这里用简单方式）
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 添加学生信息
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Database is full.\n");
        return;
    }
    printf("Enter student ID: ");
    scanf("%d", &students[studentCount].id);
    getchar();  // 吸收换行符

    printf("Enter student name: ");
    scanf("%s", students[studentCount].name);
    getchar();

    printf("Enter student score: ");
    scanf("%f", &students[studentCount].score);
    getchar();

    studentCount++;
}

// 打印所有学生信息
void printStudents() {
    if (studentCount == 0) {
        printf("No students.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }
}

// 删除学生信息
void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student deleted.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

// 更新学生信息
void updateStudent() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Enter new score: ");
            scanf("%f", &students[i].score);
            getchar();
            printf("Score updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

// 插入学生信息
void insertStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Database is full.\n");
        return;
    }
    int position;
    printf("Enter the position to insert (0-based index): ");
    scanf("%d", &position);
    getchar();

    if (position < 0 || position > studentCount) {
        printf("Invalid position.\n");
        return;
    }
    for (int i = studentCount; i > position; i--) {
        students[i] = students[i - 1];
    }
    printf("Enter student ID: ");
    scanf("%d", &students[position].id);
    getchar();
    printf("Enter student name: ");
    scanf("%s", students[position].name);
    getchar();
    printf("Enter student score: ");
    scanf("%f", &students[position].score);
    getchar();

    studentCount++;
}


// 生成随机成绩 (0-100)
float randomScore() {
    return (float)(rand() % 101);
}

// 批量生成随机学生数据
void generateRandomData() {
    int count;
    printf("How many students to generate? ");
    scanf("%d", &count);
    getchar();

    if (studentCount + count > MAX_STUDENTS) {
        printf("Only %d slots available. Will generate %d students.\n",
               MAX_STUDENTS - studentCount, MAX_STUDENTS - studentCount);
        count = MAX_STUDENTS - studentCount;
    }

    srand((unsigned)time(NULL));  // 随机种子

    for (int i = 0; i < count; i++) {
        students[studentCount].id = studentCount + 1;  // 学号从1开始递增
        sprintf(students[studentCount].name, "Student%d", studentCount + 1);
        students[studentCount].score = randomScore();
        studentCount++;
    }
    printf("Successfully generated %d students.\n", count);
}
// 生成成绩报告（数据分析核心）
void generateReport() {
    if (studentCount == 0) {
        printf("No data.\n");
        return;
    }

    float sum = 0, maxScore = -1, minScore = 101;
    char maxName[50] = "", minName[50] = "";
    int pass = 0, excellent = 0;
    int buckets[5] = {0};  // 0-59,60-69,70-79,80-89,90-100

    for (int i = 0; i < studentCount; i++) {
        float s = students[i].score;
        sum += s;
        if (s > maxScore) {
            maxScore = s;
            strcpy(maxName, students[i].name);
        }
        if (s < minScore) {
            minScore = s;
            strcpy(minName, students[i].name);
        }
        if (s >= 60) pass++;
        if (s >= 85) excellent++;

        // 分数段统计
        if (s < 60) buckets[0]++;
        else if (s < 70) buckets[1]++;
        else if (s < 80) buckets[2]++;
        else if (s < 90) buckets[3]++;
        else buckets[4]++;
    }

    printf("\n========== Performance Report ==========\n");
    printf("Total Students: %d\n", studentCount);
    printf("Average Score: %.2f\n", sum / studentCount);
    printf("Highest: %s (%.2f)\n", maxName, maxScore);
    printf("Lowest: %s (%.2f)\n", minName, minScore);
    printf("Pass Rate (>=60): %.1f%%\n", (float)pass / studentCount * 100);
    printf("Excellent Rate (>=85): %.1f%%\n", (float)excellent / studentCount * 100);
    printf("\nScore Distribution:\n");
    printf("  0-59: %d (%.1f%%)\n", buckets[0], (float)buckets[0] / studentCount * 100);
    printf(" 60-69: %d (%.1f%%)\n", buckets[1], (float)buckets[1] / studentCount * 100);
    printf(" 70-79: %d (%.1f%%)\n", buckets[2], (float)buckets[2] / studentCount * 100);
    printf(" 80-89: %d (%.1f%%)\n", buckets[3], (float)buckets[3] / studentCount * 100);
    printf("90-100: %d (%.1f%%)\n", buckets[4], (float)buckets[4] / studentCount * 100);
    printf("=========================================\n");
}

int main() {
    int choice;

    // 初始化随机种子（可选，避免每次生成数据时重新设置）
    srand((unsigned)time(NULL));

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Print Students\n");
        printf("3. Delete Student\n");
        printf("4. Update Student\n");
        printf("5. Insert Student\n");
        printf("6. Generate Report\n");
        printf("7. Generate Random Data\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: printStudents(); break;
            case 3: deleteStudent(); break;
            case 4: updateStudent(); break;
            case 5: insertStudent(); break;
            case 6: generateReport(); break;
            case 7: generateRandomData(); break;
            case 8: return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}
