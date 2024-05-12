// win32ScoreControl.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#pragma warning(disable : 4996)
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CommCtrl.h>
#include "framework.h"
#include "win32ScoreControl.h"

#define MAX_USER 100
#define MAX_ID_LEN 50
#define MAX_PW_LEN 30
#define MAX_LOADSTRING 100

// login information for users
typedef struct
{
    int UserIndex;
    char UserID[MAX_ID_LEN];
    char UserPW[MAX_PW_LEN];
} USERINFO;

// user 100 명에 대한 구조체 배열 생성
USERINFO userInfo[MAX_USER], g_userInfo, inputUserInfo;

// Number of currently assigned users 
int numOfUsers = 0;
// 신규 이용자 정보 저장시 추가된 user 여부 확인 용 변수 
int oldNumOfUsers = 0;

// 저장된 user 정보 loading(Number of users and login ID/PW)
void userInfoLoad(void);
// 변경된 user information save
void userInfoSave(void);

// 전역 변수:
HWND hWnd, g_MainWnd;
HINSTANCE hInst;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    DlgProc1(HWND, UINT, WPARAM, LPARAM); // 메인
// login procedure
LRESULT CALLBACK    DlgProc2(HWND, UINT, WPARAM, LPARAM); // 로그인 
LRESULT CALLBACK    DlgProc3(HWND, UINT, WPARAM, LPARAM); // 관리자 
INT_PTR CALLBACK    DlgProc4(HWND, UINT, WPARAM, LPARAM); // User List Output
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //HINSTANCE hInstance;
    if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), 0, DlgProc2) == -1)
        return 0;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc1);
    return 0;
}


// 관리자 정보변경 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hDlg, IDC_EDIT1, g_userInfo.UserID);
        SetDlgItemText(hDlg, IDC_EDIT3, g_userInfo.UserPW);
        SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            char temp[MAX_PW_LEN];
            GetDlgItemText(hDlg, IDC_EDIT2, inputUserInfo.UserID, MAX_ID_LEN);
            GetDlgItemText(hDlg, IDC_EDIT4, inputUserInfo.UserPW, MAX_PW_LEN);
            GetDlgItemText(hDlg, IDC_EDIT5, temp, MAX_PW_LEN);
            if (strcmp(inputUserInfo.UserPW, temp) == 0)
            {
                if (inputUserInfo.UserID != "")
                {

                    if (inputUserInfo.UserPW != "")
                    {
                        GetDlgItemText(hDlg, IDC_EDIT2, userInfo[g_userInfo.UserIndex].UserID, MAX_ID_LEN);
                        GetDlgItemText(hDlg, IDC_EDIT3, userInfo[g_userInfo.UserIndex].UserID, MAX_ID_LEN);
                        EndDialog(hDlg, 0);
                        return (INT_PTR)TRUE;
                    }
                }
            }
            else {
                //MessageBox(0, "입력한 사용자 정보가 맞지 않습니다.", "로그인 정보 확인", MB_OK);
                SetDlgItemText(hDlg, IDC_EDIT2, "");
                SetDlgItemText(hDlg, IDC_EDIT4, "");
                SetDlgItemText(hDlg, IDC_EDIT5, "");
                SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
                return (INT_PTR)TRUE;
            }
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}

// 메인 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_32771:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hDlg, DlgProc3);
            break;
        case ID_32772:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hDlg, DlgProc4);
            break;
        }
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    }
    return (INT_PTR)FALSE;
}

