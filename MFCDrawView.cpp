
// MFCDrawView.cpp : CMFCDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MainFrm.h"
#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#include "PenWidthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENU_DRAW_LINE, &CMFCDrawView::OnMenuDrawLine)
	ON_COMMAND(ID_MENU_DRAW_RECT, &CMFCDrawView::OnMenuDrawRect)
	ON_COMMAND(ID_MENU_DRAW_ELLI, &CMFCDrawView::OnMenuDrawElli)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_LINE, &CMFCDrawView::OnUpdateMenuDrawLine)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_RECT, &CMFCDrawView::OnUpdateMenuDrawRect)
	ON_UPDATE_COMMAND_UI(ID_MENU_DRAW_ELLI, &CMFCDrawView::OnUpdateMenuDrawElli)
	ON_COMMAND(ID_MENU_LINE_COLOR, &CMFCDrawView::OnMenuLineColor)
	ON_COMMAND(ID_MENU_LINE_SOLID, &CMFCDrawView::OnMenuLineSolid)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_SOLID, &CMFCDrawView::OnUpdateMenuLineSolid)
	ON_COMMAND(ID_MENU_LINE_DASH, &CMFCDrawView::OnMenuLineDash)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_DASH, &CMFCDrawView::OnUpdateMenuLineDash)
	ON_COMMAND(ID_MENU_LINE_DOT, &CMFCDrawView::OnMenuLineDot)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_DOT, &CMFCDrawView::OnUpdateMenuLineDot)
	ON_COMMAND(ID_MENU_LINE_DASHDOT, &CMFCDrawView::OnMenuLineDashdot)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_DASHDOT, &CMFCDrawView::OnUpdateMenuLineDashdot)
	ON_COMMAND(ID_MENU_LINE_DASHDOTDOT, &CMFCDrawView::OnMenuLineDashdotdot)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_DASHDOTDOT, &CMFCDrawView::OnUpdateMenuLineDashdotdot)
	ON_COMMAND(ID_MENU_LINE_NULL, &CMFCDrawView::OnMenuLineNull)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_NULL, &CMFCDrawView::OnUpdateMenuLineNull)
	ON_COMMAND(ID_MENU_BRUSH_COLOR, &CMFCDrawView::OnMenuBrushColor)
	ON_COMMAND(ID_MENU_BRUSH_TRANSPARENT, &CMFCDrawView::OnMenuBrushTransparent)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_TRANSPARENT, &CMFCDrawView::OnUpdateMenuBrushTransparent)
	ON_COMMAND(ID_MENU_BRUSH_HORIZONTAL, &CMFCDrawView::OnMenuBrushHorizontal)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_HORIZONTAL, &CMFCDrawView::OnUpdateMenuBrushHorizontal)
	ON_COMMAND(ID_MENU_BRUSH_VERTICAL, &CMFCDrawView::OnMenuBrushVertical)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_VERTICAL, &CMFCDrawView::OnUpdateMenuBrushVertical)
	ON_COMMAND(ID_MENU_BRUSH_FDIAGONAL, &CMFCDrawView::OnMenuBrushFdiagonal)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_FDIAGONAL, &CMFCDrawView::OnUpdateMenuBrushFdiagonal)
	ON_COMMAND(ID_MENU_BRUSH_BDIAGONAL, &CMFCDrawView::OnMenuBrushBdiagonal)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_BDIAGONAL, &CMFCDrawView::OnUpdateMenuBrushBdiagonal)
	ON_COMMAND(ID_MENU_BRUSH_CROSS, &CMFCDrawView::OnMenuBrushCross)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_CROSS, &CMFCDrawView::OnUpdateMenuBrushCross)
	ON_COMMAND(ID_MENU_BRUSH_DIAGCROSS, &CMFCDrawView::OnMenuBrushDiagcross)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_DIAGCROSS, &CMFCDrawView::OnUpdateMenuBrushDiagcross)
	ON_COMMAND(ID_MENU_BRUSH_FILL, &CMFCDrawView::OnMenuBrushFill)
	ON_UPDATE_COMMAND_UI(ID_MENU_BRUSH_FILL, &CMFCDrawView::OnUpdateMenuBrushFill)
	ON_COMMAND(ID_MENU_DRAW_CLEAR, &CMFCDrawView::OnMenuDrawClear)
	ON_COMMAND(ID_MENU_LINE_WIDTH, &CMFCDrawView::OnMenuPenWidth)
