// piaoyi-shenfa.c Ʈ����
// by Lonely

inherit SKILL;

string *dodge_msg = ({
        "$n������Ȼ������󻬳����࣬��������������ס�Կ�Ѹ���ڵ��ַ���󳶶�һ�㡣\n",
        "$n˫ϥ�����������䣬��Ȼ����������֮��Ӳ�ֹ�ֺͽ�ʬ���졣\n",
        "����$n����̧�ţ�ͻȻ֮�䵹�����࣬һת����������֮�⡣\n",
        "ֻ���ú���һ����$n���ӱ�ֱ������з���ֱ������ߣ��������һ�С�\n",
        "$n��Ȼ���ΰ����ڿ��м�����������ת�ĸ�Ȧ�ӣ���ת���ߣ�һ��ת����������֮�⡣\n",
        "$n����Ȧ�ӣ���ת�������������㣬�ڼ䲻�ݷ�֮�ʶ�������С�\n",
        "$n���һ�����������ܣ����ʹ����������б�ɶ��ϣ���ʱ�Ķ������һ�С�\n",
        "$n����һ�����̣���һ������һ������תһȦ����תһȦ�������˿�ȥ��\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(object me)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 40)
                return notify_fail("�������̫���ˣ�������Ʈ������\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 30);
        me->add("neili", -20);
        return 1;
}

int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("piaoyi-shenfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}


