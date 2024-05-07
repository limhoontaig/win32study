// win32ScoreControl.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <windows.h>
#include <iostream>
#include "framework.h"
#include "win32ScoreControl.h"

#define MAX_LOADSTRING 100

// 전역 변수:
struct LOGIN_INFO
{
    char name[100];
    char password[20];
};

LOGIN_INFO g_sLoginInfo;
HWND hWnd, g_MainWnd;
//CSTUDENT g_Student;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    DlgProc1(HWND, UINT, WPARAM, LPARAM); // 메인
LRESULT CALLBACK    DlgProc2(HWND, UINT, WPARAM, LPARAM); // 로그인 
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

// 로그인 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    FILE* fp;
    static LOGIN_INFO sLoginInfo;
    static HWND hIDWnd, hPassword;
    LOGIN_INFO sInputLoin;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        fopen_s(&fp, "secret.txt", "r");
        if (fp == 0)
        {
            MessageBox(hDlg, "File Open Error", "FILE OPEN", MB_YESNO);
        }
        fscanf_s(fp, "%s, %s", sLoginInfo.name, sizeof(sLoginInfo.name), 
            sLoginInfo.password, sizeof(sLoginInfo.password));
        fclose(fp);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            GetDlgItemText(hDlg, IDC_EDIT1, sInputLoin.name, 12);
            GetDlgItemText(hDlg, IDC_EDIT2, sInputLoin.password, 12);
            if (strcmp(sLoginInfo.name, sInputLoin.name) != 0)
            {
                MessageBox(0, "아이디가 맞지 않습니다.", "로그인 정보 확인", MB_OK);
                SetDlgItemText(hDlg, IDC_EDIT1, "");
                SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
                return (INT_PTR)TRUE;
            }
            if (strcmp(sLoginInfo.password, sInputLoin.password) != 0 && 
                sInputLoin.password != NULL)
            {
                MessageBox(0, "패스워드가 맞지 않습니다.", "로그인 정보 확인", MB_OK);
                SetDlgItemText(hDlg, IDC_EDIT2, "");
                SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
                return (INT_PTR)TRUE;
            }
            memcpy(&g_sLoginInfo, &sLoginInfo, sizeof(LOGIN_INFO));
            EndDialog(hDlg, 1);
            return(INT_PTR)TRUE;
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

// 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
