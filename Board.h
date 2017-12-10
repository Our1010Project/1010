#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Shape.h"
#include <wx/wx.h>


class Board : public wxPanel
{
public:
    Board(wxFrame *parent);
    void Start();
    void Pause();

protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    enum { BoardWidth = 6, BoardHeight = 21 };

    Colours & block_at(int x,int y){return board [x][y];}

    int square_width(){return GetClientSize().GetWidth() / BoardWidth;}
    int square_height(){return GetClientSize().GetHeight() / BoardHeight;}

    void ClearBoard();
    void PieceDropped();
    void DropDown();
    void OneLineDown();
    void generate_block();
    bool try_move(const Block& new_piece,int newX ,int newY);
    void DrawSquare(wxPaintDC &dc, int x, int y, Colours block);

    wxTimer *timer;
    bool isStarted;
    bool isPaused;
    bool isFallingFinished;
    int curX;
    int curY;
    int numLinesRemoved;
    Block cur_piece;
    Colours board[BoardWidth][BoardHeight];
    wxStatusBar *m_stsbar;

};

#endif // BOARD_H_INCLUDED
