// yinyang-shiertian.c ����ʮ������
// �书������ʮ��֮ǰͨ�������񹦡������񹦡�����ʮ���ơ������񽣡��貨΢����Ǭ����Ų�ơ�
// ����ʮ��������Լ���Ϊ�������е��书��
// Modified by xiner 20/2/2009
// Updata by xiner 24/2/2010

#include <ansi.h>

inherit FORCE;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ", "�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ",
"����Ѩ", "����Ѩ", "���Ѩ", "�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", });

string *attack_name = ({
"������������", "������������", "�����޼�����", "�����޼�����", });

string *dodge_msg = ({
        HIW "$n" HIW "�������һ�Σ�$N" HIW "��Ȼ�޷�������ֻ���Ա���\n" NOR,
        HIW "ֻ��$n" HIW "��������ζ���$N" HIW "��ǰ��ʱ������������$n" HIW
        "�Ļ�Ӱ����$N" HIW "��ȫ�޷������ʵ��\n" NOR,
        HIW "$n" HIW "���Ա�����бб������һ����ȴǡ����$N" HIW "�Ĺ���ʧ֮���塣\n" NOR,
        HIW "$N" HIW "��һ�����ĺÿ죬Ȼ��$n" HIW "һ�����ƺ����Ѱ��������ȴ��$N" HIW "��һ�иպñܿ���\n" NOR,
        HIW "����$n" HIW "����һԾ���Ѳ�������Ӱ��$N" HIW "���д󺧣�ȴ�ּ�$n" HIW "���籼��������֮���ɣ���������˼�����ǡ�\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "һ�л���$n" HIW "���ϣ�ȴ��$n" HIW "��������ʮ�����ھ�������������������¡�\n" NOR,
        HIW "$n����һ����$N" HIW "�����Լ������ػ��������ŵ������˼�����\n" NOR,
        HIW "$n�ֱۻ�ת����$N" HIW "����������һ�ƣ�$N" HIW "������ա�\n" NOR,
        HIW "$n�����������$N" HIW "����������һ����$N" HIW "���Ʋ�ס��ֱ��ǰ��ȥ��\n" NOR,
        HIW "$n���β�����$N" HIW "һ�л��£�����ʯ���󺣣�������ס�ˡ�\n" NOR,
        HIW "$n��ǣ������$N" HIW "��������������ת�˺ü���Ȧ��\n" NOR,
        HIW "$n˫�ֻ�Ȧ��$N" HIW "ֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n" NOR,
        HIW "$n����һת��$N" HIW "һ�л��ڵ��ϣ�ֻ��ó������\n" NOR,
});

