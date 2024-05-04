// win32Buttons.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <windows.h>
#include <stdio.h>
#include "framework.h"
#include "win32Buttons.h"

#define MAX_LOADSTRING 100

INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);
VOID    TestFunction(HWND hDlg);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    return 0;
}
    

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    HDC hdc;
    PAINTSTRUCT ps;
    static char string[100];
    int nRadioID[3] = { IDC_RADIO1, IDC_RADIO2, IDC_RADIO3 };
    int nCheckID[3] = { IDC_CHECK1, IDC_CHECK2, IDC_CHECK3 };
    static BOOL bCheckState[3] = { 0, };

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int i;
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON4:
            for (i = 0; i < 3; i++)
            {
                CheckDlgButton(hDlg, nCheckID[i], BST_UNCHECKED);
            }
            InvalidateRect(hDlg, 0, TRUE);
            return (INT_PTR)TRUE;
        case IDC_BUTTON3:
            for (i = 0; i < 3; i++)
            {
                if (IsDlgButtonChecked(hDlg, nCheckID[i] == TRUE))
                    bCheckState[i] = TRUE;
                else
                    bCheckState[i] = FALSE;
                InvalidateRect(hDlg, 0, TRUE);
            }
            return (INT_PTR)TRUE;
        case IDC_BUTTON1: 
            for (i = 0; i < 3; i++)
            {
                // 기존의 선택된 라디오는 원상복구 되지 않음
                if (IsDlgButtonChecked(hDlg, nRadioID[i] == BST_CHECKED))
                    CheckDlgButton(hDlg, nRadioID[i], BST_UNCHECKED);// 1);
                CheckDlgButton(hDlg, IDC_RADIO2, BST_CHECKED);
                /*
                if (IsDlgButtonChecked(hDlg, nRadioID[i] == BST_CHECKED))
                {
                    TestFunction(hDlg);
                    sprintf_s(string, "%d 번째 라디오 버튼이 크릭", i);
                    MessageBox(hDlg, string, "Checked", MB_YESNO);
                    return (INT_PTR)TRUE;
                }
                */
            }
            return (INT_PTR)TRUE;
        case IDC_BUTTON2: // 동작 안함
            for (i = 0; i < 3; i++)
            {
                // 그룹별 라디오 박스중에서 하나를 선택함
                CheckRadioButton(hDlg, IDC_RADIO1,IDC_RADIO3, nRadioID[i]);// 1);
                Sleep(1000);
            }
            return (INT_PTR)TRUE;
            /*
            for (int i = 0; i < 3; i++)
            {
                if (IsDlgButtonChecked(hDlg, nRadioID[i] == BST_CHECKED))
                {
                    TestFunction(hDlg);
                    sprintf_s(string, "%d 번째 라디오 버튼이 크릭", i);
                    MessageBox(hDlg, string, "Checked", MB_YESNO);
                    return (INT_PTR)TRUE;
                }
            }
            */
            break;
        case IDC_CHECK1:
            //TestFunction(hDlg);
            //MessageBox(hDlg, "CHECK Box 1 Selected", "CHECK Box 1", MB_YESNO);
            break;
        case IDC_CHECK2:
            //MessageBox(hDlg, "CHECK Box 3 Selected", "CHECK Box 2", MB_YESNO);
            break;
        case IDC_CHECK3:
            //MessageBox(hDlg, "CHECK Box 3 Selected", "CHECK Box 3", MB_YESNO);
            break;

        case IDC_RADIO1:
            //TestFunction(hDlg);
            //MessageBox(hDlg, "Radio Box 1 Selected", "Radio Box 1", MB_YESNO);
            break;
        case IDC_RADIO2:
            //MessageBox(hDlg, "Radio Box 3 Selected", "Radio Box 2", MB_YESNO);
            break;
        case IDC_RADIO3:
            //MessageBox(hDlg, "Radio Box 3 Selected", "Radio Box 3", MB_YESNO);
            break;            
        }
        switch (wParam)
        {

        
        case IDOK:
            break;
        case IDCANCEL:
            Sleep(300);
            
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case WM_CLOSE:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        
    case WM_PAINT:
        hdc = BeginPaint(hDlg, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        for (int i = 0; i < 3; i++)
        {
            if (bCheckState[i])
                sprintf_s(string, "% s", "ON");
            else
                sprintf_s(string, "% s", "OFF");
            TextOut(hdc, 300 + 85 * i, 205, string, strlen(string));
        }

        EndPaint(hDlg, &ps);
        return TRUE;
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

VOID    TestFunction(HWND hDlg)
{
    HDC hdc = GetDC(hDlg);
    //Rectangle(hdc, 5, 5, 10, 10);

    for (int i = 1; i < 20; i++)
    {
        Rectangle(hdc, i * 5 + 150, i * 5 + 150, i * 10 + 150, i * 10 + 150);
    }

    ReleaseDC(hDlg, hdc);
    //InvalidateRect(hWnd, NULL, FALSE);

}