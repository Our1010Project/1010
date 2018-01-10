#include "Board.h"
#include<vector>
#include<algorithm>
#include<iostream>


using namespace std ;

Board::Board(wxFrame *parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition,wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    timer = new wxTimer(this, 1);

    m_stsbar = parent->GetStatusBar();
    isFallingFinished = false;
    isCleanFinished=true;
    isAdjustFinished=true;
    isJumpFinished=true;
    isStarted = false;
    isPaused = false;
    score=0;
    scoreLevel=0;
    numLinesRemoved = 0;

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
    isCleanFinished=true;
    isAdjustFinished=true;
    isJumpFinished=true;
    score=0;
    scoreLevel=0;
    numLinesRemoved = 0;
    ClearBoard();

    generate_block();
    timer->Start(200);
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
        timer->Start(200);
        wxString str;
        str.Printf(wxT("%d"), score);
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
        for (int j = curJ; j < BoardWidth; ++j) {
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
        scoreLevel=0;
        if (can_be_cleaned()) {isCleanFinished=false;}
        break;
    default:
        event.Skip();
    }

}

void Board::OnTimer(wxCommandEvent& event)
{
    /*if (isFallingFinished) {
        isFallingFinished = false;
    }*/
    bool next{true};//即本轮是否进行过动作，是否继续往下检测
    if (!isCleanFinished) {clean();next=false;}
    if (next&&!isAdjustFinished) {adjust();next=false;}
    if (next&&!isJumpFinished) {jump();next=false;}
    Refresh();
    for (int i=0;i<BoardWidth;i++)
    {   if (height(i)==BoardHeight-2)
        {timer->Stop();
        isStarted = false;
        wxString str;
        str.Printf(wxT("Game Over.Total score:%d"), numLinesRemoved);
        m_stsbar->SetStatusText(str);
        return;}
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
    isFallingFinished=true;

}

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

//////////////////////////////////////////////////////////////////////////////////
void Board::adjust()
{
  isAdjustFinished=true;
  for (int x=0;x<BoardWidth;++x)
  {
      for (int y=0;y<BoardHeight-1;++y)
      {
        if (board[x][y].colour==no_colour)
        {
            int CurrentHeight{y};//当前待填空位置
            for (int k=y;k<BoardHeight-1;++k){
                if (board[x][k].colour!=no_colour){
                     block_at(x,CurrentHeight)=block_at(x,k);
                     block_at(x,k)=default_property();
                     isAdjustFinished=false;
                     break;
                }
            }
        }
        if (!isAdjustFinished) break;
      }
      if (!isAdjustFinished) break;
  }
  if (isAdjustFinished)
    {if (can_be_cleaned()) {isCleanFinished=false;}
      else isJumpFinished=false;}
}

void Board::clean()
{
  board[clean_list[clean_list.size()-2]][clean_list[clean_list.size()-1]].colour=no_colour;
  clean_list.pop_back();
  clean_list.pop_back();
  if (clean_list.size()==0) {isCleanFinished=true;isAdjustFinished=false;}
}

void Board::scan(int x,int y,vector<int>&same_color_list)
    {
      if (same_color(x,y,x,y+1))             //up
        if (!board[x][y+1].already_scaned){
          same_color_list.push_back(x);
          same_color_list.push_back(y+1);
          board[x][y+1].already_scaned=true;
          scan(x,y+1,same_color_list);
        }
      if (same_color(x,y,x,y-1))             //down
        if (!board[x][y-1].already_scaned){
          same_color_list.push_back(x);
          same_color_list.push_back(y-1);
          board[x][y-1].already_scaned=true;
          scan(x,y-1,same_color_list);
        }
      if (same_color(x,y,x-1,y))             //left
        if (!board[x-1][y].already_scaned){
          same_color_list.push_back(x-1);
          same_color_list.push_back(y);
          board[x-1][y].already_scaned=true;
          scan(x-1,y,same_color_list);
        }
      if (same_color(x,y,x+1,y))             //right
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
      clean_list.clear();
      for (int x=0;x<BoardWidth;++x)
      for (int y=0;y<height(x);++y){
        board[x][y].already_scaned=false;
      }
      for (int x=0;x<BoardWidth;++x)
      for (int y=0;y<height(x);++y){
        if (!board[x][y].already_scaned)
        {
          vector<int> same_color_list{x,y};
          board[x][y].already_scaned=true;
          scan(x,y,same_color_list);
          if (same_color_list.size()>=6){
              cb_cleaned=true;
              isCleanFinished=false;
              for (int i=0;i<same_color_list.size();++i)
              {
                clean_list.push_back(same_color_list[i]);
              }
              switch(same_color_list.size()/2)
              {
              case 3: case 4:
                scoreLevel+=1;
                score+=same_color_list.size()*2;
                break;
              case 5: case 6:
                scoreLevel+=2;
                score+=same_color_list.size()*3;
                break;
              case 8: case 9:
                scoreLevel+=3;
                score+=same_color_list.size()*4;
                break;
              default:
                scoreLevel+=4;
                score+=same_color_list.size()*5;
                break;
              }
              wxString str;
              str.Printf(wxT("score:%d"),score);
              m_stsbar->SetStatusText(str);
              Refresh();
          }
        }
      }
      return cb_cleaned;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////

void Board::jump()
{
  bool next{true};
  if (can_jump_l()) {jump_to_l();next=false;}
  if (next&&can_jump_r()) {jump_to_r();next=false;}
  if (next) {isJumpFinished=true;}
}

bool Board::can_jump_l(){
   for(int x=1;x<BoardWidth;++x){
      if (jump_left(x)) return true;
   }
   return false;
}

bool Board::can_jump_r(){
   for(int x=0;x<BoardWidth-1;++x){
      if (jump_right(x)) return true;
   }
   return false;
}

bool Board::jump_left(int x){
    if (height(x)-height(x-1)>1)return true;
    else return false;
}

bool Board::jump_right(int x){
    if (height(x)-height(x+1)>1)return true;
    else return false;
}

int Board::next_to_jump_l(){
    int y=0;
    for(int x=1;x<BoardWidth;++x){
       if(jump_left(x)) {y=x;break;}}
    for(int x=y;x<BoardWidth;++x){
       if(jump_left(x)&&height(x)>height(y)) {y=x;}}
    return y;
}

int Board::next_to_jump_r(){
    int y=0;
    for(int x=0;x<BoardWidth-1;++x){
       if(jump_right(x)) {y=x;break;}}
    for(int x=0;x<BoardWidth-1;++x){
       if(jump_right(x)&&height(x)>height(y)) {y=x;}}
    return y;
}

void Board::jump_to_l(){
   int x=next_to_jump_l();
   board[x-1][height(x-1)].colour=board[x][height(x)-1].colour;
   board[x][height(x)-1].colour=no_colour;
}

void Board::jump_to_r(){
   int x=next_to_jump_r();
   board[x+1][height(x+1)].colour=board[x][height(x)-1].colour;
   board[x][height(x)-1].colour=no_colour;
}

/////////////////////////////////////////////////////////////////////

/*void Board::tryRemove()
{
   while
}*/
