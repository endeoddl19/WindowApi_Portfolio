// WindowApi_Portfolio.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowApi_Portfolio.h"
#include "GameManager.h"

#define MAX_LOADSTRING 100
#define IDC_MAPTOOL_BTN 1000
#define IDC_SAVE_BTN 1001
#define IDC_LOAD_BTN 1002
#define IDC_END_BTN 1003
#define IDC_TOLEFTSP_BTN 1004
#define IDC_TORIGHTSP_BTN 1005
#define IDC_PLAY_BTN 1006

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

static RECT rectView;
ULONG_PTR g_GdiToken;
HWND    ChildWnd[3];
MapTool mt;
GameManager gm;
GameStatus gs;
OPENFILENAME OFN, SFN;

void GDI_Init();
void GDI_End();
void printGameStatus(HDC);

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    GameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    MapToolWndProc(HWND, UINT, WPARAM, LPARAM);
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

    wcex.lpfnWndProc = GameWndProc;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("Game Window Class");
    RegisterClassExW(&wcex);

    wcex.lpfnWndProc = MapToolWndProc;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _T("MapTool Window Class");
    RegisterClassExW(&wcex);

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


   /*HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, szWindowClass, szTitle, WS_POPUP,
       0, 0, GetSystemMetrics(SM_CXSCREEN)-1, GetSystemMetrics(SM_CYSCREEN)-1,
       nullptr, nullptr, hInstance, nullptr);*/
   RECT rt = { 0,0,1200,900 };
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
    HDC     hdc;
    HWND    hBtn[3];
    int w, h;

    static HWND hWndClient;
    CLIENTCREATESTRUCT  clientcreate;
    MDICREATESTRUCT     mdicreate;
    HWND hWndChild;

    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        w = rectView.right / 5;
        h = rectView.bottom / 7;
        hBtn[0] = CreateWindow(_T("button"), _T("플레이"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w, h * 5, w, h, hWnd,
            (HMENU)IDC_PLAY_BTN, hInst, NULL);
        hBtn[1] = CreateWindow(_T("button"), _T("맵 에디터"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 3, h * 5, w, h, hWnd,
            (HMENU)IDC_MAPTOOL_BTN, hInst, NULL);

        clientcreate.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
        clientcreate.idFirstChild = 100;
        hWndClient = CreateWindow(
            _T("MDCLIENT"), NULL,
            WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
            0, 0, 0, 0,
            hWnd, NULL, hInst,
            (LPSTR)&clientcreate);
        ShowWindow(hWndClient, SW_SHOW);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, &rectView, false);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDC_PLAY_BTN:
            {
                ChildWnd[0] = CreateWindow(
                    _T("Game Window Class"), NULL, WS_CHILD | WS_VISIBLE,
                    0, 0, rectView.right, rectView.bottom,
                    hWnd, NULL, hInst, NULL);
                return 0;
            }
            case IDC_MAPTOOL_BTN:
            {
                /*mdicreate.szClass = _T("MapTool Window Class");
                mdicreate.szTitle = _T("MapTool Window Title");
                mdicreate.hOwner = hInst;
                mdicreate.x = CW_USEDEFAULT;
                mdicreate.y = CW_USEDEFAULT;
                mdicreate.cx = CW_USEDEFAULT;
                mdicreate.cy = CW_USEDEFAULT;
                mdicreate.style = 0;
                mdicreate.lParam = 0;
                hWndChild = (HWND)SendMessage(hWndClient,
                    WM_MDICREATE, 0,
                    (LPARAM)(LPMDICREATESTRUCT)&mdicreate);
                return 0;*/
                ChildWnd[1] = CreateWindow(
                    _T("MapTool Window Class"), NULL, WS_CHILD | WS_VISIBLE,
                    0, 0, rectView.right, rectView.bottom,
                    hWnd, NULL, hInst, NULL);
                return 0;
            }
                break;
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
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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

LRESULT CALLBACK GameWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = GetDC(hWnd);

    int     w, h, x, y;
    int     cost;
    static int state = 0;
    static int hnum = -1;

    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        w = rectView.right / ROW;
        h = rectView.bottom / COL;
        GDI_Init();
        gm.SetGame(rectView);
        w = rectView.right / 12;
        h = rectView.bottom / 9;

        SetTimer(hWnd, 1, 32, NULL);
        SetTimer(hWnd, 2, 2000, NULL);
        SetTimer(hWnd, 3, 100, NULL);
        break;
    case WM_TIMER:
        if (state == 0)
        {
            switch (wParam)
            {
            case 1:
                gm.Update();
                break;
            case 2:
                gm.CreateEnemy();
                gs.wave--;
                break;
            }
        }
        else if (state == 1)
        {
            switch (wParam)
            {
            case 3:
                
                break;
            }
        }
        InvalidateRect(hWnd, &rectView, false);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        }

    }
    break;
    case WM_LBUTTONDOWN:
    {
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        if (state == 0)
        {
            if (x < rectView.right / 2)
                gm.setState(1);
            else
                gm.setState(2);
            hnum = (x / (rectView.right / 6));

            state = 1;
        }
        else if (state == 1 && gm.isBuyable(hnum))
        {
            gm.CreateHero({ x, y }, hnum);
            state = 0;
            gm.setState(0);
        }
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        gm.Play(hWnd, hdc);
        printGameStatus(hdc);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        GDI_End();
        gm.close();
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        KillTimer(hWnd, 3);
        ReleaseDC(hWnd, hdc);
        PostQuitMessage(0);
        break;
    }
    return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}


