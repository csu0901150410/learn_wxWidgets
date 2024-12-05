#include <wx/wx.h>

// APP类
class lsApp : public wxApp
{
public:
	virtual bool OnInit();
};

// 窗口类
class lsFrame : public wxFrame
{
public:
	lsFrame(const wxString& title);

	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()
};

// 事件驱动表
BEGIN_EVENT_TABLE(lsFrame, wxFrame)
	EVT_MENU(wxID_ABOUT, lsFrame::onAbout)
	EVT_MENU(wxID_EXIT, lsFrame::onQuit)
END_EVENT_TABLE()

lsFrame::lsFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// 菜单项
	wxMenu* menuFile = new wxMenu;
	wxMenu* menuHelp = new wxMenu;

	menuFile->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
		wxT("Quit application"));

	menuHelp->Append(wxID_ABOUT, wxT("&About...\tF1"),
		wxT("Show about dialog"));

	// 菜单栏
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menuBar);

	// 状态栏
	CreateStatusBar(1);
	SetStatusText(wxT("Welcom to wxWidgets!"));
}

void lsFrame::onQuit(wxCommandEvent& event)
{
	Close();
}

void lsFrame::onAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("Welcome to %s"),
		wxVERSION_STRING);
	wxMessageBox(msg, wxT("About"), wxOK | wxICON_INFORMATION, this);
}

bool lsApp::OnInit()
{
	lsFrame* frame = new lsFrame(wxT("wxWidgets App"));
	frame->Show(true);
	return true;
}

// 为了使用lsApp& wxGetApp()
DECLARE_APP(lsApp);

// 指定app类
IMPLEMENT_APP(lsApp)
