// hun.c ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,force;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("daya-jian", 1);

        if (! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("sword") != "daya-jian") 
                return notify_fail("��û���ô��Ž������޷�ʹ�ô������׾��У�\n");

        if (skill < 100)
                return notify_fail("��Ĵ��Ž����ȼ�������������������\n");

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

        msg = HIC "\n$N" HIC "���д���ھ�����������" NOR CYN "���ŹŽ���" HIC "��ʱ���������쾡�£�\n" +
              weapon->name() + HIC "��ͬ����һ�����û������콣Ӱ����$n" HIC "����������\n\n" NOR;

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        force = me->query_skill_mapped("force");
        if (!stringp(force)) force = "force";
        
        msg = HIM "\n$N" HIM "һ���֮�󣬺�Ȼ��ʽһ�������μ��ˣ�������������֮�⡣\n"
              "$n" HIM "��$N" HIM "���в��̣���Ҫ���Ϸ�����$N" HIM "ͻȻ�̽�������˫Ŀ����$n" HIM "��\n"
              "$n" HIM "����Ϭ����Ŀ���ŵ�һ���£�����$N" HIM "�Ǻ��⣬��ͷһ����㯡�\n"
              "����$N" HIM "���һ��:\n"
              HIW "����������ˮ����׳ʿһȥ�ⲻ����!\n"
              HIM "�����л�����ǿ����" HIR + to_chinese(force)+ HIM"��$n" HIM "����������ҡ�\n"
              "��ʱ��ֻ��$N" HIM "�˽���һ�������ǡ������磬����$n" HIM "������" NOR CYN "���ŹŽ���" HIM "��" HIW "������ʽ��" HIM"����\n\n" NOR;

        weapon2 = target->query_temp("weapon");
        
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += HIM "$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "һ�����" + weapon->name() + HIM "�Ľ���\n"
                               "$N" HIM "�����������ţ�" HIW "������ʽ��" HIM "�Ծ�һ��ֱǰ��$n" HIM "����" + weapon2->name() + HIM "Ϊ$N�����ֹ���룬���������\n" NOR;
                else
                        msg += HIM "$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N" HIM "\n"
                               "$N" HIM "�����������ţ�" HIW "������ʽ��" HIM "�Ծ�һ��ֱǰ��$n" HIM "�޿��κΣ����������ţ�\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon2)
                        msg += HIM "$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "һ�����" + weapon->name() + HIM "�Ľ���\n"
                               "$N" HIM "������һ����" HIW "������ʽ��" HIM "��Ȼ��գ�\n" NOR;
                else
                        msg += HIM "$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N" HIM "\n"
                               "$N" HIM "������һ����" HIW "������ʽ��" HIM "��Ȼ��գ���$n" HIM "Ҳ��$N" HIM "�����Ѫ��ӿ��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


