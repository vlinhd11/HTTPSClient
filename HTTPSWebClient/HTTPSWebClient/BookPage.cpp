#include "StdAfx.h"
#include "BookPage.h"

CBookPage::CBookPage(void)
{
	isGet = FALSE;
}

CBookPage::~CBookPage(void)
{
}

void CBookPage::BuildRequest( TrainInfo& input )
{
	reqStr = L"/otsweb/order/querySingleAction.do?method=submutOrderRequest";
 	reqData.Format(L"station_train_code=%s"
 		L"&train_date=%s"
 		L"&seattype_num="
 		L"&from_station_telecode=%s"
 		L"&to_station_telecode=%s"
 		L"&include_student=00"
 		L"&from_station_telecode_name=%s"
 		L"&to_station_telecode_name=%s"
 		L"&round_train_date=%s"
 		L"&round_start_time_str=00%%3A00--24%%3A00"
 		L"&single_round_type=1"
 		L"&train_pass_type=QB"
 		L"&train_class_arr=QB%%23D%%23Z%%23T%%23K%%23QT%%23"
 		L"&start_time_str=00%%3A00--24%%3A00"
 		L"&lishi=%s"
 		L"&train_start_time=%s"
 		L"&trainno4=%s"
 		L"&arrive_time=%s"
 		L"&from_station_name=%s"
 		L"&to_station_name=%s"
 		L"&from_station_no=%s"
 		L"&to_station_no=%s"
 		L"&ypInfoDetail=%s"
 		L"&mmStr=%s"
 		L"&locationCode=%s",
 		input.trainCode,
 		input.trainDate,
 		input.stationFromCode,
 		input.stationToCode,
 		stationFromTeNameGet(input),
 		stationToTeNameGet(input),
 		input.trainRoundDate,
 		durationGet(input),
 		trainStartTimeGet(input),
 		input.trainNo,
 		timeArriveGet(input),
 		stationFromNameGet(input),
 		stationToNameGet(input),
 		input.stationFromNo,
 		input.stationToNo,
 		input.infoDetail,
 		input.mmStr,
 		input.locationCode
 		);
	refStr = L"/otsweb/order/querySingleAction.do?method=init";
}

void CBookPage::ParseOutput( TicketInfo& output )
{
	if(status != ERROR_OK)
		return;

	// search for unpaid order
	if(respStr.Find(L"还有未处理的订单") != -1)
	{
		status = ERROR_ORDER;
		return;
	}
	// split results
	CRegex regex;
	CString pattern, restStr, matchStr;

	matchStr = respStr;

	pattern = L"org\\.apache\\.struts\\.taglib\\.html\\.TOKEN\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.token);
	matchStr = restStr;

	pattern = L"left_ticket\\\"\\b*\\n\\b*value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.leftTicketStr);
	matchStr = restStr;

	pattern = L"orderRequest\\.train_date\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.train_date);
	matchStr = restStr;

	pattern = L"orderRequest\\.train_no\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.train_no);
	matchStr = restStr;

	pattern = L"orderRequest\\.station_train_code\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.station_train_code);
	matchStr = restStr;

	pattern = L"orderRequest\\.from_station_telecode\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.from_station_telecode);
	matchStr = restStr;

	pattern = L"orderRequest\\.to_station_telecode\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.to_station_telecode);
	matchStr = restStr;

	pattern = L"orderRequest\\.bed_level_order_num\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.bed_level_order_num);
	matchStr = restStr;

	pattern = L"orderRequest\\.start_time\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.start_time);
	matchStr = restStr;

	pattern = L"orderRequest\\.end_time\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.end_time);
	matchStr = restStr;

	pattern = L"orderRequest\\.from_station_name\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.from_station_name);
	matchStr = restStr;

	pattern = L"orderRequest\\.to_station_name\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.to_station_name);
	matchStr = restStr;

	pattern = L"orderRequest\\.cancel_flag\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.cancel_flag);
	matchStr = restStr;

	pattern = L"orderRequest\\.id_mode\\\" value=\\\"{[^\\\"]+}\\\"";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.id_mode);
	matchStr = restStr;

	// add seat type select logic
	pattern = L"id=\"passenger_1_seat\">{.+?}</select>";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	CString seatOptions;
	regex.matchGet(0, seatOptions);
	matchStr = restStr;

	// find proper seat
	// priority: <passenger select>, O, M, 9, 3, 4, 2, 1
	for(int i = 0; i < output.passengers.GetCount(); i++)
	{
		CString& passenger_seat = output.passengers[i].seatTyp;
		if(seatOptions.Find(passenger_seat) != -1)
		{
			// this is what passenger want!
		}
		else if(seatOptions.Find(L"O") != -1)
		{
			passenger_seat = L"O";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <second class seat> instead");
		}
		else if(seatOptions.Find(L"M") != -1)
		{
			passenger_seat = L"M";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <first class seat> instead");
		}
		else if(seatOptions.Find(L"9") != -1)
		{
			passenger_seat = L"9";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <business seat> instead");
		}
		else if(seatOptions.Find(L"3") != -1)
		{
			passenger_seat = L"3";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <hard sleeper> instead");
		}
		else if(seatOptions.Find(L"4") != -1)
		{
			passenger_seat = L"4";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <soft sleeper> instead");
		}
		else if(seatOptions.Find(L"2") != -1)
		{
			passenger_seat = L"2";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <soft seat> instead");
		}
		else if(seatOptions.Find(L"1") != -1)
		{
			passenger_seat = L"1";
			CLog::GetLog().AddLog(L"cannot find passenger select, use <hard seat> instead");
		}
		else
		{
			// oops, can't find a proper seat
			CLog::GetLog().AddLog(L"cannot find a proper seat!");
			CLog::GetLog().AddLog(seatOptions);
			status = ERROR_NOSEAT;
			return;
		}
	}

	pattern = L"submit_form_confirm\\(\\\'confirmPassenger\\\',\\\'{[^\\\']+}\\\'";
	regex.patternLoad(pattern);
	if(regex.contextMatch(matchStr, restStr) == FALSE)
	{
		CLog::GetLog().AddLog(L"ticket info cannot found!");
		status = ERROR_GENERAL;
		return;
	}
	regex.matchGet(0, output.tFlag);
	matchStr = restStr;


	status = ERROR_OK;
	CLog::GetLog().AddLog(L"book page success!");
}
CString CBookPage::stationFromTeNameGet( TrainInfo& input )
{
	return GetUTF8Str(input.stationFromTeName);
}

CString CBookPage::stationToTeNameGet( TrainInfo& input )
{
	return GetUTF8Str(input.stationToTeName);
}

CString CBookPage::durationGet( TrainInfo& input )
{
	CString str = input.duration;
	str.Replace(L":", L"%3A");
	return str;
}

CString CBookPage::trainStartTimeGet( TrainInfo& input )
{
	CString str = input.trainStartTime;
	str.Replace(L":", L"%3A");
	return str;
}

CString CBookPage::timeArriveGet( TrainInfo& input )
{
	CString str = input.timeArrive;
	str.Replace(L":", L"%3A");
	return str;
}

CString CBookPage::stationFromNameGet( TrainInfo& input )
{
	return GetUTF8Str(input.stationFromName);
}

CString CBookPage::stationToNameGet( TrainInfo& input )
{
	return GetUTF8Str(input.stationToName);
}
