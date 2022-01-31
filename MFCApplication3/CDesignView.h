#pragma once
#include <wtypes.h>

class CDesignView
{
public:
	CDesignView();
	~CDesignView();
public:
	static	void InsertSuperCView(HWND hWnd,void *view = NULL, int uIdSubclass = 0);
	static void DrawBorderRect(HDC hdc, CRect& rect, COLORREF color, int size);

	RECT maxREct;
	RECT minREct;
	RECT CloseREct;
	void* view;
	BOOL isMaximized;
	BOOL isActive;

	static COLORREF activeColor ;
	static COLORREF passiveColor ;

	static COLORREF activeFrameColor;
	static COLORREF passiveFrameColor;





	static const int FRAMEID = 1001;
	static const int VIEWID = 1000;


private:

};

void DrawTitle(BOOL& fActive, const HWND& hWnd, WPARAM wParam,
	LPARAM lParam, DWORD_PTR dwRefData, UINT_PTR uIdSubclass);
