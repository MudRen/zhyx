#include <ansi.h> 
inherit SKILL;

mapping *action = ({
([      "action" : "$Nָ�ϴ򱱣�������磬$w�������֣����������$n��ȥ",
        "force" : 510,
        "attack": 180,
        "dodge" : 115,
        "parry" : 125,
        "damage": 325,
        "damage_type": "����"
]),
([      "action":"$N���е�$w�������������糤��������������$n������һƬ��Ӱ֮��",
        "force" : 510,
        "attack": 188,
        "dodge" : 112,
        "parry" : 115,
        "damage": 310,
        "damage_type": "����"
]),
([      "action":"$N�����������֮�࣬�������е�$w����$nֱ�̹�ȥ",
        "force" : 532,
        "attack": 225,
        "dodge" : 120,
        "parry" : 102,
        "damage": 365,
        "damage_type": "����"
]),
([      "action":"$N�趯����$w���ó���һ�����⻷����������������ʱ��$nΧ��ˮй��ͨ",
        "force" : 565,
        "attack": 210,
        "dodge" : 115,
        "parry" : 105,
        "damage": 390,
        "damage_type": "����"
]),
([      "action":"$N��������˽���һ��������������$nֱ���ȥ",
        "force" : 550,
        "attack": 248,
        "dodge" : 110,
        "parry" : 120,
        "damage": 420,
        "damage_type": "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tianzi-jianfa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  
        object m_weapon;

        if ((int) me->query_skill("tianzi-jianfa", 1) < 150 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;


        cost = damage / 2;

        if (cost > 100) cost = 100;

        ap = ob->query_skill("force");
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("tianzi-jianfa", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIY "$n" HIY "��¶��������֮�࣬������"
                                            "��$N" HIY "ֻ��$n�������������Ѱ��" HIY 
                                            "һʱ������޴ӹ�����\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "$N" HIY "һ�л���$n" HIY "����"
                                            "����ȴ��$n�����������壬��ʽ����������\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "����$n" HIR "���������¼���"
                                            "���ֽ�����$N" HIR "��һ�У�ȴû���ܵ�"
                                            "����˺���\n" NOR]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon = me->query_temp("weapon");

        lvl = me->query_skill("tianzi-jianfa", 1);


        if (damage_bonus < 150
           || lvl < 140
           || me->query("neili") < 300 )         
      	    return 0;


             if (objectp(weapon) && weapon->query("skill_type") != "sword")                
                         return 0;
           
             if (objectp(weapon) && weapon->query("skill_type") == "sword"
                 && me->query_skill_mapped("sword") != "tianzi-jianfa")
                         return 0;

        if (random(2) == 1)return 0;

        if (damage_bonus / 5 > victim->query_con())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 76) / 2, me);
                victim->add("neili", -((damage_bonus - random(70)) / 2), me);
         
                return random(2) ? HIY "$N" HIY "һ���ӳ�����������ǧ�������ܽ�����"
                                   "��������$n" HIY "���ڣ�\n" NOR:
                                   HIM "$N" HIM "ͻȻ����������$n" HIM "ֻ��ȫ��һ"
                                   "�𣬵�ʱ���̳������˿ڣ�\n" NOR;
        }
}

int practice_skill(object me)
{
        int cost;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        
        if ( me->query_skill("tianzi-jianfa",1) < 200 )
        return notify_fail("������ӽ�����ⲻ�����죬�в��������ж�����\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 75)
                return notify_fail("����������������ӽ�����\n");

        cost = me->query_skill("tianzi-jianfa", 1) / 2 + 250;

        if ((int)me->query("neili") < cost)
                return notify_fail("����������������ӽ�����\n");

        me->receive_damage("qi", 150);
        me->add("neili", -cost);
        return 1;

}

int valid_learn(object me)
{
        int level;
        
        if ( ! me->query("special_skill/emperor"))
                return notify_fail("�㲻����������,�޷���ϰ���ӽ�����\n");

        if (me->query("gender") == "����")
                return notify_fail("���޸����ԣ�����������������ϰ�������������ӽ�����\n");
     
        level = me->query_skill("tianzi-jianfa", 1);

        if (me->query_skill("sword", 1) < level)
                return notify_fail("��Ի�����������⻹�������޷���������"
                                   "��������ӽ�����\n");
       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("�����ѧ�����������޷���������"
                                   "��������ӽ�����\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("tianzi-jianfa", 1) > 300)
       return 1500;
       else   return 1000;
}

string perform_action_file(string action)
{
        object me = this_player();

        if ( ! me->query("special_skill/emperor") )
               return "�������������޷�ʹ�����ӽ�����";

        return __DIR__"tianzi-jianfa/" + action;
}


