
// zhen.c һ������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;



#define ZHEN "��" HIY "һ������" NOR "��"

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        
         if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	    if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 250)
                return notify_fail("��˻�����Ψ�Ҷ��𹦻�򲻹�������ʩչ" ZHEN "��\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 300)
                return notify_fail("�����ɽ�����Ʋ�����죬����ʩչ" ZHEN "��\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ���㣬����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("��û�м�����ɽ�����ƣ�����ʩչ" ZHEN "��\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang")
                return notify_fail("��û��׼����ɽ�����ƣ�����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("force") != "bahuang-gong")
                return notify_fail("��û�м����˻�����Ψ�Ҷ��𹦣�����ʩչ" ZHEN "��\n");

        if (me->query("neili") < 800)
                return notify_fail("�������������㣬����ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIW" \nֻ��$N" HIW "��Ȼ��Ե�����������֮ɫ��˿˿����������䣬ת˲���ѽ�$P�����ư���������\n" +
             "���ô�ʱ��$n" HIW "�Ѿ������֪�������㣬$N" HIW "���С�" HIY "һ������" HIW "����Ȼ������ǰ��������\n" +
             "������$pֻ�����ܵĿ����·��Ѿ����ᣬ��һ��֮���ѽ���������ǰ�����������ʵ����\n"+
             "�԰��ѡ�˲��Ŀ�������ֱ��һ����մ󶴣�ʹ�����ܵ��˾�����һ�����ͣ�\n\n"NOR;

        ap = me->query_skill("force") + me->query_skill("strike") + me->query_skill("dodge") + me->query_skill("parry");
        dp = target->query_skill("force")*2 + target->query_skill("parry") + target->query_skill("dodge");
             
        if (ap *2/3 + random(ap) > dp)
        {
                damage = ap+random(ap/2);
                me->add("neili", -500);

                pmsg = HIR "$n" HIR "�ۼ�$N" HIR "һ���������ƾ���飬�������ȣ�Ȼ��������������֮�У����޿ɱܣ�ֻ��\n" +
                       "��΢Ų���Ų�Ҳ������֮���������$N" HIR "һ��ӡ����ǰ���Ǹ�һ��ʹ����裬ȴ���߹Ǳ�\n" +
                       "��һ��֮����ϣ���Ѫ��ӿ��Ȼʧ�أ�һ����Ѫ�����ӿڱ������˳�����\n\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100, pmsg);
                
                me->start_busy(2);      
        } else
        {
                msg += HIG "����$n" HIG "�����쳣��һ�۵���$N" HIG "���е�����֮���������е����ģ���伫Ϊ����������\n"+
                       "���ֳ�ָ��������$N" HIG "���������ϣ�������ָ����$P���ĵ�" HIR "�ٸ�"
                       HIG "��" HIR "�͹�" HIG "��Ѩ�����$N" HIG "Ѩ����\n" +
                      "�⣬�������޴���й������ʴ�������$P�����ֽ���ڴ����࣬����������ˣ�\n\n" NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

