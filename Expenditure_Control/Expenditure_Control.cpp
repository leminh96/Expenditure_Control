#include "stdafx.h"
#include "Expenditure_Control.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include "RibbonFramework.h"
#include "RibbonIDs.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;                       
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

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

	CoInitialize(NULL);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXPENDITURE_CONTROL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXPENDITURE_CONTROL));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	CoUninitialize();
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;//CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXPENDITURE_CONTROL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EXPENDITURE_CONTROL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 250, 30, 720, 700, nullptr, nullptr, hInstance, nullptr);

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
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	InitializeFramework(hWnd);
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	HFONT mFont = CreateFont(-16, 0, 0, 0, FW_BOLD, 0,
		0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT nFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0,
		0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	RECT main;
	GetWindowRect(hWnd, &main);
	
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 10, 15, 680, 150, hWnd, NULL, hInst, NULL);
	hwnd = CreateWindowEx(0, L"STATIC", L"Thêm một loại chi tiêu", WS_CHILD | WS_VISIBLE | SS_LEFT, 35, 10, 110, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	
	hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu:", WS_CHILD | WS_VISIBLE | SS_LEFT, 30, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung:", WS_CHILD | WS_VISIBLE | SS_LEFT, 210, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền:", WS_CHILD | WS_VISIBLE | SS_LEFT, 390, 40, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 580, 50, 100, 60, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_combobox = CreateWindowEx(0, WC_COMBOBOX, TEXT(""), CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		20, 70, 120, 40, hWnd, NULL, hInst,	NULL);
	SendMessage(hwnd_combobox, WM_SETFONT, WPARAM(hFont), TRUE);
	Add_String_To_Combobox(hwnd_combobox);
	hwnd_content = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 210, 70, 120, 30, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_content, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_money = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 70, 120, 30, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_money, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 10, 200, 680, 200, hWnd, NULL, hInst, NULL);
	hwnd = CreateWindowEx(0, L"STATIC", L"Danh sách chi tiêu", WS_CHILD | WS_VISIBLE | SS_LEFT, 35, 195, 90, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_listview = CreateWindowEx(0, WC_LISTVIEWW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT, 30, 220, 640, 160, hWnd, NULL, NULL, NULL);
	SendMessage(hwnd_listview, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 10, 430, 680, 180, hWnd, NULL, hInst, NULL);
	hwnd = CreateWindowEx(0, L"STATIC", L"Thông tin thống kê", WS_CHILD | WS_VISIBLE | SS_LEFT, 35, 425, 90, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Tổng cộng:", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 570, 120, 30, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Biểu đồ phân bố", WS_CHILD | WS_VISIBLE | SS_LEFT, 150, 465, 200, 50, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(nFont), TRUE);
	hwnd_total = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 570, 100, 30, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_total, WM_SETFONT, WPARAM(mFont), TRUE);
	hwnd_eating = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 450, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_eating, WM_SETFONT, WPARAM(hFont), TRUE);
	SetTextColor(HDC(hwnd_eating), RGB(255, 0, 0));
	hwnd_moving = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 470, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_moving, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_accommodation = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 490, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_accommodation, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_vehicle = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 510, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_vehicle, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_essential = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 530, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_essential, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd_service = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 550, 170, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd_service, WM_SETFONT, WPARAM(hFont), TRUE);

	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;

	lvCol.cx = 150;
	lvCol.pszText = L"Loại chi tiêu";
	ListView_InsertColumn(hwnd_listview, 0, &lvCol);

	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 300;
	lvCol.pszText = L"Nội dung";
	ListView_InsertColumn(hwnd_listview, 1, &lvCol);

	lvCol.cx = 170;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.pszText = L"Số tiền";
	ListView_InsertColumn(hwnd_listview, 2, &lvCol);

	Read_File();
	Percent_Money();
	Create_Color();
	
	return true;
}

