#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "�����˶���" NOR);
        set("long", HIW @LONG

                     ���˶�

    ���Ƿ�����λ�˻ʺ����ӵĶ��츣�ء��������ڸ��٣�������������һ�������
��Ȼ����һ�񡣶��ڳ���һ�Ծ�ת����ݣ���ں��ѷ��֡�


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
                     
                       
                              write(CYN "ֻ������һ�����ȣ�����λ" + 
                                    RANK_D->query_respect(me) + CYN 
                                    "����ô����������!��\n" NOR); 
                              return 1; 
                      
                    
                   
              } 
              return 0; 
      } 




