#include <ansi.h> 
inherit ROOM;
string look_gaoshi();

void create ()
{
        set ("short", "比武场大门");
        set ("long", @LONG
这是〖中华英雄〗比武场的大门，一座高高的木制牌坊，上书『比武场』
三个镏金大字。这里经常举办各种类型的比武大会。所有的人都有机会参
加。门旁边贴一张告示(gaoshi)。
LONG);
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
        set("no_fight",1);
        set("no_clean_up",1);
        set("exits", ([
                "north"   : __DIR__"zoulang",
                "south"   : "/d/city/ximenroad",
        ]));
        set("objects", ([
                __DIR__"npc/gongping" : 1,
        ]));
        setup();
}

string look_gaoshi()
{
        object ob;

        return "比武场命令：玩家可以使用：\n
		"HIY" chaxun 命令"NOR" 查询比赛相关信息。\n
		"HIY" canjia 命令"NOR" 参加比赛。\n
		"HIY" menpai 命令"NOR" 申请门派比赛。\n";
}


int valid_leave(object me, string dir)
{
        object ob, where;

        if (!where=find_object(__DIR__"gate"))
                where=load_object(__DIR__"gate");
        ob=present("gongping zi", where);
    
        if ( !wizardp(me) && dir=="north" ) {
        if (!present("men piao", me))
        {
                return notify_fail(CYN"公平子说道：对不起，阁下没有门票。\n"NOR);
        }
                if(me->query("snowzongshi"))
                        return ::valid_leave(me, dir);
                if( ob->query("fangshi")!="个人赛" && !ob->query("start/start"))
                        return notify_fail("现在没有任何比武，你不能进去。\n");
        }
        return ::valid_leave(me, dir);
}

