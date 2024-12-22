﻿#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>

#ifndef LS_USE_CV
#endif

#ifdef LS_USE_CV
class lsImagePanel;
#endif

class lsDrawPanel;

// 窗口类
class lsFrame : public wxFrame
{
public:
	lsFrame();

	// 事件处理函数
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnZoomIn(wxCommandEvent& event);
	void OnZoomOut(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnViewConsole(wxCommandEvent& event);
	void OnSplitterSashPosChanged(wxSplitterEvent& event);

#ifdef LS_USE_CV
	void OnBinarize(wxCommandEvent& event);
	void OnOpenCamera(wxCommandEvent& event);
	void OnCloseCamera(wxCommandEvent& event);
#endif

	void OnRedrawCanvas(wxCommandEvent& event);

	void ShowConsole(bool show);
	bool IsConsoleShown() const;
	void Log(const wxString& message);

private:
	wxToolBar* m_toolBar;
	wxSplitterWindow* m_splitter;// 分隔的窗口，上边是绘图区，下边是控制台
	wxTextCtrl *m_console;
	lsDrawPanel* m_canvas;
	int m_lastSashPosition = 300;

#ifdef LS_USE_CV
	lsImagePanel* m_imgpanel;
#endif
};

enum
{
    ID_USER_CUSTOM = wxID_HIGHEST + 1,
	ID_ZOOM_IN,
	ID_ZOOM_OUT,
	ID_VIEW_CONSOLE,

#ifdef LS_USE_CV
	ID_TOOL_BINARIZE,
	ID_VIEW_OPEN_CAMERA,
	ID_VIEW_CLOSE_CAMERA,
#endif

	ID_VIEW_REDRAW_CANVAS
};