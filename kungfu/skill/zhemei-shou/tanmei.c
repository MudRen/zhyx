// feilong.c ��ң��÷�֡���÷.��ѩ.ɢ���㡿

#include <ansi.h>
#include <combat.h>

#define TANMEI "" HIG "��" HIM "��÷." HIW "��ѩ." HIY "ɢ����" HIG "��" NOR ""

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, pp, fp, bp;


        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TANMEI "ֻ����ս���жԶ���ʹ�á�\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 800)
                return notify_fail("����ң��÷�ֲ�����죬�޷�ʩչ" TANMEI "��\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 500)
                return notify_fail("��˻�����Ψ�Ҷ��𹦲�����죬�޷�ʩչ" TANMEI "��\n");

        if (me->query("dex") < 40)
                return notify_fail("�����������㣬�޷�ʩչ" TANMEI "��\n");

        if (me->query("con") < 40)
                return notify_fail("��������ǲ��㣬�޷�ʩչ" TANMEI "��\n");

	if (! me->query("reborn"))        
		return notify_fail("����δת���������޷����˾��У�\n");
      
        if( (int)me->query("max_neili") < 12000 )
                return notify_fail("���������Ϊ̫��޷�ʩչ" TANMEI "��\n"); 

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����������������޷�ʩչ" TANMEI "��\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("��û�м�����ң��÷�֣��޷�ʹ��" TANMEI "��\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou")
                return notify_fail("��û��׼����ң��÷�֣�����ʩչ" TANMEI "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -800);

        ap = me->query_skill("bahuang-gong", 1) + me->query_skill("zhemei-shou", 1) + me->query_skill("qimen-wuxing", 1) + me->query("jiali");
        dp = target->query_skill("dodge") + target->query_skill("qimen-wuxing", 1);
        pp = target->query_skill("parry") + target->query_skill("qimen-wuxing", 1);
        fp = target->query_skill("force") + target->query_skill("qimen-wuxing", 1);
        bp = dp + pp + fp;
        
        msg = HIM "                                          ���� ÷��\n"NOR;
        msg += HIM "$N΢΢һЦ����" HIC "���͵��˼�ѩ��˪���ٻ�ͷ�϶����㡹" HIM "��ͬʱ��������$n���ᵯ����������Ҫ��ȥ÷�������¶�飡\n" NOR;
        if (ap * 3 / 5 + random(ap) > dp)
        {       damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50 + random(10),
                                           HIM "$n" HIM "����ǰ�ľ�����ס�ˣ���Ȼ�����˺��ˣ���ܲ�������$N"
                                           HIM "��ÿ�����Ѫ��Ҳ��Ȼ��֪��\n" NOR);
        }
        else
                msg += CYN "$n" CYN "ʶ����$N����ͼ��΢΢б������һ����\n" NOR;

        msg += HIW "                                          ���� ѩ��\n"NOR; 
        msg += HIW "$N˫�ּ��ӣ�����ҡ�ڣ��ó�����÷������ѩ�Ƶ���$n������\n" NOR;
        if (ap * 3 / 5 + random(ap) > pp)
        {       damage += random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                           HIW "��ѩ���죬����" HIG "��Ʈ�����꾪�쪣��仨��ѩ��ãã��" HIW "��$n" HIW "�������ü���"
                                           "���мܣ�ֻ��$N" HIW "�������£�$n"
                                           HIW "�ǿ���Ѫ��\n" NOR);
        }
        else
                msg += CYN "$n" CYN "�жϳ���÷���ķ������������һ�ˣ��ܹ��˷�ѩ���÷����\n" NOR;                

        msg += YEL "                                          ��ɢ���㡿\n"NOR;
        msg += YEL "$nͻȻ�ŵ�һ���������޵���ζ����Գ����֮��$N��˫������$n�ؿ�������\n" NOR;
        if (ap / 2 + random(ap) > fp)
        {       damage += random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(10),
                                           YEL "$n" YEL "�������,$N��������" WHT "����ѩ������������ͬ����췼������" YEL ",һ�����С�\n"
                                           "$n" YEL "������Ѫ��ȴҲ��֪������$N���м�������" WHT "����Ȼһҹ���㷢��ɢ��Ǭ�����ﴺ��" YEL "��\n" NOR);
        
        }
        else
                msg += CYN "$n" CYN "��֮���˫�ֻ��أ�Ӳ��������һ����\n" NOR;
       
        msg += HIC "$N" HIC "����������֮��������÷��֮�У�˫�ֻó�������Ӱ���������÷������$n������һƬ÷��֮�У�\n" NOR;
        if (ap * 3 / 2 + random(ap) > bp)
        {       damage += random(ap);
                 msg += HIM "ֻ��$n" HIM "һ����Х��$N" HIM "����ɫ÷"
                               "���Ѿ�������$p" HIM "���壬��ʱ��$p" HIM "��"
                               "Ϊһ��Ѫ�ˡ�\n" NOR;
                 target->receive_damage("qi", damage, me);
                 target->receive_wound("qi", damage / 2, me);
                 target->receive_damage("jing", damage / 3, me);
                 target->receive_wound("jing", damage / 4, me);
                 target->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN "����ͼ��˿"
                      "����Ϊ��������$P" CYN "������û������κ����á�\n" NOR;
                me->start_busy(2);
        }


        me->start_busy( 1 + random(3));
        message_combatd(msg, me, target);
        return 1;
}
