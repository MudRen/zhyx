#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIY"������"NOR);
        set("long",
"��������ŵ��������ֵĵ��������ܴ���������е��κ�һ��Ҳ\n"
"�Խ�����ȡ����֮���ڴ�������ĵ���Ϊ���˳Ƶ���\n\n"); 
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);      
	set("objects", ([
                __DIR__"npc1" : 1,
                __DIR__"npc2" : 1,
                __DIR__"npc3" : 1,
                __DIR__"npc4" : 1,
                __DIR__"npc5" : 1,  
	]));
	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
                "down" : "/d/wizard/herodoor"
	]));	
	setup(); 
}
