// anying-fuxiang.c
// by Lonely

inherit SKILL;
 
string *dodge_msg = ({
        "ֻ��$nһ�С�������硹���������ϱ�ֱ���������࣬�����$N��һ�С�\n",
        "$nһ�С�������֡�������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
        "$nʹ��������չ�᡹����һ��ƮȻ�ݳ��������ŵء�\n"
        "����$nһ�С����ն�����������Ʈ��������һ�ݣ����ѱܿ���\n",
        "$nһ�С�Ӱ�����ơ���������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$nʹ��������޳���������һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻��أ�һ�С���ȥ���⡹������Ծ�����ߣ����˿�ȥ��\n",
        "$nһ�С�������ҡ�������΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) 
{ 
        return usage == "dodge"; 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˣ���������Ӱ���㡣\n");
        if ((int)me->query("neili") < 50)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 50);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"anying-fuxiang/" + action;
}


