// jue.c  �ط����������������

#include <ansi.h>
#include <combat.h>

#define JUE "��" HIW "����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/huifeng-jian/jue"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("����ʹ�õ��������ԣ��޷�ʩչ" JUE "��\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("��û�м����ط�����������޷�ʩչ" JUE "��\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 200)
                return notify_fail("��ط��������������죬�޷�ʩչ" JUE "��\n");
         if ((int)me->query_skill("linji-zhuang", 1) < 200)
                return notify_fail("���ټ�ʮ��ׯ������죬�޷�ʩչ" JUE "��\n");        

        if ((int)me->query_skill("force",1) < 200)
                return notify_fail("���ڹ���򲻹����޷�ʩչ" JUE "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�����������������޷�ʩչ" JUE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wname = weapon->name();

        //damage = (int)me->query_skill("huifeng-jian", 1) / 3;
        //damage += random(damage / 2);
       

        // ��һ��
        ap = me->query_str()+me->query_skill("sword")+random(me->query_skill("mahayana",1)/2);
        dp = target->query_str()+target->quest_skill("force");
        msg = HIC "$N" HIC "һ�����������е�" + wname + HIC "��׼$n" HIC "ֱ����"
              "�£����ǻط��������" NOR + HIW "����" NOR + HIC "��������\n" NOR;
        if (ap *2/3 + random(ap) > dp)
        {damage = ap+random(ap/4);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "�����ֵ���ȴ�����мܵ�ס����$P"
                                           HIR "��һ�����£���ʱ��Ѫ������\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "�ٵ�һ����Ӳ������$P"
                       CYN "��һ���ܿ���˿������\n" NOR;
        }

        // �ڶ���
        ap = me->query_int()+me->query_skill("sword")+random(me->query_skill("mahayana",1)/2);
        dp = target->query_int()+target->query_skill("force");
        msg += "\n" HIC "$N" HIC "�漴һ����Ц�����е�" + wname +
               HIC "�����������������£����Ī�⣬��㽣������$n" HIC "��\n" NOR;
        if (ap *2/3 + random(ap) > dp)
        {damage = ap+random(ap/3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$p" HIR "��󲻽⣬һʱ���Կ�͸��"
                                           "�а��һ�����˼��У�����������\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "����һЦ����Ȼ����$P"
                CYN "����������������У����⽫֮�ܿ���\n" NOR;
        }

        // ������
        ap = me->query_con()+me->query_skill("sword")+random(me->query_skill("mahayana",1)/3);
        dp = target->query_con()+target->quest_skill("force");
        msg += "\n" HIC "$N" HIC "��������һ���������е�" + wname +
               HIC "�û���һ��ǳǳ�Ĺ�â���˽���һ����$n" HIC "��ȥ��\n" NOR;
        if (ap *3/5 + random(ap) > dp)
        {damage = ap+random(ap/2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "�����ֵ���ֻ����һ��͸������"
                                           "Ϯ��������һ�����裬�������̱�ÿտյ�����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "һ�����Ե�������������$P"
                CYN "���彣â��Ȼ������ȴδ����$p" CYN "�ֺ���\n" NOR;
        }

        // ������
        ap = me->query_dex()+me->query_skill("sword")+random(me->query_skill("mahayana",1)/3);
        dp = target->query_dex()+target->quest_skill("force");
        msg += "\n" HIC "$N" HIC "�Ų�һ�Σ���Ȼ��������������죬���е�" + wname +
               HIC "Ӧ�����𣬴���$n" HIC "��\n" NOR;
        if (ap *3/ 5 + random(ap) > dp)
        {damage = ap+random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$p" HIR "ֻ������һ������ʱ��$P"
                                           HIR "��һ�����˸����У���Ѫ�Ĵ����䣡\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "��ȴ�Ǹ��죬ֻ��һ�ˣ���$P"
                CYN "��һ�п���������Ч��\n" NOR;
        }

        // ������
        ap = me->query_skill("sword")+random(me->query_skill("mahayana",1)/4);
        dp = target->query_skill("parry");
        msg += "\n" HIC "$N" HIC "һ����̾�������ú������飬" + wname +
               HIC "���ƶ�ת��������������˵����Ĳ���֮�⡣\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {damage = ap*2 + random(ap*2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$p" HIR "ֻ������ԡ�ڷ���һ�㣬�����о�Ȼ���޿ɵֵ�����"
                                           HIR "�������˸�Ѫ��ģ����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
                       "����������ֵ�����©���������\n" NOR;
        }

        me->start_busy(3 + random(6));
        me->add("neili", -600 - random(300));
        message_combatd(msg, me, target);
        return 1;
}
