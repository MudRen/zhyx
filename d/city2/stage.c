#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "Ϸ̨");
	set("long", @LONG
������Ϸ̨����Ȼ��ЩС�����Ǻܸɾ���һ��Ϸ�����ڱ��ݡ�
��һ̤��Ϸ̨���鲻�Խ��ؾͳ��������
LONG );
	set("exits", ([
		"down" : __DIR__"xiyuan",
	        "southdown":__DIR__"houtai",
	]));
	set("objects", ([
		"/d/city2/npc/xizi": 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
        int i;

        if (! userp(me) || me->query_temp("hastryup"))
                return ::valid_leave(me, dir);

        if (dir=="down")
        {
                message_vision("\n$Nһ�����գ�һҾ��������ƽ�ɣ���̨"
                               "��Ծ����˫��أ��\n��ȭ�����������̬"
                               "������������Ȳɡ�\n", me);
                i = this_player()->query("meili");
                if (i<20)
                {
                        i += 10;
                        me->set("meili", i);
                        message_vision(HIC "\n$N������ֵ����ˡ�\n" NOR,
                                       me);
                }
        }

        return ::valid_leave(me, dir);
}
