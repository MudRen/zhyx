inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "������ջ");
        set("long", @LONG
���Ǿ��ǻ���·��ͷ�ڽֵ�һ�ҿ�ջ����ջ����ǰ������һ���ͻ���ɽ
�ľ޻������Ź��Ŷ�ԧ��������ϵ�ż���СС�Ļ�ͭ���塣΢���ӹ�������
��������ö��Ķ����������к�����������ջ����
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("objects", ([
                __DIR__"npc/xiaoer3" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"fu_2",
                  "north" : __DIR__"kediandayuan",
        ]));
        set("no_clean_up", 0);
        set("coor/x",-10);
	set("coor/y",981);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{
	if (! me->query_temp("rent_paid") && dir == "north")
	        return notify_fail(CYN "��С��һ�µ�������ǰ������һ���������ţ����ס����\n" NOR);
	if (me->query_temp("rent_paid") && dir == "south")
	        return notify_fail(CYN "��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ�\n" NOR);

	return ::valid_leave(me, dir);
}
*/
