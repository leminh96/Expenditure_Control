#pragma once
#include "resource.h"
#include <windowsx.h>
#include <winuser.h>
#include <commctrl.h>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <vector>
using namespace std;
#define RECTANGLE 1
const int BUFFERSIZE = 260;

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void Add_String_To_Combobox(HWND hwnd_combobox);
HWND hwnd_combobox, hwnd_listview, hwnd_content, hwnd_money, hwnd_total, hwnd_eating, hwnd_moving, hwnd_accommodation, hwnd_vehicle, hwnd_essential, hwnd_service;
int total_money, number_of_data, eating_money, moving_money, accommodation_money, vehicle_money, essential_money, service_money = 0;
double eating_percent, moving_percent, accommodation_percent, vehicle_percent, essential_percent, service_percent;
float one_percent_length = 4.2;
float eating_a, moving_a, accommodation_a, vehicle_a, essential_a, service_a;
float eating_b, moving_b, accommodation_b, vehicle_b, essential_b, service_b;
void InsertListViewItems(HWND hListView);
void Set_Percent_Text(double a, HWND hwnd, int type);
void Read_File();
void Adding_Money(int i);
void Percent_Money();
void Draw_Chart(HWND hWnd, int a, int b);
void Percent_Chart();
void Create_Color();
struct S_Expenditure
{
	WCHAR Type[20];
	WCHAR Content[50];
	WCHAR Money[30];
};

S_Expenditure My_Expenditure[50];
class My_Shape {
public:
	virtual void Draw(HDC hdc) = 0;
	virtual My_Shape* Create() = 0;
	virtual void Set_Data(int a, int b, int c, int d) = 0;
};

class My_Rectangle : public My_Shape
{
public:
	int x1;
	int y1;
	int x2;
	int y2;
public:
	void Draw(HDC hdc)
	{
		Rectangle(hdc, x1, y1, x2, y2);
	}
	My_Shape* Create() { return new My_Rectangle; }
	void Set_Data(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
};
vector<My_Shape*> prototypes;
vector<My_Shape*> shapes;
My_Shape* shape;
HBRUSH hbrush[5];
