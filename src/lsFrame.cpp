#include <wx/artprov.h>

#include "lsFrame.h"
#include "lsCanvas.h"
#include "lsUtils.h"

lsFrame::lsFrame()
	: wxFrame(nullptr, wxID_ANY, wxT("OCV Image Viewer"), wxDefaultPosition, wxSize(800, 600))
{
	// 初始化图片处理器
	wxInitAllImageHandlers();

	// 创建菜单栏
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, wxT("打开\tCtrl+O"));
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, wxT("退出\tAlt+F4"));

    wxMenu* menuView = new wxMenu;
    menuView->Append(ID_ZOOM_IN, wxT("放大\tCtrl++"));
    menuView->Append(ID_ZOOM_OUT, wxT("缩小\tCtrl+-"));

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, wxT("关于"));

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("文件"));
    menuBar->Append(menuView, wxT("查看"));
    menuBar->Append(menuHelp, wxT("帮助"));
    SetMenuBar(menuBar);

    // 创建工具栏
    m_toolBar = CreateToolBar();
    m_toolBar->AddTool(wxID_OPEN, wxT("打开"), 
        wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR));
    m_toolBar->AddTool(wxID_SAVE, wxT("保存"), 
        wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR));
    m_toolBar->AddSeparator();
    m_toolBar->AddTool(ID_ZOOM_IN, wxT("放大"), 
        wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR));
    m_toolBar->AddTool(ID_ZOOM_OUT, wxT("缩小"), 
        wxArtProvider::GetBitmap(wxART_MINUS, wxART_TOOLBAR));
	m_toolBar->AddTool(ID_TOOL_ADD_ARC, wxT("添加圆弧"),
		GetBitmap(wxT("resources/images/icons/add_arc_32.png")));
    m_toolBar->Realize();

    // 创建状态栏
    CreateStatusBar();
    SetStatusText(wxT("就绪"));

	// 创建图片显示面板
	m_canvas = new lsCanvas(this);

	// 绑定事件处理函数
	Bind(wxEVT_MENU, &lsFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &lsFrame::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_MENU, &lsFrame::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_MENU, &lsFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &lsFrame::OnExit, this, wxID_EXIT);
}

void lsFrame::OnOpen(wxCommandEvent &event)
{
	wxFileDialog openDialog(this, wxT("打开图片文件"), "", "",
		"图片文件|*.png;*.jpg;*.jpeg;*.bmp|所有文件|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openDialog.ShowModal() == wxID_OK)
	{
		m_canvas->LoadImage(openDialog.GetPath());
		SetStatusText(openDialog.GetPath());
	}
}

void lsFrame::OnZoomIn(wxCommandEvent &event)
{
	// 放大
}

void lsFrame::OnZoomOut(wxCommandEvent &event)
{
	// 缩小
}

void lsFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox(wxT("OpenCV图片查看器"), wxT("关于"), wxOK | wxICON_INFORMATION);
}

void lsFrame::OnExit(wxCommandEvent &event)
{
	Close(true);
}
