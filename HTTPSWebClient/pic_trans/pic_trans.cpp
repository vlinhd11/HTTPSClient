
// pic_trans.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "pic_trans.h"
#include "pic_transDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpic_transApp

BEGIN_MESSAGE_MAP(Cpic_transApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cpic_transApp 构造

Cpic_transApp::Cpic_transApp()
{
	
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Cpic_transApp 对象

Cpic_transApp theApp;


// Cpic_transApp 初始化

BOOL Cpic_transApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项

	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	Cpic_transDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
