// �沨������

inherit SKILL;
string *dodge_msg = ({
        "$nһʽ���沨�����������������е�һҶ����һ��������$N����ʽ���ߣ��벻������\n",
        "$nһʽ��������ӿ���������Ծ������к�Ȼ���ˣ���ƮƮ����������֮�⡣\n",
        "$nһʽ�������İ�������������$N���ڼ䲻�ݷ�֮�ʱܿ���$N��һ�С�\n",
        "$nһʽ��˳ˮ���ۡ������ӱ�������㣬����һж���ͽ�$NϮ������ʽ�Ƶ�һ�ԡ�\n",
        "$nһʽ��������ɳ�����ݸ߷��ͣ���$N�ۻ�����֮ʱ�ѱܿ��˴��С�\n",
        "$nһʽ��������������������ϣ��������ܾ��˵Ĵ򷨣�$Nһ��֮�£�$n�Ѱ�ȫ����\n",
        "$nһʽ���Ǻӵ�������˫��΢�ţ��������ƽƽ�ɳ���������������С�\n",
        "$nһʽ����ʹ��ۡ���ٿ��Զ�Σ�ֻһ���䣬���Ӿ�����ʮ�ɿ��⣡\n",
});

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
        return dodge_msg[random(sizeof(dodge_msg))];
}


int practice_skill(object me)
{
        if( (int)me->query("qi") < 40 )
                return notify_fail("�������̫���ˣ��������沨��������\n");
        me->receive_damage("qi", 30);
        return 1;
}

