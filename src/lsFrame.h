#pragma once

#include <wx/wx.h>

class lsCanvas;

// 窗口类
class lsFrame : public wxFrame
{
public:
	lsFrame();

	// 事件处理函数
	void OnOpen(wxCommandEvent& event);
	void OnZoomIn(wxCommandEvent& event);
	void OnZoomOut(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

private:
	wxToolBar* m_toolBar;
	lsCanvas* m_canvas;
};

enum
{
    ID_USER_CUSTOM = wxID_HIGHEST + 1,
	ID_TOOL_ADD_ARC,
	ID_ZOOM_IN,
	ID_ZOOM_OUT
};