// yanling-shenfa.c ������
// by Lonely

inherit SKILL;

string *dodge_msg = ({
        "$nһʽ�������Ϸɡ�����Žż�����ҽ���շ�����������������ˮ�㻬�����ࡣ\n",
        "$nһʽ��һҶ��Ŀ����������ת��˫�Űϵض��𣬶�ʱ������$N���������ơ�\n",
        "$nһʽ��˫��ַɡ�������˫������߳����ţ���ʱ�䵽$N���Ͽա�\n",
        "$nһʽ�����ӳ�������ͻȻ������ǰ�ˣ���������ĳ���$N����$N������롣\n",
        "$nһʽ����������������������ȫ��Χ��$N������ת����$N��æ���ң�$n���䵽����Զ�ĵط���\n",
        "$nһʽ������������˫����յ�أ������ݷ����У���$Nͷ����Ծ������\n",
        "$nһʽ�����ӻ�ͷ����˫�����������ƣ�����������Ʈ����ʱ����$N���������ơ�\n",
        "$nһʽ�����Ϲ鳲�������������ݰ㼱ת�������γ�һ�������У���$N������䡣\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˣ���������������\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("�������������\n");
        me->receive_damage("qi", 20);
        me->add("neili", -10);
        return 1;
}

 

