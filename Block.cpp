#include"Block.h"

namespace Game
{
  Block::Block()//默认构造函数
    :color{default_block().color},
     wait_to_clean{default_block().wait_to_clean}
  {};

  Block::Block(int cc,bool ww):color{cc},wait_to_clean{ww}{}

  const Block& default_block()//默认Block
  {
    static Block bb{no_color,false};//改变Block以后要记得改呀！！
    return bb;
  }
}
