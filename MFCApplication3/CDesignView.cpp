#include "pch.h"
#include <string>
#include "CDesignView.h"

CDesignView::CDesignView()
{
	maxREct = { -10,0,0,0 };
	minREct = { -10,0,0,0 };;
	CloseREct = { -10,0,0,0 };;
	view = NULL;
	isMaximized = FALSE;
	isActive = FALSE;
}

CDesignView::~CDesignView()
{
}


//COLORREF CDesignView::activeColor = RGB(161, 187, 215);
//COLORREF CDesignView::passiveColor = RGB(192, 206, 220);
COLORREF CDesignView::activeColor = RGB(0, 220, 0);
COLORREF CDesignView::passiveColor = RGB(0, 180, 0);

COLORREF CDesignView::activeFrameColor = RGB(220, 0, 0);
COLORREF CDesignView::passiveFrameColor = RGB(180, 0, 0);




// HitTest Constants

LRESULT CALLBACK OwnerProc_CViewCaption(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	LRESULT raz = TRUE;;
	BOOL fActive = FALSE;
	BOOL m_bOver = TRUE;
	if (dwRefData == NULL) {
		raz = DefWindowProc(hWnd, uMsg, wParam, lParam);
		return raz;
	}
	CDesignView* pDesignView = (CDesignView*)dwRefData;

	switch (uMsg)
	{
	case WM_NCCALCSIZE:
	{

		CRect rc;
		GetWindowRect(hWnd, rc);

		LPNCCALCSIZE_PARAMS pncc = (LPNCCALCSIZE_PARAMS)lParam;

		int captionSize = GetSystemMetrics(SM_CYCAPTION);


		//pncc->rgrc[0] is the new rectangle
		//pncc->rgrc[1] is the old rectangle
		//pncc->rgrc[2] is the client rectangle

		int delta = GetSystemMetrics(SM_CXFIXEDFRAME);

		raz = DefWindowProc(hWnd, WM_NCCALCSIZE, wParam, lParam);

		auto lStyle1 = GetWindowLongPtr(hWnd, GWL_STYLE);

		if ((lStyle1 & WS_MAXIMIZE) != WS_MAXIMIZE) {
			const int cxBorder = GetSystemMetrics(SM_CXFRAME);
			const int cyBorder = GetSystemMetrics(SM_CYFRAME);
			InflateRect((LPRECT)lParam, cxBorder, cyBorder);
			pDesignView->isMaximized = FALSE;
		}
		else {
			pDesignView->isMaximized = TRUE;
		}

		return FALSE;
		////	pncc->rgrc[0].top += GetSystemMetrics(SM_CYCAPTION);

	}
	break;
	case WM_NCHITTEST: {
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		switch (raz)
		{
		case HTMAXBUTTON:
		{
			return raz;
		}
		break;
		case HTMINBUTTON:
		{
			return raz;
		}
		break;
		case HTCLOSE:
		{
			return raz;
		}
		break;
		}
		return raz;

	}
		 break;
	case WM_SETTEXT:
	{
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return FALSE;
	}
	break;
	case 0x00ae:
	{
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return raz;
	}
	break;
	case WM_ACTIVATEAPP: {
		fActive = (BOOL)wParam;
		pDesignView->isActive = fActive;

		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		int classID = (int)uIdSubclass;

		if (CDesignView::FRAMEID == classID) {
			DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		}
		return FALSE;
	}
		 break;
	case WM_MDIACTIVATE:
	{
		int classID = (int)uIdSubclass;
		if (CDesignView::FRAMEID == classID) {
			fActive = (BOOL)wParam;
			pDesignView->isActive = fActive;
			raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
			DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
			return FALSE;
		}
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		return raz;

	}
	break;


	case WM_NCACTIVATE:
	{
		fActive = (BOOL)wParam;
		pDesignView->isActive = fActive;
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return raz;
	}
	break;
	case WM_SETFOCUS: {
		fActive = TRUE;
		pDesignView->isActive = fActive;
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);

		return raz;
	}
					break;
	case WM_KILLFOCUS: {
		fActive = FALSE;
		pDesignView->isActive = fActive;
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);

		return raz;
	}
					 break;
	case WM_SIZE: {

		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		
		if (SIZE_MAXIMIZED == wParam) {
		//	::SendMessage(hWnd, WM_SETREDRAW, FALSE, 0);
		}
		else {
			DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		}
		return raz;
	}
				break;
	case WM_MOVE: {
		fActive = TRUE;
		pDesignView->isActive = fActive;
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return raz;
	}
				break;
	case WM_WINDOWPOSCHANGED: {
		fActive = TRUE;
		pDesignView->isActive = fActive;
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return raz;
	}
	case WM_NCPAINT: {

		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return FALSE;
	}
				   break;
	case WM_ACTIVATE: {
		fActive = (BOOL)wParam;
		pDesignView->isActive = fActive;
		DrawTitle(fActive, hWnd, wParam, lParam, dwRefData, uIdSubclass);
		return FALSE;
	}
					break;
	case WM_DESTROY:
	{
		RemoveWindowSubclass(hWnd, OwnerProc_CViewCaption, uIdSubclass);
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);
		delete pDesignView;
		pDesignView = NULL;
		return raz;
	}
	break;
	default:
		raz = DefSubclassProc(hWnd, uMsg, wParam, lParam);;
		break;

	}
	return raz;

}

