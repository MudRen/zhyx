#include <room.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����£�ԭ����������Ժ���ֽ��˽��¡�������������������ӵ
��Ȼͦ�������ɽ�������ͻص�����ϡ�
LONG);
        set("exits", ([
            	"west"   : __DIR__"road15",
            	"enter"   : __DIR__"jingci",
        ]));
        set("no_clean_up", 0);
        set("coor/x",195);
	set("coor/y",-420);
        set("coor/z",0);
	setup();
        //replace_program(ROOM);
}