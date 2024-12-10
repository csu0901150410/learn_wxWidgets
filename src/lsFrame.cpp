#include <wx/artprov.h>
#include <wx/numdlg.h>

#include "lsFrame.h"
#include "lsCanvas.h"
#include "lsUtils.h"

lsFrame::lsFrame()
	: wxFrame(nullptr, wxID_ANY, wxT("OCV Image Viewer"), wxDefaultPosition, wxSize(1920, 1080))
{
	// 初始化图片处理器
	wxInitAllImageHandlers();

	// 创建菜单栏
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, wxT("打开\tCtrl+O"));
    menuFile->Append(wxID_SAVE, wxT("保存\tCtrl+S"));
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
        wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), wxT("打开图像文件"));
    m_toolBar->SetToolLongHelp(wxID_OPEN, wxT("打开一个图像文件(支持PNG、JPG/JPEG、BMP等格式)"));

    m_toolBar->AddTool(wxID_SAVE, wxT("保存"), 
        wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), wxT("保存图像文件"));
    m_toolBar->SetToolLongHelp(wxID_SAVE, wxT("将工作区图像保存到文件"));

    m_toolBar->AddSeparator();
    m_toolBar->AddTool(ID_ZOOM_IN, wxT("放大"), 
        wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR), wxT("放大工作区图像"));
    m_toolBar->SetToolLongHelp(ID_ZOOM_IN, wxT("放大工作区图像(快捷键: Ctrl++)"));

    m_toolBar->AddTool(ID_ZOOM_OUT, wxT("缩小"), 
        wxArtProvider::GetBitmap(wxART_MINUS, wxART_TOOLBAR), wxT("缩小工作区图像"));
    m_toolBar->SetToolLongHelp(ID_ZOOM_OUT, wxT("缩小工作区图像(快捷键: Ctrl+-)"));

	m_toolBar->AddTool(ID_TOOL_BINARIZE, wxT("二值化"),
		GetBitmap(wxT("resources/images/icons/add_arc_32.png")), wxT("二值化工作区图像"));
    m_toolBar->SetToolLongHelp(ID_TOOL_BINARIZE, wxT("二值化工作区图像(阈值: 127)"));

    m_toolBar->Realize();

    // 创建状态栏
    CreateStatusBar();
    SetStatusText(wxT("就绪"));

	// 创建图片显示面板
	m_canvas = new lsCanvas(this);

	// 绑定事件处理函数
	Bind(wxEVT_MENU, &lsFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &lsFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &lsFrame::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_MENU, &lsFrame::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_MENU, &lsFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &lsFrame::OnExit, this, wxID_EXIT);

    Bind(wxEVT_MENU, &lsFrame::OnBinarize, this, ID_TOOL_BINARIZE);

	Centre();
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

void lsFrame::OnSave(wxCommandEvent &event)
{
    if (!m_canvas->HasImage())
    {
        wxMessageBox(wxT("没有可保存的图片！"), wxT("错误"), wxOK | wxICON_ERROR);
        return;
    }

    wxFileDialog saveDialog(this, wxT("保存图片"), "", "",
        "PNG文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg|BMP文件(*.bmp)|*.bmp",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveDialog.ShowModal() == wxID_OK)
    {
        if (!m_canvas->SaveImage(saveDialog.GetPath()))  // 修改为使用canvas的保存方法
        {
            wxMessageBox(wxT("保存图片失败！"), wxT("错误"), wxOK | wxICON_ERROR);
        }
        else
        {
            SetStatusText(wxT("图片已保存至: ") + saveDialog.GetPath());
        }
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

void lsFrame::OnBinarize(wxCommandEvent &event)
{
    if (!m_canvas->HasImage())
    {
        wxMessageBox(wxT("没有可处理的图片！"), wxT("错误"), wxOK | wxICON_ERROR);
        return;
    }

    // 弹出阈值设置对话框
    wxNumberEntryDialog dlg(this,
        wxT("请输入二值化阈值:"),
        wxT("阈值 (0-255):"),
        wxT("二值化设置"),
        128, 0, 255);

    if (dlg.ShowModal() == wxID_OK)
    {
        int threshold = dlg.GetValue();
        if (m_canvas->Binarize(threshold))
        {
            SetStatusText(wxString::Format(wxT("图像已二值化 (阈值: %d)"), threshold));
        }
        else
        {
            wxMessageBox(wxT("二值化处理失败！"), wxT("错误"), wxOK | wxICON_ERROR);
        }
    }
}
