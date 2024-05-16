

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
        case IDC_BUTTON1:
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
        EndDialog(hDlg, -1);
        return (INT_PTR)FALSE;
    }
    return (INT_PTR)FALSE;
}
