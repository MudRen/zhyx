#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name(HIY "����ʮ�ػƽ��" NOR, ({ "wall" }) );
        set("location", "/u/yuchang/workroom");
        set("board_id", "yuchang_b");
        set("long", HIY "���ǽ�Ͽ�����ϣ��Źֵ����ģ�Ҳ��֪��������Щʲô��\n" NOR);
        setup();
        set("capacity", 3000);
        replace_program(BULLETIN_BOARD);
}

