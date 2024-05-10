// c_UserInfo.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#pragma warning (disable : 4996)
#include <stdio.h>

#define MAX_USER 100
#define MAX_ID_LEN 50
#define MAX_PW_LEN 30

typedef struct UserInfo
{
	int UserIndex;
	char UserID[MAX_ID_LEN];
	char UserPW[MAX_PW_LEN];
} UserInfo;
// 전역변수
UserInfo userInfo[MAX_USER];
int numOfUsers = 0;
int oldNumOfUsers = 0;

void userInfoLoad(void)
{
	FILE* fp;
	char buf[100];
	int len;
	numOfUsers = 0;
	// 총 유저수 구하기
	fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "r");
	if (fp == NULL) {
		fp = fopen("C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32ScoreControl\\secret.txt", "r");
		if (fp == NULL)
			printf("파일열기 실패\n");
	}
	while (1)
	{
		fgets(buf, 100, fp);
		len = strlen(buf);
		if (len == 0)
			break;
		++numOfUsers;
		buf[0] = NULL;
	}
	fclose(fp);

	fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "r");
	if (fp == NULL) {
		fp = fopen("C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32ScoreControl\\secret.txt", "r");
		if (fp == NULL)
			printf("파일열기 실패\n");
	}
	//printf("No 순번     User ID      User password\n");
	//printf("== ==== =============== ===============\n");
	for (int i = 0; i < numOfUsers; i++)
	{
		fscanf(fp, "%d %s %s", &userInfo[i].UserIndex, &userInfo[i].UserID, &userInfo[i].UserPW);
		//printf("%2d %4d %-15s %-15s\n", i,
			//userInfo[i].UserIndex, userInfo[i].UserID, userInfo[i].UserPW);
	}
	oldNumOfUsers = numOfUsers;
	fclose(fp);
}

int main()
{
	
	userInfoLoad();
	while (1) {
		int menu = 0;

		printf("==========메뉴=========\n");
		printf("1. Input Add New User\n");
		//printf("2. User Load from File\n");
		printf("2. Save User Data to File\n");
		printf("4. Delete User\n");
		printf("5. Play the User List on Screen\n");
		printf("6. Quit the Program\n\n");
		scanf("%d", &menu);
		if (menu < 1 || menu > 5)
		{
			printf("잘못된 입력입니다. 1 ~ 5 사이의 숫자를 입력하세요\n");
			continue;
		}
		if (menu == 1)
		{
			printf("=== 신규 이용자 정보 입력 ===\n");
			printf("이용자 번호: %d\n", numOfUsers + 1);
			userInfo[numOfUsers].UserIndex = numOfUsers + 1;
			printf("이용자 아이디: ");
			scanf("%s", &userInfo[numOfUsers].UserID);
			printf("이용자 비밀번호: ");
			scanf("%s", &userInfo[numOfUsers].UserPW);
			numOfUsers++;
		}
		else if(menu == 2)
		{
			FILE* fp;
			if (oldNumOfUsers < numOfUsers)
			{
				fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "w");
				if (fp == NULL) {
					fp = fopen("C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32ScoreControl\\secret.txt", "w");
					if (fp == NULL)
						printf("파일열기 실패\n");
				}
				for (int i = 0; i < numOfUsers; i++)
				{
					fprintf(fp, "%d %s %s\n",
						userInfo[i].UserIndex, userInfo[i].UserID, userInfo[i].UserPW);
				}
				fclose(fp);
			}
			else
			{ 
				printf("추가할 내용이 없습니다.\n\n");
				continue;
			}
			
		}
		else if (menu == 5)
		{
			printf("No 순번     User ID      User password\n");
			printf("== ==== =============== ===============\n");
			for (int i = 0; i < numOfUsers; i++)
			{
				printf("%2d %4d %-15s %-15s\n", i,
					userInfo[i].UserIndex, userInfo[i].UserID, userInfo[i].UserPW);
			}
		}
		else if (menu == 6)
			return 0;
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
