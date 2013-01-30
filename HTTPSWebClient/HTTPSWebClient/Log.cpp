#include "StdAfx.h"
#include "Log.h"

CLog::CLog(void)
{
	CString fileName;
	fileName.Format(L"http_%x.log", GetCurrentProcessId());
	//fileName.Format(L"http.log");
	logFile.Open(fileName, 
	CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::shareDenyWrite);
	logFile.SeekToEnd();
}

CLog::CLog( const CLog& log )
{

}

CLog::~CLog(void)
{
	logFile.Close();
}

void CLog::AddLog( CString content )
{
	// format
	// [2013.01.01 12:59:59] <log content>
	CTime currentTime = CTime::GetCurrentTime();
	CString str = currentTime.Format(L"[%Y.%m.%d %H:%M:%S] ");
	logFile.Write(str.GetString(), str.GetLength()*sizeof(TCHAR));
	logFile.Write(content.GetString(), content.GetLength()*sizeof(TCHAR));
	str = L"\r\n";
	logFile.Write(str.GetString(), str.GetLength()*sizeof(TCHAR));
}

CLog& CLog::GetLog()
{
	static CLog log;
	return log;
}

CLog& CLog::operator=( CLog const& log )
{
	return GetLog();
}
