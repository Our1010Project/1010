#include "my1010.h"
#include "Board.h"

My1010::My1010(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(294, 1029))
{
  wxStatusBar *sb = CreateStatusBar();
  sb->SetStatusText(wxT("score:0"));
  Board *board = new Board(this);
  board->SetFocus();
  board->Start();
}
