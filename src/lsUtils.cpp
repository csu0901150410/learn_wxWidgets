#include "lsUtils.h"

wxBitmap GetBitmap(const wxString &name)
{
    wxImage image(name, wxBITMAP_TYPE_PNG);
    return wxBitmap(image);
}
