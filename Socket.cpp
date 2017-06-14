// Socket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "Socket.h"


// Socket

Socket::Socket(CMFCDrawView* f) :
	father(f)
{
}

Socket::~Socket()
{
}


// Socket member functions

void Socket::error(int nErrorCode)
{
	if (0 != nErrorCode) {
	switch (nErrorCode)	{
		case WSAEADDRINUSE:
			AfxMessageBox(_T("The specified address is already in use.\n"));
			break;
		case WSAEADDRNOTAVAIL:
			AfxMessageBox(_T("The specified address is not available from ")
				_T("the local machine.\n"));
			break;
		case WSAEAFNOSUPPORT:
			AfxMessageBox(_T("Addresses in the specified family cannot be ")
				_T("used with this socket.\n"));
			break;
		case WSAECONNREFUSED:
			AfxMessageBox(_T("The attempt to connect was forcefully rejected.\n"));
			break;
		case WSAEDESTADDRREQ:
			AfxMessageBox(_T("A destination address is required.\n"));
			break;
		case WSAEFAULT:
			AfxMessageBox(_T("The lpSockAddrLen argument is incorrect.\n"));
			break;
		case WSAEINVAL:
			AfxMessageBox(_T("The socket is already bound to an address.\n"));
			break;
		case WSAEISCONN:
			AfxMessageBox(_T("The socket is already connected.\n"));
			break;
		case WSAEMFILE:
			AfxMessageBox(_T("No more file descriptors are available.\n"));
			break;
		case WSAENETUNREACH:
			AfxMessageBox(_T("The network cannot be reached from this host ")
				_T("at this time.\n"));
			break;
		case WSAENOBUFS:
			AfxMessageBox(_T("No buffer space is available. The socket ")
				_T("cannot be connected.\n"));
			break;
		case WSAENOTCONN:
			AfxMessageBox(_T("The socket is not connected.\n"));
			break;
		case WSAENOTSOCK:
			AfxMessageBox(_T("The descriptor is a file, not a socket.\n"));
			break;
		case WSAETIMEDOUT:
			AfxMessageBox(_T("The attempt to connect timed out without ")
				_T("establishing a connection. \n"));
			break;
		case WSAEACCES:
			AfxMessageBox(_T("Permission denied.\n"));
			break;
		default:
			TCHAR szError[256];
			_stprintf_s(szError, _T("Socket error: %d"), nErrorCode);
			AfxMessageBox(szError);
			break;
		}
	}
}

void Socket::OnConnect(int nErrorCode)
{
	error(nErrorCode);
	CAsyncSocket::OnConnect(nErrorCode);
}



void Socket::OnReceive(int nErrorCode)
{
	error(nErrorCode);
	if (nErrorCode == 0) // �޴��󣬵��öԻ����OnReceive����
		father->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}


void Socket::OnSend(int nErrorCode)
{
	error(nErrorCode);
	CAsyncSocket::OnSend(nErrorCode);
}
