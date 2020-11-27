#include <ansi.h>
#include <combat.h>

#define SANHUA "��" HIM "��Ůɢ����" NOR "��"

inherit F_SSERVER;

void remove_effect(object me, int amount);


int perform(object me, object target)
{
        string msg;
	 int level, count;
        
        if ((level = me->query_skill("xuannv-jian", 1)) < 250)
                return notify_fail("�����Ů��������������������ʩչ" SANHUA "��\n" NOR);

        if ((int)me->query("neili") < 600)
                return notify_fail("�������������㣬����ʩչ" SANHUA "��\n" NOR);

        if (me->query_temp("sanhua"))
                return notify_fail("���Ѿ�����" SANHUA "�ˡ�\n");

       
        msg = HIM "\n$N̤����Ůɢ������������ӯ�ޱȣ�����һ˿����������\n"
                  "�侰���������·����������ӣ��������磬ϼ�����䡣\n"
                  "�������˲�����������������������Ʋ�֪���ںδ���\n" NOR;       

        message_sort(msg, me);

        count = level / 20;       

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->add_temp("apply/dodge", count * 6);	
        me->set_temp("sanhua", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :),  level / 3);  
        me->add("neili", -400);
        return 1;

}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("sanhua"))
        {
                me->add_temp("dex", -amount);
                me->add_temp("apply/dodge", - amount * 6);
                me->delete_temp("sanhua");
                tell_object(me, "���" SANHUA "������ϣ��������ջص��\n");
        }
}
