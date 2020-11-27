// wuliang.c �����ơ�Ǭ��������
// Create for Haiyan 2002

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count, acter;
        int i, bsy, lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ǭ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("��û�м��������ƣ��޷�ʩչ��Ǭ����������\n"); 

        if ((int)me->query_skill("bagua-zhang", 1) < 120)
                return notify_fail("��İ����Ʋ�����죬����ʹ�á�Ǭ����������\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("��Ǭ��������ֻ�ܿ���ʩչ��\n");  

        if (! me->query_skill_prepare() || me->query_skill_prepare() && 
            me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("������û��׼��ʹ�ð����ƣ��޷�ʹ�á�Ǭ����������\n"); 

        if (me->query("neili") < 350)
                return notify_fail("��������������޷�ʹ�á�Ǭ����������\n");

        msg = HIY "$N" HIY "�Ʒ���Ȼ��죬ʹ�������Ʒ���Ǭ���������������ذ��Է�λ���ߣ�˫������ʵʵ������$n��\n" NOR;

        dp = (target->query_skill("force", 1) + 
             target->query_skill("parry", 1) +
             target->query_skill("martial-cognize", 1)) / 3 +
             target->query_skill("count", 1); 

        if (me->query("character") == "��������" || me->query("character") == "������") 
             acter = 3;
        else
             acter = 4;

        ap = (me->query_skill("taiji-shengong", 1) +
             me->query_skill("bagua-zhang", 1) +
             me->query_skill("martial-cognize", 1) + 
             me->query_skill("taoism", 1)) / acter; 

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "��$N" HIR
                       "��һ�仯���˸����ֲ������������ء��������ƣ�" HIR
                       "���������Ѫ����ɫ���ɷ�ף�\n" NOR;
                count = ap / 28; 
                bsy = 2;
                lvl = me->query_skill("bagua-zhang", 1) / 60;
                me->add_temp("apply/attack", count);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "��Ȼ���У����Ҵ��⣬��æ��Ϣ������С��Ӧ�ԣ���$N"
                       HIC "����ʽ������⡣\n" NOR;
                count = 0;
                lvl = 0;
                bsy = 5;
        }
                
        message_combatd(msg, me, target);

        me->add("neili", -150);

        for (i = 0; i < lvl; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(2 + random(bsy));

        return 1;
}

