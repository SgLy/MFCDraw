
// MFCDrawView.cpp : CMFCDrawView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MainFrm.h"
#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#include "PenWidthDlg.h"

#include "Socket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// ��׼��ӡ����
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

// CMFCDrawView ����/����

#define HS_FILL 6

Socket * c_sock;

CMFCDrawView::CMFCDrawView()
{
	isButtonDown = false;

	option.penCol = RGB(0, 0, 128);
	option.penWidth = option.solidPenWidth = 5;
	option.penStyle = PS_SOLID;
	p0 = new CPen(PS_DOT, 0, RGB(128, 128, 128));
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);

	option.brushStyle = HS_FILL;
	option.transparent = false;
	option.brushCol = RGB(128, 128, 255);
	b0 = new CBrush(option.brushCol);

	AfxSocketInit();

	c_sock = new Socket();
	c_sock->Create();

	c_sock->Connect(L"localhost", 64190);

	option.mode = DRAW_LINE;
}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView ����

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCDrawView ��ӡ

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCDrawView ���

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView ��Ϣ�������

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
	c_sock->Send(&option, sizeof(option), 0);

	if (option.mode == DRAW_LINE) {
		p->MoveTo(st);
		p->LineTo(ed);
	} else if (option.mode == DRAW_RECT)
		p->Rectangle(CRect(st, ed));
	else if (option.mode == DRAW_ELLI)
		p->Ellipse(CRect(st, ed));

}

void CMFCDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	isButtonDown = true;
	option.st = option.ed = point;
	
	CString buf;
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	buf.Format(L"���: (%d, %d)", option.st.x, option.st.y);
	pFrmWnd->setStatusBarVal(pFrmWnd->start_point, buf);

	CView::OnLButtonDown(nFlags, point);
}


void CMFCDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isButtonDown) {
		CDC * pDC = GetDC();

		// Erase former
		pickEmpty(pDC);
		realDraw(pDC, option.st, option.ed);

		// Draw final
		option.ed = point;
		pickReal(pDC);
		realDraw(pDC, option.st, option.ed);

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
	buf.Format(L"ָ��λ��: (%d, %d)", point.x, point.y);
	pFrmWnd->setStatusBarVal(pFrmWnd->cursor, buf);
	if (isButtonDown) {
		pickEmpty(pDC);
		realDraw(pDC, option.st, option.ed);
		option.ed = point;
		realDraw(pDC, option.st, option.ed);

		buf.Format(L"��С: (%d, %d)", abs(point.x - option.st.x), abs(point.y - option.st.y));
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
		realDraw(pDC, option.st, option.ed);
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
	option.mode = DRAW_LINE;
}
void CMFCDrawView::OnMenuDrawRect()
{
	option.mode = DRAW_RECT;
}
void CMFCDrawView::OnMenuDrawElli()
{
	option.mode = DRAW_ELLI;
}


void CMFCDrawView::OnUpdateMenuDrawLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.mode == DRAW_LINE);
}
void CMFCDrawView::OnUpdateMenuDrawRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.mode == DRAW_RECT);
}
void CMFCDrawView::OnUpdateMenuDrawElli(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.mode == DRAW_ELLI);
}


void CMFCDrawView::OnMenuLineColor()
{
	CColorDialog colDlg(option.penCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		option.penCol = colDlg.GetColor();
		delete p1;
		p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
	}
}

void CMFCDrawView::OnMenuLineSolid()
{
	option.penStyle = PS_SOLID;
	delete p1;
	option.penWidth = option.solidPenWidth;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineSolid(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_SOLID);
}

