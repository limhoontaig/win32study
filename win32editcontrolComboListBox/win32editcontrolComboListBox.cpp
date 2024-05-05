// win32editcontrolComboListBox.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Windowsx.h>
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
    static HWND hComboBox;
    const static char* strMenu[] = {"메뉴 01", "메뉴 02" , "메뉴 03" };
    static int nIndex = 2;
    char string[100];
    static char strItem[100];
    int nVal;
    switch (message)
    {
    case WM_INITDIALOG:
        hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
        for (int i = 0; i < 3; i++)
            ComboBox_AddString(hComboBox, strMenu[i]);
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
        case IDC_BUTTON3:
            SetDlgItemText(hDlg, IDC_EDIT1, "SetDlgIetmText");
            return (INT_PTR)TRUE;
        case IDC_BUTTON4:
            SetDlgItemInt(hDlg, IDC_EDIT1, -100, TRUE);
            return (INT_PTR)TRUE;
        case IDC_BUTTON5:
            ComboBox_AddString(hComboBox, IDC_COMBO1, "Add_string", TRUE);
            return (INT_PTR)TRUE;
        case IDC_BUTTON6:
            if (nIndex >= 0)
                ComboBox_DeleteString(hComboBox, nIndex--);
            else
                MessageBox(hDlg, "삭제할 콤보 메뉴가 없습니다.", "콤보 박스 항목 삭제 오류", MB_OK);
            return (INT_PTR)TRUE;
        case IDC_BUTTON7:
            nIndex = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, TRUE);
            GetDlgItemText(hDlg, IDC_EDIT3, strItem, 99);
            ComboBox_InsertString(hComboBox, nIndex, strItem);
            nIndex++;
            return (INT_PTR)TRUE;
        case IDC_BUTTON8:
            SetDlgItemInt(hDlg, IDC_EDIT1, -100, TRUE);
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
