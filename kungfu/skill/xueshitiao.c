// xueshitiao.c ѩʨ��
// by Lonely

inherit SKILL;

string *dodge_msg = ({
        "$nһʽ������ѩ�ڡ���һ�»������⿪ȥ����$N���ƻ�����Ρ�\n",
        "$nʹ������ʨ���衹��һ�����$Nͷ��һ��������$N��$n���š�\n",
        "$n�Ų���ȣ�������ң�ʹ����ѩ��ƺӡ���$N��Ҹ�´���$P���ᡣ\n",
        "$n΢Ц����������������һ�٣�һʽ����ѩ���Ρ����$N��һ����\n",
        "$n��ת���ӣ�����һԾ��һʽ��ʨ��ҡͷ�����赭д�ػ���$N��һ�С�\n",
        "$n��������һ�ݣ�ʹ��һʽ��̤ѩ�޺ۡ�Ծ�����ߣ�ƮȻ�䵽һ�ԡ�\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˣ�������ѩʨ����\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 20);
        me->add("neili", -10);
        return 1;
}


