// by Lonely

inherit SKILL;

string *action_msg = ({
        "$N����б��������Ծ������,һ�С�����չ�᡹�����е�$w��$n��$l������ȥ",
        "$Nһ�С����ɽ�ڡ�������$w��$n�����̻�ȥ����δʹ�ϣ�����ֱ��$n��$l",
        "$Nһ�С����Ƽ��ա������е�$w��$n�鿳һ�������к���ת��$n��$l��ȥ",
        "$N���浶���������Ծ��һ�С���ӥ���¡���ֱ��$n�Ҽ磬��ͽ���涵�˸���Բ������ͻ��,б��$n��$l",
        "$N��Ȼ���з���һ�С������ѩ�������е�$w���������⣬��$n��$l��ȥ",
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("�������������ϰ���鵶����\n");
       if ((int)me->query_skill("taiji-shengong", 1) < 10)
               return notify_fail("���̫���񹦻��̫ǳ��\n");
       return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(30),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : "����",
        ]);
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "blade")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query("qi") < 20)
               return notify_fail("����������������鵶����\n");
       me->receive_damage("qi", 20);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}

