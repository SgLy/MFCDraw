
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

//������������
#include <windows.h>
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )  

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
	ON_COMMAND(ID_LINE_PEN, &CMFCDrawView::OnLinePen)
	ON_UPDATE_COMMAND_UI(ID_LINE_PEN, &CMFCDrawView::OnUpdateLinePen)
	ON_COMMAND(ID_MENU_NET_SERVER, &CMFCDrawView::OnMenuNetServer)
	ON_COMMAND(ID_MENU_NET_CLIENT, &CMFCDrawView::OnMenuNetClient)
	ON_COMMAND(ID_EDIT_UNDO, &CMFCDrawView::OnEditUndo)
	ON_COMMAND(ID_BGM_PLAY, &CMFCDrawView::OnBgmPlay)
	ON_UPDATE_COMMAND_UI(ID_BGM_PLAY, &CMFCDrawView::OnUpdateBgmPlay)
	ON_COMMAND(ID_CLIENT_SAVE, &CMFCDrawView::OnClientSave)
	ON_COMMAND(ID_BACK_STRE, &CMFCDrawView::OnBackStre)
	ON_COMMAND(ID_BACK_TILE, &CMFCDrawView::OnBackTile)
	ON_COMMAND(ID_BACK_ORIG, &CMFCDrawView::OnBackOrig)
	ON_COMMAND(ID_BACK_CLEAR, &CMFCDrawView::OnBackClear)
END_MESSAGE_MAP()

// CMFCDrawView ����/����

#define HS_FILL 6

Socket * sock, * s_list_sock;

CMFCDrawView::CMFCDrawView()
{
	isButtonDown = false;

	option.penCol = RGB(0, 0, 128);
	option.penWidth = option.solidPenWidth = 5;
	option.penStyle = PS_SOLID;

	option.brushStyle = HS_FILL;
	option.transparent = false;
	option.brushCol = RGB(128, 128, 255);

	option.mode = DRAW_LINE;

	history.clear();

	AfxSocketInit();

	m_bPlay = false;
	m_bOnOff = false;

	m_iVar = 0;
	m_bClear = false;
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

void CMFCDrawView::OnDraw(CDC* pDC)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!img.IsNull() && m_iVar != 0 && m_bClear == false) {
		if (m_iVar == 1) {  //����
			CRect ClientRect;
			GetClientRect(&ClientRect);
			int W = ClientRect.Width(), H = ClientRect.Height();
			int w = img.GetWidth(), h = img.GetHeight();
			pDC->SetStretchBltMode(HALFTONE);  //������ģʽ����ֹʧ��
			img.StretchBlt(pDC->m_hDC, 0, 0, W, H, SRCCOPY);   //λͼ���ͣ����죩
		}
		else if (m_iVar == 2) {  //ƽ��
			CRect ClientRect;
			GetClientRect(&ClientRect);
			int W = ClientRect.Width(), H = ClientRect.Height();
			int w = img.GetWidth(), h = img.GetHeight();
			pDC->SetStretchBltMode(HALFTONE);  //������ģʽ����ֹʧ��
			for (int i = 0; i < W; i += w)
				for (int j = 0; j < H; j += h)
					img.BitBlt(pDC->m_hDC, i, j, SRCCOPY);
		}
		else if (m_iVar == 3) {  //ԭͼ
			img.Draw(pDC->m_hDC, 0, 0);   //ֱ�ӻ�ͼ
		}
	}
	if (m_bClear ==  true) {  //�����ͼ
		CRect ClientRect;
		GetClientRect(&ClientRect);
		InvalidateRect(ClientRect);
		UpdateWindow();
		m_bClear = false;
	}
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


