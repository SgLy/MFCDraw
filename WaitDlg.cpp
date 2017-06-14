// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "WaitDlg.h"
#include "afxdialogex.h"


// CWaitDlg dialog

IMPLEMENT_DYNAMIC(CWaitDlg, CDialog)

CWaitDlg::CWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG4, pParent)
	, prompt(_T(""))
{

}

CWaitDlg::~CWaitDlg()
{
}

void CWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROMPT_LABEL, prompt);
}


BEGIN_MESSAGE_MAP(CWaitDlg, CDialog)
END_MESSAGE_MAP()


// CWaitDlg message handlers
