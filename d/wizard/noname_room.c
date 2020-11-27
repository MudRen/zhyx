// /d/wizard/guest_room.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "����������" NOR);
	set("long", @LONG
��������������Ը���վ��ʦ���ֲ���������ҿ�������
ô������������(post)��������ҽ����ܿ����������ԣ�����
�������Ծٱ��������id������������Ϊ����վ��ʦ��Ϊ����
������ȫ���ܡ�
LONG );

	set("exits", ([
		//"north": __DIR__"herodoor",
        "down": "/d/wizard/advice",
        "up": __DIR__"wizard_room",
        ]));

	set("no_fight", 1);

	setup();
	"/clone/board/noname_b"->foo();
}

int valid_leave(object me, string dir)
{
	if (dir == "up" && ! wizardp(me))
		return notify_fail("����������磬ֻ����ʦ������ȥ��\n");

	return ::valid_leave(me, dir);
}


