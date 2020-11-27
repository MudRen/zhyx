//selfstudy.c ��ʦ��ͨ
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "��ʦ��ͨ" NOR; }

int perform(object me, string skill)
{        	
	int lvl1, lvl2, lvl3, lvl4, lvl5, lvl6;

	if (! me->query("reborn"))        
            return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
      
	lvl1 = me->query_skill("literate", 1);
	lvl2 = me->query_skill("sanscrit", 1);
	lvl3 = me->query_skill("muslim", 1);
	lvl4 = me->query_skill("mathematics", 1);
	lvl5 = me->query_skill("qimen-wuxing", 1);
	lvl6 = me->query_skill("count", 1);

	if (lvl1 >= 600 && lvl2 >= 600 && lvl3 >= 600
	 && lvl4 >=400 && lvl5 >= 400 && lvl6 >= 400)
		return notify_fail("����������ʹ�ô˼��ܣ�\n");

	message_vision(HIC "$N" HIC "��Ŀ������ڤ��˼������ͼ"
                       "����ǰ����ѧ��\n" NOR, me);   

	me->set_short_desc("�������ڵ���ڤ˼����");
	me->delete_temp("pending/selfstudy");   

	me->start_busy((:call_other, __FILE__, "check" :), 
                      (:call_other, __FILE__, "halt" :)); 
	return 1;
}

int check(object me)
{
    if ( me->add_temp("pending/selfstudy", 1) < (40 + random(10)) )
        return 1;
   
     message_vision(HIW "$N" HIW "��������˫Ŀ��"
                    "���������ڤ�롣\n" NOR, me);

     if (random(5) != 0 )
        tell_object(me, "\n��е����ڤ�벢�޶���չ��"
                        "�޷�������ǰ����ѧ��֪ʶ��\n\n");
     else
     {
        tell_object(me, HIG"\nͻȻ��е����Ƕٿ���"
                         "������ǰ��ѧ��֪ʶɲ�Ǽ�ӡ���Ժ���\n\n"NOR);
        tell_object(me, HIW"\n����ѧ�ɹ��ˡ�\n\n"NOR);

	me->set_skill("literate", 600);
	me->set_skill("sanscrit", 600);
	me->set_skill("muslim", 600);
	me->set_skill("qimen-wuxing", 400);
	me->set_skill("mathematics", 400);
	me->set_skill("count", 400);
     }
    me->set_short_desc(0);  
    me->delete_temp("pending/selfstudy");
    return 0;
}

int halt(object me)
{            
	 message_vision(HIG"$N����˫�ۣ����������ڤ�롣\n"NOR, me);        
        me->set_short_desc(0);  
        me->delete_temp("pending/selfstudy");     
        return 1;
}


