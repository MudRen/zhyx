//���ǵ��ط������в�����
//�������о������
//buy gentl
//update 2012.11.29

#include <ansi.h>
#include <combat.h>

#define BAGUA "��" HIY "����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg, wp;
        int skill;        
        int damage;       
        int ap, dp , p, str, cp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BAGUA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" BAGUA "��\n");

        if ((int)me->query_skill("bagua-dao", 1) < 350)
                return notify_fail("��İ��Ե���������죬����ʩչ" BAGUA "��\n");

        if ((int)me->query_skill("wai-bagua", 1) < 350)
                return notify_fail("���������񹦲�����죬����ʩչ" BAGUA "��\n");

        if ((int)me->query_skill("nei-bagua", 1) < 350)
                return notify_fail("����ڰ����񹦲�����죬����ʩչ" BAGUA "��\n");

        if (me->query_skill_mapped("force") != "nei-bagua")
                return notify_fail("��û�м����ڰ����񹦣�����ʩչ" BAGUA "��\n");

        if (me->query_skill_mapped("parry") != "wai-bagua")
                return notify_fail("��û�м���������񹦣�����ʩչ" BAGUA "��\n");

        if ((int)me->query("max_neili") < 6000)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" BAGUA "��\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("��������������������ʩչ" BAGUA "��\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("��û�м������Ե���������ʩչ" BAGUA "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "���һ������" + weapon->name() +  HIY "��������ǧ��������ʱ���������������ӿ��������$n" HIY "ȫ��\n\n" NOR;
        ap = me->query_skill("bagua-dao", 1) + me->query_skill("nei-bagua", 1) + me->query_skill("wai-bagua", 1);
        dp = target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("dodge", 1);
        cp = me->query_skill("bagua-bu", 1) + me->query_skill("bagua-quan", 1) + me->query_skill("bagua-zhang", 1);
        ap += cp/6;		
        damage = ap / 2 + random(ap/2);
		
		        me->add("neili", -600);
		
// ��һ��
        msg += HIM "��Ǭ���־��������������������������Ű��ԡ�\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           GRN"$N���������Ǭ���죬�����أ��������Σ���ת��ʼ��\n"
                                           GRN"$nֻ��������������֮�����Լ�ѹ�������ζ�ʱ����������\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += HIC "\n�������־����������������������������޵С�\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           GRN"$Nһ����һ���죬�����������Ī��֮���ƣ�\n"
                                           "�����Ե����ӵ����쾡�£�ֱ����$n��ȥ��\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += HIW "\n���㡻�־������������������������ᵶ����\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                          GRN"$N������" + weapon->name() + GRN"бб������$n��ȥ��ֻ��"+ weapon->name() + GRN"���������յ����ͣ�\n"
                                           "����$n��ȥ,$n����$N�����ƣ���ʱ����һ�߿հס�\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += HIG "\n�����־�������������������������ս��ʤ��\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           "$N��ָ��񷣬���һ����Я��ս��ʤ֮��ɱ��$n��\n"
                                           "$n����ǿ���ս�����ƣ�ֻ����־һ���Ժ���\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += HIY "\n�������־������������������������ĺ�ƽ����\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           "$N��ʹ���Ե�����̤���Բ�����ʱ������������$N����$n��\n" 
                                            "$nֻ���ۻ����ң������ֲ����ĸ��������ҽ�һ����������������\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += HIR "\n���ҡ��־������������������������ٲ����\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           GRN"$Nһ����Х�����˰����񹦣�"+ weapon->name() + GRN"��Ȼ����һ����â���ƿշ���$n��\n"
                                           "ֻ��$nһ���ҽУ��ѱ���â�������\n"NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }
// ���������Ҫ������
     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("bagua-dao", 1) > 499 
     	    && (int)me->query_skill("nei-bagua", 1) > 499 && me->query("int") > 35)
      {           
	              me->add("neili", -600);
				  
                  ap += cp/6;		      
                  damage += cp/2;

          msg += CYN "\n���롻�־���������������������������ɽ�ӡ�\n" NOR;

        if (ap + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           GRN"$N�ð�������ת"+ weapon->name() + GRN"����ʽ�󿪴��أ�����$n��\n" 
                                            "$n�ܲ��˴˹�����ֻ���׷��겻�ѣ��޷��˹��࿹��Ԫ������\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }

        msg += WHT "\n���ޡ��־�������������������������ɨǧ����\n" NOR;
        if (ap + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           GRN"�����" + weapon->name() + GRN"�����������֮����$n��ȥ�����е������ƴ�׾��ʵ����ɣ�\n"
                                           "���Ե��п��֮��ɫ��$n�����쵶����Ʈ�㣬��ʱ��֪���룬�������ء�\n" NOR);
        } else
        {
                msg += CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }
      }

///�������а��Ժ�һ����ʱûд��



        me->start_busy(3 + random(3));
        message_combatd(msg, me, target);
        return 1;

}

