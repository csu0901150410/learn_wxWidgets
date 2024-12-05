#include <wx/wx.h>

// APP��
class lsApp : public wxApp
{
public:
	virtual bool OnInit();
};

// ������
class lsFrame : public wxFrame
{
public:
	lsFrame(const wxString& title);

	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);

private:
	DECLARE_EVENT_TABLE()
};

// �¼�������
BEGIN_EVENT_TABLE(lsFrame, wxFrame)
	EVT_MENU(wxID_ABOUT, lsFrame::onAbout)
	EVT_MENU(wxID_EXIT, lsFrame::onQuit)
END_EVENT_TABLE()

lsFrame::lsFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// �˵���
	wxMenu* menuFile = new wxMenu;
	wxMenu* menuHelp = new wxMenu;

	menuFile->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
		wxT("Quit application"));

	menuHelp->Append(wxID_ABOUT, wxT("&About...\tF1"),
		wxT("Show about dialog"));

	// �˵���
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuHelp, wxT("&Help"));
	SetMenuBar(menuBar);

	// ״̬��
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

// Ϊ��ʹ��lsApp& wxGetApp()
DECLARE_APP(lsApp);

// ָ��app��
IMPLEMENT_APP(lsApp)
