#include"Block.h"

namespace Game
{
  Block::Block()//Ĭ�Ϲ��캯��
    :color{default_block().color},
     wait_to_clean{default_block().wait_to_clean}
  {};

  Block::Block(int cc,bool ww):color{cc},wait_to_clean{ww}{}

  const Block& default_block()//Ĭ��Block
  {
    static Block bb{no_color,false};//�ı�Block�Ժ�Ҫ�ǵø�ѽ����
    return bb;
  }
}
