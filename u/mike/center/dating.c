#include <ansi.h>
inherit ROOM;

       void create() 
       { 
                   set("short", HIY "\n中华英雄会员服务大厅" NOR);                  
                   set("long", HIW "这里便是中华英雄会员服务大厅，正东方是一块巨大的玻璃门，\n"
                               "远远望去可以看见里面的会员购物中心。\n" NOR);
                   set("objects", ([
                           __DIR__"npc/yubo"  :  1,
                   ]));
                   set("exits", ([
                           "east"  :  __DIR__"sell",
                           "out"  :  __DIR__"out_center",
                   ]));

                   setup();     
       } 

int valid_leave(object me, string dir)
{
        me = this_player();
        if ( dir == "enter" && objectp(present("ji xixi", environment(me)))
             && ! me->query("is_member"))
                return notify_fail(HIG "纪惜惜跳了出来，说道：“非中华英雄会员不得入内”。\n" NOR);

        return ::valid_leave(me, dir);
}