void DrawTitle(BOOL& fActive, const HWND& hWnd, WPARAM wParam,
	LPARAM lParam, DWORD_PTR dwRefData, UINT_PTR uIdSubclass)
{
	COLORREF color;

	int classID = (int)uIdSubclass;

	CDesignView* pDesignView = (CDesignView*)dwRefData;


	if (CDesignView::FRAMEID == classID) {
		if (!fActive) {
			color = CDesignView::passiveFrameColor;

		}
		else {
			color = CDesignView::activeFrameColor;

		}
	}
	else {
		if (!fActive) {
			color = CDesignView::passiveColor;

		}
		else {
			color = CDesignView::activeColor;

		}
	}

	BOOL active = pDesignView->isActive;

	// To accesses the entire screen area of a CWnd 
	// (both client and nonclient areas).
	CWnd* pWnd = CWnd::FromHandle(hWnd);
	CWindowDC dc(pWnd);

	CRect rc;
	GetWindowRect(hWnd, rc);

	int xBorder;


	CRect clientRect;
	::GetClientRect(pWnd->m_hWnd, &clientRect);

	CRect rcAll;
	GetWindowRect(hWnd, rcAll);


	xBorder = (rcAll.Width() - clientRect.Width()) / 2;

	CRect bRect;
	bRect.top = 0;
	bRect.left = 0;
	bRect.bottom = rcAll.bottom - rcAll.top;
	bRect.right = rcAll.right - rcAll.left;

	if (!pDesignView->isMaximized) {
		CDesignView::DrawBorderRect(dc.m_hDC, bRect, RGB(255, 255, 255), xBorder * 2);
	}

	int captionSize = GetSystemMetrics(SM_CYCAPTION);


	rc.bottom = captionSize + GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYFIXEDFRAME);


	RECT rect;
	rect.left = xBorder;
	rect.right = rc.Width() - xBorder;
	rect.top = xBorder;
	rect.bottom = rc.bottom;

	HBRUSH brush = CreateSolidBrush(color);
	::FillRect(dc.m_hDC, &rect, brush);
	DeleteObject(brush);

	RECT rectCaption = rect;
	rectCaption.left += (rect.bottom - rect.top) * 1.5;

	//---------------

	char buff[255] = { 0 };
	::GetWindowTextA(hWnd, buff, 255);

	int bgMode = ::SetBkMode(dc.m_hDC, TRANSPARENT);

	::DrawTextA(dc.m_hDC, buff, -1, &rectCaption, DT_LEFT | DT_SINGLELINE | DT_VCENTER);

	::SetBkMode(dc.m_hDC, bgMode);


	//---------------

	if (!pDesignView->isMaximized) {
		bRect.right -= 2;
		bRect.bottom -= 2;

		CDesignView::DrawBorderRect(dc.m_hDC, bRect, color, xBorder);
	}

	// Area for buttons
	RECT closeRect;
	int bSize;

	RECT maximizeRect;
	RECT minimizeeRect;
	int oldMode = dc.SetBkMode(TRANSPARENT);



		closeRect.top = GetSystemMetrics(SM_CYFRAME) + 5;
		closeRect.bottom = GetSystemMetrics(SM_CYSIZE);

		if (pDesignView->isMaximized) {
			closeRect.top += GetSystemMetrics(SM_CYFIXEDFRAME);
			closeRect.bottom += GetSystemMetrics(SM_CYFIXEDFRAME);
		}

		bSize = closeRect.bottom - closeRect.top;

		closeRect.left = rc.right - rc.left - bSize - 10 - xBorder;
		closeRect.right = closeRect.left + bSize + 5;

		maximizeRect.left = closeRect.left - captionSize - 5;
		maximizeRect.right = maximizeRect.left + captionSize;
		maximizeRect.top = closeRect.top;
		maximizeRect.bottom = closeRect.bottom;

		minimizeeRect.left = closeRect.left - captionSize * 2 - 10;
		minimizeeRect.right = minimizeeRect.left + captionSize;
		minimizeeRect.top = closeRect.top;
		minimizeeRect.bottom = closeRect.bottom;



	auto lStyle = GetWindowLongPtr(hWnd, GWL_STYLE);


	pDesignView->maxREct = maximizeRect;
	pDesignView->minREct = minimizeeRect;
	pDesignView->CloseREct = closeRect;

	dc.DrawFrameControl(&closeRect,
		DFC_CAPTION,
		DFCS_CAPTIONCLOSE | DFCS_TRANSPARENT);

	if ((lStyle & WS_MAXIMIZEBOX) != 0) {

		dc.DrawFrameControl(&maximizeRect,
			DFC_CAPTION,
			DFCS_CAPTIONMAX | DFCS_TRANSPARENT);
	}

	if ((lStyle & WS_MINIMIZEBOX) != 0) {
		dc.DrawFrameControl(&minimizeeRect,
			DFC_CAPTION,
			DFCS_CAPTIONMIN | DFCS_TRANSPARENT);
	}

	dc.SetBkMode(oldMode);





}


void CDesignView::DrawBorderRect(HDC hdc, CRect& rect, COLORREF color, int size)
{
	HPEN hPen = ::CreatePen(PS_SOLID, size, color);
	HPEN pOldPen = (HPEN)::SelectObject(hdc, hPen);


	::MoveToEx(hdc, rect.left, rect.bottom, NULL);
	::LineTo(hdc, rect.right, rect.bottom);

	::MoveToEx(hdc, rect.left, rect.top, NULL);
	::LineTo(hdc, rect.right, rect.top);

	::MoveToEx(hdc, rect.left, rect.top, NULL);
	::LineTo(hdc, rect.left, rect.bottom);

	::MoveToEx(hdc, rect.right, rect.top, NULL);
	::LineTo(hdc, rect.right, rect.bottom);


	SelectObject(hdc, pOldPen);
	DeleteObject(hPen);
}


void CDesignView::InsertSuperCView(HWND hWnd, void* view, int uIdSubclass)
{
	if (hWnd != NULL) {

		CDesignView* pDesignView = new CDesignView();
		pDesignView->view = view;

		::SetWindowSubclass(hWnd, OwnerProc_CViewCaption, uIdSubclass, (DWORD_PTR)pDesignView);
	}

}
