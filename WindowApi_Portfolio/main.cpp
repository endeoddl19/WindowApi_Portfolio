// WindowApi_Portfolio.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowApi_Portfolio.h"
#include "GameManager.h"

#define MAX_LOADSTRING 100
#define IDC_PLAY_BTN 999
#define IDC_MAPTOOL_BTN 1000
#define IDC_SAVE_BTN 1001
#define IDC_LOAD_BTN 1002
#define IDC_END_BTN 1003
#define IDC_TOLEFTSP_BTN 1004
#define IDC_TORIGHTSP_BTN 1005

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static RECT rectView;
ULONG_PTR g_GdiToken;
MapTool mt;
GameManager gm;
GameStatus gs;
OPENFILENAME OFN, SFN;
HWND    hBtn[3];
HWND MhBtn[5];
//HBITMAP Btn[5];

void GDI_Init();
void GDI_End();
void setBtns(HWND);

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
    LoadStringW(hInstance, IDC_WINDOWAPIPORTFOLIO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWAPIPORTFOLIO));

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPIPORTFOLIO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWAPIPORTFOLIO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


   /*HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, szWindowClass, szTitle, WS_POPUP,
       0, 0, GetSystemMetrics(SM_CXSCREEN)-1, GetSystemMetrics(SM_CYSCREEN)-1,
       nullptr, nullptr, hInstance, nullptr);*/
   RECT rt = { 0,0,1200,800 };
   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, NULL);

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       0, 0, rt.right, rt.bottom,
       nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
       return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = GetDC(hWnd);
    static HWND hWndClient;
    int     w, h, x, y;
    static int state = 2;
    // 0: 게임 플레이 / 1: 일시정지 / 2: 메인메뉴 / 3: 맵툴

    static int hnum = -1;

    static int spn = 0;

    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        setBtns(hWnd);
        GDI_Init();
        gm.SetGame(rectView);
        SetTimer(hWnd, 1, 32, NULL);
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            if (state == 0)
                gm.Update();
            break;
        case 2:
            if (state == 0)
                gm.CreateEnemy();
                break;
        }
        InvalidateRect(hWnd, &rectView, false);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDC_PLAY_BTN:
            {
                for (int i = 0; i < 2; i++)
                    ShowWindow(hBtn[i], SW_HIDE);
                state = 0;
                SetTimer(hWnd, 2, 4000, NULL);
                //gm.CreateEnemy();
                return 0;
            }
                break;
            case IDC_MAPTOOL_BTN:
            {
                mt.SetMapTool(rectView);
                state = 3;
                for (int i = 0; i < 2; i++)
                    ShowWindow(hBtn[i], SW_HIDE);
                for (int i = 0; i < 5; i++)
                    ShowWindow(MhBtn[i], SW_SHOW);
                return 0;
            }
                break;
            case IDC_TOLEFTSP_BTN:
                if (spn > 0)
                    spn--;
                mt.DrawSP(hdc, spn);
                break;
            case IDC_TORIGHTSP_BTN:
                if (spn < 2)
                    spn++;
                mt.DrawSP(hdc, spn);
                break;
            case IDC_SAVE_BTN:
                mt.SaveMap(hWnd, OFN, SFN);
                break;
            case IDC_LOAD_BTN:
                mt.LoadMap(hWnd, OFN);
                break;
            case IDC_END_BTN:
                for (int i = 0; i < 5; i++)
                    ShowWindow(MhBtn[i], SW_HIDE);
                for (int i = 0; i < 2; i++)
                    ShowWindow(hBtn[i], SW_SHOW);
                state = 2;
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
    {
        if (state == 1 || state == 0)
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            if (x > rectView.right*4/WCOL && y > rectView.bottom *8/ WCOL)
            {
                if (x < rectView.right * 7 / WCOL)
                    gm.setState(1);
                else
                    gm.setState(2);
                hnum = (x - (rectView.right * 4 / WCOL)) * WCOL / rectView.right;
                gm.setHnum(hnum);
                state = 1;
            }
            else if (state == 1 && gm.isBuyable(hnum) && y < rectView.bottom * 8 / WCOL
                && x < rectView.right * 19 / WCOL / 2 - 20)
            {
                gm.CreateHero({ x, y }, hnum);
                state = 0;
                gm.setState(0);
            }
            else if (state == 1 && x > rectView.right * 19 / WCOL / 2 - 20
                && y < rectView.bottom / WCOL / 2)
            {
                state = 0;
                gm.setState(0);
            }
            else if (state == 0 && x > rectView.right * 19 / WCOL / 2 - 20
                && y < rectView.bottom / WCOL / 2)
                state = 1;
        }
        else if (state == 3)
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            if (mt.posInMap({ x, y }))
                mt.SetTile({ x, y });
            else if (mt.posInSp({ x, y }))
                mt.SelectTile({ x,y }, spn);
            else
                break;
        }
    }
    break;
    case WM_PAINT:
        {
        hdc = BeginPaint(hWnd, &ps);

        if (state == 0 || state == 1)
            gm.Play(hdc);
        else if (state == 2)
            gm.DrawMain(hdc);
        else if (state == 3)
            mt.Draw(hWnd, hdc, spn);

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_DESTROY:
        GDI_End();
        gm.close();
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        ReleaseDC(hWnd, hdc);
        PostQuitMessage(0);
    }
    return DefFrameProc(hWnd, hWndClient, message, wParam, lParam);
}

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

void GDI_Init()
{
    GdiplusStartupInput gpsi;
    GdiplusStartup(&g_GdiToken, &gpsi, NULL);
}
void GDI_End()
{
    GdiplusShutdown(g_GdiToken);
}

void setBtns(HWND hWnd)
{
    int w, h;
    w = rectView.right / 5;
    h = rectView.bottom / WCOL;
    hBtn[0] = CreateWindow(_T("button"), _T("플레이"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w, h * COL, w, h, hWnd,
        (HMENU)IDC_PLAY_BTN, hInst, NULL);
    hBtn[1] = CreateWindow(_T("button"), _T("맵 에디터"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 3, h * COL, w, h, hWnd,
        (HMENU)IDC_MAPTOOL_BTN, hInst, NULL);

    w = rectView.right / 20;
    h = rectView.bottom / 20;
    MhBtn[0] = CreateWindow(_T("button"), _T("SAVE"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 11, h * 16, w * 2, h * 2, hWnd,
        (HMENU)IDC_SAVE_BTN, hInst, NULL);
    MhBtn[1] = CreateWindow(_T("button"), _T("LOAD"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 14, h * 16, w * 2, h * 2, hWnd,
        (HMENU)IDC_LOAD_BTN, hInst, NULL);
    MhBtn[2] = CreateWindow(_T("button"), _T("END"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 17, h * 16, w * 2, h * 2, hWnd,
        (HMENU)IDC_END_BTN, hInst, NULL);
    MhBtn[3] = CreateWindow(_T("button"), _T("<<"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 13, h * 13, w, h * 2, hWnd,
        (HMENU)IDC_TOLEFTSP_BTN, hInst, NULL);
    MhBtn[4] = CreateWindow(_T("button"), _T(">>"),
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        w * 16, h * 13, w, h * 2, hWnd,
        (HMENU)IDC_TORIGHTSP_BTN, hInst, NULL);

    for (int i = 0; i < 2; i++)
        ShowWindow(hBtn[i], SW_SHOW);
    for (int i = 0; i < 5; i++)
        ShowWindow(MhBtn[i], SW_HIDE);
}