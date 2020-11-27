// china-aojue.c �л����� 
// ��ɷ����ר�ü���
// �ɼ���Ϊ�������Ʒ����мܣ��Ṧ���ڹ���

#include <ansi.h>

inherit FORCE;

string *parry_msg = ({
        "$n��������̩ɽ�����һ������$N��һ�ߡ�\n",
        "$n����΢΢һ������ʱ��$N���˼�����\n",
        "$n��������$N��Ȼ�޷�������ֻ����ǿ�Ա���\n",
        "$n����һ�񣬽�$N�Ľ�������ȫ��������\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("china-aojue", 1);
        return lvl * lvl * 24 * 15 / 100 / 200;
}



mapping *actionf = ({
([      "action":"$N��ָ���ƣ�һ���������Ƽ�ӿ����һ������$n$l",
        "force" : 510,
        "attack": 190,
        "dodge" : 100,
        "parry" : 90,
        "damage": 180,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
([      "action":"$N˫���뷢���û�����������ӡ����������$n��$l",
        "force" : 510,
        "attack": 185,
        "dodge" : 90,
        "parry" : 120,
        "damage": 175,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
([      "action":"$N����һת��������Ѹ�ײ����ڶ�֮�ƻӳ�������$n",
        "force" : 530,
        "attack": 175,
        "dodge" : 90,
        "parry" : 110,
        "damage": 200,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
([      "action":"$N�������һ�ƻ�������$n��$l�������仺ȴ�Ʋ��ɵ�",
        "force" : 525,
        "attack": 185,
        "dodge" : 85,
        "parry" : 115,
        "damage": 185,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
([      "action":"$N����΢�Σ�˫�����������ֱ��$n��$l��",
        "force" : 530,
        "attack": 165,
        "dodge" : 90,
        "parry" : 115,
        "damage": 200,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
([      "action":"$N˫�ֺ��ƣ�΢�����������У������Ʒ���Ϯ��$n��$l",
        "force" : 540,
        "attack": 200,
        "dodge" : 115,
        "parry" : 120,
        "damage": 280,
        "weapon": HIW "�л�����" NOR,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action" : "$N���ƺ�Ȼ���٣�����$w����һ����������$nֱ����ȥ",
        "force" : 470,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "����"
]),
([      "action":"$N���е�$wͻ�������۾�һ�㣬��$n��ɨ��ȥ$n",
        "force" : 450,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "����"
]),
([      "action":"$N�������е�$w������$n���ż��̣������·�����",
        "force" : 460,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n���Ű�Χ",
        "force" : 525,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "����"
]),
([      "action":"$NĿ����ͣ���¶�¼�֮ɫ����ת����$w����������$n��$l",
        "force" : 540,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 260,
        "damage_type": "����"
]),
});

int get_ready(object me)
{
        return 1;
}

string *usage_skills = ({ "sword", "strike", "dodge", "parry", "force" });
string *usage_skills2 = ({ "sword", "strike", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}


int valid_force(string force)
{
        return 1;
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("china-aojue", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 50;
        if (lvl < 250) return 60;
        if (lvl < 300) return 70;
        if (lvl < 350) return 80;
        if (lvl < 400) return 90;
        return 100;
}

int valid_learn(object me)
{
        int level;
        int i;
     
        level = me->query_skill("china-aojue", 1);

        if ( ! me->query("special_skill/lonely"))
                return notify_fail("�㲻����ɷ���ǣ��޷���ϰ�л�������\n");

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("�����ѧ�����������޷���������������л�������\n");

        for (i = 0; i < sizeof(usage_skills2); i++)
                if (me->query_skill(usage_skills2[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills2[i]) +
                                           "����⻹�������޷���������������л�������\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�л�����������޷��򵥵�ͨ����ϰ������\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("china-aojue", 1) < 150 ||
            ! living(me) || (int)me->query("neili") < 150 ||
            me->query_skill_mapped("parry") != "china-aojue")
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("china-aojue", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "Ĭ���л���������סȫ��$N" HIR
                                            "һ�л���$n" HIR "ǰ�أ�ֻ�����ִ��ƺ�����һ��"
                                            "�޻������޳���֮���� \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "һ�й�����$n" HIR "ŭ��һ��������"
                                            "����������$N" HIR "���бƻء�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "ȫ����һ����������$N" HIR "��"
                                            "�н�����ʽ����������\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIW "$n" HIW "Ĭ���л���������סȫ������$N" HIW
                                 "�������棬ͻȻ�仯��һ�о���ʵ�ش���$n" HIW
                                 "�ؿڡ�\n" NOR;
                        break;
                case 1:
                        result = HIW "$n" HIW "���˷�������ͼ��$N" HIW "����ʽ�ƻء�����"
                                 "$N" HIW "ͻȻ����������$n" HIW "⧲���������Ȼ���С�\n" NOR;
                        break;

                default:
                        result = HIW "$n" HIW "ȫ����һ������������$N" HIW "�Ľ���"
                                 "��ʽ��������������$N" HIW "������������ų���$N" HIW
                                 "�ѱ����������С�\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}


mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        if (me->query_temp("weapon"))return 1;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
           || me->query("neili") < 200
           || me->query_skill("china-aojue", 1) < 250)
        	return 0;


        if (damage_bonus / 4 > victim->query_con())
        {
                me->add("neili", -100);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                victim->add("neili", -((damage_bonus - random(80)) / 2), me);

                return random(2) ? HIR "$N" HIR "����ͻȻ�ӿ죬˫����Ȼ������$n" HIR "���\n" NOR:
                                   HIR "$N" HIR "����������ȫ�����������Ƽ䣬�͵�����$n" 
                                   HIR "�ؿڴ�Ѩ��\n" NOR;
        }        
}

int difficult_level()
{
        return 1600;
}

string perform_action_file(string action)
{
        return __DIR__"china-aojue/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"china-aojue/exert/" + action;
}
