// fuyu-shengong by yuchang@zhyx
 

#include <ansi.h>

inherit FORCE;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

string *attack_name = ({
"���������", "���ƾ�����", "����������", "��Ͼ�����", });

string *dodge_msg = ({
       "$n��������Ծ��ƽ���ӳ�������һ�㣬���Ʒ��������һ�ۣ������˳�ȥ��\n",
       "$n��δ�أ�����ȴ�ص��ɶ������������ǣ�б�����䡣\n",
       "$nһ�㣬�ּ��س������ȥ�ƾ�����$n�ڽ�����ӳҫ�������ȸ�������ƿն�ȥ��\n",
       "������һ���ۼ䣬$nٿȻ�����ˣ�һ����ӹ����������͡�\n",
        "$nʩչ�ˡ������񹦡��еġ���ӳ����������ɫ��������ʧ�ˡ�\n",   
       "����΢�磬��ɼ������������,$n������Ҷ����Ʈ��$N����������"+HIW"��������"NOR+"һ��\n",
});

string *parry_msg = ({
       "$n��"+MAG"��ʦ�̾���"NOR+"֮�ƣ�������$N֮��,����$N����һ�ִ��.\n",
      "$n����ɲ�Ǽ䣬��������һ����ľ������˲�佫���е�Ѩ��ȫ������.����"+HIM"��ľ�����NOR\n",
       "$n����"+CYN"��ˮ�ž���"NOR+"��$n��Χ������������ˮ����$N������ȫ����ˮǽ�ϣ����޷�͸��.\n",
        "$n����ңԶ�Ļ��ҡ�Σ���"+RED"�����Ӿ���"NOR+"֮�ƣ�������Ŀ,����һ��.\n",
        "$n��"+YEL"�����ھ���"NOR+"Ѹ�ٵ��ڵ��Ͼ򿪶�,$n������\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("fuyu-shengong", 1);
        return lvl * lvl * 10 * 35 / 100 / 200;
}

mapping *actionf = ({
([      "action": "$Nʹ���������е�"+HIY"���������"NOR+"$N�ѷ·������ں���һ����ɲ�Ǽ���ǲԲ���񷣬���޵�ֹ��Ҳû�и��顣\n" NOR,
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "���������" NOR,
        "damage_type":  "����"
]),
([      "action": "$Nʹ���������е�"+HIW"�����ƾ���"NOR+"��$N��ʱ������ǣ��ٵ���϶���˻�����\n" NOR,
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIR "���ƾ�����" NOR,
        "damage_type":  "����"
]),
([      "action": "$N" HIY "�ٽ���ü����ׯ������$w�������ڰ�գ�ңָ$n��ʹ���������е�"+HIR"����������" NOR+"\n" NOR,
        "force" : 750,
        "attack": 400,
        "dodge" : 300,
        "parry" : 300,
        "damage": 200,
        "weapon": HIY "����������" NOR,
        "damage_type":  "����"
]),
([      "action": "$N" WHT "ʹ���������е�"+HIB"����˼����"NOR+"����һЩ���������ơ����֡���������ס$n���Ծ���������������ʹ$n׹�������³���֮��\n" NOR,
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "��˼������" NOR,
        "damage_type": "����"
]),
([      "action": "$N" HIW "ʹ�����꽣���е�"+HIC"����Ͼ���"NOR+"��ٿ��һ������������ȥ��һ���֣���ժ�±����$w�������ࡱ������һ��������\n" NOR,
        "force" : 650,
        "attack": 300,
        "dodge" : 400,
        "parry" : 400,
        "damage": 500,
        "weapon": HIW "��Ͼ�����" NOR,
        "damage_type":  "����"
]),
([      "action": "$N" WHT "ֻ��һ�ɹ���ؾó��ĺ����������м���ȫ��ʹ�����꽣���е�"+BLU"����������"NOR+"����Ϯ$n��\n" NOR,
        "force" : 950,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": HIW"����������" NOR,
        "damage_type": "����"
]),
});

mapping *actionw = ({
([      "action": "$n" HIY "ֻ����һ��ǿ���ѹ��������ǵص�ӿѹ������������Ȼ�к������Ǹ��꽣���еġ���������\n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 350,
        "weapon": WHT "����������" NOR,
        "damage_type": "����"
]),
([      "action": "$n" HIY "��Ҫ�̳�����Ȼ���÷�ӿ�ƶ�������$Nһ���Զ����裬���˽�ȥ,   ����"+HIG"����������� \n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 350,
        "weapon": WHT "���������" NOR,
        "damage_type": "����"
]),
([      "action": "$N" HIY "�������е�$w�����ް����飬����һ����$w��$n��ȥ��\n" NOR,
        "force" : 550,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 300,
        "weapon": WHT "�������彣��" NOR,
        "damage_type": "����"
]),

([      "action": "$N" HIY "��Ц��ת$w" HIY "����������һָ��ָ�죬����ָ�أ���������������"+HIG"���������¡���\n" NOR,
        "force" : 1000,
        "attack": 300,
        "dodge" : 250,
        "parry" : 250,
        "damage": 500,
        "weapon": WHT "����������������" NOR,
        "damage_type": "����"
]),
});

string main_skill()
{
        return "fuyu-shengong";
}


string *usage_skills = ({"sword", "dodge", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills[i]) + "����⻹"
                                           "�������޷�������������ĸ����񹦡�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
        return 3000;
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
        dp = me->query_skill("fuyu-shengong", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIW "$n" "��"MAG"��ʦ�̾���֮�ƣ�������$N֮��,"
                                                  "����$N����һ�ִ����\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" "����ɲ�Ǽ䣬��������һ����ľ��"
                                                  "����˲�佫���е�Ѩ��ȫ������.����"HIM"��ľ�������\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" "����"CYN"��ˮ�ž�����$n��Χ������������ˮ����"
                                                   "$N������ȫ����ˮǽ�ϣ����޷�͸����\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" "����ңԶ�Ļ��ҡ�Σ���"RED"�����Ӿ���֮�ƣ�"
                                                     "������Ŀ,����һ�ԡ�\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fuyu-shengong", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fuyu-shengong", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"fuyu-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"fuyu-shengong/exert/" + action;
}


