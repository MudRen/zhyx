#include <ansi.h>
#include <combat.h>

#define MIAN "��" HIW "�������" NOR "��"

inherit F_SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object weapon;
        string msg;
		int count;

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" MIAN "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" MIAN "��\n");

        if (me->query_skill("wuyue-shenjian", 1) < 400)
                return notify_fail("�����������Ϊ����������ʩչ" MIAN "��\n");

        if (! me->query("reborn"))         
                return notify_fail("����δת���������޷����˾��У�\n"); 

        if (me->query("neili") < 500)
                return notify_fail("�����������������ʩչ" MIAN "��\n");

        if (me->query_skill_mapped("parry") != "wuyue-shenjian")
                return notify_fail("��û�м���������Ϊ�мܣ�����ʩչ" MIAN "��\n");
				
		if ((int)me->query_temp("wysj_mian"))
                return notify_fail("���Ѿ���ʩչ" MIAN "�ˡ�\n");
				
		if (me->is_fighting())
                me->start_busy(3);
                
        count=(int) (me->query_skill("wuyue-shenjian", 1)/3);        
		msg = HIW "$N" HIW "����һ�����е�" + weapon->name() + HIW "��ֻ����â��˸����Ȼ�������������к�ɽ�ɾ�ѧ��������롱��\n" NOR;
		message_combatd(msg, me, target);               
		me->add("neili", -200);            
		me->set_temp("wysj_mian", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, count :), count);            
        
        return 1;
}
        

void remove_effect(object me, int amount)
{
        if (me->query_temp("wysj_mian"))
        {    	
        	me->delete_temp("wysj_mian");
        	tell_object(me, "���" MIAN "������ϣ��������ջص��\n");
        }
}