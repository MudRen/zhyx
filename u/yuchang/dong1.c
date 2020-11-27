// Room: /u/yuchang/dong1.c
// BY Yuchang

#include <ansi.h>

inherit ROOM; 

string* dirs = ({"east", "south", "west", "north"});

void create()
{
	set("short", HIR "�����" NOR);
        set("long", HIR "\n\n" 
"��������ߡ������پ�һ��������������������������\n"
"��ȥ������һƬͨ�죬������ð��˿˿�������ŵ׾��ҵ���ʹ\n"
"ʹ�㼸�����Ų�ס���ȷ����¡¡�������Ŷ��ģ��������\n"
"�����¯֮�У�ȫ���ˮ�ֶ��ڱ�һ�εεؿ��ɡ���е�����\n" 
"�������ȥ����\n\n" NOR 
     ); 
        set("exits", ([
                "east"      : __DIR__"dong1",
                "south"     : __DIR__"dong2",
                "west"      : __DIR__"dong1",
                "north"     : __DIR__"dong1",
	]));
        set("no_clean_up", 0);
        set("no_rideto",1);
         set("no_drop", 1);
        set("no_stab", 1); 
        setup();
}

void init()
{
        this_player()->set_temp("die_reason", "��������ߣ�������������");
        this_player()->receive_damage("qi", 1000);
        this_player()->receive_wound("qi",  1000);
        message_vision(HIR "ͻȻ����ȼ�������һ�����Ϯ��$N��\n" NOR, this_player());
}

int valid_leave(object me, string dir)
{
	int count;

	if (member_array(dir, dirs) != -1)
	{
		if (dir == "west")
		{
//			write("*��˽�*\n");
			me->move("/d/city/wumiao");
			return notify_fail("��������أ��ص�������\n");
		}
	}
	return ::valid_leave(me, dir);
}

