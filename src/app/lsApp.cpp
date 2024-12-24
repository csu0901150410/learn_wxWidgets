#include "lsApp.h"
#include "lsFrame.h"

#include "lsDebug.h"

bool lsApp::OnInit()
{
    LS_DEBUG->print("lsApp::OnInit() -- format : %s", "test");

	lsFrame* frame = new lsFrame();
    wxIcon icon;
    icon.LoadFile("resources/images/icons/app.ico", wxBITMAP_TYPE_ICO);
    frame->SetIcon(icon);
    frame->SetAutoLayout(true);
	frame->Show(true);

	return true;
}

int lsApp::OnExit()
{
	// 释放申请的资源
	return 0;
}

// 指定app类
IMPLEMENT_APP(lsApp)
