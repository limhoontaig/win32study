// win32ScoreControl.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <windows.h>
#include "framework.h"
#include "win32ScoreControl.h"

#define MAX_LOADSTRING 100

// 전역 변수:
//LOGIN_INFO g_sLoginInfo;
HWND hWnd, g_MainWnd;
//CSTUDENT g_Student;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //HINSTANCE hInstance;
    if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProc) == NULL)
        return 0;
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
    return 0;
}

// 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
