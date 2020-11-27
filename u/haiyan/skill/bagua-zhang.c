// SKILL bagua-zhang.c
// ���ԣ���ָ�����ޣ�̫�����������㣨�����������루���������ҡ�Ǭ��̫������
// ̫�������ǣ���������
// ����������̫����������������̫����
// ����������
// Create for Haiyan 2002

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N��̤��Ǭ��λ������һ�ƣ����ƻ�������$n",
        "force" : 150,
        "attack": 5,
        "dodge" : 60,
        "parry" : 70,
        "lvl"   : 10,
        "damage_type" : "����"
]),
([      "action" : "$N�ҽ������ޡ�λ����ɫ���أ�˫����ƮƮ������$n",
        "force" : 180,
        "attack": 8,
        "dodge" : 80,
        "parry" : 95,
        "lvl"   : 50,
        "damage_type" : "����"
]),
([      "action" : "$N����һ�ˣ��ҽ��Ѳ��ڡ�����λ��˫�ƻó�һƬ��Ӱ����$n�������ڡ�",
        "force" : 210,
        "attack": 13,
        "dodge" : 102,
        "parry" : 118,
        "lvl"   : 80,
        "damage_type" : "����"
]),
([      "action" : "$N����һת��˫�ŷ������㡹λ��������$n��������",
        "force" : 260,
        "attack": 18,
        "dodge" : 126,
        "parry" : 140,
        "lvl"   : 100,
        "damage_type" : "����"
]),
([      "action" : "$N���һ�����ҽ�������λ��˫����������$n",
        "force" : 300,
        "attack": 23,
        "dodge" : 160,
        "parry" : 170,
        "lvl"   : 130,
        "damage_type" : "����"
]),
([      "action" : "$N����������վ�ڡ��롹λ��˫��ƽ�ӣ�����$n",
        "force" : 350,
        "attack": 28,
        "dodge" : 175,
        "parry" : 190,
        "lvl"   : 180,
        "damage_type" : "����"
]),
([      "action" : "$N�ҽ�һ̧�������򡸶ҡ�λ��ֻ��һƬ��Ӱ����$n",
        "force" : 360,
        "attack": 34,
        "dodge" : 205,
        "parry" : 215,
        "lvl"   : 250,
        "damage_type" : "����"
]),
([      "action" : "$N����վ�ڡ�����λ������һ�Σ����ƻ�������$n",
        "force" : 380,
        "attack": 42,
        "dodge" : 230,
        "damage": 10,
        "parry" : 235,
        "lvl"   : 300,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="parry" || usage=="strike"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������ơ�������֡�\n");

        if ((int)me->query_skill("taiji-shengong") < 100)
                return notify_fail("���̫���񹦻�򲻹����޷����������ơ���\n");

        if ((int)me->query_skill("taoism") < 250)
                return notify_fail("��ĵ�ѧ�ķ���Ϊ�������޷����������ơ���\n");

        if ((int)me->query_skill("taiji-quan") < 150)
                return notify_fail("���̫��ȭˮƽ̫�ͣ��������������ơ���\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷����������ơ���\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bagua-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ġ������ơ���\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("bagua-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mapping result; 
        int ap, dp, acter; 

        if ((int)me->query_skill("bagua-zhang", 1) < 100 || 
            me->query_temp("weapon")) 
                return; 

        ap = (ob->query_skill("force", 1) + 
             ob->query_skill("dodge", 1) +
             ob->query_skill("martial-cognize", 1)) / 3 +
             ob->query_skill("count", 1); 
        if (me->query("character") == "��������" || me->query("character") == "������") 
             acter = 4; 
        else
             acter = 5; 
        dp = (me->query_skill("parry", 1) +
             me->query_skill("bagua-zhang", 1) +
             me->query_skill("martial-cognize", 1) + 
             me->query_skill("taoism", 1)) / acter; 

        if ( ap / 2 + random(ap) < dp ) 
        { 
                result = ([ "damage": -damage ]); 

                switch (random(4)) 
                { 
                case 0: 
                        result += (["msg" : HIC "$n" HIC "�ŲȰ��Է�λ����$N"
                                            HIC "���ܿ������ߣ�$N"
                                            HIC "��ǰһ��������ȫȻ��ա�\n" NOR]); 
                        break; 
                case 1: 
                        result += (["msg" : HIC "$n" HIC "˫�������ζ�������ǰ"
                                            HIC "�γ�һ�ɾ޴����������$N"
                                            HIC "�Ĺ�����Ϊ���С�\n" NOR]); 
                        break; 
                case 2: 
                        result += (["msg" : HIC "$n" HIC "����$N"
                                            HIC "����ʽ��·������һ����$N" 
                                            HIC "�����Լ�����ʽȫ������������"
                                            HIC "��æ���Ծ����\n" NOR ]); 
                        message_vision(HIY "$N" HIY "��ʽһ�䣬ʩչ��̫����������������������"
                                       HIY "$n" HIY "�Ĺ���ȫ��ת��" 
                                       HIY "$n" HIY "�Լ�����!\n"NOR,me,ob); 
                        ob->receive_damage("qi", damage / 6); 
                        me->add("neili", -30); 
                        break; 
                default: 
                        result += (["msg" : HIC "$n" HIC "����һ�٣�˫�ƻó�������Ӱ��ʹ$N"
                                            HIC "������ȫ������һ�ߡ�\n" NOR]);
                        break; 
                } 
                return result; 
        } 
} 

int practice_skill(object me)
{
        int cost;
        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˡ�\n");
        cost = me->query_skill("bagua-zhang", 1) / 2 + 80; 
        if ((int)me->query("neili") < cost)
                return notify_fail("��������������������ơ���\n");

        me->receive_damage("qi", 80);
        me->add("neili", -cost);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"bagua-zhang/" + action;
}

