// ��������Դ��书���� ԭ��maxim@nju_fengxue��д������xgchen@zzfy�޸�
// chhu
// ��ս��Ұ
// ����һֻСС��[2;37;0m
// 42941418
// Ů��
// sword
// �������





inherit SKILL;

////////////////////////////////

mapping *action = ({

// ZHAOSHI :0

([
"action" :"$N����һԾ������$wһ��$HIW$�����к�ء�$NOR$��׼��$lбб�̳�һ��",
"force" :50,
"dodge" :20,
"damage_type": "����",
"attack" : 50,
"parry" : 50,
"lvl" : 0,
"skill_name" : "���ذ�"
]),
 });
// ZHAOSHI :1
int valid_learn(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon"))
     || (string)weapon->query("skill_type") != "sword") return notify_fail("��ʹ�õ��������ԡ�\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("�������̫�����޷���"+"�������"+"��\n");
        return 1;
}
int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
    level = (int)me->query_skill("chhu-sword",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword") return notify_fail("��ʹ�õ��������ԡ�\n");    if( (int)me->query("qi") < 100 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        if( (int)me->query("neili") < 100 )
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        me->receive_damage("qi", 90);
        me->add("neili", -70);
        return 1;
} //total 34 lines!
string perform_action_file(string action)
{
        return __DIR__"meskill/" + action;
}