string *pfail_msg = ({
        "$n��������ʮ���죬��ͼ����������������£�Ȼ��$N���ѿ������а�������仯Ī�⡣\n",
        "$n����һ����$N�����Լ������ػ���������æ���У���ת���⣬����$n����ʤ����\n",
        "$n�ֱۻ�ת����$N����������һ�ƣ�Ȼ��$N��������һ�䣬��δ��ա�\n",
        "$n�����������$N����������һ����$N���Ʋ�ס��˳�Ʊ�����ǰֱ����\n",
        "$n��ǣ������$N����������˳�Ʊ��У�Բת���⣬����������\n",
        "$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ȼ���ѣ�������һ�㣬�����Է���\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        return lvl * lvl * 15 * 35 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        return lvl * 18 / 5;
}


mapping *actionf = ({
([      "action": HIW "$N" HIW "������ָһ�����������񽣡���ǰ�̳��������ĵ�����"
                  "Ȼ���죬���ν���ֱָ$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "�������ν���" NOR,
        "damage_type":  "����"
]),
([      "action": HIR "$N" HIR "����һ�࣬һ�����������һ�ɳ����ޱȵ�������ʱ��"
                  "��ӿ��$n" HIR "ȫ�����",
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIR "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action": HIY "$N" HIY "����һת��ȭͷЯ�ż�����ת�������ӳ����������磬"
                  "��������������$n" HIY,
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIY "�����޼���" NOR,
        "damage_type":  "����"
]),
([      "action": WHT "$N" WHT "˫��ƽƽ�ᵽ��ǰ����ɫ���صĻ���ʩ��������ʮ����"
                  "������$n" WHT "ȫ�����",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 300,
        "weapon": WHT "�����޼���" NOR,
        "damage_type": "����"
]),
([      "action": HIW "$N" HIW "˫��ʮָ���죬��ʮ���������ٳ�Ѩ�м������������"
                  "���񽣡�������磬ָ��$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "�������ν���" NOR,
        "damage_type":  "����"
]),
([      "action": WHT "$N" WHT "ͻȻ���η���˫�ƾӸ�����һ�С�����ʮ���ơ��ں�"
                  "Х����Ѹ���ޱȵ�����$n" WHT "ȫ�����",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 250,
        "weapon": WHT "�����޼���" NOR,
        "damage_type": "����"
]),
});

mapping *actionw = ({
([      "action": HIY "$N" HIY "���ƺ��������裬$w" HIY "�仯�޳���׽��������$n"
                  HIY "������ȥ",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "���е�$w" HIY "ͻ������ɭ�ϣ�����ǧ�������۶�"
                  "������ͬ����һ���ɨ$n" HIY,
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "�������е�$w" HIY "����������һ�����$n" HIY "��"
                  "�����ң�û�а���·�",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "����$w" HIY "�û���һ��һ��ԲȦ���ƺ�Ҫ��$n" HIY
                  "���Ű�Χ",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "����"
]),
([      "action": HIY "$N" HIY "��Ц��ת$w" HIY "������һָ���ĵ��黨ָ֮�⣬��"
                  "��$n" HIY "ȫ��",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "����"
]),
});

string main_skill()
{
        return "yinyang-shiertian";
}
/*
mapping sub_skills = ([
        "wudang-jiuyang"   : 300,
        "shaolin-jiuyang"  : 300,
        "emei-jiuyang"     : 300,
        "dafumo-quan"      : 300,
        "jiuyin-baiguzhao" : 300,
        "cuixin-zhang"     : 300,
        "shexing-lifan"    : 300,
        "yijin-duangu"     : 300,
        "yinlong-bian"     : 300,
        "liumai-shenjian"  : 300,
        "xianglong-zhang"  : 300,
        "lingbo-weibu"     : 300,
        "qiankun-danuoyi"  : 300,
        ]);
*/
mapping sub_skills = ([
        "jiuyang-shengong" : 350,
        "jiuyin-shengong"  : 350,
        "liumai-shenjian"  : 350,
        "xianglong-zhang"  : 350,
        "lingbo-weibu"     : 350,
        "qiankun-danuoyi"  : 350,
        ]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if ((int)me->query("age") > 30)
	{
                tell_object(me, "��Ҫ���˴�뱲�ӣ��ܵ��������ţ������Լ����书�����Ѿ��޷���ɡ�\n");
                return 0;
        }

        if (me->query("str") < 41)
        {
                tell_object(me, "��������ϣ������Լ�������������㣬�޷�������ʮ������������ɡ�\n");
                return 0;
        }
        
        if (me->query("int") < 41)
        {
                tell_object(me, "��������ϣ������Լ����������Բ��㣬�޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (me->query("con") < 41)
        {
                tell_object(me, "��������ϣ������Լ���������ǲ��㣬�޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (me->query("dex") < 41)
        {
                tell_object(me, "��������ϣ������Լ������������㣬�޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (me->query_skill("sword", 1) < 350)
        {
                tell_object(me, "��������ϣ������Լ��Ļ��������д���ߣ������޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (me->query_skill("parry", 1) < 350)
        {
                tell_object(me, "��������ϣ������Լ��Ļ����м��д���ߣ������޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 300)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ������޷�������ʮ������������ɡ�\n");
                return 0;
        }

        if (random(10) < 3)
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

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger", "sword", "blade", "whip", "dodge", "parry", "force" });

string *usage_skills2 = ({ "unarmed", "parry", "force" , "martial-cognize", "dodge", "sword" });


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

        level = me->query_skill("yinyang-shiertian", 1);
	if (level > 399)
	{
	        for (i = 0; i < sizeof(usage_skills2); i++)
        	        if (me->query_skill(usage_skills2[i], 1) < level)
                	        return notify_fail("���" + to_chinese(usage_skills2[i]) +"����⻹"
                        	                   "�������޷������������������ʮ�����졣\n");
	}else
	{
	        for (i = 0; i < sizeof(usage_skills); i++)
        	        if (me->query_skill(usage_skills[i], 1) < level)
                	        return notify_fail("���" + to_chinese(usage_skills[i]) + "����⻹"
                        	                   "�������޷������������������ʮ�����졣\n");
	}
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("����ʮ�����첩����޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
        int lvl;
        lvl = this_player()->query_skill("yinyang-shiertian", 1);
        if (lvl < 400) return 1300;
        if (lvl < 800) return 2300;
        return 3300;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2, weapon;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        if (me->is_busy()
           || ! living(victim)
           || damage_bonus < 150
           || me->query("neili") < 200
           || me->query_skill_mapped("force") != "yinyang-shiertian"
           || (me->query_skill_mapped("unarmed") != "yinyang-shiertian" 
		&& me->query_skill_mapped("sword") != "yinyang-shiertian"
		&& me->query_skill_mapped("blade") != "yinyang-shiertian")
           || me->query_skill("yinyang-shiertian", 1) < 300)
        	return 0;

        victim->receive_wound("qi", damage_bonus * 4 / 5, me);
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
        string msg;
        int ap, dp, mp;

	if ((int) me->query_skill("yinyang-shiertian", 1) < 300 ||
            me->query_skill_mapped("force") != "yinyang-shiertian" ||
            me->query_skill_mapped("parry") != "yinyang-shiertian" ||
            me->query_skill_mapped("dodge") != "yinyang-shiertian" ||
            ! living(me))
		return;

	mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("yinyang-shiertian", 1);

        if (ap / 5 + random(ap) < dp * 3 / 2)
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 300)
        {
                msg = pfail_msg[random(sizeof(pfail_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 300) return 100;
        if (lvl < 350) return 120;
        if (lvl < 400) return 140;
        if (lvl < 500) return 160;
        if (lvl < 600) return 180;
        return 200;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 300) return 100;
        if (lvl < 350) return 120;
        if (lvl < 400) return 140;
        if (lvl < 500) return 160;
        if (lvl < 600) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"yinyang-shiertian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"yinyang-shiertian/exert/" + action;
}

void skill_improved(object me)
{
	int i;
	string *sub_skillnames;

	sub_skillnames = keys(sub_skills);
	for (i = 0; i < sizeof(sub_skillnames); i++)
		me->delete_skill(sub_skillnames[i]);
}