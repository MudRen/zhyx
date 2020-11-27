// shuang.c ��ʿ��˫
// ���ü��ܣ����ѡ��һ���Ը� by xiner 2009/4/05


#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��ʿ��˫" NOR; }

int perform(object me, string skill)
{
	if (! me->query("reborn"))
		return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");

	message_vision(HIC "$N" HIC "��Ŀ������ڤ��˼������ͼ"
                       "�ı��Լ��������Ը�\n" NOR, me);   

	me->set_short_desc("�������ڵ���ڤ˼����");
	me->delete_temp("pending/shuang");   
	me->start_busy((:call_other, __FILE__, "check" :), 
			(:call_other, __FILE__, "halt" :)); 
	return 1;
}

int check(object me)
{
	string char;

	if ( me->add_temp("pending/shuang", 1) < (30 + random(10)) )
		return 1;
   
	message_vision(HIW "$N" HIW "��������˫Ŀ��"
                    "���������ڤ�롣\n" NOR, me);

	if (random(6) != 0 )
		tell_object(me, HIC "\n��е����ڤ�벢û��ʲôЧ����"
                      "�޷������𵱳�ѡ���츳���龰��\n"NOR);
	else
	{
        	tell_object(me, HIG"\nͻȻ��е����Ƕٿ���"
                	         "������������Դ���龰����ѡ�����츳��\n"NOR);

	        switch (random(4))
        	{
			case 0:
				char = "�ĺ�����";
				break;
			case 1:
				char = "������";
				break;
			case 2:
				char = "���ռ�թ";
				break;
			default:
				char = "��������";
				break;
        	}
	        tell_object(me, HIW"\n����츳�����"HIR +char+ HIW "��\n\n"NOR);
        	me->set("character", char);
	}
	me->set_short_desc(0);  
	me->delete_temp("pending/shuang");
	return 0;
}

int halt(object me)
{            
	message_vision(HIG"$N����˫�ۣ����������ڤ�롣\n"NOR, me);        
	me->set_short_desc(0);  
	me->delete_temp("pending/shuang");     
	return 1;
}

