#include "main.h"
#include "my1010.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    srand(time(NULL));
    My1010 *tetris = new My1010(wxT("my1010"));
    tetris->Centre();
    tetris->Show(true);

    return true;
}
