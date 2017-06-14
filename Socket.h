#pragma once

// Socket command target
#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

class Socket : public CAsyncSocket
{
public:
	Socket(CMFCDrawView*);
	virtual ~Socket();
	virtual void OnConnect(int nErrorCode);
private:
	CMFCDrawView * father;
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	void error(int nErrorCode);
};


