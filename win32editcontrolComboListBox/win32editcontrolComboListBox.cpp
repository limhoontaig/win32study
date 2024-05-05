// win32editcontrolComboListBox.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "resource.h"
#include "framework.h"
#include "win32editcontrolComboListBox.h"

#define MAX_LOADSTRING 100


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), NULL, DlgProc);
    return 0;
}




INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    char string[100];
    int nVal;
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetDlgItemText(hDlg, IDC_EDIT1, string, strlen(string));
            MessageBox(hDlg, string, "GetDlgItemText()", MB_YESNOCANCEL);
            return (INT_PTR)TRUE;
        case IDC_BUTTON2:
            nVal = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
            //std::cout << "GetDlgItemInt(): " << nVal << std::endl;
            sprintf_s(string, "GetDlgItemInt(): %d", nVal);
            MessageBox(hDlg, string, "GetDlgItemInt()", MB_YESNOCANCEL);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
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
