// by yuchang
#include <ansi.h>  
inherit ROOM;
void create()
{
        set("short", "宝库");
        set("long", @LONG  
这是一个宽阔的密封地室，室顶四角均有通气口，两边 
平排放置共几十个箱子，贴墙有几十个兵器架(jia)，放满
各种兵器 ,足够装备一个几千人的军队了!
LONG); 
        set("item_desc", ([           
          "jia" : "兵器架上有几块石头特别吸引人，你要拿(pick)出来看看吗?\n",  
        ]));
        set("exits", ([
                "up" : __DIR__"baoku",
        ]));
        
        setup();
}
void init()
{    
     add_action("do_pick", "pick"); 
 } 


int do_pick(string arg)
{
    object stone, me = this_player();

     

    if( !arg || arg != "stone" )
        return notify_fail("你是想(pick stone)吗?\n");
                             
    if( me->query("reborn_start/ygbz/stone") )
        return notify_fail("你不是已经拿到一块女娲石了吗?\n");

    message_vision(HIY"$N从兵器架上拿下一块石头!\n\n"NOR, me);
    stone = new(__DIR__"obj/kaitian-jian");
    stone->move(me);   
    me->set("reborn_start/ygbz/stone", 1);

    message("visione", HBRED HIW"【宝藏传闻】" + me->query("name") + 
              "在杨公宝库里找到开女娲石了!\n"NOR,users()); 

    remove_call_out("get_out");
    call_out("get_out", 2, me);
    return 1; 
}

void get_out(object me)
{
     message_vision(HIC"突然$N的脚底下裂开一个洞，$N掉了下去。\n"NOR, me); 
     me->move("/d/changan/bei-chengmen"); 

}