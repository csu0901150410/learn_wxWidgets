#include "lsApp.h"
#include "lsFrame.h"

bool lsApp::OnInit()
{
    // Install some image handlers, mainly for help
    if( wxImage::FindHandler( wxBITMAP_TYPE_PNG ) == nullptr )
        wxImage::AddHandler( new wxPNGHandler );

    if( wxImage::FindHandler( wxBITMAP_TYPE_GIF ) == nullptr )
        wxImage::AddHandler( new wxGIFHandler );

    if( wxImage::FindHandler( wxBITMAP_TYPE_JPEG ) == nullptr )
        wxImage::AddHandler( new wxJPEGHandler );

	lsFrame* frame = new lsFrame();

    wxIcon icon;
    icon.LoadFile("resources/images/icons/app.ico", wxBITMAP_TYPE_ICO);
    frame->SetIcon(icon);

	frame->Show(true);
	return true;
}

int lsApp::OnExit()
{
	// 释放申请的资源
	return 0;
}
