// ����Ů������Ĳ�

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "����Ů������Ĳ�");
	set("long", @LONG
����������Ů������Ĳ㡣
LONG );
	set("exits", ([		
		"down"       : __DIR__"floor3",
              "up"        : __DIR__"floor5",
	]));
	set("no_fight",1);	
       set("no_sleep_room",1); 
       set("no_ride",1);		
	setup();	
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();
       if ( ! me->is_player() ) return 1;

	if (dir == "up" )
	{
		c_skill = (int)me->query_skill("dodge", 1);
                if (me->query("qi") > 20)
                {    if (c_skill < 100 ) 
                     {   
                         me->receive_damage("qi", 10 + random(10));
		           tell_object(me,"������һ��¥���о���Щ���ˡ�\n");
        		    if (me->can_improve_skill("dodge") )
                        {                        
        		        me->improve_skill("dodge", 20 + c_skill / 5);
        		        tell_object(me,"��о��ƺ������ȽŸ�����ˡ�\n");
                         }
                      }
                } else
                {                       
        		   tell_object(me,"�������������ˡ�\n");
                        return -1;
                }
	}
	return 1;
}






