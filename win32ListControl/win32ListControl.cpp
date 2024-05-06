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
VOID                ClearEditControl(HWND);

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
    LVITEM lvItem;
    static char string[100];
    static int nIndex = -1;

    switch (message)
    {
    case WM_INITDIALOG:
        hList = GetDlgItem(hDlg, IDC_LIST1);
        ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1: // ListView Insert Item

            // ListView 초기화 및 Index 생성
            lvItem.iItem = ListView_GetItemCount(hList);
            
            lvItem.iSubItem = 0;
            lvItem.mask = LVIF_TEXT;
            sprintf_s(string, "%d", lvItem.iItem);
            lvItem.pszText = string;
            ListView_InsertItem(hList, &lvItem);
            
            // ListView SubItem Input
            GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
            ListView_SetItemText(hList, lvItem.iItem, 1, string);
            GetDlgItemText(hDlg, IDC_EDIT2, string, 10);
            ListView_SetItemText(hList, lvItem.iItem, 2, string);
            GetDlgItemText(hDlg, IDC_EDIT3, string, 10);
            ListView_SetItemText(hList, lvItem.iItem, 3, string);
            
            // 데이터 입력용 EditControl 데이터 클리어
            ClearEditControl(hDlg);
            return (INT_PTR)TRUE;
        case IDC_BUTTON2: // Modified
            if (nIndex != -1)
            {
                // ListView SubItem Input
                GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
                ListView_SetItemText(hList, nIndex, 1, string);
                GetDlgItemText(hDlg, IDC_EDIT2, string, 10);
                ListView_SetItemText(hList, nIndex, 2, string);
                GetDlgItemText(hDlg, IDC_EDIT3, string, 10);
                ListView_SetItemText(hList, nIndex, 3, string);

                // 데이터 입력용 EditControl 데이터 클리어
                ClearEditControl(hDlg);
                return (INT_PTR)TRUE;
            }
            break;
        case IDC_BUTTON3: // Insert
            if (nIndex != -1)
            {
                lvItem.iItem = nIndex;
                lvItem.iSubItem = 0;
                lvItem.mask = LVIF_TEXT;
                sprintf_s(string, "%d", lvItem.iItem);
                lvItem.pszText = string;
                ListView_InsertItem(hList, &lvItem);

                // ListView SubItem Input
                GetDlgItemText(hDlg, IDC_EDIT1, string, 10);
                ListView_SetItemText(hList, nIndex, 1, string);
                GetDlgItemText(hDlg, IDC_EDIT2, string, 10);
                ListView_SetItemText(hList, nIndex, 2, string);
                GetDlgItemText(hDlg, IDC_EDIT3, string, 10);
                ListView_SetItemText(hList, nIndex, 3, string);

                // 데이터 입력용 EditControl 데이터 클리어
                ClearEditControl(hDlg);
                // 순번을 다시 설정함
                int nCount = ListView_GetItemCount(hList);
                for (int i = nIndex + 1; i < nCount; i++)
                {
                    sprintf_s(string, "%d", i);
                    ListView_SetItemText(hList, i, 0, string);
                }
                return (INT_PTR)TRUE;
            }
            break;
        case IDC_BUTTON4: // Delete Currently Selected Item
            if (nIndex != -1)
            {
                ListView_DeleteItem(hList, nIndex);
                int nCount = ListView_GetItemCount(hList);
                for (int i = nIndex; i < nCount; i++)
                {
                    sprintf_s(string, "%d", i);
                    ListView_SetItemText(hList, i, 0, string);
                }
                return (INT_PTR)TRUE;
            }
            break;
        case IDC_BUTTON5: // Delete All
            if (nIndex != -1)
            {
                int msgBoxID = MessageBox(
                    hDlg,
                    "모든 데이터를 삭제 하시겠습니까? \n삭제를 원할 경우 확인 버튼을 눌러주세요!!",
                    "삭제 확인",
                    MB_ICONWARNING | MB_YESNO);
                switch(msgBoxID)
                {
                case IDOK:
                    break;
                case IDNO:
                    ListView_DeleteAllItems(hList);
                    // 데이터 입력용 EditControl 데이터 클리어
                    ClearEditControl(hDlg);
                    MessageBox(hDlg, "IDOK", "삭제 확인", MB_ICONWARNING | MB_YESNO);
                    MessageBox(
                        hDlg,
                        "IDNO",
                        "삭제 확인",
                        MB_ICONWARNING | MB_YESNO);
                    break;
                }
                return (INT_PTR)TRUE;
            }
            else {
                MessageBox(hDlg, "Not Selected ListView. Try Again.", "Error Notifier", MB_OK);
                break;
            }
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
        case NM_CLICK:
            nIndex = ListView_GetNextItem(hList, -1, LVNI_SELECTED);
            
            ListView_GetItemText(hList, nIndex, 1, string, 10);
            SetDlgItemText(hDlg, IDC_EDIT1, string);
            ListView_GetItemText(hList, nIndex, 2, string, 10);
            SetDlgItemText(hDlg, IDC_EDIT2, string);
            ListView_GetItemText(hList, nIndex, 3, string, 10);
            SetDlgItemText(hDlg, IDC_EDIT3, string);
            return TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
// 데이터 입력후 입력 창 지우기
VOID ClearEditControl(HWND hDlg)
{
    SetDlgItemText(hDlg, IDC_EDIT1, NULL);
    SetDlgItemText(hDlg, IDC_EDIT2, NULL);
    SetDlgItemText(hDlg, IDC_EDIT3, NULL);
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
