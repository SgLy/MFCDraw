// RoomListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "RoomListDlg.h"
#include "afxdialogex.h"
#include "MFCDrawView.h"


// CRoomListDlg dialog

IMPLEMENT_DYNAMIC(CRoomListDlg, CDialog)

CRoomListDlg::CRoomListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG3, pParent)
{
}

CRoomListDlg::~CRoomListDlg()
{
}

void CRoomListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROOM_LIST, room_list);
}


BEGIN_MESSAGE_MAP(CRoomListDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRoomListDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRoomListDlg message handlers


void CRoomListDlg::OnBnClickedOk()
{
	if (room_list.GetCurSel() == LB_ERR)
		return;
	room_list.GetText(room_list.GetCurSel(), selected_ip);
	CDialog::OnOK();
}