void CMFCDrawView::Draw(draw_mode_t mode, draw_net_t net)
{
	option_t op = option;
	if (DRAW_SEND == net) {
		if (sock)
			sock->Send(&option, sizeof(option), 0);
	}
	else if (DRAW_RECV == net) {
		if (sock)
			sock->Receive(&op, sizeof(op), 0);
	}

	if (DRAW_COPY == mode) {
		history.push_back(op);
	}

	CDC * p = GetDC();

	// Set pen
	p0 = new CPen(PS_DOT, 0, RGB(128, 128, 128));
	p1 = new CPen(op.penStyle, op.penWidth, op.penCol);

	// Set brushes
	if (op.transparent)
		b0 = new CBrush();
	else {
		if (op.brushStyle == HS_FILL)
			b0 = new CBrush(op.brushCol);
		else
			b0 = new CBrush(op.brushStyle, op.brushCol);
	}

	// Pick corresponding pen and brush
	if (DRAW_XOR == mode) {
		p->SelectObject(p0);
		p->SelectStockObject(NULL_BRUSH);
		p->SetROP2(R2_XORPEN);
		p->SetBkMode(TRANSPARENT);
	}
	else if (DRAW_COPY == mode) {
		p->SelectObject(p1);
		p->SelectObject(b0);
		p->SetROP2(R2_COPYPEN);
	}


	if (op.mode == DRAW_LINE) {
		p->MoveTo(op.st);
		p->LineTo(op.ed);
	}
	else if (op.mode == DRAW_RECT)
		p->Rectangle(CRect(op.st, op.ed));
	else if (op.mode == DRAW_ELLI)
		p->Ellipse(CRect(op.st, op.ed));
	else if (op.mode == DRAW_PEN) {
		p->MoveTo(op.st);
		p->LineTo(op.ed);
  }

	// Release resources
	delete p0;
	delete p1;
	delete b0;
}

void CMFCDrawView::OnReceive() {
	Draw(DRAW_COPY, DRAW_RECV);
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
		Draw(DRAW_XOR, DRAW_NULL);

		// Draw final
		option.ed = point;
		Draw(DRAW_COPY, DRAW_SEND);

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
		if (option.mode != DRAW_PEN) {
		  Draw(DRAW_XOR, DRAW_NULL);
		  option.ed = point;
		  Draw(DRAW_XOR, DRAW_NULL);
		}
		else {
			option.st = option.ed;
			option.ed = point;
      Draw(DRAW_COPY, DRAW_SEND);
		}

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
		Draw(DRAW_XOR, DRAW_SEND);
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
	}
}

void CMFCDrawView::OnMenuLineSolid()
{
	option.penStyle = PS_SOLID;
	option.penWidth = option.solidPenWidth;
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
	}
}


void CMFCDrawView::OnMenuBrushTransparent()
{
	option.transparent = !option.transparent;
	option.brushStyle = -1;
}


void CMFCDrawView::OnUpdateMenuBrushTransparent(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.transparent);
}


void CMFCDrawView::OnMenuBrushHorizontal()
{
	option.brushStyle = HS_HORIZONTAL;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushHorizontal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_HORIZONTAL);
}

void CMFCDrawView::OnMenuBrushVertical()
{
	option.brushStyle = HS_VERTICAL;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushVertical(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_VERTICAL);
}
void CMFCDrawView::OnMenuBrushFdiagonal()
{
	option.brushStyle = HS_FDIAGONAL;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushFdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_FDIAGONAL);
}
void CMFCDrawView::OnMenuBrushBdiagonal()
{
	option.brushStyle = HS_BDIAGONAL;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushBdiagonal(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_BDIAGONAL);
}
void CMFCDrawView::OnMenuBrushCross()
{
	option.brushStyle = HS_CROSS;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushCross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_CROSS);
}
void CMFCDrawView::OnMenuBrushDiagcross()
{
	option.brushStyle = HS_DIAGCROSS;
	option.transparent = false;
}
void CMFCDrawView::OnUpdateMenuBrushDiagcross(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(option.brushStyle == HS_DIAGCROSS);
}
void CMFCDrawView::OnMenuBrushFill()
{
	option.brushStyle = HS_FILL;
	option.transparent = false;
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
	}
}

void CMFCDrawView::OnLinePen()
{
	// TODO: �ڴ���������������
	option.mode = DRAW_PEN;
}


void CMFCDrawView::OnUpdateLinePen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(option.mode == DRAW_PEN);
}

