#pragma once

// Socket command target

class Socket : public CAsyncSocket
{
public:
	Socket();
	virtual ~Socket();
	virtual void OnConnect(int nErrorCode);
};


