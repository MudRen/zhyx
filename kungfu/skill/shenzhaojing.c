// ���վ��� shenzhaojing.c
// Editd By Vin On 26/4/2001
// Modified By xiner 28/3/2009 ����Ϊת���߼�SK��������ר��

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * lvl * 15 * 23 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * 14 / 6;
}

string *msg = ({
"$NͻȻ������һ�࣬��ס$n��·������������ӿ����",
"$N����΢�࣬ͻȻ����һ�ţ�����$n����·���ŵ���;���͵�һ̧������$n����",
"$NٿȻԾ��������һȭ����һȭ������Ӱ��ȥ�ƿ켫����$n���ؿڴ�ȥ",
"$N˿��������ɫ������ƽ�죬�����������վ��񹦵ľ���������һ������$n",
"$N����΢΢һչ����Ȼ������$n��ǰ����Ȼ��˫����ʩ����$n���Ķ�ȥ",
"$N�˺�һ����˫�ƻ��գ���ջ���һ��ԲȦ����ʱһ�����ȵ�����ֱӿ$n����",
});

string *parry_msg = ({
"$n���˷�����һ����������ֱ��$N���������мܣ������˺�\n",
"ֻ��$N����$n�����Ȼһ�г�$n�ĺ�����ȥ�������Ϸ�������������\n",
"$N����$n����������������ȫ��һ������$n���ϣ����������ϵ���һ����ǽֱײ\n��������$N�Ĺ���Ӳ�����ص�����\n",
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

int valid_enable(string usage)
{
        int lvl;

        lvl = (int)this_player()->query_skill("shenzhaojing", 1);

	if ((int)this_player()->query("int") > 14)
		return usage == 0;;
	
	if(lvl > 199)
                return usage == "force" || usage == "unarmed" || usage == "parry";
	else
                return usage == "force";
}

int valid_learn(object me)
{
        if ((int)me->query("str") < 48)
                return notify_fail("�����������������޷��������վ��񹦡�\n");

        if ((int)me->query("con") < 42)
                return notify_fail("����������������޷��������վ��񹦡�\n");

	if ((int)me->query("int") > 14 && (int)me->query_skill("shenzhaojing", 1) > 50)
                return notify_fail("����������̫�࣬����������������վ��񹦡�\n");

        if ( me->query("gender") == "����" && me->query("shenzhaojing", 1) > 29)
                return notify_fail("���޸����ԣ�������������������������վ��񹦡�\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ���վ��񹦡�\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż���㣬����ѧ���վ��񹦡�\n");

        if ((int)me->query("max_neili", 1) < 4000)
                return notify_fail("���������Ϊ���㣬����ѧ���վ��񹦡�\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ������������վ��񹦡�\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���������Զ������������վ��񹦡�\n");

        return ::valid_learn(me);
}


mapping query_action(object me, object weapon)
{
	int lvl = me->query_skill("shenzhaojing", 1);

	if ( lvl > 400 ) lvl = 400;

	return ([
		"action" : msg[random(sizeof(msg))],
		"force"  : 200 + random(lvl),
		"attack" : 100 + random(lvl * 2 / 3),
		"damage" : 100 + random(lvl * 3 / 4),
		"dodge"  : 100 + random(lvl / 2),
		"parry"  : 100 + random(lvl / 2),
		"damage_type" : "����",
		]);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, mp;
        int cost; 
        string msg;

        if ((int)me->query_skill("shenzhaojing", 1) < 200 
		|| (int)me->query("neili") < 1000
		|| !me->query_temp("shield")
		|| (me->query_skill_mapped("force") != "shenzhaojing" && me->query_skill_mapped("force") != "jiuyin-shengong")
		|| me->query_skill_mapped("parry") != "shenzhaojing"
		|| me->query_skill_mapped("unarmed") != "shenzhaojing"
		||! living(me))
                return;

        cost = damage / 2;
        if (cost > 200) cost = 200;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") * 12 + ob->query("max_neili") + mp * 12;
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp * 4 / 5)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(5))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "���˷�����һ����������ֱ��$N"
                                            HIG "���������мܣ������˺�\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "ֻ��$N" HIY "����$n�����Ȼһ�г�$n"
                                            HIY "�ĺ�����ȥ�������Ϸ�������������\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "����$n����������������ȫ��һ������$n" HIW "���ϣ���"
                                            "�������ϵ���һ����ǽֱײ\n��������$N�Ĺ���Ӳ�����ص�����\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "$N" HIC "һ������$n" HIC "���ϣ��ɼ�$n"
                                            HIC "�������ܣ�ֻ��ȫ��Ѹ��һ����$N" HIC "�����������������������"
                                            "������\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" MAG "��$N�������׹����������������һЦ������һԾ"
                                            MAG "ֱ��$N������ײȥ������\n$N������������Ǳ�����!\n" NOR]);
                        break;
                }
                return result;
        }  else
        if (mp >= 100)
        {
                msg = "$nĬ�˻����񹦣��������Ż��ص�����ʵʵ������$N"
                      "��ͨ�����˹ӣ���$n���񹦾����ƽ⡣\n";
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }

}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);

        if (damage_bonus < 160
           || lvl < 180
           || me->query("neili") < 300
	   || me->query("jiali") < 10
           || me->query_temp("weapon")
           || me->query_temp("secondary_weapon")
           || (me->query_skill_mapped("force") != "shenzhaojing" && me->query_skill_mapped("force") != "jiuyin-shengong")
           || (me->query_skill_mapped("unarmed") != "shenzhaojing" && me->query_skill_mapped("unarmed") != "jiuyin-shengong" )
           || (me->query_skill_prepared("unarmed") != "shenzhaojing" && me->query_skill_prepared("unarmed") != "jiuyin-shengong"))
                return 0;

        if (damage_bonus / 3 > victim->query_con())
        {
		me->add("neili", -50);
		victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
		victim->affect_by("shenzhao",
			([ "level" : me->query("jiali") + random(me->query("jiali")),
				"id"    : me->query("id"),
				"duration" : lvl / 100 + random(lvl / 10) ]));
		return HIR "$n" HIR "һ���Һ���ȫ��������������"
                       "�����߹ǡ��۹ǡ��ȹ�ͬʱ���ۡ�\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);
	if (lvl < 100) return 0;
	if (lvl < 150) return 10;
	if (lvl < 200) return 20;
	if (lvl < 250) return 30;
	if (lvl < 300) return 40;
	if (lvl < 350) return 60;
	if (lvl < 400) return 70;
	if (lvl < 450) return 80;
	if (lvl < 500) return 100;
	return 110;
}

int practice_skill(object me)
{
        return notify_fail("���վ���ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
	object me;
	int lvl1,lvl2;
	if (me = this_player())
	{
		lvl1 = me->query_skill("jiuyin-shengong", 1);
		lvl2 = me->query_skill("shenzhaojing", 1);
		if (lvl2 <= lvl1) return 300;
	}
        return 800;
}

string perform_action_file(string action)
{
	if ((int)this_player()->query("int") > 14)
		return "��˼ǰ��󣬹���̫���޷�ʩչ���վ��ľ��С�";

        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}
