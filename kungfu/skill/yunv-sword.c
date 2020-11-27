// yunv-sword.c ��Ů����(��ɽ)
// by Lonely

#include <ansi.h>

inherit SKILL;

string *action_msg = ({
        "$Nʹһ��" HIM "���������ߡ�" NOR "����̤�й�������$wֱָ$n$l",
        "$N������ת��һ��" HIR "�������޷졹" NOR "������һƬ��Ӱ������$n��$l",
        "$N�趯$w��ʹ��һ��" HIB "��ҹ��ԧ�졹" NOR "���������ң���˸������ֱ��$n��$l",
        "$N��Ȼ����ֱ�ϣ�һ��" MAG "��С�����ˡ�" NOR "������$w�������ϴ���$n��$l",
});

int valid_learn(object me)
{
        object ob;
        
        if ((string)me->query("gender") != "Ů��" )
                return notify_fail("��Ů������ֻ��Ů�Ӳ��������书��\n");
                
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������û�а취����Ů������\n") ;
                
        if ((string)me->query_skill_mapped("force") != "zixia-shengong")
                return notify_fail("��Ů�������������ϼ�񹦲�������\n");
                
        if (! objectp(ob = me->query_temp("weapon"))
        ||  (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�ѽ�������������\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(40),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70
        ||  (int)me->query("neili") < 70)
                return notify_fail("�����������������û�а취��ϰ��Ů������\n");
                
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        
        return 1;
}

int query_effect_parry(object attacker, object me) 
{
        int lvl;
        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("yunv-sword", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}


string perform_action_file(string action)
{
        return __DIR__"yunv-sword/" + action;
}