void Read_File()
{
	WCHAR buffer[BUFFERSIZE];
	WCHAR curPath[BUFFERSIZE];
	WCHAR configPath[BUFFERSIZE];
	WCHAR number_buffer[10];
	WCHAR type_buff[20];
	WCHAR content_buff[50];
	WCHAR money_buff[20];
	WCHAR temp[5];
	GetCurrentDirectory(BUFFERSIZE, curPath);
	wsprintf(configPath, L"%s\\data.ini", curPath);
	GetPrivateProfileString(L"app", L"number", L"Default value", buffer, BUFFERSIZE, configPath);
	number_of_data = _wtof(buffer);

	for (int i = 0; i < number_of_data; i++)
	{
		wcscpy_s(number_buffer, L"type");
		swprintf(temp, 5, L"%d", i);
		wcscat_s(number_buffer, temp);
		GetPrivateProfileString(L"app", number_buffer, L"Default value", buffer, 20, configPath);
		wcscpy_s(My_Expenditure[i].Type, buffer);

		wcscpy_s(number_buffer, L"content");
		swprintf(temp, 5, L"%d", i);
		wcscat_s(number_buffer, temp);
		GetPrivateProfileString(L"app", number_buffer, L"Default value", buffer, 50, configPath);
		wcscpy_s(My_Expenditure[i].Content, buffer);

		wcscpy_s(number_buffer, L"money");
		swprintf(temp, 5, L"%d", i);
		wcscat_s(number_buffer, temp);
		GetPrivateProfileString(L"app", number_buffer, L"Default value", buffer, 20, configPath);
		wcscpy_s(My_Expenditure[i].Money, buffer);

		total_money += _wtof(My_Expenditure[i].Money);

		LVITEM item;
		WCHAR * buff;
		buff = new WCHAR[50];
		item.mask = LVIF_TEXT;
		item.cchTextMax = 6;
		
		item.iSubItem = 0;
		item.pszText = My_Expenditure[i].Type;
		item.iItem = 0;
		ListView_InsertItem(hwnd_listview, &item);
		ListView_SetItemText(hwnd_listview, 0, 1, My_Expenditure[i].Content);
		ListView_SetItemText(hwnd_listview, 0, 2, My_Expenditure[i].Money);
		swprintf(buff, 30, L"%d", total_money);
		SetWindowText(hwnd_total, buff);
		Adding_Money(i);
	}
}

void Adding_Money(int i)
{
	if (wcscmp(My_Expenditure[i].Type, L"Ăn uống") == 0)
	{
		eating_money += _wtof(My_Expenditure[i].Money);
	}
	else if (wcscmp(My_Expenditure[i].Type, L"Di chuyển") == 0)
	{
		moving_money += _wtof(My_Expenditure[i].Money);
	}
	else if (wcscmp(My_Expenditure[i].Type, L"Nhà cửa") == 0)
	{
		accommodation_money += _wtof(My_Expenditure[i].Money);
	}
	else if (wcscmp(My_Expenditure[i].Type, L"Xe cộ") == 0)
	{
		vehicle_money += _wtof(My_Expenditure[i].Money);
	}
	else if (wcscmp(My_Expenditure[i].Type, L"Nhu yếu phẩm") == 0)
	{
		essential_money += _wtof(My_Expenditure[i].Money);
	}
	else if (wcscmp(My_Expenditure[i].Type, L"Dịch vụ") == 0)
	{
		service_money += _wtof(My_Expenditure[i].Money);
	}
}

double round2(double a)
{
	if (((int)(a * 1000)) % 10 >= 5)
	{
		return ((double)((int)(a * 100 + 1))) / 100;
	}
	else
	{
		return ((double)((int)(a * 100))) / 100;
	}
}

void Set_Percent_Text(double a, HWND hwnd, int type)
{
	WCHAR temp[50], temp_money[30];
	switch (type)
	{
	case 0:
		wcscpy_s(temp, L"Ăn uống: ");
		swprintf(temp_money, 10, L"%d - ", eating_money);
		break;
	case 1:
		wcscpy_s(temp, L"Di chuyển: ");
		swprintf(temp_money, 10, L"%d - ", moving_money);
		break;
	case 2:
		wcscpy_s(temp, L"Nhà cửa: ");
		swprintf(temp_money, 10, L"%d - ", accommodation_money);
		break;
	case 3:
		wcscpy_s(temp, L"Xe cộ: ");
		swprintf(temp_money, 10, L"%d - ", vehicle_money);
		break;
	case 4:
		wcscpy_s(temp, L"Nhu yếu phẩm: ");
		swprintf(temp_money, 10, L"%d - ", essential_money);
		break;
	case 5:
		wcscpy_s(temp, L"Dịch vụ: ");
		swprintf(temp_money, 10, L"%d - ", service_money);
		break;
	}
	wcscat_s(temp, temp_money);
	swprintf(temp_money, 50, L"%.2f", a);
	wcscat_s(temp, temp_money);
	wcscat_s(temp, L"%");
	SetWindowText(hwnd, temp);
}

