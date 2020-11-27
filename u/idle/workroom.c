#include <ansi.h> 
#include <room.h>
inherit ROOM; 

int is_chat_room() 
{
        return 1; 
}

void create()
{       object ob;
        set("short", HIY "\n\n                发呆居" NOR);
        set("long", HIY "\n\n"
"    空荡荡、白茫茫的一片，什么也没有。\n" NOR
);

        set("exits", ([
                 "gc" : "/d/city/guangchang", 
                   "kd" : "/d/city/kedian",                
        ]));

        set("no_fight", 1);
        set("valid_startroom", 1);
        set("sleep_room", 1);
        set("chat_room",1);
        set("valid_startroom", 1); 

        setup();
}
