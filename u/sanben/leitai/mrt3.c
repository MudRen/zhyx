#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIY"������--�ϵ۾�"NOR);
        set("long",
"��������ŵ������������ϵ۵ĵ��������ܴ������\n"
"�ɽ���ȡ����֮���ڴ�������ĵ���Ϊ���˳Ƶ���\n"); 
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);      
	set("objects", ([
                __DIR__"npc3" : 1,
	]));
	set("exits", ([		
		"north" : __DIR__"mrt5",            
	]));	
	setup(); 
}
