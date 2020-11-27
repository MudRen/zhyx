#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "������ǰ");
        set("long",@LONG
�����������˳ɶ��ֲ��Ĵ���ǰ�棬�����˵ĳɶ��ֲ�����λ
�ü��ã���ӳ����ɽ��ˮ֮�䡣����һ����߷��Ľ��������˾�
��һ�������ƴ������֮�䡣          
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "west" :  __DIR__"eastroad3",
                "east" : __DIR__"xym_cddt",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if (! me->query_temp("good_xym2") && me->query("bang_good/name") != "������")
               return notify_fail("����һ����ס�㣬�����ȵ��������������������˵���������\n"); 
           else
           {
              me->delete_temp("good_xym2");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

