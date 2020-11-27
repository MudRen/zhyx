//by xiner 02/3/2009

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if ((int)me->query_temp("baifu"))
                return notify_fail("���Ѿ��������������ˡ�\n");

        if ((int)me->query_skill("qingfu-shenfa", 1)< 200)
                return notify_fail("����������ȼ�����������ʩչ���������\n");

        if ((me->query_skill_mapped("force") != "jiuyang-shengong")) 
                return notify_fail("������û�м���������Ϊ�ڹ�����������ʩչ���������𡹡�\n"); 

        if ((int)me->query_dex() < 30)
                return notify_fail("���������ʹ�á��������𡹾�����\n");

        if ((int)me->query_skill("force", 1)< 200)
                return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

        if ((int)me->query_skill("dodge", 1)< 200)
                return notify_fail("����Ṧ��Ϊ����������ʹ�ô��������\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ����ʹ�á��������𡹣�\n");

        if ((int)me->query("neili") < 250)
                return notify_fail("���ʱ���������㣡\n");

        msg = HIB "$N" HIB "��������񹦣�ʩչ���������𡹾���,"
                  "��Хһ������һֻ����һ���������������Խ��Խ�ᡣ\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("qingfu-shenfa", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50 + cnt;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->set_temp("baifu", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        me->add("neili", -200);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("baifu"))
        {
                me->add_temp("dex", -amount);
                me->delete_temp("baifu");
                tell_object(me, "��ġ����������˹���ϣ��������ջص��\n");
        }
}