void CMFCDrawView::OnMenuLineDash()
{
	if (option.penStyle == PS_SOLID)
		option.solidPenWidth = option.penWidth;
	option.penStyle = PS_DASH;
	option.penWidth = 1;
	delete p1;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineDash(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_DASH);
}
void CMFCDrawView::OnMenuLineDot()
{
	if (option.penStyle == PS_SOLID)
		option.solidPenWidth = option.penWidth;
	option.penStyle = PS_DOT;
	option.penWidth = 1;
	delete p1;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineDot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_DOT);
}
void CMFCDrawView::OnMenuLineDashdot()
{
	if (option.penStyle == PS_SOLID)
		option.solidPenWidth = option.penWidth;
	option.penStyle = PS_DASHDOT;
	option.penWidth = 1;
	delete p1;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineDashdot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_DASHDOT);
}
void CMFCDrawView::OnMenuLineDashdotdot()
{
	if (option.penStyle == PS_SOLID)
		option.solidPenWidth = option.penWidth;
	option.penStyle = PS_DASHDOTDOT;
	option.penWidth = 1;
	delete p1;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineDashdotdot(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_DASHDOTDOT);
}
void CMFCDrawView::OnMenuLineNull()
{
	if (option.penStyle == PS_SOLID)
		option.solidPenWidth = option.penWidth;
	option.penStyle = PS_NULL;
	option.penWidth = 1;
	delete p1;
	p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
}
void CMFCDrawView::OnUpdateMenuLineNull(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.penStyle == PS_NULL);
}

void CMFCDrawView::OnMenuBrushColor()
{
	CColorDialog colDlg(option.brushCol, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		option.brushCol = colDlg.GetColor();
		if (option.transparent)
			return;
		delete b0;
		if (option.brushStyle == HS_FILL)
			b0 = new CBrush(option.brushCol);
		else
			b0 = new CBrush(option.brushStyle, option.brushCol);
	}
}


void CMFCDrawView::OnMenuBrushTransparent()
{
	option.transparent = !option.transparent;
	option.brushStyle = -1;
	if (option.transparent)
		b0 = new CBrush();
	else {
		if (option.brushStyle == HS_FILL)
			b0 = new CBrush(option.brushCol);
		else
			b0 = new CBrush(option.brushStyle, option.brushCol);
	}
}


void CMFCDrawView::OnUpdateMenuBrushTransparent(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.transparent);
}


void CMFCDrawView::OnMenuBrushHorizontal()
{
	option.brushStyle = HS_HORIZONTAL;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushHorizontal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_HORIZONTAL);
}
void CMFCDrawView::OnMenuBrushVertical()
{
	option.brushStyle = HS_VERTICAL;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushVertical(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_VERTICAL);
}
void CMFCDrawView::OnMenuBrushFdiagonal()
{
	option.brushStyle = HS_FDIAGONAL;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushFdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_FDIAGONAL);
}
void CMFCDrawView::OnMenuBrushBdiagonal()
{
	option.brushStyle = HS_BDIAGONAL;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushBdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_BDIAGONAL);
}
void CMFCDrawView::OnMenuBrushCross()
{
	option.brushStyle = HS_CROSS;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushCross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_CROSS);
}
void CMFCDrawView::OnMenuBrushDiagcross()
{
	option.brushStyle = HS_DIAGCROSS;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushStyle, option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushDiagcross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_DIAGCROSS);
}
void CMFCDrawView::OnMenuBrushFill()
{
	option.brushStyle = HS_FILL;
	option.transparent = false;
	delete b0;
	b0 = new CBrush(option.brushCol);
}
void CMFCDrawView::OnUpdateMenuBrushFill(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_FILL);
}


void CMFCDrawView::OnMenuDrawClear()
{
	RedrawWindow();
}


void CMFCDrawView::OnMenuPenWidth()
{
	CPenWidthDlg dlg;
	dlg.penWidth_dlg = option.penWidth;
	if (option.penStyle == PS_SOLID)
		dlg.maxPenWidth = 2000;
	else
		dlg.maxPenWidth = 1;
	if (dlg.DoModal() == IDOK) {
		option.penWidth = dlg.penWidth_dlg;
		delete p1;
		p1 = new CPen(option.penStyle, option.penWidth, option.penCol);
	}
}
