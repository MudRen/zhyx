// shenlong-bashi ������ʽ
// by Lonely

inherit SKILL;

string *action_msg = ({
        "$Nʹһ�С���Ӱ��б������������һĨ����$n��$l��ȥ",
        "$N������ȣ�˫��ʹһ�С��嶡��ɽ��������$n��$l",
        "$N˳��ʹһ�С����в��ȡ����Ƽ�ת�����ƻ��棬����ֱ��$n",
        "$N�˺󼸲���ͻȻ����һ�ƣ�һ�С�������β�����ޱȹ���ػ���$n",
        "$Nʹһʽ�������ơ���ȫ�������ת��˫��һǰһ���͵�����$n���ؿ�",
        "$N����ʹ����Ǭ��������������֧�أ�˫�ȷ�������$n",
        "$N���һ����ʹ����ͬ���ھ���������һ�а�����$n",
        "$N����һ�����������ǳ���״����Ȼ���Ǹ��°�ֱײ��$n",
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "huagu-mianzhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��������ʽ������֡�\n");
        if ((int)me->query_skill("shenlong-xinfa", 1) < 25)
                return notify_fail("��������ķ���򲻹����޷�ѧ������ʽ.\n");
        if ((int)me->query_skill("force", 1) < 25)
                return notify_fail("��Ļ����ڹ���򲻹����޷�ѧ������ʽ��\n");
        if ((int)me->query("max_neili") < 150)
                return notify_fail("�������̫�����޷���������ʽ��\n");
        if (2*(int)me->query_skill("shenlong-xinfa",1) <(int)me->query_skill("shenlong-bashi",1))
                return notify_fail("��������ķ���򲻹����޷�����ѧ������ʽ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force" : 210 + random(60),
                "attack": 40 - random(10), 
                "dodge" : 40 - random(10), 
                "parry" : 40 - random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("�������������������ʽ��\n");
        me->receive_damage("qi", 20);
        me->add("neili", -10);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"shenlong-bashi/" + action;
}

