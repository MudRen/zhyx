#include <ansi.h>
inherit ROOM;

       void create() 
       { 
                   set("short", HIY "\n�л�Ӣ�ۻ�Ա��������" NOR);                  
                   set("long", HIW "��������л�Ӣ�ۻ�Ա�������ģ���ǰ����һ��޴�Ĳ����ţ�\n"
                               "ԶԶ��ȥ���Կ�������Ļ�Ա���������\n" NOR);
                   set("objects", ([
                           __DIR__"npc/tian"  :  1,
                   ]));
                   set("exits", ([
                           "enter"  :  __DIR__"dating",
                   ]));

                   setup();     
       } 

int valid_leave(object me, string dir)
{
        me = this_player();
        if ( dir == "enter" && objectp(present("ji xixi", environment(me)))
             && ! me->query("is_member"))
                return notify_fail(HIG "��ϧϧ���˳�����˵���������л�Ӣ�ۻ�Ա�������ڡ���\n" NOR);

        return ::valid_leave(me, dir);
}

