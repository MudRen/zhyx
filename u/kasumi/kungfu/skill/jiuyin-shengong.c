// jiuyin-shengong.c ������
// �����׹�צ�������ơ����ħȭ���������޷��������귭�Լ��׽�͹Ǻ�Ϊһ��������S����ѧ��
// �����񹦿��Լ���Ϊ����ȭ�š�צ����ȭ�����Ʒ����ַ����޷����ڹ���
// �����޶�Ϊ�ĺ�������ȡ��parryЧ��
// modify by kasumi 15/3/2007

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
        "$n��Ҳ��������$N��һ�ߡ�\n",
        "$n����΢΢һ������$N���ˡ�\n",
        "$n�������һ�Σ�$N��Ȼ�޷�������ֻ���Ա���\n",
        "$n����һ�񣬽��������н�������ȫ��������\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * 14 / 5;
}

mapping *actionf = ({
([      "action":"$N����һ̽����ʱ������Х���������ֺ��޻��ɵĲ���$n$l",
        "force" : 550,
        "attack": 180,
        "dodge" : 100,
        "parry" : 90,
        "damage": 200,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action":"$N˫����ץ���ó�ǧ���ҫ�۵Ľ�⣬��������$n��$l",
        "force" : 560,
        "attack": 180,
        "dodge" : 110,
        "parry" : 120,
        "damage": 220,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action":"$N����һת��ȭͷЯ�ż�����ת�������ӳ����������磬��������������$n",
        "force" : 570,
        "attack": 190,
        "dodge" : 110,
        "parry" : 120,
        "damage": 250,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action":"$N�Ʋ���ǰ��һ�Ʋ�������������$n��$l�������ж�ʱ����һ��̶��ı���",
        "force" : 590,
        "attack": 220,
        "dodge" : 120,
        "parry" : 115,
        "damage": 260,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action":"$N����һ�࣬һ�����������һ��������������ʱ����ӿ��$n��$l��",
        "force" : 600,
        "attack": 250,
        "dodge" : 130,
        "parry" : 120,
        "damage": 270,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action":"$N˫�ֺ�ȭ������ſ���ֻ�������͡��ƿ�֮����ʮ������һ������$n��$l",
        "force" : 610,
        "attack": 200,
        "dodge" : 115,
        "parry" : 120,
        "damage": 280,
        "weapon": HIW "�����޼���" NOR,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
        "force" : 470,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ���������۶�����$w�������һ���ɨ$n",
        "force" : 450,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "����"
]),
([      "action":"$N�������е�$w����������һ�����$n�ҿ����ң�û�а���·�",
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
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
        "force" : 540,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 260,
        "damage_type": "����"
]),
});

string main_skill() { return "jiuyin-shengong"; }

