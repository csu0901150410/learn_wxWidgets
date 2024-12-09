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
	frame->Show(true);
	return true;
}

int lsApp::OnExit()
{
	// 释放申请的资源
	return 0;
}
