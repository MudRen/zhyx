#include <ansi.h>
inherit ROOM;
string haha();
void create()
{
        set("short", HIY "Ìì×ðÊ¥µî" NOR);
     set("long", haha());

        set("exits", ([
                "down" : "/d/city/guangchang",
                "up"   : "/d/beijing/tiananmen",
                "west" : "/d/wizard/guest_room",
                "east" : "/d/city/kedian",
        ]));

set("no_fight", 1);
        set("valid_startroom", 1);
        set("sleep_room", 1);

        setup();
               "/clone/board/yuchang_b"->foo(); 
}
string haha()
{ string msg="123454";
return msg;}

