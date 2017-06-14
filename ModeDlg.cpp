// ModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "ModeDlg.h"
#include "afxdialogex.h"


// CModeDlg dialog

IMPLEMENT_DYNAMIC(CModeDlg, CDialog)

CModeDlg::CModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CModeDlg::~CModeDlg()
{
}

void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialog)
	ON_BN_CLICKED(ID_NEW_ROOM, &CModeDlg::OnBnClickedNewRoom)
	ON_BN_CLICKED(ID_ROOM_LIST, &CModeDlg::OnBnClickedRoomList)
END_MESSAGE_MAP()


// CModeDlg message handlers


void CModeDlg::OnBnClickedNewRoom()
{
	EndDialog(3);
}


void CModeDlg::OnBnClickedRoomList()
{
	EndDialog(4);
}
