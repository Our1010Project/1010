#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Shape.h"
#include <wx/wx.h>
#include <vector>

using std::vector;

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

    Property & block_at(int x,int y){return board [x][y];}

    int square_width(){return GetClientSize().GetWidth() / BoardWidth;}
    int square_height(){return GetClientSize().GetHeight() / BoardHeight;}

    void ClearBoard();
    void PieceDropped();
    void DropDown(int index);
    void OneLineDown();
    void generate_block();
    bool try_move(const Block& new_piece,int newX ,int newY);
    void DrawSquare(wxPaintDC &dc, int x, int y, Property block);

    void move_l();
    void move_r();
    int height(int index);

    wxTimer *timer;
    bool isStarted;
    bool isPaused;
    bool isFallingFinished;
    int curX;
    int curY;
    int numLinesRemoved;
    Block cur_piece;
    Property board[BoardWidth][BoardHeight];
    wxStatusBar *m_stsbar;

    //CLEAN_ZWY
    void clean();
    void scan(int x,int y,vector<int>& same_color_list);

    bool can_be_cleaned();
    bool same_color(int x1,int y1,int x2,int y2);//(x1,y1):当前，(x2,y2):周围格子

    bool can_jump_l();
    bool can_jump_r();
    bool jump_left(int x);
    bool jump_right(int x);

    int next_to_jump_l();
    int next_to_jump_r();
    void jump_to_l();
    void jump_to_r();
};

#endif // BOARD_H_INCLUDED
