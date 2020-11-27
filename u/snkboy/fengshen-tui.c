#include <ansi.h> 
#include <combat.h> 
inherit SKILL;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

string *attack_name = ({
"�����Ⱦ�", "���ɨ��Ҷ����", "Ħڭ��������", "����Ϊһ�İ�������", });

string *parry_msg = ({
       "$n��"+MAG"�������Ⱦ���"NOR+"���壬��߾�����һ�����磬��$NĿ�ɿڴ���\n",
      "$n����ɲ�Ǽ䣬�����������޹ǣ�������һ������ĸо������������������"+HIM"�����������\n",
       "$n����"+CYN"�����ɨ��Ҷ������"NOR+"������������,$N����ʽ��Ҳ��ʹ����ȥ�ˡ�\n",
        "$n���һ������"+RED"��Ħڭ����������"NOR+"֮���������ڳ����ˡ������˸ҳ����ˡ�\n",
});

mapping *action = ({
([      "action" : "$N˫����Σ�����͵ط���һʽ[1;36m�����¥�С�[0m,[1;33m������$n��$l",
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "�����Ⱦ�" NOR,
        "damage_type" : "����",
        "skill_name"  : "���¥��"
]),
([      "action" : "$N��Ŷٵأ�������ת���ҽ�һʽ[1;36m�����о��ݡ�[0m,[1;33m������$n��$l",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "���ɨ��Ҷ����" NOR,
        "damage_type" : "����",
        "skill_name"  : "���о���"
]),
([      "action" : "$N�ҽŷ�һ���߳���������׼��һʽ[1;36m���������С�[0m,[1;33m�������$n",
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "Ħڭ��������" NOR,
        "damage_type" : "����",
        "skill_name"  : "��������"
]),
([      "action" : "$N˫������Ȧת��һʽ[1;36m���������꡹[0m,[1;33m������糾������$n��ȫ��",
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "Ħڭ��������" NOR,
        "damage_type" : "����",
        "skill_name"  : "��������"
]),
([      "action" : "$N˫�Ž�������һʽ[1;36m��߳����ơ�[0m,[1;33m���ŽŲ���$n����������",
        "force" : 850,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "����Ϊһ�İ�������" NOR,
        "damage_type" : "����",
        "skill_name"  : "߳�����"
]),
});

string *usage_skills = ({ "unarmed", "parry" });

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
      return notify_fail("�����Ȳ�����޷��򵥵�ͨ����ϰ������\n");
}

int valid_learn(object me)
{
        int level;

     
        level = me->query_skill("fengshen-tui", 1);

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("��Ի���ȭ�ŵ���⻹�������޷���������"
                                   "����ķ����ȡ�\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("��Ի����мܵ���⻹�������޷���������"
                                   "����ķ����ȡ�\n");

       if (me->query_skill("martial-cognize", 1) < level)
                return notify_fail("�����ѧ�����������޷���������"
                                   "����ķ����ȡ�\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
       if ( this_player()->query_skill("fengshen-tui", 1) > 300)
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
        int ap, dp, sk1, sk2, lvl, ran;
        string msg;

        sk1 = ob->query_skill("paiyun-zhang", 1); 
        sk2 = me->query_skill("fengshen-tui", 1); 
//        ap = ob->query_skill("parry");
        ap = ob->query_skill("fanyun-daofa", 1);
        dp = me->query_skill("fengshen-tui", 1);

        lvl = ob->query_skill("paiyun-zhang", 1);

        if (lvl > 100) ran = 20;
        if (lvl > 200) ran = 15;
        if (lvl > 300) ran = 10;
        if (lvl > 400) ran = 8;
        if (lvl > 500) ran = 5;

        if (dp/2 > ap)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "��"HIR"�������Ⱦ������壬��߾�����һ,"
                                                  "�����磬��$NĿ�ɿڴ���\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "����ɲ�Ǽ䣬�����������޹ǣ���"
                                                  "��һ������ĸо������������������"HIM"�������������\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "����"CYN"�����ɨ��Ҷ��������������������,"
                                                   "$N����ʽ��Ҳ���ҳ��֡�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "���һ������"RED"��Ħڭ����������֮����"
                                                     "�����ڳ����ˡ������˸ҳ����ˡ�\n" NOR]);
                        break;
                }
                return result;
        }
        else
        if (sk1/2 > sk2 && random(ran) == 1)
        {
//                msg = "$N�����������Ʒ���������巢�ӵ����쾡�£�$n��һʱ�Ҳ����������������ƣ�";
                msg = HIY + msg + NOR; 
                msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 200, 
                HIR"$N�����������Ʒ���������巢�ӵ����쾡�£�$n��һʱ�Ҳ����������������ƣ�"NOR);
//                COMBAT_D->set_bhinfo(msg); 
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fengshen-tui/perform/" + action;
}




