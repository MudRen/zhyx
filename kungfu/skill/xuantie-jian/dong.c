// updated by kasumi 2007/3/30
#include <ansi.h>
#include <combat.h>

#define DONG "��" HIG "�󽭶�ȥ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp, www;
        string wp, msg;

        //if (userp(me) && ! me->query("can_perform/xuantie-jian/dong"))
        //        return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" DONG "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" DONG "��\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 180)
                return notify_fail("�����������������죬����ʩչ" DONG "��\n");

       // if ((int)weapon->query_weight() < 25000
       //     && ! weapon->is_item_make() && ! environment(me)->query("biwutai") )
       //         return notify_fail("�����е�" + wp + "��������������ʩչ" DONG "��\n");

        if ((int)me->query("neili") < 400)
                return notify_fail("�����ڵ��������㣬����ʩչ" DONG "��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ" DONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�������񣬶�ʱһ��������������ȱŷ������ŵ�"
              "��һ������" + wp + HIW "\n�漴��վ����������Χ��ɳ����"
              "����ʩ��������������" HIG "�󽭶�ȥ" HIW "����\n"NOR;

        
        www=(int)weapon->query_weight()/100;
        if (www>250) www=250;
        if (www<80) www=80;
        ap = me->query_skill("sword") + me->query("max_neili")/100 + www;        
        dp = target->query_skill("force") + target->query("max_neili")/100;
        
        if (ap * 2 / 3 + random(ap) > dp)
        {
                target->start_busy(1);
                damage = ap*2 + random(ap);
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "���$n" HIR "�����мܣ�ȴ��$N" HIR
                                           "��һ����ķ��𣬿�����Ѫ���²�ֹ��\n" NOR);
				me->start_busy(2 + random(3));
        } 
 		else if ( me->query("str") > random(target->query("str")*2) ) 
        {
               msg += HIY"$Nһ�����������ֳ���˳�Ʒ�ȥ��$n��̼�ֻ�������������Ʒ�ת�ˣ�վ�ڵ��أ�\n"
			          HIY"�Ȳ���������Ҳ�����ƶ��벽�����罩��һ�㡣\n"NOR;
             if (! target->is_busy())
             target->start_busy(3+random(4));
             me->start_busy(2+random(2));
        }		
		else if (ap / 3 + random(ap) > dp)
		{
		  msg += HIC"$Nֻ���Է���ײ�����ľ������಻����Խ��Խǿ,�˳������������һ����\n" NOR;
		  me->add("neili", -300);
          target->add("neili", -1000);
          me->start_busy(1+random(2));
             if (! target->is_busy())
          target->start_busy(1+random(2));
		} 
		else
		{
			msg += CYN "����$n" CYN "������$N" CYN "����ͼ����æбԾ�ܿ���\n"NOR;
            me->add("neili", -150);
			me->start_busy(2+random(2));
		}
        message_combatd(msg, me, target);


        return 1;
}



