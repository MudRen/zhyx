#include <ansi.h>

inherit BULLETIN_BOARD;

void create()
{
      set_name(HIG"�������԰�"NOR, ({ "board" }) );
      set("location", "/u/sanben/workroom");
      set("board_id", "sanben_b");
      set("long", YEL"�������������������ĺ���\n"
          "�������߱�Ϊ����������������ͬ����Ҳ��\n"NOR );
      setup();
      set("capacity", 100);
      replace_program(BULLETIN_BOARD);
}
