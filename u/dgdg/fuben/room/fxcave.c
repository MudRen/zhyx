#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "【伏羲洞】" NOR);
        set("long", HIW @LONG

                     伏羲洞

    这是伏羲退位人皇后隐居的洞天福地。伏羲正在抚琴，琴音令你身心一阵舒服。
竟然精神一振。洞口长着一丛九转还魂草，令洞口很难发现。


LONG NOR );

     set("exits", ([
                
                "south" : "/u/dgdg/fuben/room/sncave",
]));
       
        set("sleep_room", 1);
        set("objects", ([
                "/u/dgdg/fuben/npc/fuxi": 1,
               
               
        ]));
      
        setup();
}

void init()
{
        add_action("do_move", "touxi");
        add_action("do_move", "hit");
        add_action("do_yun","yun");
        add_action("do_yun","exert");
        add_action("do_move","guard");
        add_action("do_move","steal");
}



 	 int do_move(string arg) 
      { 
              object paper, 
              me = this_player(); 
       
              if (! arg || arg == "") 
                      return 0; 
                  
      
              if (arg != "") 
             { 
                     
                       
                              write(CYN "只听空中一声暴喝：“这位" + 
                                    RANK_D->query_respect(me) + CYN 
                                    "，怎么做这种事情!”\n" NOR); 
                              return 1; 
                      
                    
                   
              } 
              return 0; 
      } 




