
// MFCApplication3View.cpp : implementation of the CMFCApplication3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "CDesignView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// HitTest Constants
#define DHT_CLOSE		0x01
#define DHT_CAPTION		0x02

#define LIGHT_COLOR		250
#define DARK_COLOR		100
// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCApplication3View construction/destruction

CMFCApplication3View::CMFCApplication3View() noexcept
{
	// TODO: add construction code here

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View drawing

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rc;
	this->GetWindowRect(&rc);
	this->ScreenToClient(&rc);
	CDC* hdc = this->GetWindowDC();

	hdc->FillSolidRect(&rc, RGB(255, 0, 0));

	CFont ft;
	ft.CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));
	CFont* oldfont = hdc->SelectObject(&ft);
	CString st("Go to the THEME menu and select the different options to see the effect on the appearance of the window.");
	hdc->TextOut(10, 10, st.GetBuffer(st.GetLength()), st.GetLength());
	hdc->SelectObject(oldfont);

	// TODO: add draw code for native data here
}


// CMFCApplication3View printing


void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View diagnostics

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View message handlers





LRESULT CMFCApplication3View::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// I don't handle it: pass along

	return CView::WindowProc(message, wParam, lParam);
}


int CMFCApplication3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	HWND parent = ::GetParent(m_hWnd);
	CDesignView::InsertSuperCView(parent, this, CDesignView::VIEWID);

	return 0;
}


BOOL CMFCApplication3View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL ret =  CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);


	return ret;

}
