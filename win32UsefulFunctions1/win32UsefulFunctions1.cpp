// win32UsefulFunctions1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <iostream>
//#include <stdio.h>
#include "framework.h"
#include "win32UsefulFunctions1.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32USEFULFUNCTIONS1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32USEFULFUNCTIONS1));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32USEFULFUNCTIONS1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32USEFULFUNCTIONS1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rt = { 0,0,600,500 };
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   AdjustWindowRect(&rt, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, true);
   MoveWindow(hWnd, 0, 0, rt.right - rt.left, rt.bottom - rt.top, true);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT Crect;
    static RECT Wrect;
    char string[100];
    char GetWinRect[100];
    int bx, by;
    HDC hdc = GetDC(hWnd);
    static HDC hMemDC;
    HBITMAP hBitmap;
    static BITMAP Bitmap;
    static POINT ptXY0, ptXY1;
    switch (message)
    {
    case WM_CREATE:
        hMemDC = CreateCompatibleDC(hdc);
        hBitmap = (HBITMAP)LoadImage(NULL, "C:\\Users\\82109\\source\\repos\\limhoontaig\\win32study\\win32Bitmap\\훈련병 임채혁(0601).bmp",
            IMAGE_BITMAP, 0, 0,
            LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        SelectObject(hMemDC, hBitmap);
        if (hMemDC == NULL)
            MessageBox(hWnd, "Image Not Loaded", "File Open Error", MB_YESNO);
        DeleteObject(hBitmap);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_32771:
                MoveWindow(hWnd, 300,300, 450, 350, TRUE);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        ptXY1.x = ptXY0.x = LOWORD(lParam);
        ptXY1.y = ptXY0.y = HIWORD(lParam);
        GetClientRect(hWnd, &Crect);
        InvalidateRect(hWnd, 0, TRUE);
        break;
    case WM_MOUSEMOVE:
        if (wParam == MK_LBUTTON)
        {
            ptXY1.x = LOWORD(lParam);
            ptXY1.y = HIWORD(lParam);
            InvalidateRect(hWnd, 0, TRUE);
        }
        break;
    case WM_MOVE:
        GetWindowRect(hWnd, &Wrect);
        InvalidateRect(hWnd, 0, TRUE);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            HBITMAP hBitmap;
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            BitBlt(hdc, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
            SetROP2(hdc, R2_NOTXORPEN);
            Rectangle(hdc, ptXY0.x, ptXY0.y, ptXY1.x, ptXY1.y );

            /*hBitmap = CreateCompatibleBitmap(hdc, 200, 200);
            hMemDC = CreateCompatibleDC(hdc);
            SelectObject(hMemDC, hBitmap);
            DeleteObject(hBitmap);
            PatBlt(hMemDC, 50,50, 100,100, WHITENESS);
            Rectangle(hMemDC, 50,50,150,150);
            BitBlt(hdc, 100, 100, 300,300, hMemDC, 0,0, SRCCOPY);
            */
            //DeleteDC(hMemDC);
            
            sprintf_s(string, "GetClientRect x: %d, y: %d, x Left: %d y Bottom: %d", 
                Crect.left, Crect.top, Crect.right+1, Crect.bottom+1);
            TextOut(hdc, 20,30, string, strlen(string));
            sprintf_s(GetWinRect, "GetWindowRect x: %d, y: %d, x Left: %d y Bottom: %d",
                    Wrect.left, Wrect.top, Wrect.right, Wrect.bottom);
            TextOut(hdc, 20, 45, GetWinRect, strlen(GetWinRect));
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteDC(hMemDC);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