// User information list Output 처리기입니다.
INT_PTR CALLBACK DlgProc4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    static HWND hList;
    char* strMenu[] = { "INdex", "User No", "User ID", "User Password" };
    LVCOLUMN lvColumn;
    LVITEM lvItem;
    static char string[100];
    static int nIndex = -1;
    switch (message)
    {
    case WM_INITDIALOG:
        hList = GetDlgItem(hDlg, IDC_LIST1);
        ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT |
            LVS_EX_GRIDLINES); // | LVM_EDITLABEL (Item에 checkBox 추가됨)
        lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvColumn.fmt = LVCFMT_CENTER;
        for (int i = 0; i < 4; i++)
        {
            lvColumn.cx = strlen(strMenu[i]) * 10;
            lvColumn.pszText = strMenu[i];
            ListView_InsertColumn(hList, i, &lvColumn);
        }
        //ClearEditControl(hDlg);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1: // Data Load from File
            for (int i = 0; i < numOfUsers; i++)
            {
                // ListView 초기화 및 Index 생성
                lvItem.iItem = ListView_GetItemCount(hList);

                lvItem.iSubItem = 0;
                lvItem.mask = LVIF_TEXT;
                sprintf_s(string, "%d", lvItem.iItem);
                lvItem.pszText = string;
                ListView_InsertItem(hList, &lvItem);

                sprintf_s(string, "%d", userInfo[i].UserIndex);
                ListView_SetItemText(hList, i, 1, string);
                strcpy(string, userInfo[i].UserID);
                ListView_SetItemText(hList, i, 2, string);
                strcpy(string, userInfo[i].UserPW);
                ListView_SetItemText(hList, i, 3, string);

                //ClearEditControl(hDlg);
            }
            return (INT_PTR)TRUE;

        case IDC_BUTTON2: // ListView Add User Item
            // ListView 초기화 및 Index 생성
            numOfUsers = lvItem.iItem = ListView_GetItemCount(hList);

            lvItem.iSubItem = 0;
            lvItem.mask = LVIF_TEXT;
            sprintf_s(string, "%d", lvItem.iItem);
            lvItem.pszText = string;
            ListView_InsertItem(hList, &lvItem);

            // ListView SubItem Input
            GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
            ListView_SetItemText(hList, lvItem.iItem, 1, string);
            userInfo[lvItem.iItem].UserIndex = atoi(string);
            GetDlgItemText(hDlg, IDC_EDIT2, string, MAX_ID_LEN);
            ListView_SetItemText(hList, lvItem.iItem, 2, string);
            strcpy(userInfo[lvItem.iItem].UserID, string);
            GetDlgItemText(hDlg, IDC_EDIT3, string, MAX_PW_LEN);
            ListView_SetItemText(hList, lvItem.iItem, 3, string);
            strcpy(userInfo[lvItem.iItem].UserPW, string);
            numOfUsers++;

            // 데이터 입력용 EditControl 데이터 클리어
            //ClearEditControl(hDlg);
            return (INT_PTR)TRUE;
        case IDC_BUTTON3: // Modified
            if (nIndex != -1)
            {
                // ListView SubItem Input
                GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
                ListView_SetItemText(hList, nIndex, 1, string);
                userInfo[nIndex].UserIndex = atoi(string);
                GetDlgItemText(hDlg, IDC_EDIT2, string, MAX_ID_LEN);
                ListView_SetItemText(hList, nIndex, 2, string);
                strcpy(userInfo[nIndex].UserID, string);
                GetDlgItemText(hDlg, IDC_EDIT3, string, MAX_PW_LEN);
                ListView_SetItemText(hList, nIndex, 3, string);
                strcpy(userInfo[nIndex].UserPW, string);

                // 데이터 입력용 EditControl 데이터 클리어
                //ClearEditControl(hDlg);
                return (INT_PTR)TRUE;
            }
            break;

        case IDC_BUTTON4: // Delete Currently Selected Item
            if (nIndex != -1)
            {
                ListView_DeleteItem(hList, nIndex);
                numOfUsers--; // 삭제 유저 수 반영
                int nCount = ListView_GetItemCount(hList);
                for (int i = nIndex; i < nCount; i++)
                {
                    sprintf_s(string, "%d", i);
                    ListView_SetItemText(hList, i, 0, string);
                    userInfo[i] = userInfo[i + 1];
                }
                return (INT_PTR)TRUE;
            }
            break;
        case IDC_BUTTON6: // Save User Information 
            userInfoSave();
            break;
        }
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    case WM_NOTIFY:
        switch (((LPNMHDR)lParam)->code)
        {
        case LVN_ITEMCHANGED: // 아직 안됨 (화면에서 수정하는 방법 연구 중)
            nIndex = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

            ListView_GetItemText(hList, nIndex, 1, string, 10);
            SetDlgItemText(hDlg, IDC_EDIT1, string);
            ListView_GetItemText(hList, nIndex, 2, string, MAX_ID_LEN);
            SetDlgItemText(hDlg, IDC_EDIT2, string);
            ListView_GetItemText(hList, nIndex, 3, string, MAX_PW_LEN);
            SetDlgItemText(hDlg, IDC_EDIT3, string);
            return TRUE;

        case NM_CLICK: // 마우스 크릭하면 선택항목 보여줌
            nIndex = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

            ListView_GetItemText(hList, nIndex, 1, string, 10);
            SetDlgItemText(hDlg, IDC_EDIT1, string);
            ListView_GetItemText(hList, nIndex, 2, string, MAX_ID_LEN);
            SetDlgItemText(hDlg, IDC_EDIT2, string);
            ListView_GetItemText(hList, nIndex, 3, string, MAX_PW_LEN);
            SetDlgItemText(hDlg, IDC_EDIT3, string);
            return TRUE;
        }
    }
    return (INT_PTR)FALSE;
}

// 로그인 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hIDWnd, hPassword;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        userInfoLoad();
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            GetDlgItemText(hDlg, IDC_EDIT1, inputUserInfo.UserID, MAX_ID_LEN);
            GetDlgItemText(hDlg, IDC_EDIT2, inputUserInfo.UserPW, MAX_PW_LEN);
            for (int i = 0; i < numOfUsers; i++)
            {
                if (strcmp(userInfo[i].UserID, inputUserInfo.UserID) == 0)
                {
                    if (strcmp(userInfo[i].UserPW, inputUserInfo.UserPW) == 0)
                    {
                        memcpy(&g_userInfo, &inputUserInfo, sizeof(USERINFO));
                        EndDialog(hDlg, 1);
                        return(INT_PTR)TRUE;
                    }
                }
            }
            MessageBox(0, "입력한 사용자 정보가 맞지 않습니다.", "로그인 정보 확인", MB_OK);
            SetDlgItemText(hDlg, IDC_EDIT1, "");
            SetDlgItemText(hDlg, IDC_EDIT2, "");
            SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
            return (INT_PTR)TRUE;

        case IDCANCEL:
            EndDialog(hDlg, -1);
            return(INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)FALSE;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

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
    // 구조체 초기화
    memset(&userInfo, 0, sizeof(userInfo));
    // 파일에서 구조체 할당
    for (int i = 0; i < numOfUsers; i++)
    {
        fscanf(fp, "%d %s %s", &userInfo[i].UserIndex, &userInfo[i].UserID, &userInfo[i].UserPW);
    }
    oldNumOfUsers = numOfUsers;
    fclose(fp);
}
void userInfoSave(void)
{
    FILE* fp;
    fp = fopen("E:\\win32Study\\win32ScoreControl\\secret.txt", "w");
    if (fp == NULL) {
        fp = fopen("C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32ScoreControl\\secret.txt", "w");
        if (fp == NULL)
            printf("파일열기 실패\n");
    }
    for (int i = 0; i < numOfUsers; i++)
    {
        fprintf(fp, "%d %s %s\n", userInfo[i].UserIndex, &userInfo[i].UserID, &userInfo[i].UserPW);
    }
    fclose(fp);
}