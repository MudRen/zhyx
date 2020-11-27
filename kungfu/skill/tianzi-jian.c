// tianzi-jian.c ���ӽ��� �������Ծ�����Ů������ϰ
// �ɼ���Ϊ�������мܼ��Ṧ




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


string *usage_skills = ({ "sword", "dodge", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;  
        object m_weapon;

        if ((int) me->query_skill("tianzi-jian", 1) < 150 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            me->query_skill_mapped("parry") != "tianzi-jian" ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;


        cost = damage / 2;

        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force");
        dp = me->query_skill("parry");

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
                case 2:
                        result += (["msg" : HIW "����$n" HIW "���������¼���"
                                            "���ֽ�����$N" HIW "��һ�У�ȴû���ܵ�"
                                            "����˺���\n" NOR]);
                        break;
                }
                return result;
        }
	/* else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "��¶��������֮�࣬��������"
                                 "�������������Ѱ������$N"
                                 HIY "��ͨ������������ʵ������������\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "�������������������$N"
                                 HIY "Ȼ��$NҲ��ʾ���������ŷ�������������\n" NOR;
                        break;
                case 2:
                        result = HIW "$n" HIW "���������¼������ֽ�����$N"
                                 HIW "��һ�У�˿�����𡣿���$N"
                                 HIW "�������У�����ȴ�ǲ�ֹ��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
	*/
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon = me->query_temp("weapon");

        lvl = me->query_skill("tianzi-jian", 1);


        if (damage_bonus < 150
           || lvl < 140
           || me->query("neili") < 300 )         
      	    return 0;


             if (objectp(weapon) && weapon->query("skill_type") != "sword")                
                         return 0;
           
             if (objectp(weapon) && weapon->query("skill_type") == "sword"
                 && me->query_skill_mapped("sword") != "tianzi-jian")
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
      return notify_fail("���ӽ���������޷��򵥵�ͨ����ϰ������\n");
}

int valid_learn(object me)
{
        int level;
        
        if ( ! me->query("special_skill/emperor"))
                return notify_fail("�㲻����������,�޷���ϰ���ӽ�����\n");

        if (me->query("gender") != "����")
                return notify_fail("���ӽ���ֻ�����Է�����ϰ��\n");
     
        level = me->query_skill("tianzi-jian", 1);

        if (me->query_skill("sword", 1) < level)
                return notify_fail("��Ի�����������⻹�������޷���������"
                                   "��������ӽ�����\n");

        if (me->query_skill("dodge", 1) < level)
                return notify_fail("��Ի����Ṧ����⻹�������޷���������"
                                   "��������ӽ�����\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("��Ի����мܵ���⻹�������޷���������"
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
       if ( this_player()->query_skill("tianzi-jian", 1) > 300)
       return 1200;
       else   return 1000;
}

string perform_action_file(string action)
{
        return __DIR__"tianzi-jian/" + action;
}


