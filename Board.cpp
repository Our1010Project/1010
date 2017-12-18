#include "Board.h"
#include<vector>

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
        timer->Start(300);
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
            Property block = block_at(j, BoardHeight - i - 1);
            if (block.colour != no_colour)
                DrawSquare(dc, 0 + j * square_width(),
                           boardTop + i * square_height(),block);
        }
    }//there is something down,but i delet
/*    if (cur_piece.get_block()!=no_colour)
    {
        int x=curX+cur_piece.x(cur_piece.pieceblock);
        int y=curY;
        DrawSquare(dc, 0 + x * square_width(),
                boardTop + (BoardHeight - y - 1) * square_height(),
                cur_piece.get_block());
    }*/

}

void Board::OnKeyDown(wxKeyEvent& event)
{
    if (!isStarted ) {
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
        move_l();
        break;
    case WXK_RIGHT:
        move_r();
        break;
    case 'D':case 'd':case WXK_DOWN:
        OneLineDown();
        while (can_be_cleaned()) {clean();}
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
        return;
    }
}

void Board::ClearBoard()
{
    for (int i=0;i<BoardWidth;i++)
    {
        for (int j=0;j<BoardHeight-1;j++)
        {
            block_at(i,j)=default_property();
        }
    }
}

void Board::DropDown(int index)
{
    int h=Board::height(index);
    block_at(index,h)=block_at(index,BoardHeight-1);
}

void Board::OneLineDown()
{
    for (int i=0;i<BoardWidth;i++)
    {
        Board::DropDown(i);
    }
    Refresh();
    generate_block();
}

/*void Board::PieceDropped()
{
       int x = curX+cur_piece.x(cur_piece.pieceblock) ;
       int y = curY ;
       block_at(x,y)=cur_piece.get_block();

    //RemoveFullLines();
    if (!isFallingFinished)
        generate_block();
}*/

void Board::generate_block()
{
    for (int i=0;i<BoardWidth;i++)
    {
        cur_piece.set_random_colour();
        board[i][BoardHeight-1]=cur_piece.pieceblock;
    }
}

int Board::height(int index)
{
    int i{0};
    while(board[index][i].colour!=no_colour)
    {
        i++;
    }
    return i;
}

void Board::move_l()
{
    Property cor[BoardWidth];
    for (int i=0;i<BoardWidth;i++)
    {
        cor[i]=board[i][BoardHeight-1];
    }
    for(int i=0;i<BoardWidth;i++)
    {
       board[i][BoardHeight-1]=cor[(i+1)%6];
    }
    Refresh();
}

void Board::move_r()
{
    Property cor[BoardWidth];
    for (int i=0;i<BoardWidth;i++)
    {
        cor[i]=board[i][BoardHeight-1];
    }
    //board[0][BoardHeight-1]=cor[BoardWidth-1];
    for(int i=0;i<BoardWidth;i++)
    {
       board[i][BoardHeight-1]=cor[(i+5)%6];
    }
    Refresh();
}
/*
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
}*/

void Board::DrawSquare(wxPaintDC& dc, int x, int y, Property block)
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


    wxPen pen(light[int(block.colour)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + square_height() - 1, x, y);
    dc.DrawLine(x, y, x + square_width() - 1, y);

    wxPen darkpen(dark[int(block.colour)]);
    darkpen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkpen);

    dc.DrawLine(x + 1, y + square_height() - 1,
        x + square_width() - 1, y + square_height() - 1);
    dc.DrawLine(x + square_width() - 1,
        y + square_height() - 1, x + square_width() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(block.colour)]));
    dc.DrawRectangle(x + 1, y + 1, square_width() - 2,
        square_height() - 2);
}

//CLEAN_ZWY
void Board::clean()
{
    for (int x=0;x<BoardWidth;++x)
        for (int y=0;y<BoardHeight-1;++y)
    {
        if (board[x][y].colour==no_colour)
        {
            int CurrentHeight{y};//当前待填空位置
            for (int k=y;k<BoardHeight-1;++k)
                if (board[x][k].colour!=no_colour){
                     block_at(x,CurrentHeight)=block_at(x,k);
                     block_at(x,k)=default_property();
                     ++CurrentHeight;
                     Refresh();
                }
            break;//退出这一层循环
        }
    }
}

void Board::scan(int x,int y,vector<int>&same_color_list)
    {
      if (same_color(x,y,x,y+1))             //上
        if (!board[x][y+1].already_scaned){
          same_color_list.push_back(x);
          same_color_list.push_back(y+1);
          board[x][y+1].already_scaned=true;
          scan(x,y+1,same_color_list);
        }
      if (same_color(x,y,x,y-1))             //下
        if (!board[x][y-1].already_scaned){
          same_color_list.push_back(x);
          same_color_list.push_back(y-1);
          board[x][y-1].already_scaned=true;
          scan(x,y-1,same_color_list);
        }
      if (same_color(x,y,x-1,y))             //左
        if (!board[x-1][y].already_scaned){
          same_color_list.push_back(x-1);
          same_color_list.push_back(y);
          board[x-1][y].already_scaned=true;
          scan(x-1,y,same_color_list);
        }
      if (same_color(x,y,x+1,y))             //右
        if (!board[x+1][y].already_scaned){
          same_color_list.push_back(x+1);
          same_color_list.push_back(y);
          board[x+1][y].already_scaned=true;
          scan(x+1,y,same_color_list);
        }

    }

bool Board::same_color(int x1,int y1,int x2,int y2)
    {
      if (0<=x2&&x2<BoardWidth)
        if (0<=y2&&y2<BoardHeight-1)//最高行数待改
          if (board[x1][y1].colour==board[x2][y2].colour){
            return true;
          }
      return false;
    }

bool Board::can_be_cleaned()
    {
      bool cb_cleaned{false};
      for (int x=0;x<BoardWidth;++x)
      for (int y=0;y<height(x);++y){
        board[x][y].already_scaned=false;
        board[x][y].wait_to_clean=false;
      }

      for (int x=0;x<BoardWidth;++x)
      for (int y=0;y<height(x);++y){
        if (!board[x][y].already_scaned)
        {
          vector<int> same_color_list{x,y};
          board[x][y].already_scaned=true;
          scan(x,y,same_color_list);
          if (same_color_list.size()>=6){                                    //以后在这里可以加算分数
              cb_cleaned=true;
              for(int k=0;k<same_color_list.size();k+=2){
                board[same_color_list[k]][same_color_list[k+1]].wait_to_clean=true;
                board[same_color_list[k]][same_color_list[k+1]].colour=no_colour;
              }
              Refresh();
          }
        }
      }
      return cb_cleaned;
    }

