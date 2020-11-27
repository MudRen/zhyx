#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ԯ����"NOR);
        set("long", @LONG
������ǡ��ɹš���Ӫפ�����ˣ�ԶԶ�ؿ��Կ�����Ӫ�ڷ���ĳ�������
ʱ�м�ƥ����ɱ��������������ٿ�����Ȼವ�һö�������ͷ�Ϸɹ�������
�Ͽ��뿪�ĺá�
LONG
);
        set("defence",120);
        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south"  : __DIR__"caoyuan4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
}

void init()
{
        object me = this_player();

        if (me->query_temp("jun_quest/party") == "song")
                add_action("do_break", "break");
}

int do_break()
{
        object room = this_object(), me = this_player();

        if (me->is_busy())
                return notify_fail("����æ���أ�\n");

        if (room->query("exits/north"))
                return notify_fail("ԯ�ŵĵķ����Ѿ��������ˣ�����ȥ����\n");

        if (room->query("defence") < 1)
        {
                room->set("defence", 0);
                tell_object(me, HIR "ԯ�ŵĵķ����Ѿ��������ˣ�����ȥ����\n" NOR);
                room->set("exits/north", __DIR__"mying");
                call_out("door_close", 20, room);
                return 1;
        } else
        {
                message_vision(
                        HIY "$N����һ֧���Ƕ������ӽ�������ԯ�ŵķ������£�\n" NOR, me);
                room->add("defence", -random(me->query_temp("jun_quest/group")));
                me->start_busy(2 + random(2));
                return 1;
        }
}

void door_close(object room)
{
        if (room->query("exits/north"))
        {
                room->delete("exits/north");
                tell_object(all_inventory(room),
                        HIW "�ɹž���æ����һ֧�����ԯ�ŵķ��������޺��ˣ�\n" NOR);
        }
        return;
}