void Percent_Money()
{
	eating_percent = double(eating_money * 100) / double(total_money);
	moving_percent = double(moving_money * 100) / double(total_money);
	accommodation_percent = double(accommodation_money * 100) / double(total_money);
	vehicle_percent = double(vehicle_money * 100) / double(total_money);
	essential_percent = double(essential_money * 100) / double(total_money);
	service_percent = 100.00 - round2(eating_percent + moving_percent + accommodation_percent + vehicle_percent + essential_percent);
	Set_Percent_Text(eating_percent, hwnd_eating, 0);
	Set_Percent_Text(moving_percent, hwnd_moving, 1);
	Set_Percent_Text(accommodation_percent, hwnd_accommodation, 2);
	Set_Percent_Text(vehicle_percent, hwnd_vehicle, 3);
	Set_Percent_Text(essential_percent, hwnd_essential, 4);
	Set_Percent_Text(service_percent, hwnd_service, 5);
}

void InsertListViewItems(HWND hListView)
{
	WCHAR curPath[BUFFERSIZE];
	WCHAR configPath[BUFFERSIZE];
	GetCurrentDirectory(BUFFERSIZE, curPath);
	wsprintf(configPath, L"%s\\data.ini", curPath);

	LVITEM item;
	item.mask = LVIF_TEXT;
	item.cchTextMax = 6;

	item.iSubItem = 0;
	WCHAR * buff;
	WCHAR * buff1;
	WCHAR * combobuff;
	buff = new WCHAR[50];
	buff1 = new WCHAR[50];
	combobuff = new WCHAR[50];
	WCHAR key_buff[20];
	ComboBox_GetText(hwnd_combobox, combobuff, 20);

	item.pszText = combobuff;
	item.iItem = 0;

	int buff_size = GetWindowTextLength(hwnd_content);
	GetWindowText(hwnd_content, buff, buff_size + 1);
	int buff_size1 = GetWindowTextLength(hwnd_money);
	GetWindowText(hwnd_money, buff1, buff_size1 + 1);
	if ((wcscmp(buff, L"") == 0) || wcscmp(buff1, L"") == 0)
	{
		MessageBox(NULL, L"Hãy nhập vào mục nội dung và số tiền", L"Error", MB_ICONERROR | MB_OK | MB_DEFBUTTON2);
	}
	else
	{
		ListView_InsertItem(hListView, &item);

		WCHAR temp_num[5];
		wcscpy_s(key_buff, L"type");
		swprintf(temp_num, 5, L"%d", number_of_data);
		wcscat_s(key_buff, temp_num);
		wcscpy_s(My_Expenditure[number_of_data + 1].Type, buff);
		WritePrivateProfileString(L"app", key_buff, buff, configPath);

		ListView_SetItemText(hListView, 0, 1, buff);
		wcscpy_s(My_Expenditure[number_of_data + 1].Content, buff);

		wcscpy_s(key_buff, L"content");
		wcscat_s(key_buff, temp_num);
		WritePrivateProfileString(L"app", key_buff, buff, configPath);

		buff_size = GetWindowTextLength(hwnd_money);
		GetWindowText(hwnd_money, buff, buff_size + 1);
		int temp = _wtoi(buff);
		if (temp <= 0)
		{
			MessageBox(NULL, L"Hãy nhập số tiền bằng số, lớn hơn 0", L"Error", MB_ICONERROR | MB_OK | MB_DEFBUTTON2);
		}
		else
		{
			ListView_SetItemText(hListView, 0, 2, buff);
			wcscpy_s(My_Expenditure[number_of_data + 1].Money, buff);

			wcscpy_s(key_buff, L"money");
			wcscat_s(key_buff, temp_num);
			WritePrivateProfileString(L"app", key_buff, buff, configPath);

			swprintf(temp_num, 5, L"%d", number_of_data + 1);
			WritePrivateProfileString(L"app", L"number", temp_num, configPath);

			total_money += temp;
			swprintf(buff, 30, L"%d", total_money);
			SetWindowText(hwnd_total, buff);

			number_of_data++;
			Adding_Money(number_of_data);
		}
	}
	Percent_Money();
}

