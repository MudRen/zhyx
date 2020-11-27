// hun.c ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str,mapforce;
        object weapon,weapon2;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("nine-finger", 1);

        if (! me->is_fighting(target))
                return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("finger") != "nine-finger") 
                return notify_fail("��û���þ���������ӡ���޷�ʹ�á����������У�\n");

        if (me->query_skill_prepared("finger") != "nine-finger")
                return notify_fail("��û��׼��ʹ�þ���������ӡ���޷�ʩչ�����������С�\n");

        if (skill < 100)
                return notify_fail("��ľ���������ӡ�ȼ�������������������\n");

        if (objectp(weapon = me->query_temp("weapon")) ||
            objectp(weapon = me->query_temp("handing")) )
                return notify_fail("��������˫�ֲ���ʹ��ָ�����С�\n");

        if (me->query("neili") < 500)
                return notify_fail("�������������\n");
        
        ap = me->query_skill("finger") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        weapon2 = target->query_temp("weapon");
        
        if (me->query_skill_mapped("force"))
                mapforce = to_chinese(me->query_skill_mapped("force"));
        else
                mapforce = "����";
                
        msg = MAG "\n$N" NOR MAG "����Ĭ�о������ԣ�˫��̯������ʽ��ӡ��ס��á�\n" +
               "һʱ֮�䣬������ӡ������ǿ�ҵ�" HIW + mapforce + NOR + 
               MAG "���޼᲻�ݵ�ɱ��$n" NOR MAG "��\n" NOR;
                
        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = "\n����һ�����" HIW " �� �� �� �� �� �� �� �� ǰ !\n" NOR +  
              "ֻ��$N������ն���˫�ֺ�ʲ����ƿ��������˷�ӿ����������أ���ʹЭ��˫�����Ǳ��޿ɱܣ� \n" + 
              "����" HIW "����������ӡ" NOR "�ռ�ʽ�� " HIY "��ӡ��һ" NOR "��\n" NOR; 

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                if (weapon2)
                        msg += MAG "$n" NOR MAG "��$N" MAG "�������ͣ���������ֵ�������" + weapon2->name() + 
                               NOR MAG "�����Ӱ������ˮй��ͨ\n" + 
                               "$N" NOR MAG "�����������ţ�" HIW "��������" NOR MAG "�Ծ����಻����$n" NOR MAG "�޿��κ�֮�£����������ţ�\n" NOR; 
                else
                        msg += MAG "$n" NOR MAG "��$N" MAG "�������ͣ���������ֵ����������˫�Ʒ������$N\n" + 
                               NOR MAG "$N" NOR MAG "�����������ţ�" HIW "��������" NOR MAG "�Ծ����಻����$n" + 
                               NOR MAG "�޿��κ�֮�£����������ţ�\n" NOR;
               
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                if (weapon)
                        msg += MAG "$n" NOR MAG "��$N" NOR MAG "�������ͣ���������ֵ�������" + weapon2->name() +
                               NOR MAG "�����Ӱ������ˮй��ͨ\n" +
                               "$N" NOR MAG "������һ����" HIW "��������" NOR MAG"��Ȼ��գ�\n" NOR;

                else
                        msg += MAG "$n" NOR MAG "��$N" NOR MAG "�������ͣ���������ֵ����������˫�Ʒ������$N\n" + 
                               NOR MAG "$N" NOR MAG "������һ����" HIW "��������" NOR MAG "��Ȼ��գ���$n" NOR MAG "Ҳ��$N" NOR MAG "�����Ѫ��ӿ��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
        me->add("neili",-damage/3);
        return 1;
}

