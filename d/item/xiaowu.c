// xiaoyuan.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang" 
#define MOYE            "/adm/npc/moye" 


void create()
{
        object ob;

	set("short", "铸剑室");
	set("long", @LONG
你一走进这个屋子，就感觉到有一股热浪扑面而来。屋角有一个炉子，
里面燃着熊熊火光，似乎无数的金蛇在你面前晃动。屋子并不大，远处穿着
古怪的一男一女，正是传说中的干将、莫邪夫妻。
LONG );

        set("no_fight", 1);
        set("no_sleep_room", 1);

	set("exits", ([
                "out" : __DIR__"road5",
	]));

        GANJIANG->come_here();
        MOYE->come_here();  

	setup();
        //replace_program(ROOM);
}