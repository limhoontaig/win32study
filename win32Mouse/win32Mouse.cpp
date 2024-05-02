// win32Mouse.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <stdio.h>
#include "framework.h"
#include "win32Mouse.h"

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
VOID                Test(HWND hWnd, int nXPos, int nYPos);

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
    LoadStringW(hInstance, IDC_WIN32MOUSE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32MOUSE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32MOUSE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32MOUSE);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    HDC hdc;
    PAINTSTRUCT ps;
    static int nXPos, nYPos;
    char string[100];
    int t = rand() % 30 + 5;
    switch (message)
    {
    case WM_MOUSEMOVE:
        nXPos = LOWORD(lParam);
        nYPos = HIWORD(lParam);
        Test(hWnd, nXPos, nYPos);
        Sleep(t);
        InvalidateRect(hWnd, 0, TRUE);

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            sprintf_s(string, "Mouse x Position: %d, y Position: %d", nXPos, nYPos);
            SetTextColor(hdc, RGB(255, 0, 0));
            TextOut(hdc, 50, 50, string, strlen(string));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

VOID Test(HWND hWnd, int nXPos, int nYPos)
{
    PAINTSTRUCT ps;
    // HDC hdc = GetDC(hWnd);
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
    HPEN hPen, hOldPen;
    HBRUSH hBrush, hOldBrush;
    int r, g, b;
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
    hBrush = CreateSolidBrush(RGB(r, g, b));
    hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
    SelectObject(hdc, hBrush);
    // MoveToEx(hdc, 50, 50, NULL);
    // LineTo(hdc, 350, 50);
    
    int x, x1, y, y1;
    int ex, ex1, ey, ey1;
    x = (rand() % nXPos);
    x1 = (rand() % nXPos);
    y = rand() % nYPos;
    y1 = rand() % nYPos;
    ex = (rand() % nXPos);
    ex1 = (rand() % nXPos);
    ey = rand() % nYPos;
    ey1 = rand() % nYPos;
    /*
    if (nXPos > 500)
    {
        x = (rand() % nXPos);
        x1 = (rand() % nXPos);
        y = rand() % nYPos;
        y1 = rand() % nYPos;
        ex = (rand() % nXPos);
        ex1 = (rand() % nXPos);
        ey = rand() % nYPos;
        ey1 = rand() % nYPos;
    }
    else
    {
        x = rand() % nXPos;
        x1 = rand() % nXPos;
        y = rand() % nYPos;
        y1 = rand() % nYPos;
        ex = rand() % nXPos;
        ex1 = rand() % nXPos;
        ey = rand() % nYPos;
        ey1 = rand() % nYPos;
    }
    */
    Rectangle(hdc, x, x1, y, y1);
    Ellipse(hdc, ex, ex1, ey, ey1);

    hOldPen = (HPEN)SelectObject(hdc, hPen);
    DeleteObject(hPen);
    DeleteObject(hBrush);
        
    EndPaint(hWnd, &ps);
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
