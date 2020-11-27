#include <ansi.h>
#include <combat.h>

#define TIAN "��" HIY "�쵶����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage,ap,dp;
        string msg;
        object weapon;
        int i, count;

        if (userp(me) && ! me->query("can_perform/bagua-dao/tian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" TIAN "��\n");

        if ((int)me->query_skill("bagua-dao", 1) < 200)
                return notify_fail("��İ��Ե���������죬����ʩչ" TIAN "��\n");

        if ((int)me->query_skill("wai-bagua", 1) < 200)
                return notify_fail("���������񹦲�����죬����ʩչ" TIAN "��\n");

        if ((int)me->query_skill("nei-bagua", 1) < 200)
                return notify_fail("����ڰ����񹦲�����죬����ʩչ" TIAN "��\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" TIAN "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������������ʩչ" TIAN "��\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("��û�м������Ե���������ʩչ" TIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(HIY "$N" HIY "���һ������" + weapon->name() +
                        HIY "��������ǧ��������ʱ���������������ӿ��"
                        "������$n" HIY "ȫ��\n" NOR, me, target);

        count = me->query_skill("bagua-dao", 1) / 4;

        me->add("neili", -250);
        me->add_temp("apply/attack", count);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                me->add_temp("pfm_tiandao", 1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->delete_temp("pfm_tiandao");
        
        msg = HIR"������" "$N" HIR "�����Ц������" + weapon->name() +
              HIR "б����һ����⣬������������"
              "ɱ����ֱ��$n" HIR "��ȥ��\n" NOR;

       
        ap = me->query_skill("blade") + me->query_str() * 10 ;
        dp = target->query_skill("dodge") + target->query_con() * 10;

       
        if (ap * 3 / 5 + random(ap) > dp)
        {               
                damage = ap + random(ap);
                me->add("neili", -300);
              
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "ֻ��$n" HIR "һ���ҽУ�$N" HIR +
                                           weapon->name() + HIR "����һ��������Ƕ"
                                           "��$p" HIR "���ڳ�������һ��Ѫ�ꡣ\n"
                                           NOR);
        } else
        {
                me->add("neili", -200);
               
                msg += CYN "$n" CYN "��$P" CYN "������ӿ���������׵�"
                       "������æ������Ų������������\n" NOR;
        }
        message_combatd(msg, me, target);

      
        me->start_busy(1 + random(8));
        return 1;
}
