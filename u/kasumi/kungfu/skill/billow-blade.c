
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$NͻȻʹ��һ�С�������ɳ��������$w�����������ֱ��$n��$l",
        "skill_name" : "������ɳ",
        "force"  : 300,
        "attack" : 100,
        "dodge"  : 80,
        "parry"  : 100,
        "lvl"    : 0,
        "damage" : 110,
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С��Ʋ�����������$w�����ƶ������صĺ���$n��$l",
        "skill_name" : "�Ʋ�����",
        "force"  : 340,
        "attack" : 120,
        "dodge"  : 100,
        "parry"  : 110,
        "lvl"    : 50,
        "damage" : 120,
        "damage_type" : "����",
]),
([      "action" : "$N����һ����һ�С�Ǯ�����Ρ���$w��$n��$lбб�ó�һ��",
        "skill_name" : "Ǯ������",
        "force"  : 380,
        "attack" : 130,
        "dodge"  : 110,
        "parry"  : 120,
        "lvl"    : 100,
        "damage" : 130,
        "damage_type" : "����",
]),
([      "action" : "$N���һԾ��ֱ��һ��������һ������$w�ݺݵĿ���$n��$l",
        "skill_name" : "����һ��",
        "force"  : 420,
        "attack" : 140,
        "dodge"  : 120,
        "parry"  : 130,
        "lvl"    : 150,
        "damage" : 140,
        "damage_type" : "����",
]),
([      "action" : "$N����$w���ⷺ�ף�һ�С��δ��ȱ̡���������Ϣ��ն��$n��$l",
        "skill_name" : "�δ��ȱ�",
        "force"  : 460,
        "attack" : 150,
        "dodge"  : 130,
        "parry"  : 140,
        "lvl"    : 200,
        "damage" : 150,
        "damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_neili") < 5000 )
                return notify_fail("�������������û�а취�����˵�����\n");
               
        if (me->query("dex") < 34)
                return notify_fail("�����������㣬������ϰ���˵�����\n");       

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 200)
                return notify_fail("��Ļ����������̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("billow-blade",1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ĳ��˵�����\n");
                
        return 1;
}

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
        level   = (int) me->query_skill("hujia-daofa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}



int practice_skill(object me)
{ 
        object weapon;
        

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "blade" )
                return notify_fail("���������һ�ѵ���������������\n");
                
         if ((int)me->query("qi") < 200)
                return notify_fail("������������������˲��˵�����\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("������������������˲��˵�����\n");

        me->receive_damage("qi", 200);
        me->add("neili", -300);      

        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"billow-blade/" + action;
}


