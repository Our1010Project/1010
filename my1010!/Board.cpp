#include "Board.h"

Board::Board(wxFrame *parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition,wxDefaultSize, wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);

    m_stsbar = parent->GetStatusBar();
    isFallingFinished = false;
    isStarted = false;
    isPaused = false;
    numLinesRemoved = 0;
    curX = 0;
    curY = 0;

    ClearBoard();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
}

void Board::Start()
{
    if (isPaused)
        return;

    isStarted = true;
    isFallingFinished = false;
    numLinesRemoved = 0;
    ClearBoard();

    generate_block();
    timer->Start(300);
}

void Board::Pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer->Stop();
        m_stsbar->SetStatusText(wxT("paused"));
    } else {
        timer->Start(3000);
        wxString str;
        str.Printf(wxT("%d"), numLinesRemoved);
        m_stsbar->SetStatusText(str);
    }
    Refresh();
}


void Board::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    int boardTop = size.GetHeight() - BoardHeight * square_height();


    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            Colours block = block_at(j, BoardHeight - i - 1);
            if (block != no_colour)
                DrawSquare(dc, 0 + j * square_width(),
                           boardTop + i * square_height(),block);
        }
    }//there is something down,but i delet

}

void Board::OnKeyDown(wxKeyEvent& event)
{
    if (!isStarted || cur_piece.get_block() == no_colour) {
        event.Skip();
        return;
    }

    int keycode = event.GetKeyCode();

    if (keycode == 'p' || keycode == 'P') {
	Pause();
        return;
    }

    if (isPaused)
        return;

    switch (keycode) {
    case WXK_LEFT:
        try_move(cur_piece, curX - 1, curY);
        break;
    case WXK_RIGHT:
        try_move(cur_piece, curX + 1, curY);
        break;
    case 'D':case 'd':case WXK_DOWN:
        OneLineDown();
        break;
    default:
        event.Skip();
    }

}

void Board::OnTimer(wxCommandEvent& event)
{
    if (isFallingFinished) {
        isFallingFinished = false;
        generate_block();
    } else {
        OneLineDown();
    }
}

void Board::ClearBoard()
{
    for (int i=0;i<BoardWidth;i++)
    {
        for (int j=0;j<BoardHeight-1;j++)
        {
            board[i][j]=no_colour;
        }
    }
}

void Board::DropDown()
{
    int newY = curY;
    while (newY > 0) {
        if (!try_move(cur_piece, curX, newY - 1))
            {break;}
        --newY;
    }
    PieceDropped();
}

void Board::OneLineDown()
{
    if (!try_move(cur_piece, curX, curY - 1))
        PieceDropped();
}

void Board::PieceDropped()
{

        int x = curX ;
        int y = curY ;
       block_at(x, y) = cur_piece.get_block();


    //RemoveFullLines();

    if (!isFallingFinished)
        generate_block();
}

void Board::generate_block()
{
    for (int i=0;i<BoardWidth;i++)
    {
        cur_piece.set_random_colour();
        board[i][BoardHeight-1]=cur_piece.pieceblock;
    }
}

bool Board::try_move(const Block& new_piece,int newX ,int newY)
{
    if (newX < 0 || newX >= BoardWidth || newY < 0 || newY >= BoardHeight-1)
            return false;
    if (block_at(newX, newY) != no_colour)
            return false;

    cur_piece = new_piece;
    curX = newX;
    curY = newY;
    Refresh();
    return true;
}

void Board::DrawSquare(wxPaintDC& dc, int x, int y, Colours block)
{
    static wxColour colors[] = { wxColour(0, 0, 0), wxColour(204, 102, 102),
             wxColour(102, 204, 102), wxColour(102, 102, 204),
             wxColour(204, 204, 102), wxColour(204, 102, 204),
             wxColour(102, 204, 204), wxColour(218, 170, 0) };

    static wxColour light[] = { wxColour(0, 0, 0), wxColour(248, 159, 171),
             wxColour(121, 252, 121), wxColour(121, 121, 252),
             wxColour(252, 252, 121), wxColour(252, 121, 252),
             wxColour(121, 252, 252), wxColour(252, 198, 0) };

    static wxColour dark[] = { wxColour(0, 0, 0), wxColour(128, 59, 59),
             wxColour(59, 128, 59), wxColour(59, 59, 128),
             wxColour(128, 128, 59), wxColour(128, 59, 128),
             wxColour(59, 128, 128), wxColour(128, 98, 0) };


    wxPen pen(light[int(block)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + square_height() - 1, x, y);
    dc.DrawLine(x, y, x + square_width() - 1, y);

    wxPen darkpen(dark[int(block)]);
    darkpen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkpen);

    dc.DrawLine(x + 1, y + square_height() - 1,
        x + square_width() - 1, y + square_height() - 1);
    dc.DrawLine(x + square_width() - 1,
        y + square_height() - 1, x + square_width() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(block)]));
    dc.DrawRectangle(x + 1, y + 1, square_width() - 2,
        square_height() - 2);
}
