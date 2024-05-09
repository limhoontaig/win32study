// c_fileInOut.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#pragma warning(disable : 4996)

#include<stdio.h>

int main()
{
	FILE* fp;
	int i;
	char name[100];
	char password[20];
	int age;
	double height;
	double ave_age = 0;
	int nFileSize;
	

	/*
	if ((fp = fopen("user_info.txt", "a")) == NULL) {
		printf("파일열기 실패\n");
	}
	
	
	for (i = 0; i < 2; i++) {
		printf("%d번째 유저정보를 입력 (나이, 이름, 키 순): ", i);
		scanf("%d %s %lf", &age, name, &height);

		fprintf(fp, "%d %s %lf\n", age, name, height);
	}
	fclose(fp);
	*/
	fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "r");
	if (fp  == NULL) {
		printf("파일열기 실패\n");
	}
	/*while (1) {
		char c = fgetc(fp);
		if (c == EOF)
			break;
		printf("%c\n", c);
	}
	*/

	for (i = 0; i < 5; i++) {
		fscanf(fp, "%s %s", name, password);
		printf("name %s, password %s\n", name, password );
		//ave_age += (double)age;
	}

	//printf("유저들의 평균나이 : %0.2lf\n", ave_age / 5);
	/*
	fseek(fp, 0, SEEK_END);
	nFileSize = ftell(fp);
	printf("file size of user_info.text : %d", nFileSize);
	*/
	fclose(fp);
	//}
	return 0;

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
