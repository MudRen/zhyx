//  for huanjing1/room_door_hj.c
//  by naihe  2002-11-07

#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
    set_name(MAG"�þ���Ϸ���԰�"NOR, ({ "board" }) );
    set("location", "/u/naihe/huanjing1_pro/room_door_hj");
    set("board_id", "huanjing1_b");
    set("long", "�����԰�Ϊ��ҽ���������Ϸ�ĵá�������Ϸ��BUG�Լ���ʦ���漰�ظ�����;��\n" );
    setup();
    set("capacity", 500);
    replace_program(BULLETIN_BOARD);
}

