// jianqi.c �����ֻ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        string *learned;
        object weapon, weapon2;
        string type,perform_type;
        mapping prepare;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("liudaolunhui-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("�����ֻؽ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("sword") != "liudaolunhui-sword") 
                return notify_fail("��û���������ֻؽ������޷�ʹ�ý������У�\n");

        if (skill < 100)
                return notify_fail("��������ֻؽ����ȼ�������������������\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "��������Ĭ����ͨ����Χ��������������" + weapon->name() + HIG
              "ͨ��̺����·���Χһ�ж��Ѿ��������ˡ�\n" NOR;

        msg += HIY "$N" HIY "��$n" HIY "��Ѫ��Ӳ���޷�����֮�ʣ�����" + weapon->name() + HIY
              "����ƫ�棬����$n" HIY "ȫ�������Ѩ��˳���������С�\n" NOR;

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg = HIW "��Ȼ$N" HIW "���һ����" + weapon->name() + HIW
                      "ңңָ��$n��\n" HIW "һ���������ɫ��������ӿ�籡��������Χ�̹ǵĺ���Ϯ��$n" HIW "��ȫ��\n" + 
                      "����$n" HIW "��Ȼ������ȴΪʱ����" HIR "����" HIW "��͸�������ȫ����Ѫ���̣��·𱻶����ˣ�\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg = HIW "$N" HIW "���������е�" + weapon->name() + HIW "Ѱ���Ż��ᣬ"
                      "����$n" HIW "ƴ��������$N" HIW "һʱ��Ҳ�޻��ɳˡ�\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


