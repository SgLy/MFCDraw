#pragma once
#include "afxwin.h"

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"


// CRoomListDlg dialog

class CRoomListDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomListDlg)

public:
	CRoomListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoomListDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox room_list;
	CString selected_ip;
	afx_msg void OnBnClickedOk();
};
