#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
��������߰�����ֻ������ͷ������һЩ�����������ż
����ï�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���
ζ�����ᴫ��Ұ�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ����ݴ���
��Լ��һ����Ѩ(cave)��
LONG);
              set("item_desc", ([ 
                      "cave" : WHT "\n����һ���ڲ����еĴ󶴣����治֪��" 
                               "��Щʲô�Ź֡�\n" NOR,
              ])); 	
        set("exits", ([
		"east"  : __DIR__"shulin1",
		"north" : __DIR__"shulin4",
	]));
        set("quarrys", ([
                "tu"        : 100000,
                "ji"        : 80000,
                "pao"       : 50000,
                "caihuashe" : 50000,
                "dushe"     : 20000,
                "hu"        : 5000,
                "bao"       : 2000,
                "laohu"     : 2000,
        ]));
	set("outdoors", "huanghe");
	setup();
	//replace_program(ROOM);
}


      void init() 
      { 
               
              add_action("do_enter", "enter");
      } 

int do_enter(string arg) 

{ 
	int n;
	object *inv; 
	object me; 
	me = this_player();
	
	if (! arg || arg == "")
                return 0;
               
       
       inv = deep_inventory(me); 
           
             for (n = 0; n < sizeof(inv); n++) 
             
            { 
                    if (! playerp(inv[n])) continue; 
                    	
                    else 
                    { 
                            message_vision(CYN "\n��������ȵ���������ˣ�ʥ��֮��"
                              "���ɲ��������ţ������ϲ���ʲô!����������\n" NOR, me); 
                              
                      return 1; 
                    } 
            } 

                
    if (arg == "cave")
    	{             
	 if (me->query_skill("force",1)>600||me->query_skill("dodge",1)>600||
	 	   me->query_skill("parry",1)>600||me->query_skill("sword",1)>600||
	 	   me->query_skill("unarmed",1)>600||me->query_skill("martial-cognize",1)>600||
                   me->query("max_qi")>50000)
	 	   
	  {  message_vision(CYN "\n��������ȵ���������ˣ�ʥ��֮��"
                              "���ɲ��������ţ�����������\n" NOR, me); 
                              return 1;
    }
                              
               me->move("/u/dgdg/fuben/room/wolfcave");  

}
}