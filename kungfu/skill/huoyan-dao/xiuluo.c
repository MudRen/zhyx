 // ���޽��� xiuluo.c

#include <ansi.h>
#include <combat.h>


#define XIULUO "��" HIY "���޽���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, ap, dp, count;
		int damage;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail(XIULUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
           return notify_fail("����������ʹ������" XIULUO "��\n");

        if ( me->query_skill_mapped("unarmed") != "huoyan-dao")
                return notify_fail("��û�м������浶������ʩչ" XIULUO "��\n");
        if(me->query_skill("huoyan-dao", 1) < 150 )
                return notify_fail("��Ļ��浶��򲻹�������ʩչ" XIULUO "��\n");

        if(me->query_skill("unarmed", 1) < 150 )
                return notify_fail("��Ļ���ȭ�Ż�������죬����ʩչ" XIULUO "������\n");


        if(userp(me) && (int)me->query_skill("longxiang-gong", 1) < 100 )
                return notify_fail("�������������ȼ������ߣ�����ʩչ" XIULUO "��\n");

        if (me->query("max_neili") < 2000)
           return notify_fail("���������Ϊ����������ʩչ" XIULUO "��\n");

       if (me->query("neili") < 500)
           return notify_fail("�����������������ʩչ" XIULUO "��\n");

       if (me->query("jing") < 80)
           return notify_fail("��ľ�������������ʩչ" XIULUO "��\n");



        msg = HIW "$N" HIW "������" + weapon->name() + HIW "����ѹ��$n"
              HIW "�������������ŷ���֮��������ȡ������ɱ�š�" HIR "��"
              "��Ǭ��" HIW "����\nֻ�����˾�ȫ���ϵ������֣�" +
              weapon->name() + HIW "����ǧ�ٸ����ƣ�������������" HIW"$n" HIW"�ҳ������У�\n" NOR;			  

        ap = me->query_skill("club") + me->query_skill("force") + me->query_skill("buddhism" ,1) / 2;
        dp = target->query_skill("parry") + target->query_skill("force");
		damage = ap / 2 + random(ap/2);


		msg += HIM "\n       ��������������\n"
               HIM"       ���������޸���\n"
               HIM"       ��������������\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);            
        
		msg += HIR "\n       ��������������\n"
               HIR "       ���¶�������\n"
               HIR "       ��������������\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);     
								   
		msg += HIY "\n       ��������������\n"
               HIY"       ��ǧ�������\n"
               HIY"       ��������������\n\n" NOR; 
              
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);     								   
					
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        return 1;
}