END_MESSAGE_MAP()

// CMFCDrawView 构造/析构

#define HS_FILL 6

CMFCDrawView::CMFCDrawView()
{
	isButtonDown = false;

	penCol = RGB(0, 0, 128);
	penWidth = solidPenWidth = 5;
	penStyle = PS_SOLID;
	p0 = new CPen(PS_DOT, 0, RGB(128, 128, 128));
	p1 = new CPen(penStyle, penWidth, penCol);

	brushStyle = HS_FILL;
	transparent = false;
	brushCol = RGB(128, 128, 255);
	b0 = new CBrush(brushCol);

	mode = DRAW_LINE;
}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView 绘制

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCDrawView 打印

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCDrawView 诊断

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView 消息处理程序

void CMFCDrawView::pickEmpty(CDC * p)
{
	p->SelectObject(p0);
	p->SelectStockObject(NULL_BRUSH);
	p->SetROP2(R2_XORPEN);
	p->SetBkMode(TRANSPARENT);
}

void CMFCDrawView::pickReal(CDC * p)
{
	p->SelectObject(p1);
	p->SelectObject(b0);
	p->SetROP2(R2_COPYPEN);
}

void CMFCDrawView::realDraw(CDC * p, const CPoint &st, const CPoint &ed)
{
	if (mode == DRAW_LINE) {
		p->MoveTo(st);
		p->LineTo(ed);
	} else if (mode == DRAW_RECT)
		p->Rectangle(CRect(st, ed));
	else if (mode == DRAW_ELLI)
		p->Ellipse(CRect(st, ed));
}

void CMFCDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	isButtonDown = true;
	st = ed = point;
	
	CString buf;
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	buf.Format(L"起点: (%d, %d)", st.x, st.y);
	pFrmWnd->setStatusBarVal(pFrmWnd->start_point, buf);

	CView::OnLButtonDown(nFlags, point);
}


void CMFCDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isButtonDown) {
		CDC * pDC = GetDC();

		// Erase former
		pickEmpty(pDC);
		realDraw(pDC, st, ed);

		// Draw final
		ed = point;
		pickReal(pDC);
		realDraw(pDC, st, ed);

		ReleaseDC(pDC);
		isButtonDown = false;

		CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
		pFrmWnd->setStatusBarVal(pFrmWnd->start_point, L"");
		pFrmWnd->setStatusBarVal(pFrmWnd->size, L"");
	}

	CView::OnLButtonUp(nFlags, point);
}

BOOL CMFCDrawView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(LoadCursor(NULL, IDC_CROSS));
	return 0;
}


void CMFCDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDC * pDC = GetDC();
	CString buf;
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	buf.Format(L"指针位置: (%d, %d)", point.x, point.y);
	pFrmWnd->setStatusBarVal(pFrmWnd->cursor, buf);
	if (isButtonDown) {
		pickEmpty(pDC);
		realDraw(pDC, st, ed);
		ed = point;
		realDraw(pDC, st, ed);

		buf.Format(L"大小: (%d, %d)", abs(point.x - st.x), abs(point.y - st.y));
		pFrmWnd->setStatusBarVal(pFrmWnd->size, buf);
	}
	ReleaseDC(pDC);

	CView::OnMouseMove(nFlags, point);
}


void CMFCDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 27 && isButtonDown) {
		CDC * pDC = GetDC();
		pickEmpty(pDC);
		realDraw(pDC, st, ed);
		ReleaseDC(pDC);
		isButtonDown = false;
		
		CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
		pFrmWnd->setStatusBarVal(pFrmWnd->start_point, L"");
		pFrmWnd->setStatusBarVal(pFrmWnd->size, L"");
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCDrawView::OnMenuDrawLine()
{
	mode = DRAW_LINE;
}
void CMFCDrawView::OnMenuDrawRect()
{
	mode = DRAW_RECT;
}
void CMFCDrawView::OnMenuDrawElli()
{
	mode = DRAW_ELLI;
}


void CMFCDrawView::OnUpdateMenuDrawLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mode == DRAW_LINE);
}
void CMFCDrawView::OnUpdateMenuDrawRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mode == DRAW_RECT);
}
void CMFCDrawView::OnUpdateMenuDrawElli(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mode == DRAW_ELLI);
}


