// win32ListBox.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <windows.h>
#include <Windowsx.h>
#include <iostream>
#include "framework.h"
#include "win32ListBox.h"

#define MAX_LOADSTRING 100

// 전역 변수:

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    static HWND hListBox;
    char string[100];
    static int nIndex = 1;
    const char* strMenu[3] = { "메뉴 1", "메뉴 2", "메뉴 3" };
    switch (message)
    {
    case WM_INITDIALOG:
        hListBox = GetDlgItem(hDlg, IDC_LIST1);
        for (int i = 0; i < 3; i++)
        {
            ListBox_AddString(hListBox, strMenu[i]);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            sprintf_s(string, "메뉴 %d", nIndex++);
            ListBox_AddString(hListBox, string);
            return (INT_PTR)TRUE;
        case IDC_BUTTON2:
            nIndex = ListBox_GetCurSel(hListBox);
            if (nIndex >= 0)
            {
                sprintf_s(string, "%s 를 선택", strMenu[nIndex]);
                MessageBox(hDlg, string, "ListBox Cursor Selected Notifier", MB_YESNO);
                return (INT_PTR)TRUE;
            }
            else
            {
                MessageBox(hDlg, "ListBox Not Selected!!", "ListBox Error Identifier", MB_YESNO);
                return (INT_PTR)TRUE;
            }
            return (INT_PTR)TRUE;
        
        }
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
