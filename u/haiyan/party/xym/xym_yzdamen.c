//xym_yzdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "��  ��");
        set("long",@LONG
���������������ݷֶ�Ĵ��ţ�һ�����ӭ����չ�����顰��
���񾡡��ĸ����֡�
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "south" :  "/d/city/ximenroad",
                "north" : __DIR__"xym_yzfb",
        ])); 
        set("objects", ([   
             __DIR__"xym_guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if (! me->query_temp("good_xym") && me->query("bang_good/name") != "������")
               return notify_fail("����һ����ס�㣬�����ȵ��������������������˵���������\n"); 
           else
           {
              me->delete_temp("good_xym");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

