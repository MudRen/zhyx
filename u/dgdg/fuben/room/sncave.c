#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "����ũ���᡿" NOR);
        set("long", HIW @LONG

                     ��ũ�ϲ���

    ����һ���ò�Ҷ��Ĳ��ᣬ���ܾ����ĵģ�����һ�ɹ����硣
����Ʈ��һ��ҩ��ζ���������ũ���ٲ�;����ʱ����֮����


LONG NOR );

     set("exits", ([
                "north" : "/u/dgdg/fuben/room/fxcave",
]));
        
        set("sleep_room", 1);
    
        set("objects", ([
                "/u/dgdg/fuben/npc/shennong": 1,
                "/u/dgdg/fuben/npc/shennong dizi":1,
                "/u/dgdg/fuben/npc/tongzi":1,
               
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


int do_yun(string arg)
{
        object ob = this_player();

        if (arg == "roar")
        {
                message_vision(CYN "\n��������ȵ���ʲô�ˣ�ʥ��֮��"
                               "���ɲ��������ţ�\n" NOR, ob);
                return 1;
        }
        return 0;
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

