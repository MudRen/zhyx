// feng.c ���Ž� �������
//Created by kasumi
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define feng "��" HIM "�������" NOR "��"


int perform(object me, object target)
{
	object weapon;
    int damage,ap,dp,n,i;
	int skill;
	string msg;

	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/daya-jian/feng"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail(feng"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("daya-jian", 1) < 180)
		return notify_fail("��Ĵ��Ž�������죬����ʹ�á�������ޡ���\n");
	
	if ((int)me->query_skill("force") < 270)
		return notify_fail("����ڹ�������죬����ʹ�á�������ޡ���\n");
	
	if ((int)me->query("neili") < 400)
		return notify_fail("�������������\n");	

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");	  


	   msg = HIG "$N" HIG "�����⶯������������ֻ��ǧǧ������������һ����ɫ��Ӱ�ӻ������裬\n"
		     HIG"����΢�����ƿ�֮�����羪�κ���......\n"NOR;
	    ap = me->query_skill("sword") + me->query_skill("tanqin-jifa", 1);
        dp = target->query_skill("dodge") + target->query_skill("tanqin-jifa", 1);

		if (me->query_skill("chess", 1) > 250)
		{
			ap=ap+me->query_skill("chess", 1);
			dp=dp+target->query_skill("chess", 1);
		}

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = ap + random(ap);                
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "$n" HIR "ֻ������һ������������ʹ���·����ǽڴ����ѣ�\n" NOR);

				if (me->query_skill("chess", 1) >= 275 && me->query("family/family_name") == "������")
				{
					msg += HIW"ֻ�����������������ȼӡ����콣Ӱ�������岼����������$n��\n"NOR;
					n= 1 + random((int) (me->query_skill("chess", 1)/100));
					if (n>5)
						n=5;
					for (i = 0; i < n; i++)
					{
						  damage = ap + random(ap/2);  
			              msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50+random(10),
                                           HIR "$n" HIR "ֻ����ǰһ�ڣ������׹���������������������Ѫ����ֹ��\n" NOR);
						  me->add("neili", -150);
					}
				}

        } else
        {
                me->start_busy(2);
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ������һԾ�����˿�ȥ��\n" NOR;
        }

        message_combatd(msg, me, target);
	return 1;
}
