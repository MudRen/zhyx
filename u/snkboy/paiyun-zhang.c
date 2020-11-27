//paiyun-zhang.c ������
//By dream@rx
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С�����������˫��ǰ���ĳ����Լ�������ַ���������$n",
        "force"  : 300,
        "attack" : 220,
        "dodge"  : 100,
        "parry"  : 100,
        "damage" : 150,
        "lvl" : 0,
        "damage_type": "����"
]),
([      "action" : "$Nһ�С��ƺ����Ρ�˫�ƴ󿪴�ϣ�����һ������һ��ӿ��$n",     
        "force"  : 330,
        "attack" : 250,
        "dodge"  : 130,
        "parry"  : 130,
        "damage" : 180,
        "lvl" : 50,
        "damage_type": "����"
]),
([      "action" : "$Nһ�С������ɾ�������������ת��������γ�һƬ��������$n",
        "force"  : 360,
        "attack" : 280,
        "dodge"  : 160,
        "parry"  : 160,
        "damage" : 210,
        "lvl" : 100,
        "damage_type": "����"
]),
([      "action" : "$N���鱯�ߣ�һ�С����Ʋҵ�����Ѷ�ײ����ڶ�֮�ƹ���$n",
        "force"  : 390,
        "attack" : 310,
        "dodge"  : 190,
        "parry"  : 190,
        "damage" : 240,
        "lvl" : 100,
        "damage_type": "����"
]),
([      "action" : "$N��Ȼ���Ծ��һ�С������콵������$n��ͷ��ȥ",
        "force"  : 420,
        "attack" : 340,
        "dodge"  : 220,
        "parry"  : 220,
        "damage" : 270,
        "lvl" : 150,
        "damage_type": "����"
]),
([      "action" : "$Nʹ��һ�С�������ˮ���������Σ�Χ��$n������ͣ",
        "force"  : 450,
        "attack" : 370,
        "dodge"  : 250,
        "parry"  : 250,
        "damage" : 300,
        "lvl" : 200,
        "damage_type": "����"
]),
([      "action" : "$Nʹ�������ƴ��¡������ƴӲ���˼��ĽǶ�����$n",
        "force"  : 480,
        "attack" : 400,
        "dodge"  : 280,
        "parry"  : 280,
        "damage" : 330,
        "lvl" : 200,
        "damage_type": "����"
]),
([      "action" : "$NѸ�ٴܵ�$n����ǰ��һ�С����Ʊ��ա���ע��������˫�Ƶ�ͷѹ��$n",
        "force"  : 520,
        "attack" : 430,
        "dodge"  : 310,
        "parry"  : 310,
        "damage" : 360,
        "lvl" : 300,
        "damage_type": "����"
]),
([      "action" : HIW"$Nʹ����˺�����ơ���һ����أ�һ�����죬Ȼ��˫������$n����һ��"NOR,
        "force"  : 600,
        "attack" : 500,
        "dodge"  : 350,
        "parry"  : 350,
        "damage" : 400,
        "lvl" : 400, //�ȼ��ﵽ400������ʹ�ô���ʽ
        "damage_type": "����" //ֱ�Ӷ���Ѫ����ֵ���˺�����
]),
([      "action" : HIC"$Nȫ���½��޷��Զ���һ�С���ɽ��������ȫ�������粨�ΰ�ӿ��$n"NOR,
        "force"  : 650,
        "attack" : 550,
        "dodge"  : 400,
        "parry"  : 400,
        "damage" : 450,
        "lvl" : 500, //�ȼ��ﵽ500������ʹ�ô���ʽ
        "damage_type": "����"
]),
([      "action" : BLINK HIG"$Nһ�С����Ƹ��꡹��˫�Ʒ·�ͻ����ʱ��Ϳռ�����ƣ��԰�������֮�ƻ���$n"NOR,  
        "force"  : 700,
        "attack" : 600,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 600,
         "lvl" : 600, //�ȼ��ﵽ600������ʹ�ô���ʽ
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}  

int valid_learn(object me)
{

        if ((int)me->query("str") < 30)
                return notify_fail("������������������������������ơ�\n");

        if ((int)me->query("con") < 30)
                return notify_fail("�����������������������������ơ�\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹����������������ơ�\n");

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ���㣬�������������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 300)
                return notify_fail("��Ļ����Ʒ���򲻹����������������ơ�\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("paiyun-zhang", 1))
                return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ�������������������ơ�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("paiyun-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 40, level / 8)];
}

int practice_skill(object me)
{
        int cost;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");

        if ((int)me->query("qi") < 500)
                return notify_fail("�������̫���ˡ�\n");

        cost = me->query_skill("paiyun-zhang", 1) / 5 + 90;

        if ((int)me->query("neili") < cost)
                return notify_fail("������������������ơ�\n");

        me->receive_damage("qi", 200);
        me->add("neili", -cost);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("paiyun-zhang", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);

                return random(2) ? HIR "ֻ��$n" HIR "һ���ҽУ����Ǳ�"
                                   "�����Ƶ�����͸�������\n" NOR:

                                   HIR "$n" HIR "��ɫȫ�ף��������������Ƶ��������뾭��"
                                   "�˵�һ����$n������Ѫ���������\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"paiyun-zhang/" + action;
}

