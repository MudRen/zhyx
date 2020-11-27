// ����Ů��������

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "����Ů���񶥲�");
	set("long", @LONG
����������Ů����Ķ��㡣������Ը������ŦԼ�ۡ�
��˵����һ�������й���Ϊ��Ӣ�۵����;����ڴ˴�������
�£�����������һ������Ṧ����Ҳ��������(jump)��ǽ��
���п�ͻ����שͷ,��֪ȥ(push zhuan)һ�»�������
LONG );
	set("exits", ([		
              "down"        : __DIR__"floor4",
	]));
	set("item_desc",([		
              "zhuan"	: "һ��ͻ����שͷ���ƺ��е�Ź֡���֪��"
                             "(push)һ�»�������\n",	
	]));
       set("no_fight",1);
       set("no_sleep_room",1); 
       set("no_ride",1);       		
	setup();	
}

void init()
{	
	add_action("do_jump", "jump"); 
       add_action("do_push", "push");             
}

int do_push(string arg)
{
        object room, me;

        me = this_player();

        if (! arg || arg != "zhuan" )
        {
		write("��Ҫ��ʲô��\n");
              return 1;        
        }
        message_sort(HIY"\n$N�ߵ�ǽ�ߣ���������һ��ͻ����ש�顣"
                     "\n" NOR, me);

        if (! me->query("special_skill/lonely") )
        {
           message_sort(HIY"\n����$N��ôҲ��������ש��\n" NOR);
           return 1;        
        }

        message_sort(HIY"\nͻȻǽ��һ�����������¶��һ���󶴣�\n"
                     "���������ͨ��һ�����ҡ�"
                     "\n\n" NOR, me);
        set("exits/enter", __DIR__"anshi");

        if (room = find_object(__DIR__"anshi"))
        {
        	room->set("exits/out", __FILE__);
           	message("vision", HIY "\nǽ�ں�Ȼ����������������"
                        "¶��һ�������ͨ����\n" NOR, room );
        }
        remove_call_out("close_andao");
        call_out("close_andao", 5);
        return 1;
}

void close_andao()
{
    	object room;
        int i;

        if (! query("exits/enter")) return;
    		message("vision", HIY "\nֻ��ƹ��һ���죬ש���Զ�"
                        "�ƻ�ԭ��������Ҳ��֮��ʧ�ˡ�\n" NOR, this_object());

    	if (room = find_object(__DIR__"anshi"))
    	{
              room->delete("exits/enter");
        	message("vision", HIY "\nֻ��ƹ��һ���죬����İ���"
                        "���Զ�����ʵʵ�ع���������\n" NOR, room);
    	}
    	delete("exits/enter");
}




int do_jump()
{
        object me;

        int i, ging_cost, qi_cost;

        me = this_player();
        me->start_busy(5);
        i = (int)me->query_skill("dodge", 1) + random(5);

        ging_cost = 300 / (int)me->query("int");
        qi_cost = 200 / (int)me->query("int");

        if (((int)me->query("jing") < ging_cost) ||
            ((int)me->query("qi") < qi_cost))
                i = 0;

        message_vision("$Nһ������������ȥ��\n", me);
        me->move(__DIR__"newyork");
	 message_vision("ֻ�����须��һ��$N��Ů��������������\n", me);

        if (i < 30)
		message_vision("$N���ص�ˤ�˸�����࣬�������Ṧ�������ҡ�\n", me);
	else
        {
		message_vision(WHT"$N�����ȵ�վ�ڵ��ϡ�\n"NOR, me);
		if ( me->query_skill("dodge", 1) < 200)
              {
		     me->improve_skill("dodge", 2 * (10 + random(me->query("dex"))));
		     me->receive_damage("jing", ging_cost);
		     me->receive_damage("qi", qi_cost);
                   tell_object(me,HIC"��ġ������Ṧ������һ���Ľ�������\n"NOR);
             } else
               tell_object(me,WHT"����Ṧ�Ѿ�û��Ҫ������������ˡ�\n"NOR);
	}

        return 1;
}








