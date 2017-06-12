// MFCDrawView.h : CMFCDrawView ��Ľӿ�
//

#pragma once

#include <vector>

enum mode_t {
	DRAW_LINE,
	DRAW_RECT,
	DRAW_ELLI,
	DRAW_PEN
};

enum draw_mode_t { DRAW_XOR, DRAW_COPY };
enum draw_net_t { DRAW_SEND, DRAW_RECV, DRAW_NULL };

struct option_t {
	mode_t mode;
	bool transparent;
	CPoint st, ed;
	COLORREF penCol;
	int penWidth, solidPenWidth, penStyle;
	COLORREF brushCol;
	int brushStyle;
};

class CMFCDrawView : public CView
{
protected: // �������л�����
	CMFCDrawView();
	DECLARE_DYNCREATE(CMFCDrawView)

	// ����
public:
	CMFCDrawDoc* GetDocument() const;

	// ����
public:
	void Draw(draw_mode_t mode, draw_net_t net);
	void OnReceive();
	void OnAccept();
	bool m_bPlay;    //���Ʋ˵���UI����
	bool m_bOnOff;    //�������ֲ���
	CImage img;
	int m_iVar;  //�жϵ�ͼ�򿪷�ʽ
	bool m_bClear;  //�Ƿ������ͼ

	void OnLoad();  //װ��ͼƬ��img��
	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CMFCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	option_t option;
	bool isButtonDown;
	CPen * p0, *p1;
	CBrush * b0;
	std::vector<option_t> history;

public:
	afx_msg void OnMenuDrawLine();
	afx_msg void OnMenuDrawRect();
	afx_msg void OnMenuDrawElli();
	afx_msg void OnUpdateMenuDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDrawElli(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineColor();
	afx_msg void OnMenuLineSolid();
	afx_msg void OnUpdateMenuLineSolid(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineDash();
	afx_msg void OnUpdateMenuLineDash(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineDot();
	afx_msg void OnUpdateMenuLineDot(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineDashdot();
	afx_msg void OnUpdateMenuLineDashdot(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineDashdotdot();
	afx_msg void OnUpdateMenuLineDashdotdot(CCmdUI *pCmdUI);
	afx_msg void OnMenuLineNull();
	afx_msg void OnUpdateMenuLineNull(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushColor();
	afx_msg void OnMenuBrushTransparent();
	afx_msg void OnUpdateMenuBrushTransparent(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushHorizontal();
	afx_msg void OnUpdateMenuBrushHorizontal(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushVertical();
	afx_msg void OnUpdateMenuBrushVertical(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushFdiagonal();
	afx_msg void OnUpdateMenuBrushFdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushBdiagonal();
	afx_msg void OnUpdateMenuBrushBdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushCross();
	afx_msg void OnUpdateMenuBrushCross(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushDiagcross();
	afx_msg void OnUpdateMenuBrushDiagcross(CCmdUI *pCmdUI);
	afx_msg void OnMenuBrushFill();
	afx_msg void OnUpdateMenuBrushFill(CCmdUI *pCmdUI);
	afx_msg void OnMenuDrawClear();
	afx_msg void OnMenuPenWidth();
	afx_msg void OnLinePen();
	afx_msg void OnUpdateLinePen(CCmdUI *pCmdUI);
	afx_msg void OnMenuNetServer();
	afx_msg void OnMenuNetClient();
	afx_msg void OnEditUndo();
	afx_msg void OnBgmPlay();
	afx_msg void OnUpdateBgmPlay(CCmdUI *pCmdUI);
	afx_msg void OnClientSave();
	afx_msg void OnBackStre();
	afx_msg void OnBackTile();
	afx_msg void OnBackOrig();
	afx_msg void OnBackClear();
};

#ifndef _DEBUG  // MFCDrawView.cpp �еĵ��԰汾
inline CMFCDrawDoc* CMFCDrawView::GetDocument() const
{
	return reinterpret_cast<CMFCDrawDoc*>(m_pDocument);
}
#endif