void CMFCDrawView::OnMenuNetServer()
{
	s_list_sock = new Socket(this);
	s_list_sock->Create(64190);
	s_list_sock->Listen();
}

void CMFCDrawView::OnMenuNetClient()
{
	sock = new Socket(this);
	sock->Create();
	sock->Connect(L"localhost", 64190);
}

void CMFCDrawView::OnAccept()
{
	sock = new Socket(this);
	s_list_sock->Accept(*sock);
}


void CMFCDrawView::OnEditUndo()
{
	RedrawWindow();
	auto old_history = history;
	old_history.pop_back();
	history.clear();
	auto option_backup = option;
	for (auto op : old_history) {
		option = op;
		Draw(DRAW_COPY, DRAW_NULL);
	}
	option = option_backup;
}


void CMFCDrawView::OnBgmPlay()
{
	// TODO: �ڴ���������������
	m_bOnOff = !m_bOnOff;
	m_bPlay = !m_bPlay;
	if (m_bOnOff) PlaySound((LPCTSTR)IDR_WOTW, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	else PlaySound(NULL, NULL, NULL);
}


void CMFCDrawView::OnUpdateBgmPlay(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (m_bPlay) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnClientSave()
{
	// TODO: �ڴ���������������
	RECT ClientRect;
	GetClientRect(&ClientRect);
	int w = ClientRect.right;//
	int h = ClientRect.bottom; // 
	CDC *pDC = GetDC(); // ��ȡ��ǰDC
	CDC mdc; // �����ڴ�DC
	mdc.CreateCompatibleDC(pDC); // �����뵱ǰDC���ݵ��ڴ�DC
	CBitmap bmp; // ����λͼ���������ڴ�DC�еĻ�����
				 // �������Ϊw��h���뵱ǰDC���ݵ�λͼ
	CBitmap *pOldBmp;
	bmp.CreateCompatibleBitmap(pDC, w, h);
	pOldBmp = mdc.SelectObject(&bmp); // ����λͼѡ���ڴ�DC
	mdc.BitBlt(0, 0, w, h, pDC, 0, 0, SRCCOPY);
	GetTopLevelFrame()->ShowWindow(SW_SHOW); // ��ʾ���򴰿�
											 // �����ļ��Ի���Ҫ�õ���չ����������
	wchar_t filters[] = L"����ͼ��ר����[JPEG]�ļ�(*.jpg)|*.jpg|";
	GetTopLevelFrame()->ShowWindow(SW_HIDE); // ���س��򴰿�
	CFileDialog fileDlg(FALSE, L"jpg", L"s.jpg", OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK) {
		CImage img;
		img.Attach(bmp);
		img.Save(fileDlg.GetPathName());
	}
	GetTopLevelFrame()->ShowWindow(SW_SHOW); // ��ʾ���򴰿�
	mdc.SelectObject(pOldBmp);
	bmp.DeleteObject();
	ReleaseDC(pDC);
}


void CMFCDrawView::OnBackStre()
{
	// TODO: �ڴ���������������
	RedrawWindow();
	m_iVar = 1;
	OnLoad();
}


void CMFCDrawView::OnBackTile()
{
	// TODO: �ڴ���������������
	RedrawWindow();
	m_iVar = 2;
	OnLoad();
}


void CMFCDrawView::OnBackOrig()
{
	// TODO: �ڴ���������������
	RedrawWindow();
	m_iVar = 3;
	OnLoad();
}


void CMFCDrawView::OnLoad()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	CString FileName;
	HRESULT hResult;
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();    //ѡ����ļ�·��   
		if (!img.IsNull()) img.Destroy();
		hResult = img.Load(FileName);
		if (FAILED(hResult)) {
			MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
			return;
		}
	}
	Invalidate(); // ǿ�Ƶ���OnDraw
}

void CMFCDrawView::OnBackClear()
{
	// TODO: �ڴ���������������
	m_iVar = 0;
	m_bClear = true;
	Invalidate(); // ǿ�Ƶ���OnDraw
}
