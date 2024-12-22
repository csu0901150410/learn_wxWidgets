#pragma once

#include <wx/wx.h>

// APP类
class lsApp : public wxApp
{
public:
	virtual bool OnInit();

	virtual int OnExit();
};

// 为了使用lsApp& wxGetApp()
DECLARE_APP(lsApp);
