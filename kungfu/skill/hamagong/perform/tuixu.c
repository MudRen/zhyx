// tui.c ����ʽ֮��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int n;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦������ʽ��֮��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("���ֱֳ������޷�ʩչ��󡹦�ľ�����\n");
	         
	      if (!(int)me->query_temp("tuitimes"))
                return notify_fail("������������󡹦�ġ�����ʽ���ˡ�\n");
                
        msg = HIG "$N" HIG "�֡��á���һ����У�������������һ�ģ�����һ���̹�����......\n" NOR;   
        n=me->query_temp("tuitimes");
        n=n+1;
        me->set_temp("tuitimes",n);
		if (me->query("qi") < me->query("eff_qi"))
		{
		    me->add("qi", me->query_skill("hamagong", 1)*2);
		}
        message_combatd(msg, me, target);
         me->start_busy(1);
        return 1;
}
