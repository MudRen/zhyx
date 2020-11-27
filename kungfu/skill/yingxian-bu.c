// yingxian-bu.c ���ɲ�
// By Alf, Last Update 2001.10

// �׽����������������������ѩ������ϼ��ͨ�������������
// ����β�˭�ŵ������췽�����������Ⱥ��ͬ�С�������߽�

inherit SKILL;

mapping *action = ({
([    "action" : "$n��ⷢ����һʽ���׽������������������κ󵴶�����������һ�ԡ�\n",
    "dodge"  : 10
]),
([    "action" : "$n˫�����㣬һʽ�����������ѩ����ȫ��Ϊһ����Ӱ��������ת���ݡ�\n",
    "dodge"  : 20
]),
([    "action" : "$n��������������˫�㣬һʽ������ϼ��ͨ����������ƾ�յ��ض���\n",
    "dodge"  : 30
]),
([    "action" : "$n˫�㽻���ż�Ÿ��࿿��һʽ����������¡�����������ˮ�㻬�����ࡣ\n",
    "dodge"  : 40
]),
([    "action" : "$n�������Σ�һʽ������β�˭�ŵ�����$Nֻ����ǰһ����������$n����Ӱ��\n",
    "dodge"  : 50
]),
([    "action" : "$n���ε��ӣ�һʽ�����췽������������������ת���˳����ɿ��⡣\n",
    "dodge"  : 60
]),
([    "action" : "$nϢ���������������һʽ������Ⱥ��ͬ�С�������ƮȻ����\n",
    "dodge"  : 70
]),
([    "action" : "$nȫ���ֱ��һʽ��������߽ࡹ���εض����ڰ����һת�������������⡣\n",
    "dodge"  : 80
])
});

mapping query_action(object me, object weapon)
{
    int zhaoshu, level;

    zhaoshu = sizeof(action);
    level   = (int) me->query_skill("yingxian-bu",1);

    if (level < 60 )
    zhaoshu--;

    if (level < 50 )
    zhaoshu--;

    if (level < 40 )
    zhaoshu--;

    return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
    return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
    return 1;
}

string query_dodge_msg(string limb)
{
    object me, ob;
    mapping action;

    me = this_player();
    action = query_action(me, ob);

    return action["action"];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
        return notify_fail("�������̫���ˣ����������ɲ���\n");
    me->receive_damage("qi", 30);

    return 1;
}