LRESULT CALLBACK MapToolWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hWnd);
    PAINTSTRUCT ps;
    Graphics* graphic = new Graphics(hdc);

    HWND hBtn[5];
    HBITMAP Btn[5];
    int     w, h;
    static int x, y;
    static int spn = 0;
    static POINT mpt, tpt;

    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        w = rectView.right / 20;
        h = rectView.bottom / 20;

        hBtn[0] = CreateWindow(_T("button"), _T("SAVE"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 11, h * 16, w * 2, h * 2, hWnd,
            (HMENU)IDC_SAVE_BTN, hInst, NULL);
        hBtn[1] = CreateWindow(_T("button"), _T("LOAD"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 14, h * 16, w * 2, h * 2, hWnd,
            (HMENU)IDC_LOAD_BTN, hInst, NULL);
        hBtn[2] = CreateWindow(_T("button"), _T("END"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 17, h * 16, w * 2, h * 2, hWnd,
            (HMENU)IDC_END_BTN, hInst, NULL);
        hBtn[3] = CreateWindow(_T("button"), _T("<<"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 13, h * 13, w, h * 2, hWnd,
            (HMENU)IDC_TOLEFTSP_BTN, hInst, NULL);
        hBtn[4] = CreateWindow(_T("button"), _T(">>"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            w * 16, h * 13, w, h * 2, hWnd,
            (HMENU)IDC_TORIGHTSP_BTN, hInst, NULL);
        GDI_Init();
        mt.SetMapTool(rectView);
        SetTimer(hWnd, 1, 32, NULL);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, &rectView, false);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDC_TOLEFTSP_BTN:
            if (spn > 0)
                spn--;
            mt.DrawSP(graphic,spn);
            break;
        case IDC_TORIGHTSP_BTN:
            if (spn < 2)
                spn++;
            mt.DrawSP(graphic, spn);
            break;
        case IDC_SAVE_BTN:
            mt.SaveMap(hWnd, OFN, SFN);
            break;
        case IDC_LOAD_BTN:
            mt.LoadMap(hWnd, OFN);
            break;
        case IDC_END_BTN:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }
    }
    break;
    case WM_LBUTTONDOWN:
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
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        mt.Draw(hWnd, hdc, spn);

        mpt = mt.curposition();
        tpt = mt.curtile();

        TCHAR strTest1[32];
        _stprintf_s(strTest1, _countof(strTest1), _T("%d, %d"), mpt.x,mpt.y);
        TextOut(hdc, 10, 10,
            strTest1, _tcslen(strTest1));
        TCHAR strTest2[32];
        _stprintf_s(strTest2, _countof(strTest2), _T("%d, %d"), tpt.x, tpt.y);
        TextOut(hdc, 10, 30,
            strTest2, _tcslen(strTest2));
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        GDI_End();
        delete graphic;
        KillTimer(hWnd, 1);
        ReleaseDC(hWnd, hdc);
        PostQuitMessage(0);
        break;
    }
    return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
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

void printGameStatus(HDC hdc)
{
    gs = gm.CurStatus();

    TCHAR strTest[32];
    _stprintf_s(strTest, _countof(strTest), _T("Stage : %d"), gs.stage);
    TextOut(hdc, 10, 10, strTest, _tcslen(strTest));
    _stprintf_s(strTest, _countof(strTest), _T("Coin : %d"), gs.coin);
    TextOut(hdc, 10, 30, strTest, _tcslen(strTest));
    _stprintf_s(strTest, _countof(strTest), _T("Life : %d"), gs.life);
    TextOut(hdc, 10, 50, strTest, _tcslen(strTest));
    _stprintf_s(strTest, _countof(strTest), _T("Wave : %d"), gs.wave);
    TextOut(hdc, rectView.right / 2, 10, strTest, _tcslen(strTest));
}