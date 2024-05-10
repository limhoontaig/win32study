// c_struct.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#pragma warning (disable : 4996)
#include <stdio.h>
#define MAX_NAME_LEN 100
#define MAX_STUDENT 100

typedef struct student {
    int snum;
    char sname[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
} student;

int main(void) {
    student students[MAX_STUDENT];
    int num_of_student = 0;
    while (1) {
        int menu = 0;
        printf("=====메뉴=====\n");
        printf("1. 학생 입력\n");
        printf("2. 학생 리스트 출력\n");
        printf("3. 학생 번호 검색\n");
        printf("4. 학생 삭제\n");
        printf("5. 프로그램 종료\n");
        printf("메뉴 번호를 입력하세요 : ");
        scanf("%d", &menu);
        if (menu < 1 || menu > 5) {
            printf("잘못된 입력입니다.\n");
            continue;
        }
        if (menu == 5) {
            return 0;
        }
        else if (menu == 1) {
            printf("===유저 인포 입력===\n");
            printf("이용자 번호: ");
            scanf("%d", &students[num_of_student].snum);
            printf("이용자 아이디: ");
            scanf("%s", &students[num_of_student].sname);
            printf("이용자 비밀번호: ");
            scanf("%s", &students[num_of_student].password);
            num_of_student++;
        }
        else if (menu == 2) {
            printf("===학생 리스트 출력===\n");
            for (int i = 0; i < num_of_student; i++) {
                printf("이용자 번호 : %d 이용자 아이디 : %s 이용자 비밀번호 : %s\n", students[i].snum,
                    students[i].sname, students[i].password);
            }
        }
        else if (menu == 3) {
            int snum;
            int exists = 0;
            printf("===학생 번호 검색===\n");
            printf("학생 번호: ");
            scanf("%d", &snum);
            for (int i = 0; i < num_of_student; i++) {
                if (students[i].snum == snum) {
                    printf("이용자 번호 : %d 이용자 아이디 : %s 이용자 비밀번호 : %s\n", students[i].snum,
                        students[i].sname, students[i].password);
                    exists++;
                    break;
                }
            }
            if (exists == 0) {
                printf("학생번호 %d 이 존재하지 않습니다.", snum);
            }
        }
        else if (menu == 4) {
            int snum;
            int exists = 0;
            printf("===학생 삭제===\n");
            printf("학생 번호: ");
            scanf("%d", &snum);
            for (int i = 0; i < num_of_student; i++) {
                if (students[i].snum == snum) {
                    printf("학생 번호 : %d 이용자 아이디 : %s 이 삭제됩니다.\n",
                        students[i].snum, students[i].sname);
                    for (int j = i; j < num_of_student; j++) {
                        students[j] = students[j + 1];
                    }
                    num_of_student--;
                    exists++;
                    break;
                }
            }
            if (exists == 0) {
                printf("학생번호 %d 이 존재하지 않습니다.\n", snum);
            }
        }
    }
    return 0;
}