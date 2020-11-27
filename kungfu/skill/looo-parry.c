 // douzhuan-xingyi ��ת����

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({
        "ֻ�������ϡ�һ����$n��$p����һ�У�������$N��һ����\n",
        "���Ǳ�$n�����б���ж����\n",
        "����$n����һ�࣬����ת�����е�$p����$N�о���������ʩ��\n",
});

string *unarmed_parry_msg = ({
        "���Ǳ�$p˫��һ�ƣ�$N�Ĺ��ƶ�ʱ���˷���\n",
        "$n����һת��$Nֻ���õ����е�����ȫ�����䵽�˿մ���\n",
        "����$N�о�����޻���һ����˵�����Ĺ��졣\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("zihui-xinfa", 1) < 100)
                return notify_fail("����ϻ��ķ���򻹲���������ѧϰ��ת���ơ�\n");

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("��Ļ����мܼ������յĻ������������޷�ѧϰ��ת���ơ�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��ת����ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed valid_damage(object target, object me, int damage, object weapon)
{


        string msg;
        mapping result;
        int ap, dp;

        if ((int) me->query_skill("douzhuan-xingyi", 1) < 100)
        return;

       dp = target->query_skill("force", 1);
       ap = me->query_skill("parry", 1) + me->query_skill("zihui-xinfa", 1) / 4;



        if (ap + random(ap) > dp)
        if ((int) me->query_skill("zihui-xinfa", 1) < 280)
        {
                result = ([ "damage" : -damage ]);

                switch(random(2))
                {
                case 0:
                        result += ([ "msg" : HIC "$N" HIC  "��Ȼ,\n" NOR ]);

                     damage = 200;   
                me->add("neili", -30);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,2,
                       HIR "\n$N" HIR "������������ͼ��"
                       HIR "$n" HIR "�Ĺ���ת��"
                       HIR "$n" HIR "�Լ�����!\n\n"
                       HIY "$N" HIY "���һ�����䲻��"
                       HIY "���һ���������ֵ�!!\n" NOR);
                 message_combatd(msg, me, target);

                        break;


                default:
                        result += ([ "msg" : HIC "$N" HIC "һ���ۿ�������$n"
                                             HIC "��Ȼ��$n" HIC "����һж��"
                                             "��$N" HIC "�Ĺ������������Ρ�\n" NOR ]);
                        break;
                }
                       return result;
           }

      else
           {

                result = ([ "damage" : -damage ]);

                switch(random(5))
                {
                case 0:
                        result += ([ "msg" : HIY "$N" HIY "ֻ����ȫ���ܵ������𵴣���ɫ��Ĳ԰ס�\n" NOR ]);



                        message_vision(HIR "\n\n̸Ц�䣬" HIR "$N" HIR "��ʹ��" HIR "$n" HIR "��������,"
                                       HIR "��" HIR "$n" HIR "�Ĺ���ת��"
                           HIR "$n" HIR "�Լ�����!\n\n"NOR,me,target);
                        target->receive_damage("qi", damage / 5);
                        me->add("neili", -30);

                        break;
                case 1:
                        result += ([ "msg" : HIY "$N" HIY "��ôҲ�벻��" HIY "$n" HIY "�ܹ�ʹ���Լ��ĳ���������"
                                             HIY "ֻ����ȫ���ܵ������𵴣����İ��ʹ��һ����Ѫ���!!\n"NOR ]);


                        message_vision(HIR "\n\n��Ȼ���ذ���" HIR "$N" HIR "ʹ��" HIR "$n" HIR "�ľ��У�"
                                       HIR "�����������ڼ�������" HIR "$n" HIR "��ȥ��\n\n"NOR,me,target);

                        target->receive_damage("qi", damage / 2);
                         me->add("neili", -100);

                        break;

                case 2:
                        result += ([ "msg" : MAG "�����һ��������������" MAG "$n" MAG "һ��һ����"
                                             MAG "$n" MAG "��������Խ����������һ�ԡ�\n" NOR ]);
                        break;


                case 3:
                        result += ([ "msg" : MAG "����һ����������" MAG "$N" MAG "��" MAG "$N" MAG "����"
                                             MAG "$n" MAG "������"
                                             MAG "Ī��������ﻬ��һ�� ��\n" NOR ]);
                        break;


                default:
                        result += ([ "msg" : MAG "ֻ�������ϡ�һ����" MAG "$n" MAG "��������һ�У�"
                                             MAG "������" MAG "$N" MAG "��һ����\n" NOR ]);
                        break;
                }
                return result;
        }


}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}
