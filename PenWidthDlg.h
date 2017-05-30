#pragma once


// CPenWidthDlg dialog

class CPenWidthDlg : public CDialog
{
	DECLARE_DYNAMIC(CPenWidthDlg)

public:
	virtual BOOL OnInitDialog();
	CPenWidthDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenWidthDlg();
	int maxPenWidth;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int penWidth_dlg;
};
