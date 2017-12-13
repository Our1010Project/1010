#ifndef _GAME_H
#define _GAME_H

#include "Block.h"
#include "Clean.h"

namespace Game
{
  class Run{
  private:
    Block table[row_number][column_number];// 定义名为table的二维数组，7*13，
                                           //第0行用于存储当前列的最高行数
  };
}


#endif // _GAME_H
