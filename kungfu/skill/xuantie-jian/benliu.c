//benliu.c �󺣱���
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int) (me->query_skill("sword"));
        j = skill/3;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("���󺣱�����ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query("gender") != "����")
                return notify_fail("�㲻����������,�޷�ʹ����˾�����\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")

                return notify_fail("�����ʹ����������ʹ�á��󺣱�������\n");

        if(me->query_skill_mapped("sword") != "xuantie-jian") 
                return notify_fail("��û���������������޷�ʹ�ô󺣱�����\n");

        if( (int)me->query_skill("xuantie-jian", 1) < 220 )

                return notify_fail("�������������������죬ʹ�������󺣱�����������\n");

        if ((int)weapon->query_weight() < 30000)

                return notify_fail("�����е�" + weapon->name() + "�����������޷�ʩչ�󺣱�����\n");

        if( (int)me->query_skill("nuhai-kuangtao", 1) < 220 )

                return notify_fail("���ŭ�����εȼ���������ʹ�������󺣱�����������\n");

        if( (int)me->query_skill("force") < 200 )

                return notify_fail("����ڹ��ȼ�����������ʹ�á��󺣱�������\n");

        if ((string)me->query_skill_mapped("force") != "nuhai-kuangtao")
                return notify_fail("��û�м���ŭ�������ķ����޷�ʹ������������\n");

        if( (int)me->query_str() < 45 )

                return notify_fail("�������������ǿ����ʹ�������󺣱���������\n");


        if ( me->query_skill_mapped("sword") != "xuantie-jian")


               return notify_fail("��û�н����޷�ʹ�á��󺣱�������\n");

        if( (int)me->query("max_neili") < (me->query_skill("force")+j+2500) )

                return notify_fail("���������Ϊ��Ҫ��һ����ߣ�����ʹ�����󺣱��������ֱ�ɱ��\n");

        if( (int)me->query("neili") < (me->query_skill("force")+j) )

                return notify_fail("����������̫��������ʹ�á��󺣱�������\n");


        msg = HIM "\n$N" HIM "���һ�����ֳ�"+ weapon->name() + HIM "Ю���˳�ӿ֮��,������죬������ᣬ����Ȼ\n"
              HIM "�����������֮���������ߴΣ���" HIM "$n" HIM "ϯ���ȥ��\n" NOR;
        message_combatd(msg, me, target);

        me->add_temp("apply/str", 10);
        me->add_temp("apply/damage", j);
        me->add_temp("apply/attack", j);

        me->add("neili", -(me->query_skill("force")+400));



        for (i = 1; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                msg = HIR "\n�������飬�����ݺᣡ��\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(4);

        target->start_busy(1);

        me->add_temp("apply/str", -10);
        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -j);

        return 1;
}

