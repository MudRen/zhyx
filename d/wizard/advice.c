#include <ansi.h>
inherit ROOM;
int is_chat_room()      { return 1;}
void create()
{
       set("short", HIY "�л�Ӣ�ۿͷ���" NOR);
        set("long", HIY "\n\n"
"��Ϸ�����������⼰��Ϸ��չ�����������POST�����\n\n" NOR);
 
           /*  set("objects", ([ 
                     "/u/dgdg/npc/gifter" :1,       
                     "/u/dgdg/npc/lottery" :1,                               
              ])); */
        set("exits", ([
                "down" : "/d/city/kedian",
                "up":"/d/wizard/noname_room",
        ]));
                set("no_fight", 1);
                set("no_sleep_room",1);
        setup();
        "/clone/board/advice_b"->foo();

}




