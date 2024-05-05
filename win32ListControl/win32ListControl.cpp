// win32ListControl.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <iostream>
#include <windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>
#include "framework.h"
#include "win32ListControl.h"

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

// 다이어로그 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    //HWND hDlg;
    static HWND hList;
    char* strMenu[] = { "항목 1", "항목 2", "항목 3", "항목 4"};
    LVCOLUMN lvColumn;

    switch (message)
    {
    case WM_INITDIALOG:
        hList = GetDlgItem(hDlg, IDC_LIST1);
        lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM ;
        lvColumn.fmt = LVCFMT_CENTER;
        for (int i = 0; i < 4; i++)
        {
            lvColumn.cx = strlen( strMenu[i] ) * 15 ;
            lvColumn.pszText = strMenu[i];
            ListView_InsertColumn(hList, i, &lvColumn);
        }
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
