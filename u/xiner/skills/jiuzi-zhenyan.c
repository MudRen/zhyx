//jiuzi-zhenyan.c��������(������)����DTSL����
//ת��SK��������ǿ���Ե������ӽ�
//update by xiner 2009-02-16

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
	"$n���Ʊ任�޳������ش����ؼܿ���$N�Ľ�����\n",
	"$n΢΢һЦ������һ�ӣ�$N�Ľ����Ѿ��������߽⣡\n",
	"$n����һ�ӣ����������Ѱ���Ž����Ļ��ᡣ\N",
	"$n���Ʋ�ס�任�����Ǽ򵥵���ʽ��ȴ��ס��$N��ȫ������֮����\n",
});

mapping *action = ({
([      "action": "$N���������������Ĳ����������뾲�ĸ�ɮ����ʩ������������ӡ����һ��������������ɢ������\n",
        "force"    : 500,
        "attack"   : 180,
        "dodge"    : 100,
        "parry"    : 100,
        "damage"   : 300,
        "weapon"   : HIW "��������ӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N���������ӡ�����Ϻ�����֣�ֻ��һ�����˳�$nӿȥ��",
        "force"    : 450,
        "attack"   : 190,
        "dodge"    : 110,
        "parry"    : 110,
        "damage"   : 310,
        "weapon"   : HIW "������ӡ" NOR,
        "damage_type" : "����",
]),
([	"action": "$Nһ�����壬��Цһ����ٿ��������ȥ����������$n��ͬʱ���ְ���ʨ��ӡ������һ�����͡���",
        "force"    : 500,
        "attack"   : 200,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 310,
        "weapon"   : HIW "��ʨ��ӡ" NOR,
        "damage_type" : "����",
]),
([	"action": "$N���ְ�����ʨ��ӡ������һ�ӣ�ֻ��һ����ǽ��$n����ȥ��",
        "force"    : 550,
        "attack"   : 200,
        "dodge"    : 110,
        "parry"    : 110,
        "damage"   : 320,
        "weapon"   : HIW "��ʨ��ӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N���ڸ�ӡ��Ϊ�⸿ӡ��Ĵָ������࣬�������£�$n��ʱӦӡ�����ٺᷭ��ȥ��",
        "force"    : 500,
        "attack"   : 180,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 320,
        "weapon"   : HIW "�⸿ӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N�ڸ�ӡ���������������棬�������Դ���������ӿ������$n���ھ�����",
        "force"    : 550,
        "attack"   : 180,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 330,
        "weapon"   : HIW "�ڸ�ӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N������ȭӡ��ͻȻȭ��ͻ�䣬�����������ǣ���$n����Ҫ����ȥ��",
        "force"    : 450,
        "attack"   : 200,
        "dodge"    : 130,
        "parry"    : 130,
        "damage"   : 330,
        "weapon"   : HIW "��ȭӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N��������ӡ�����ƽ���֮�䣬�����������˷����������ھ���$nӿȥ��",
        "force"    : 450,
        "attack"   : 200,
        "dodge"    : 150,
        "parry"    : 150,
        "damage"   : 340,
        "weapon"   : HIW "����ӡ" NOR,
        "damage_type" : "����",
]),
([      "action": "$N����ƿӡ����ƿ��ȭ���ٷǸ߶ȼ��е�һ�ţ�������һ��ǽ��ֱ��$nѹ��ȥ��",
        "force"    : 500,
        "attack"   : 200,
        "dodge"    : 120,
        "parry"    : 120,
        "damage"   : 350,
        "weapon"   : HIW "������ƿӡ" NOR,
        "damage_type" : "����",
]),
});


string main_skill() { return "jiuzi-zhenyan"; }

