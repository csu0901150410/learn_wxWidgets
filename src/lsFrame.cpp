#include <wx/artprov.h>
#include <wx/numdlg.h>

#include "lsFrame.h"
#include "lsImagePanel.h"
#include "lsUtils.h"
#include "lsDrawPanel.h"

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

    wxMenuItem *itemViewConsole = menuView->AppendCheckItem(ID_VIEW_CONSOLE, wxT("显示控制台\tCtrl+`"));
    itemViewConsole->Check(false);

    menuView->Append(ID_VIEW_OPEN_CAMERA, wxT("打开摄像头"));
    menuView->Append(ID_VIEW_CLOSE_CAMERA, wxT("关闭摄像头"));

    menuView->Append(ID_VIEW_REDRAW_CANVAS, wxT("重绘画布\tCtrl+R"));

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

    m_toolBar->AddSeparator();
    m_toolBar->AddTool(ID_VIEW_REDRAW_CANVAS, wxT("重绘画布"),
        wxArtProvider::GetBitmap(wxART_GO_HOME, wxART_TOOLBAR), wxT("重绘画布"));

    m_toolBar->Realize();

    // 创建状态栏
    CreateStatusBar();
    SetStatusText(wxT("就绪"));

    // 分隔器
    m_splitter = new wxSplitterWindow(this, wxID_ANY,
                                    wxDefaultPosition, wxDefaultSize,
                                    wxSP_3D | wxSP_LIVE_UPDATE);

    // 用容器包含画布
    wxPanel *canvasPanel = new wxPanel(m_splitter);
    wxBoxSizer *canvasSizer = new wxBoxSizer(wxVERTICAL);
	// m_imgpanel = new lsImagePanel(canvasPanel);
    // canvasSizer->Add(m_imgpanel, 1, wxEXPAND);
    m_canvas = new lsDrawPanel(canvasPanel);
    canvasSizer->Add(m_canvas, 1, wxEXPAND);
    canvasPanel->SetSizer(canvasSizer);

    // 控制台
    m_console = new wxTextCtrl(m_splitter, wxID_ANY, wxEmptyString,
                            wxDefaultPosition, wxSize(-1, m_lastSashPosition),
                            wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
    m_console->SetBackgroundColour(wxColor(53, 53, 53));
    m_console->SetForegroundColour(wxColor(0, 255, 0));
    m_console->Show(false);

    m_splitter->SplitHorizontally(canvasPanel, m_console, -m_lastSashPosition);
    m_splitter->SetMinimumPaneSize(150);
    m_splitter->SetSashGravity(0.5);

    // 主界面布局
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_splitter, 1, wxEXPAND);
    SetSizer(mainSizer);

	// 绑定事件处理函数
	Bind(wxEVT_MENU, &lsFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &lsFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &lsFrame::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_MENU, &lsFrame::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_MENU, &lsFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &lsFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &lsFrame::OnViewConsole, this, ID_VIEW_CONSOLE);

    Bind(wxEVT_MENU, &lsFrame::OnBinarize, this, ID_TOOL_BINARIZE);
    Bind(wxEVT_MENU, &lsFrame::OnOpenCamera, this, ID_VIEW_OPEN_CAMERA);
    Bind(wxEVT_MENU, &lsFrame::OnCloseCamera, this, ID_VIEW_CLOSE_CAMERA);
    Bind(wxEVT_MENU, &lsFrame::OnRedrawCanvas, this, ID_VIEW_REDRAW_CANVAS);

    // 绑定分隔条事件
    m_splitter->Bind(wxEVT_SPLITTER_SASH_POS_CHANGED, 
                    &lsFrame::OnSplitterSashPosChanged, 
                    this);

	Centre();

    Log(wxT("lsImagePanel ctor called!"));

    ShowConsole(false);
}

void lsFrame::OnOpen(wxCommandEvent &event)
{
	wxFileDialog openDialog(this, wxT("打开图片文件"), "", "",
		"图片文件|*.png;*.jpg;*.jpeg;*.bmp|所有文件|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openDialog.ShowModal() == wxID_OK)
	{
		m_imgpanel->LoadImage(openDialog.GetPath());
		SetStatusText(openDialog.GetPath());
	}

    Log(wxString::Format(wxT("Load image: %s"), openDialog.GetPath()));
}

void lsFrame::OnSave(wxCommandEvent &event)
{
    if (!m_imgpanel->HasImage())
    {
        wxMessageBox(wxT("没有可保存的图片！"), wxT("错误"), wxOK | wxICON_ERROR);
        return;
    }

    wxFileDialog saveDialog(this, wxT("保存图片"), "", "",
        "PNG文件(*.png)|*.png|JPEG文件(*.jpg)|*.jpg|BMP文件(*.bmp)|*.bmp",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveDialog.ShowModal() == wxID_OK)
    {
        if (!m_imgpanel->SaveImage(saveDialog.GetPath()))  // 修改为使用canvas的保存方法
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

void lsFrame::OnViewConsole(wxCommandEvent &event)
{
    ShowConsole(event.IsChecked());
}

void lsFrame::OnSplitterSashPosChanged(wxSplitterEvent &event)
{
    m_lastSashPosition = -m_splitter->GetSashPosition();
    event.Skip();
}

void lsFrame::OnBinarize(wxCommandEvent &event)
{
    if (!m_imgpanel->HasImage())
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
        if (m_imgpanel->Binarize(threshold))
        {
            SetStatusText(wxString::Format(wxT("图像已二值化 (阈值: %d)"), threshold));
        }
        else
        {
            wxMessageBox(wxT("二值化处理失败！"), wxT("错误"), wxOK | wxICON_ERROR);
        }
    }
}

void lsFrame::OnOpenCamera(wxCommandEvent &event)
{
    if (!m_imgpanel)
        return;

    if (m_imgpanel->OpenCamera(0))
    {
        Log(wxT("Camera open success!"));
    }
    else
    {
        Log(wxT("Camera open failed!"));
    }
}

void lsFrame::OnCloseCamera(wxCommandEvent &event)
{
    if (!m_imgpanel)
        return;
    
    m_imgpanel->CloseCamera();
    Log(wxT("Camera closed!"));
}

void lsFrame::OnRedrawCanvas(wxCommandEvent &event)
{
    m_canvas->Redraw();
}

void lsFrame::ShowConsole(bool show)
{
    if (show)
    {
        if (m_splitter->IsSplit())
            return;
        
        wxWindow* upperPanel = m_splitter->GetWindow1();
        m_splitter->SplitHorizontally(upperPanel, m_console, -m_lastSashPosition);
    }
    else
    {
        if (!m_splitter->IsSplit())
            return;
        m_lastSashPosition = -m_splitter->GetSashPosition();
        m_splitter->Unsplit(m_console);
    }
    Layout();
}

bool lsFrame::IsConsoleShown() const
{
    return m_console ? m_console->IsShown() : false;
}

void lsFrame::Log(const wxString &message)
{
    if (!m_console)
        return;

    wxDateTime now = wxDateTime::Now();
    wxString timestamp = now.FormatTime();
    m_console->AppendText(wxString::Format("[%s] %s\n", timestamp, message));
    m_console->ShowPosition(m_console->GetLastPosition());
}
