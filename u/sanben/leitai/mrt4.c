#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIY"������--��ؤ��"NOR);
        set("long",
"��������ŵ����ڶ����ֱ�ؤ�ĵ��������ܴ������\n"
"�ɽ���ȡ����֮���ڴ�������ĵ���Ϊ���˳Ƶ���\n"); 
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);      
	set("objects", ([
                __DIR__"npc4" : 1,
	]));
	set("exits", ([		
		"south" : __DIR__"mrt5",            
	]));	
	setup(); 
}
