#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name( HIG" ����  "+HIR"��ˮ��"NOR, ({ "board" }) );
        set("location", "/u/kan/workroom");
        set("board_id", "shc_b");
        set("long", HIR"�� ּ �� ˮ ��Υ �� �� ն ��\n"NOR );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
