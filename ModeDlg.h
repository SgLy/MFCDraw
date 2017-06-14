#pragma once


// CModeDlg dialog

class CModeDlg : public CDialog
{
	DECLARE_DYNAMIC(CModeDlg)

public:
	CModeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNewRoom();
	afx_msg void OnBnClickedRoomList();
};
