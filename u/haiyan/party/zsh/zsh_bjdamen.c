//zsh_bjdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "ǰ��");
        set("long",@LONG
�����������ᱱ���ֻ����ڵء��������������������֮�£���
�����Ϸ�չ׳����཭���ú���Ľ��������
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "south"  :  __DIR__"zsh_bjfh",
                "north"  :  __DIR__"yong_3",
        ])); 
        set("objects", ([   
             "/d/suzhou/npc/zsh_guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "south") 
        {
           if (! me->query_temp("good_zsh") && me->query("bang_good/name") != "������")
               return notify_fail("����һ����ס�㣺���������᲻��ӭ���ˣ���ذɣ���\n"); 
           else
           {
              me->delete_temp("good_zsh");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

