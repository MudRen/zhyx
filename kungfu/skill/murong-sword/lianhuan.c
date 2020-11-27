// lianhuan.c Ľ�ݽ���
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
      {
        int count, skill, i, j, d;
        object weapon;

        i = me->query_skill("murong-sword",1)/5;
        j = me->query_skill("canhe-zhi",1)/5;
        d = me->query_skill("zihui-xinfa",1)/5;
        skill = me->query_skill("murong-sword",1);

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("�߽�����ָֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("murong-sword", 1) < 120 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ���߽�����ָ��\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("������û�н����޷�ʹ���߽�����ָ��\n");

        if((int)me->query_skill("canhe-zhi", 1) < 120 )
                return notify_fail("��Ĳκ�ָ����δ���ɣ�����ʹ���߽�����ָ��\n");

        if(me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û���òκ�ָ���޷�ʹ���߽�����ָ��\n");

        if(me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("��û��׼���κ�ָ���޷�ʹ���߽�����ָ��\n");

        if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ���߽�����ָ��\n");

        if((int)me->query_temp("lianhuan"))
                return notify_fail("������ʹ���߽�����ָ��\n");

        if((int)me->query_skill("sword", 1) < 120 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ���߽�����ָ��\n");

        if((int)me->query_skill("finger", 1) < 120 )
                return notify_fail("��Ļ���ָ��������죬�����ڽ�����ʹ���߽�����ָ��\n");

        message_vision(MAG"\n$Nʹ���߽�����ָ������һת������ʳָ���ŵ�����ֻ������ָ�������ӳ��ֱϮ$n��\n"NOR, me,target);
        me->add("neili", -300);
        me->add("jing", -50);

        count = (i+j)/3*2;
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", d);
        me->set_temp("lianhuan",1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count, d :), skill / 2);
        return 1;
}



void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("lianhuan"))
        {
            me->add_temp("apply/attack", -amount);
            me->add_temp("apply/damage", -amount1);
            me->delete_temp("lianhuan");
                tell_object(me, HIY "��ġ��߽�����ָ������������ϣ����ص���,�����չ���\n" NOR);
        }
}
