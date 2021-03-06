#include "StdAfx.h"
#include "Page.h"

CPage::CPage(void)
:reqStr(L"")
,reqData(L"")
,respStr(L"")
,status(-1)
,isGet(TRUE)
,size(MAX_DATA_SIZE)
{
	buff = new BYTE[MAX_DATA_SIZE];
}

CPage::~CPage(void)
{
	if(buff)
	{
		delete []buff;
		buff = NULL;
	}
}

void CPage::GetPageStr( CHTTPConnection& content )
{
	CLog& log = CLog::GetLog();
	BOOL sendResult;

	content.SetRefStr(refStr);
	if(isGet)
	{
		sendResult = content.SendDatabyGet(reqStr);
		log.AddLog(reqStr);
	}
	else
	{
		sendResult = content.SendDatabyPost(reqStr, reqData);
		log.AddLog(reqStr);
		log.AddLog(reqData);
	}
	if(sendResult == TRUE)
	{
		content.GetResponseStr(respStr);
		if(respStr.IsEmpty())
		{
			status = ERROR_SERVER;
			return;
		}
	}
	else
	{
		status = ERROR_HTTP;
		log.AddLog(L"send data failed.");
		return;
	}
	status = ERROR_OK;
}

int CPage::GetStatus()
{
	return status;
}

CString CPage::GetResponse()
{
	return respStr;
}

void CPage::GetPageData( CHTTPConnection& content )
{
	CLog& log = CLog::GetLog();
	BOOL sendResult;

	content.SetRefStr(refStr);
	if(isGet)
	{
		sendResult = content.SendDatabyGet(reqStr);
		log.AddLog(reqStr);
	}
	else
	{
		sendResult = content.SendDatabyPost(reqStr, reqData);
		log.AddLog(reqStr);
		log.AddLog(reqData);
	}
	if(sendResult == TRUE)
	{
		content.GetResponseRaw(buff, size);
		if(size == 0)
		{
			status = ERROR_SERVER;
			return;
		}
	}
	else
	{
		status = ERROR_HTTP;
		log.AddLog(L"send data failed.");
		return;
	}
	status = ERROR_OK;
}
