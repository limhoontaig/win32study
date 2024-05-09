// fopen 등 사용을 위한 에러 방지 
#pragma warning(disable : 4996)

#include<stdio.h>

struct USER_INFO
{
	int index;
	char User_ID[30];
	char User_PW[20];
};

int main()
{
	FILE* fp;
	int i = 0;
	char name[100];
	char password[20];
	int age;
	double height;
	double ave_age = 0;
	int nFileSize;
	char buf[100];
	int len;
	int count = 0;
	int const num_Users = 10;
	int* pnum_Users = &num_Users;
	
	struct USER_INFO U_I[10];

	void NumberOfUsers(int* num_Users);

	NumberOfUsers(&num_Users);

	(struct USER_INFO*) puser = struct USER_INFO;
	= (struct USER_INFO*)malloc(sizeof(struct USER_INFO) * 10);// num_Users);
	printf("Number of Users : %d\n\n", num_Users);
	
	fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "r");
	if (fp == NULL) {
		fp = fopen("C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32ScoreControl\\secret.txt", "r");
		if (fp == NULL) 
			printf("파일열기 실패\n");
	}
	
	for (int i = 0; i < num_Users; i++)
	{
		fscanf(fp, "%d %s %s", user[i]->index, user[i]->User_ID, user[i]->User_PW);
		printf("No %d, 순번 %d, name %s, password %s\n", i, index, name, password );
	}
	fclose(fp);
	return 0;
}

void NumberOfUsers(int* a) {
	FILE* fp;
	char buf[100];
	int len;
	int count= 0;
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
		*a = ++count;
		buf[0] = NULL;
	}
	fclose(fp);
}