mapping sub_skills = ([
        "dafumo-quan"      : 230,
        "jiuyin-baiguzhao" : 230,
        "cuixin-zhang"     : 230,
        "shexing-lifan"    : 230,
        "yijin-duangu"     : 230,
        "yinlong-bian"     : 230,
        ]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if (me->query("gender") == "����")
        {
                tell_object(me, "��������ϣ�ֻ����Ѫ��ӿ�������Լ������������޷����������񹦡�\n" NOR);
                return 0;
        }
        
        if (me->query("character") != "�ĺ�����")
                return notify_fail("�����Բ������޷���������񹦡�\n");
        

        if (me->query("con") < 34)
        {
                tell_object(me, "��������ϣ������Լ����������̫��޷��������澭�ڵ��书��һ��\n");
                return 0;
        }

        if (me->query("str") < 39)
        {
                tell_object(me, "��������ϣ������Լ������������������޷��������澭�ڵ��书��һ��\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "����þ����澭�ڵ��书��������£��������о�һ��ѧ�ʿ��ܸ��а�����\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 250)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ������޷��������澭�ڵ��书��һ��\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 4500)
        {
                tell_object(me, "������Լ��������̣��޷��������������񹦡�\n");
                return 0;
        }

        if (random(10) < 8)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ�������ߺ�һ��\n");
                return 0;
        }

        tell_object(me, HIW "һ�󷲳�����ӿ����ͷ���㼸��������̾�����Ǽ䣬����ۻ��ף�����һ��Ī��\n"
                        "�ı�������ʦ̩�����ָ߳���ʤ������̩ɽ��С����֮����Ȼ��������ֻ������\n����"
                        "��ѧ���ڿ����Ƕ�ô����С��Ц��\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

string *usage_mapped_skills = ({ "unarmed", "dodge", "parry", "force" });
string *usage_skills = ({ "unarmed", "strike", "finger", "claw", "hand", 
                          "cuff", "dodge", "whip", "parry", "force" });
string *usage_skills2 = ({ "unarmed", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;
                       
        if (me->query("character") != "�ĺ�����")
                return notify_fail("�����Բ������޷���������񹦡�\n");
       
        if (me->query("str") < 39)
                return notify_fail("�㷢���Լ����������㣬�޷����������������硣\n");

        if (me->query("con") < 34)
                return notify_fail("�㷢���Լ�������ǲ��㣬�޷���ת�����񹦡�\n");

        if (me->query("gender") == "����")
                return notify_fail("���޸����ԣ���������������������ľ����񹦡�\n");

        level = me->query_skill("jiuyin-shengong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 250)
                return notify_fail("����þ����񹦹�����£����Լ�����ѧ����ȫȻ�޷����ס�\n");

        for (i = 0; i < sizeof(usage_skills2); i++)
                if (me->query_skill(usage_skills2[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills2[i]) +
                                           "�����⻹�������޷�������������ľ����񹦡�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("jiuyin-shengong", 1) < 150 ||
            ! living(me) || (int)me->query("neili") < 150 ||
            me->query_skill_mapped("parry") != "jiuyin-shengong" ||
            ob->query_temp("weapon"))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("jiuyin-shengong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "Ĭ�˾����������סȫ����$N" HIR
                                            "һ�л���$n" HIR "С����ֻ�����ִ���"
                                            "����ģ���������ʧ����Ӱ���١� \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "һ�й�����$n" HIR "ŭ��һ��������"
                                            "����������$N" HIR "���бƻء�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "���΢Ц�����赭д�䣬�ѽ�$N" HIR "��"
                                            "�н�����ʽȫ��������\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "Ĭ�˾����������סȫ��������$N" HIY
                                 "��������ޱȣ���̾һ����һ�о���ʵ�ش���$n" HIY
                                 "���ϡ�\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "���˷�������ͼ��$N" HIY "����ʽ�ƻء�����"
                                 "$N" HIY "��ʽ��Ȼһ�䣬$n" HIY "��ʱһ����ȴ��Ȼ���С�\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "���΢Ц�����赭д������$N" HIY "�Ľ���"
                                 "��ʽ����������$N" HIY "���ѿ�ȥ�������飬��Цһ����$N" HIY
                                 "ȴ�����С�\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

*/
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        if (me->query_temp("weapon"))return 1;

        if (me->is_busy()
           || ! living(victim)
           || damage_bonus < 120
           || me->query("neili") < 200
           || me->query_skill("jiuyin-shengong", 1) < 250)
        	return 0;


        if (damage_bonus > 150)
        {
                me->add("neili", -50);
                victim->receive_wound("qi", (damage_bonus - 100) / 2, me);
                victim->add("neili", -((damage_bonus - random(100)) / 2), me);

                return random(2) ? HIR "$N" HIR "��ʽ��Ȼһ�䣬���ֳ�צ����Ȼ��ץ��$n" HIR "������Ѩ��\n" NOR:
                                   HIR "$N" HIR "�첽��ǰ��ȫ��������������ʳָ���͵ش�$n" HIR "�ؿڴ�Ѩ��\n" NOR;
        }        
}

int difficult_level()
{
        return 800;
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-shengong/exert/" + action;
}