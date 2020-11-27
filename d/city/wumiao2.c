#include <room.h>
#include <ansi.h>
inherit ROOM;


void create()
{
	set("short", "�����¥");
	set("long", @LONG
������������Ķ�¥�����﹩�������ɵĳ������ƺ�����
���ܣ�����������������Ӣ��������
LONG);

	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);

	set("exits", ([
		"down" : __DIR__"wumiao",              
	]));
    set("objects", ([
                "/u/sanben/xquest/npc/zixu" : 1,
    ]));
	set("coor/x",-10);
	set("coor/y",19);
	set("coor/z",10);
	setup();

    // "/u/baqukq/baqukq_b"->foo();
        //replace_program(ROOM);
}


int valid_leave(object me, string dir) 
{ 
    int i, ban;
    object *obj;
    ban = 0;
   
    if ( ! me->is_player() ) return 0;
    if (objectp(present("zixu daoren", environment(me))) && dir == "up") 
    {
       obj = deep_inventory(me);
       for(i=0;i<sizeof(obj);i++)
       {          
           if ( ! clonep(obj[i]) ) ban = 1;            
       }
    } 
    if ( ban == 1 )
    return notify_fail(HIR"���������ס��˵����������������߻�Ψһ������Ʒ�����ô�����䳡�ء�\n\n"NOR);  
    else          
    return ::valid_leave(me, dir); 
} 
