#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "��Զ��ͨ����" NOR);
        set("long", HIW @LONG

                   Զ��ͨ��

    ������ɭ�ֲ�����ʱ����һ���Ǻ�֮�������˺��¡����ܴ�������
��磬������һ����ζ������ǳ��Ĳ�������ݴ�����Լ��һ����(dong)


LONG NOR );

     set("exits", ([
                "out" : "/d/huanghe/shulin2",
             //   "north" :"/u/dgdg/fuben/room/sncave",
]));
       
        set("sleep_room", 1);
        
        
       set("objects", ([
          //      "/u/dgdg/fuben/npc/shennong": 1,
                "/u/dgdg/wolfmm":1,
               
        ])); 
      
        setup();
        "/u/dgdg/fuben/room/dgdgcave_b"->foo();
}

void init()
{
        add_action("do_move", "enter");
        add_action("do_act", "touxi");
        add_action("do_act", "hit");
        add_action("do_act", "kill");
}

int do_act(string arg)
{
      object me;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg != "")
        {
                if ( objectp(present("tie chuanjia", environment(me))))
                {
                        write(CYN "ֻ������һ�����ȣ�����λ" +
                              RANK_D->query_respect(me) + CYN
                              "����ͣ������\n" NOR);
                        return 1;
                }
               
               
        }
        return 0;
}

int do_move(string arg)

{ 
	//int n;
	//object *inv; 
	object me; 
	me = this_player();
	
	if (! arg || arg == "")
                return 0;
                
     /*    
       inv = deep_inventory(me); 
           
             for (n = 0; n < sizeof(inv); n++) 
             
            { 
                    if (! playerp(inv[n])) continue; 
                    	
                    else 
                    { 
                            message_vision(CYN "\n��������ȵ���������ˣ�ʥ��֮��"
                              "���ɲ��������ţ������ϲ���ʲô!����������\n" NOR, me); 
                              
                      return; 
                    } 
            }  */

                
    if (arg == "dong")
    	{             
	 if (me->query_skill("force",1)>550||me->query_skill("dodge",1)>550||
	 	   me->query_skill("parry",1)>550||me->query_skill("sword",1)>550||
	 	   me->query_skill("unarmed",1)>550||me->query_skill("martial-cognize",1)>550)
	 	   
	  {  message_vision(CYN "\n��������ȵ���������ˣ�ʥ��֮��"
                              "���ɲ��������ţ�����������\n" NOR, me); 
                              return 1;
    }
                              
               me->move("u/dgdg/fuben/room/sncave");  

}
}