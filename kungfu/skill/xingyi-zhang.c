// xingyi-zhang ��ת������
// by Lonely

inherit SKILL;

string *action_msg = ({
        "$Nʹһ�С����α�Ӱ����˫�ֻ��˸���Ȧ������$n��$l",
        "$N�����鰴������ʹһ�С����ǵ�㡹����$n��$l��ȥ",
        "$N˫����ȭ����ǰ��󻮻���һ�С������Ƕ�������$n��$l",
        "$N�����黮������һ�ǡ��嶷�ǳ�������$n������",
        "$Nʩ�����������ǡ������ֻ���$n��$l�����ֹ���$n���ɲ�",
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)  
{
        object me = this_player();
        mapping myfam;

        if (mapp(myfam = me->query("family")) && myfam["master_name"] == "Ľ�ݲ�") 
                 return combo == "canhe-zhi";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ת�����Ʊ�����֡�\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 15)
                return notify_fail("�����Ԫ����򲻹����޷�ѧ��ת�����ơ�\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷�����ת�����ơ�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force" : 260 + random(60),
                "attack": 50 + random(10), 
                "dodge" : 50 + random(10), 
                "parry" : 50 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 60)
                return notify_fail("���������������ת�����ơ�\n");
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xingyi-zhang/" + action;
}