void CMFCDrawView::OnMenuLineColor()
{
	CColorDialog colDlg(penCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		penCol = colDlg.GetColor();
		delete p1;
		p1 = new CPen(penStyle, penWidth, penCol);
	}
}

void CMFCDrawView::OnMenuLineSolid()
{
	penStyle = PS_SOLID;
	delete p1;
	penWidth = solidPenWidth;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineSolid(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_SOLID);
}

void CMFCDrawView::OnMenuLineDash()
{
	if (penStyle == PS_SOLID)
		solidPenWidth = penWidth;
	penStyle = PS_DASH;
	penWidth = 1;
	delete p1;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineDash(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_DASH);
}
void CMFCDrawView::OnMenuLineDot()
{
	if (penStyle == PS_SOLID)
		solidPenWidth = penWidth;
	penStyle = PS_DOT;
	penWidth = 1;
	delete p1;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineDot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_DOT);
}
void CMFCDrawView::OnMenuLineDashdot()
{
	if (penStyle == PS_SOLID)
		solidPenWidth = penWidth;
	penStyle = PS_DASHDOT;
	penWidth = 1;
	delete p1;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineDashdot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_DASHDOT);
}
void CMFCDrawView::OnMenuLineDashdotdot()
{
	if (penStyle == PS_SOLID)
		solidPenWidth = penWidth;
	penStyle = PS_DASHDOTDOT;
	penWidth = 1;
	delete p1;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineDashdotdot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_DASHDOTDOT);
}
void CMFCDrawView::OnMenuLineNull()
{
	if (penStyle == PS_SOLID)
		solidPenWidth = penWidth;
	penStyle = PS_NULL;
	penWidth = 1;
	delete p1;
	p1 = new CPen(penStyle, penWidth, penCol);
}
void CMFCDrawView::OnUpdateMenuLineNull(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(penStyle == PS_NULL);
}

void CMFCDrawView::OnMenuBrushColor()
{
	CColorDialog colDlg(brushCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		brushCol = colDlg.GetColor();
		if (transparent)
			return;
		delete b0;
		if (brushStyle == HS_FILL)
			b0 = new CBrush(brushCol);
		else
			b0 = new CBrush(brushStyle, brushCol);
	}
}


void CMFCDrawView::OnMenuBrushTransparent()
{
	transparent = !transparent;
	brushStyle = -1;
	if (transparent)
		b0 = new CBrush();
	else {
		if (brushStyle == HS_FILL)
			b0 = new CBrush(brushCol);
		else
			b0 = new CBrush(brushStyle, brushCol);
	}
}


void CMFCDrawView::OnUpdateMenuBrushTransparent(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(transparent);
}


void CMFCDrawView::OnMenuBrushHorizontal()
{
	brushStyle = HS_HORIZONTAL;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushHorizontal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_HORIZONTAL);
}
void CMFCDrawView::OnMenuBrushVertical()
{
	brushStyle = HS_VERTICAL;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushVertical(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_VERTICAL);
}
void CMFCDrawView::OnMenuBrushFdiagonal()
{
	brushStyle = HS_FDIAGONAL;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushFdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_FDIAGONAL);
}
void CMFCDrawView::OnMenuBrushBdiagonal()
{
	brushStyle = HS_BDIAGONAL;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushBdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_BDIAGONAL);
}
void CMFCDrawView::OnMenuBrushCross()
{
	brushStyle = HS_CROSS;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushCross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_CROSS);
}
void CMFCDrawView::OnMenuBrushDiagcross()
{
	brushStyle = HS_DIAGCROSS;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushStyle, brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushDiagcross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_DIAGCROSS);
}
void CMFCDrawView::OnMenuBrushFill()
{
	brushStyle = HS_FILL;
	transparent = false;
	delete b0;
	b0 = new CBrush(brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushFill(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(brushStyle == HS_FILL);
}


void CMFCDrawView::OnMenuDrawClear()
{
	RedrawWindow();
}


void CMFCDrawView::OnMenuPenWidth()
{
	CPenWidthDlg dlg;
	dlg.penWidth_dlg = penWidth;
	if (penStyle == PS_SOLID)
		dlg.maxPenWidth = 2000;
	else
		dlg.maxPenWidth = 1;
	if (dlg.DoModal() == IDOK) {
		penWidth = dlg.penWidth_dlg;
		delete p1;
		p1 = new CPen(penStyle, penWidth, penCol);
	}
}
