// buddhism.c ��ת��ͯ
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��ת��ͯ" NOR; }

int perform(object me, string skill)
{        	
	int lvl1, lvl2, lvl3, lvl4;

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
      
	lvl1 = me->query_skill("buddhism", 1);
	lvl2 = me->query_skill("lamaism", 1);
	lvl3 = me->query_skill("mahayana", 1);
	lvl4 = me->query_skill("taoism", 1);

	message_vision(HIY "$N" HIY "��Ŀ������ڤ��˼������ͼ��"
                       "���������Ϊһ�塣\n" NOR, me);   

	me->set_short_desc("�������ڵ���ڤ�룬�ƺ��������������Ϊһ��");
	me->delete_temp("pending/buddhism");   

	if (lvl1 >= 500 && lvl2 >= 500 && lvl3 >= 500 && lvl4 >= 400)
	{
		if (me->is_busy())
			return notify_fail("����æ������ͷ��������˵��\n");

		if (me->is_fighting())
			return notify_fail("��ߴ��һ��ڤ�룿������ġ�\n");

		if (me->query("potential") - me->query("learned_points") < 10000)
			return notify_fail("������Ǳ�ܲ��������һ��ڤ�룡\n");

		me->set_short_desc("��ϥ�����������Ŀ������");

		me->start_busy((:call_other, __FILE__, "check2" :),
				(:call_other, __FILE__, "halt2" :));
	}else
		me->start_busy((:call_other, __FILE__, "check" :),
				(:call_other, __FILE__, "halt" :));

	return 1;
}

int check(object me)
{
    if ( me->add_temp("pending/buddhism", 1) < (40 + random(10)) )
        return 1;
   
     message_vision(HIY "$N" HIY "��������˫Ŀ��"
                    "������������С�\n" NOR, me);

     if (random(5) != 0 )
        tell_object(me, "\n��е�������в��޶���չ��"
                        "�޷���������ǰ�ķ�ѧ�͵�ѧ֪ʶ��\n\n");
     else
     {
        tell_object(me, HIG"\nͻȻ��е����Ƕٿ���"
                         "������ǰ�ķ�ѧ�͵�ѧɲ�Ǽ�ӡ���Ժ���\n\n"NOR);
        tell_object(me, HIW"\n��Է�ѧ�͵�ѧ�����ˡ�\n\n"NOR);

        me->set_skill("buddhism", 500);
        me->set_skill("lamaism", 500); 
        me->set_skill("mahayana", 500);
	me->set_skill("taoism", 400);
     }
    me->set_short_desc(0);  
    me->delete_temp("pending/buddhism");
    return 0;
}

int halt(object me)
{            
	message_vision(HIG"$N����˫�ۣ����������ڤ�롣\n"NOR, me);        
	me->set_short_desc(0);  
	me->delete_temp("pending/buddhism");     
	return 1;
}

int check2(object me)
{
	if ((int)me->query("potential") - (int)me->query("learned_points") > 50)
	{
		me->add("learned_points", 20 + random(30));
		switch (random(9))
		{
		case 0:
			tell_object(me, HIW "��������ķ������µ�����\n" NOR);
			if (me->query_skill("buddhism",1) < 800)
				me->improve_skill("buddhism", 6000 + random(3000));
			break;
		case 1:
			tell_object(me, HIW "��������ķ������µ�����\n" NOR);
			if (me->query_skill("lamaism",1)< 800)
				me->improve_skill("lamaism", 6000 + random(3000));
			break;
		case 2:
			tell_object(me, HIW "��Դ�����̹������µ�����\n" NOR);
			if (me->query_skill("mahayana",1)< 800)
				me->improve_skill("mahayana", 6000 + random(3000));
			break;
		case 3:
			tell_object(me, HIW "��Ե�ѧ�ķ������µ�����\n" NOR);
			if (me->query_skill("taoism",1)< 800)
				me->improve_skill("taoism", 6000 + random(3000));
			break;
		default:
			//tell_object(me, HIW "�㰲���������������������ѡ�\n" NOR);
		}
		return 1;
	}
	message_vision(HIY "$N" HIY "��������˫Ŀ��������������С�\n" NOR, me);
	me->set_short_desc(0);  
	return 0;
}

int halt2(object me)
{            
	message_vision(HIG"$N����˫�ۣ����������ڤ�롣\n"NOR, me);
	me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
	me->set_short_desc(0);
	me->delete_temp("pending/buddhism");
	return 1;
}


