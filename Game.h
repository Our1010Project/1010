#ifndef _GAME_H
#define _GAME_H

#include "Block.h"
#include "Clean.h"

namespace Game
{
  class Run{
  private:
    Block table[row_number][column_number];// ������Ϊtable�Ķ�ά���飬7*13��
                                           //��0�����ڴ洢��ǰ�е��������
  };
}


#endif // _GAME_H
