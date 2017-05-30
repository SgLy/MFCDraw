// PenWidthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "PenWidthDlg.h"
#include "afxdialogex.h"


// CPenWidthDlg dialog

IMPLEMENT_DYNAMIC(CPenWidthDlg, CDialog)

CPenWidthDlg::CPenWidthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, penWidth_dlg(0)
{

}

CPenWidthDlg::~CPenWidthDlg()
{
}

BOOL CPenWidthDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CSpinButtonCtrl*)GetDlgItem(IDC_PEN_WIDTH_SPIN))->SetRange(1, maxPenWidth);

	return TRUE;
}

void CPenWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, penWidth_dlg);
	DDV_MinMaxInt(pDX, penWidth_dlg, 1, maxPenWidth);
}


BEGIN_MESSAGE_MAP(CPenWidthDlg, CDialog)
END_MESSAGE_MAP()


// CPenWidthDlg message handlers
