#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIY"名人堂--西毒居"NOR);
        set("long",
"这里放置着当世第四高手西毒的雕像，若你能打败他则\n"
"可将他取而代之，在此立起你的雕像为后人称道。\n"); 
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);      
	set("objects", ([
                __DIR__"npc2" : 1,
	]));
	set("exits", ([		
		"east" : __DIR__"mrt5",            
	]));	
	setup(); 
}