mapping sub_skills = ([
        "shou-yin"	: 300,        // 1
        "fengyun-shou"	: 200,        // 2
        "qianye-shou"	: 200,        // 3
        "longzhua-gong"	: 200,        // 4
        "yingzhua-gong"	: 200,        // 5
        "nianhua-zhi"	: 200,        // 6
        "wuxiang-zhi"	: 200,        // 7
        "luohan-quan"	: 200,        // 8
        "changquan"	: 300,        // 9
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
                tell_object(me, "��������ϣ�ֻ����Ѫ��ӿ�������Լ���������"
                                "���޷�ѧ���湦��\n" NOR);
                return 0;
        }

        if (me->query("int") < 35)
        {
                tell_object(me, "��������ϣ�ֻ�о����书����ǣ��������"
                                "��������ԣ��޷������һ��\n");
                return 0;
        }

        if (me->query("con") < 35)
        {
                tell_object(me, "��������ϣ������Լ����������̫��޷�����"
                                "�������ԡ�\n");
                return 0;
        }

        if (me->query("str") < 35)
        {
                tell_object(me, "��������ϣ�ֻ���ֱ��������������޷�������"
                                "���ܺ�һ��\n");
                return 0;
        }

        if (me->query("dex") < 35)
        {
                tell_object(me, "��������ϣ�ֻ���Լ������鶯��̫��޷���ͨ"
                                "�������ԡ�\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 300)
        {
                tell_object(me, "����þ������Լ�����£��������о�һ��ѧ�ʿ��ܸ��а�"
                                "����\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 300)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 300)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 450)
        {
                tell_object(me, "������Լ������ڹ���Ϊ̫ǳ�����������޷�����"
                                "�������ԡ�\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 300)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ���"
                                "���޷�����������������һ��\n");
                return 0;
        }

        if ((int)me->query_skill("hand", 1) < 300)
        {
                tell_object(me, "������Լ��Ļ����ַ����д���ߣ������޷���ͨ��"
                                "�����ԡ�\n");
                return 0;
        }



        if ((int)me->query("max_neili") < 6000)
        {
                tell_object(me, "��������ϣ������᲻��������������Ӧ��"
                                "��������������\n");
                return 0;
        }

        if (random(30) <= 28)
        {
                tell_object(me, "��Ծ������Եİ����������򣬻�������������"
                                "�����ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIW "һ�󷲳�����ӿ����ͷ���㼸��������̾�����Ǽ䣬"
                        "����ۻ��ף�����һ��Ī��\n�ı�������ʦ̩�����ָ߳�"
                        "��ʤ������̩ɽ��С����֮����Ȼ��������ֻ������\n��"
                        "����ѧ���ڿ����Ƕ�ô����С��Ц��\n" NOR);
        return 1;
}

int double_attack() { return 1; }

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jiuzi-zhenyan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl = me->query_skill("jinshe-jian", 1);

        if (damage_bonus < 100) return 0;

	switch(random(3))
	{
           case 0:
             if (damage_bonus / 4 > victim->query_str() &&
                 ! me->is_busy() &&
                 ! victim->is_busy())
		{
                 message_sort( HIY "$N" HIY "���Ʊ任�޳����·����������������٣�"
			       "��$n" HIY "����Χס�������ã�\n" NOR,me,victim);
                 me->start_busy(1);
                 victim->start_busy(1 + random(lvl / 10));
	        }
		break;

           default :
	        if (damage_bonus / 4 > victim->query_str())
	        {
        	        victim->receive_wound("qi", (damage_bonus - 140) / 2);
                	victim->add("neili", -((damage_bonus - random(90)) / 2), me);
	                return HIR "$N" HIR "ͻȻ�������ƣ�$n" HIR "ֻ�о���ǰ"HIW"��Ӱ"HIR"���ϣ�"
        	                    "��ʱ�������ƣ���Ѫ��ֹ��\n" NOR;
	        }
	}
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ա�����֡�\n");

        if ((int)me->query("int") < 35)
                return notify_fail("�����������̫�ͣ��޷����������ԡ�\n");

        if ((int)me->query("dex") < 35)
                return notify_fail("����������������޷������������ԡ�\n");

        if ((int)me->query("con") < 35)
                return notify_fail("����������̫�ͣ��޷����������ԡ�\n");

        if ((int)me->query("str") < 35)
                return notify_fail("�����������������޷������������ԡ�\n");

        if (! me->query("reborn"))
                return notify_fail("�㻹û��ͨ������Ŀ��飬�޷������������ԡ�\n");

        if ((int)me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("�����ѧ����̫�ͣ��޷���ϰ�������ԡ�\n");

        if ((int)me->query_skill("buddhism", 1) < 300)
                return notify_fail("��������ķ����򲻹����޷���ϰ�������ԡ�\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("hand", 1) < 300)
                return notify_fail("��Ļ����ַ����̫ǳ��\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("jiuzi-zhenyan",1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������ľ������ԡ�\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����������ӡ��������֡�\n");

        if ((int)me->query("qi") < 350)
                return notify_fail("������������������˾������ԡ�\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("������������������˾������ԡ�\n");

        me->receive_damage("qi", 200);
        me->add("neili", -300);
        return 1;
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jiuzi-zhenyan", 1);
        if (lvl < 200) return 50;
        if (lvl < 300) return 70;
        if (lvl < 400) return 90;
        if (lvl < 500) return 100;
        return 110;
}

string perform_action_file(string action)
{
        return __DIR__"jiuzi-zhenyan/" + action;
}

