#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "����");
    set("long",
"���������������������������������Ϸ������������黹�Һ� \n"
"ɽ�ĺ��ҡ����������Ƕ�ž��ұ����ĸ����֡����˵��ˣ��������� \n"
"�����Ϲ��Ͼ���������ݡ�\n"
);
    set("no_fight", 1);
    set("no_steal", 1);
    set("no_sleep_room", 1);

    set("valid_startroom", 1);
    set("objects", ([
            //    "/u/xgchen/xmas/man" : 1,
               "/u/sanben/npc/bobo" : 1,
                __DIR__"obj/box" : 1,

    ]));

    set("exits", ([
        "east" : __DIR__"beidajie2",
        "up"   : __DIR__"wumiao2",
            //    "down" : "/d/wizard/herodoor"
    ]));
    set("coor/x",-10);
    set("coor/y",19);
    set("coor/z",0);
    setup();
    "/clone/board/wumiao_b"->foo(); 
    //replace_program(ROOM);
}
int valid_leave(object me, string dir) 
{ 
       
    if ( ! me->is_player() && dir == "up" ) return 0;
    
    return 1;
} 

