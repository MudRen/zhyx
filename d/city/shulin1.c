//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"����"NOR);
        set("long",@LONG
��Ȼ��ɫһת��ǰ������һƬ��������֡��㿴���˿����ܣ�
������Χ��Щ�ط���̫��ͷ������ȴ˵�ϲ����������������ƺ���
Щ��������������Ҫ��Ҫ��ȥ�أ��㲻�ɳ��������
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  "/d/wudang/wdroad1",
                "north" : __DIR__"shulin",
        ])); 
        set("objects", ([   
             __DIR__"npc/xdh-guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir)
{
    if (! userp(me) && objectp(present("shou wei", environment(me))) && dir == "north")
        return notify_fail("NPC����ȥ��\n");
    return ::valid_leave(me, dir);
}