void Add_String_To_Combobox(HWND hwnd_combobox)
{
	WCHAR Types[6][20] =
	{
		(L"Ăn uống"), (L"Di chuyển"), (L"Nhà cửa"), (L"Xe cộ"),
		(L"Nhu yếu phẩm"), (L"Dịch vụ")
	};

	WCHAR A[16];
	int  k = 0;

	memset(&A, 0, sizeof(A));
	for (k = 0; k < 6; k++)
	{
		wcscpy_s(A, sizeof(A) / sizeof(WCHAR), (WCHAR*)Types[k]);

		SendMessage(hwnd_combobox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}

	SendMessage(hwnd_combobox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
}

void Percent_Chart()
{
	eating_a = 30;
	eating_b = eating_a + one_percent_length * eating_percent;
	moving_a = eating_b;
	moving_b = moving_a + one_percent_length * moving_percent;
	accommodation_a = moving_b;
	accommodation_b = accommodation_a + one_percent_length * accommodation_percent;
	vehicle_a = accommodation_b;
	vehicle_b = vehicle_a + one_percent_length * vehicle_percent;
	essential_a = vehicle_b;
	essential_b = essential_a + one_percent_length * essential_percent;
	service_a = essential_b;
	service_b = service_a + one_percent_length * service_percent;
}

void Draw_Chart(HWND hWnd, int a, int b)
{
	shape = prototypes[0]->Create();
	shape->Set_Data(a, 520, b, 550);
	shapes.push_back(shape);
	InvalidateRect(hWnd, NULL, TRUE);
}

void Draw_Little_Chart(HWND hWnd, int a, int b, int c, int d)
{
	shape = prototypes[0]->Create();
	shape->Set_Data(a, b, c, d);
	shapes.push_back(shape);
	InvalidateRect(hWnd, NULL, TRUE);
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDC_BUTTON1:
		InsertListViewItems(hwnd_listview);
		Percent_Chart();
		prototypes.push_back(new My_Rectangle);
		Draw_Chart(hWnd, eating_a, eating_b);
		Draw_Chart(hWnd, moving_a, moving_b);
		Draw_Chart(hWnd, accommodation_a, accommodation_b);
		Draw_Chart(hWnd, vehicle_a, vehicle_b);
		Draw_Chart(hWnd, essential_a, essential_b);
		Draw_Chart(hWnd, service_a, service_b);
		Draw_Little_Chart(hWnd, 465, 450, 475, 460);
		Draw_Little_Chart(hWnd, 465, 470, 475, 480);
		Draw_Little_Chart(hWnd, 465, 490, 475, 500);
		Draw_Little_Chart(hWnd, 465, 510, 475, 520);
		Draw_Little_Chart(hWnd, 465, 530, 475, 540);
		Draw_Little_Chart(hWnd, 465, 550, 475, 560);
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < shapes.size(); i++)
		{
			int k = i - 6;
			if (i <= 5)
			{
				SelectObject(hdc, hbrush[i]);
			}
			else SelectObject(hdc, hbrush[k]);
			shapes[i]->Draw(hdc);
		}
		shapes.clear();
		EndPaint(hWnd, &ps);
		break;
	}
}

void Create_Color()
{
	hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
	hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
	hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
	hbrush[3] = CreateSolidBrush(RGB(0, 0, 255));
	hbrush[4] = CreateSolidBrush(RGB(204, 0, 204));
	hbrush[5] = CreateSolidBrush(RGB(255, 128, 0));
}

void OnPaint(HWND hWnd)
{
	Percent_Chart();
	prototypes.push_back(new My_Rectangle);
	Draw_Chart(hWnd, eating_a, eating_b);
	Draw_Chart(hWnd, moving_a, moving_b);
	Draw_Chart(hWnd, accommodation_a, accommodation_b);
	Draw_Chart(hWnd, vehicle_a, vehicle_b);
	Draw_Chart(hWnd, essential_a, essential_b);
	Draw_Chart(hWnd, service_a, service_b);
	Draw_Little_Chart(hWnd, 465, 450, 475, 460);
	Draw_Little_Chart(hWnd, 465, 470, 475, 480);
	Draw_Little_Chart(hWnd, 465, 490, 475, 500);
	Draw_Little_Chart(hWnd, 465, 510, 475, 520);
	Draw_Little_Chart(hWnd, 465, 530, 475, 540);
	Draw_Little_Chart(hWnd, 465, 550, 475, 560);
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < shapes.size(); i++)
	{
		int k = i - 6;
		if (i <= 5)
		{
			SelectObject(hdc, hbrush[i]);
		}
		else SelectObject(hdc, hbrush[k]);
		shapes[i]->Draw(hdc);
	}
	shapes.clear();
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	DestroyFramework();
	PostQuitMessage(0);
}