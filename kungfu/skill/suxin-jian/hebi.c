#include <ansi.h>
#include <combat.h>

#define HEBI "��" HIG "˫��"HIY"���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string type1, type2, msg;
        object weapon1, weapon2;
        int ap, dp, damage,i,n,count;
        
        if (userp(me) && ! me->query("can_perform/suxin-jian/hebi"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (me->query_skill("suxin-jian", 1) < 200)
                return notify_fail("�����Ů���Ľ����ȼ������޷�ʹ��" HEBI " ��\n");
        
        if (me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("���ȫ�潣���ȼ������޷�ʹ��" HEBI " ��\n");
                
        if (me->query_skill("zuoyou-hubo", 1) < 100)
                return notify_fail("������һ������ܵȼ������޷�ʹ��" HEBI " ��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(HEBI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ��˫��������ʩչ" HEBI "��\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");       

        if (me->query_skill_mapped("sword") != "suxin-jian")
                return notify_fail(HEBI"��Ҫ������Ů���Ľ�����\n");        

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" HEBI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
                
        msg = HIW "$N" HIW "����ֹˮ��˫��һ��˫�ַ�ʹȫ�潣������Ů��������Ȼ�������С�\n" NOR;
        msg +=HIR "$n" HIR "����$N" HIR "˫�����裬��ʽ������������Ϊ��һ����ȥ����֪����мܣ�\n"NOR;
        message_combatd(msg, me, target);
                
        n=(int) me->query_skill("zuoyou-hubo", 1) /60;
		if (n>5) n=5;
        count= (int)me->query_skill("suxin-jian", 1)+ (int)me->query_skill("quanzhen-jian", 1)+ (int)me->query_skill("zuoyou-hubo", 1);
        count=count/3;
        
        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count * 2 / 3);

        for (i = 0; i < n; i++)
        {
            if (! me->is_fighting(target))
                 break;
            
            if (random(2) && ! target->is_busy())
                        target->start_busy(1);
            
            COMBAT_D->do_attack(me, target, weapon1, 0);        
            weapon1->move(me, 1);
            weapon2->wield();
            me->map_skill("sword","quanzhen-jian");
            COMBAT_D->do_attack(me, target, weapon2, 0);
            weapon2->move(me, 1);
            weapon1->wield();
            me->set_temp("handing", weapon2);
            me->map_skill("sword","suxin-jian");
        }
        
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count * 2 / 3);
        me->add("neili", -n*70);
        me->start_busy(1 + random(7));
               
        return 1;
}
