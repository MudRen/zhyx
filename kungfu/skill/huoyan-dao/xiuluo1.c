 // ���޽��� xiuluo.c

#include <ansi.h>
inherit F_SSERVER;
#include <weapon.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>


#define XIULUO "��" HIY "���޽���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
      object weapon;
      int damage;
      int i, jiali;
      string msg;

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



        me->add("neili", -500);
        msg =HIR "ͻȻ" HIR "$N" HIR "˫�ƴ��˼��ֻ꣬�����������죬�����浶����" HIR "$N" HIR "��ǿ�ھ��Ķ�Ȼ���֮��\n"
             HIR "���ƴ�ʢ��������������ε��������һƬ�������������޽���������" HIR "$n" HIR "ֱ������! \n" NOR;

        i = me->query_skill("force") / 4;
        jiali = me->query("jiali");
	damage = i  + random(i/2);


        msg += BBLU"\n\n����������           ��ɽ�𺣣�           ���������� \n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);    


        msg += BRED"   ����������        �޾�������        ����������\n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);


        msg += BMAG"       ����������     �ķ�����     ����������\n\n"NOR;
        msg += COMBAT_D->do_damage(me,target,msg, WEAPON_ATTACK, damage, 50,
                                   HIR "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã���\n" NOR);


        message_combatd(msg, me, target);
        me->start_busy(1+random(6));
        return 1;
}

