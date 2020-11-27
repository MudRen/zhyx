// poshan-dao.c ���Ƶ���

#include <ansi.h>
inherit SKILL;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

string *attack_name = ({
"���Ƶ���", "���굶��", "������������", "�췭�ظ���������", });

string *parry_msg = ({
       "$n��"+MAG"�����Ƶ�����"NOR+"���壬��߾�����һ�����磬��$NĿ�ɿڴ���\n",
      "$n����ɲ�Ǽ䣬�����������޹ǣ�������һ������ĸо������������������"+HIM"�����������\n",
       "$n����"+CYN"���췭�ظ�����������"NOR+"������������,$N����ʽ��Ҳ��ʹ����ȥ�ˡ�\n",
        "$n���һ������"+RED"����������������"NOR+"֮���������ڳ����ˡ������˸ҳ����ˡ�\n",
});

mapping *action = ({
([      "action" : "$N�ս�����$wһ�С�����һ��������$n��$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "���Ƶ���" NOR,
        "damage_type" : "����"
]),
([      "action" : "$N��ǰ����һ��������$wʹ�������Ƹ��꡹����$n�ĺ�",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "���굶��" NOR,
        "damage_type" : "����"
]),
([      "action" : "ֻ��$N�������е�$w��ʹ�������������������ֱ��$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "������������" NOR,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��������������������$w�������һ����˸����������$n",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "���굶��" NOR,
        "damage_type" : "����"
]),
([      "action" : "$N����ʹ������֮���塸����Ϊ�ơ�������$w�����һ������ǵصĿ���$n",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "������������" NOR,
        "damage_type" : "����"
]),
([      "action" : HIY"$Nʹ�����Ƶ���֮���վ���[1;36m���췭�ظ���[0m,[1;33m����$w��������һ������$n[0m"NOR,
        "force" : 1000,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 500,
        "weapon": WHT "�췭�ظ���������" NOR,
        "damage_type" : "����"
]),
});


string *usage_skills = ({ "blade", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
int practice_skill(object me)
{
      return notify_fail("���Ƶ���������޷��򵥵�ͨ����ϰ������\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fanyun-daofa", 1);

        if (me->query_skill("blade", 1) < level)
                return notify_fail("��Ի�����������⻹�������޷���������"
                                   "����ķ��Ƶ�����\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("��Ի����мܵ���⻹�������޷���������"
                                   "����ķ��Ƶ�����\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("�����ѧ�����������޷���������"
                                   "����ķ��Ƶ�����\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fanyun-daofa", 1) > 300)
       return 1200;
       else   return 1000;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        me->add("neili", me->query("jiali") / 3);

        if (victim->query("neili") < 500)
                victim->set("neili", 0);
        else
                victim->add("neili", -300);

        return NOR + HIR "$n" HIR "����$N" HIR "һ�У�" + name2 + "��ʱ�����"
               "�룬ȫ��������" + name1 + "��к������\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("fanyun-daofa", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "��"HIR"�����Ƶ��������壬��߾�����һ,"
                                                  "�����磬��$NĿ�ɿڴ���\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "����ɲ�Ǽ䣬�����������޹ǣ���"
                                                  "��һ������ĸо������������������"HIM"�������������\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "����"CYN"���췭�ظ�������������������������,"
                                                   "$N����ʽ��Ҳ���ҳ��֡�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "���һ������"RED"����������������֮����"
                                                     "�����ڳ����ˡ������˸ҳ����ˡ�\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fanyun-daofa", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fanyun-daofa/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"fanyun-daofa/exert/" + action;
}


