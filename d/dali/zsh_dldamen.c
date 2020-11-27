//zsh_dldamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "ǰ��");
        set("long",@LONG
���������������ֻ����ڵء����������������֮�ٵõ�����
���ڶ�������ʿ�ĳ��ޣ���а��֮�������ջ̡̻���཭���ú���Ľ
���������������������֮�����Բ��Ϸ�չ׳��
LONG );
        set("outdoors", "dali");
        set("exits", ([    
                "south"  :  __DIR__"zsh_dlfh",
                "east"   :  __DIR__"dahejiewest",
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

