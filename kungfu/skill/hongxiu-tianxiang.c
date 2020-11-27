//
#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hongxiu-tianxiang", 1);
        return lvl * lvl * 15 * 21 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        lvl = (int)me->query_skill("hongxiu-tianxiang", 1);
        return lvl * 9 / 5;
}

string *parry_msg = ({
	"$n���λζ��·𻨼����裬��ͬ����֮�꣬ңң��ס$N�Ĺ��ơ�\n",
        "�ۿ�$Nת���ѹ�����$n��ȻһЦ�����赭д��$N����ʽ�������Ρ�\n",
        "$N�ۿ�����֮�ʣ�ͻ��һ�����ᾢ�����������������Ȼ���ˡ�\n",
        "$N����һ�ݣ�����$n���������ﳤ�տ�Զ��֪�����ȫ�޴����֡�\n",
});

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_enable(string usage)
{
        object me = this_player();
        if (me->query_skill("xuannv-jian", 1)
	    || me->query_skill("yinyang-shiertian", 1)
	    || me->query_skill("jiuzi-zhenyan", 1)
	    || me->query_skill("shenzhaojing", 1)
	    || me->query_skill("dugu-jiujian", 1)
	    || me->query("sex/times")
	    || me->query("gender") != "Ů��"
	    || !me->query("reborn"))
                return usage == 0;
	else
         return usage == "force" || usage == "parry";
}

int valid_learn(object me)
{
	int level;
	int i;

	if (me->query("gender") != "Ů��")
                return notify_fail("�㴿��֮�����㣬����������ĺ������㡣\n");

	if (me->query("sex/times"))
                return notify_fail("����������������Ǵ���֮��\n");

        if (me->query("int") < 30 && me->query_int() < 80 )
                return notify_fail("����ú���������ڼ��������⡣\n");

        level = me->query_skill("hongxiu-tianxiang", 1);

	if (me->query_skill("literate", 1) < level / 3 && me->query_skill("literate", 1) < 600)
		return notify_fail("��Զ���д�ֵ���⻹�������޷���������"
                                   "����ĺ������㡣\n");

	if (me->query_skill("force", 1) < level)
		return notify_fail("��Ի����ڹ�����⻹�������޷���������"
                                   "����ĺ������㡣\n");

	if (me->query_skill("parry", 1) < level)
		return notify_fail("��Ի����мܵ���⻹�������޷���������"
                                   "����ĺ������㡣\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("hongxiu-tianxiang", 1) < 150
           || me->query_skill_mapped("parry") != "hongxiu-tianxiang"
           || ob->query("gender") != "����"
           || (int)me->query("neili") < 500
           || ! me->query_temp("shield")
           || ! living(me)
           || random(2) == 1)
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("buddhism", 1);
        ap = ob->query_skill("force",1) * 5 + mp;
        dp = me->query_skill("hongxiu-tianxiang",1) * 5 + me->query_per() * 15;

        if (ap / 3 + random(ap) < dp)
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else

        if (mp >= 300)
        {
                msg = "$nĬ�˺������㣬��ͼ�Ի�$N�Ĺ���������$N"
                      "��ͨ�𷨾��˿����Ϊ$n��ò������\n";
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        string wn;
        object weapon;

        lvl = me->query_skill("hongxiu-tianxiang", 1);
	weapon = me->query_temp("weapon");

        if (lvl < 150
	   ||me->query_skill_mapped("force") != "hongxiu-tianxiang"
           || ! me->query_temp("powerup")
	   ||me->query("neili") < 300
	   ||victim->query("gender") != "����"
	   ||random(2) == 1)
		return 0;

	if (weapon)
	{
		wn = weapon->name();
                me->add("neili", -50);
		damage_bonus = lvl / 3 + me->query_per() * 10;
		damage_bonus += random(damage_bonus / 3);
                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
		victim->receive_wound("jing", damage_bonus * 2 / 3, me);
                return HIG "$N" HIG "��ȻһЦ������" + wn + HIG "�������������һ˿����֮������������������\n" NOR;
	} else
	{
                me->add("neili", -50);
		damage_bonus = lvl / 3 + me->query_per() * 10;
		damage_bonus += random(damage_bonus / 3);
                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);
		victim->receive_wound("jing", damage_bonus * 2 / 3, me);
                return HIM "$N" HIM "���������㹦���������ޣ�һ�������ھ����಻����ӿ��$n" HIM "�����ڣ�\n" NOR;
	}
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("hongxiu-tianxiang", 1);
        if (lvl < 100) return 0;
        if (lvl < 200) return 60;
        if (lvl < 300) return 70;
        if (lvl < 400) return 80;
        if (lvl < 500) return 90;
        if (lvl < 600) return 100;
        return 110;
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
	if (this_player()->query_skill("literate", 1) < 200)
		return 1000;

	if (this_player()->query_skill("literate", 1) < 300)
		return 800;

	if (this_player()->query_skill("literate", 1) < 400)
		return 600;

	if (this_player()->query_skill("literate", 1) < 500)
		return 400;

	if (this_player()->query_skill("literate", 1) < 600)
		return 200;

	return 100;
}

string exert_function_file(string action)
{
        object me = this_player();
        if (me->query_skill("xuannv-jian", 1)
	    || me->query_skill("yinyang-shiertian", 1)
	    || me->query_skill("jiuzi-zhenyan", 1)
	    || me->query_skill("shenzhaojing", 1)
	    || me->query_skill("dugu-jiujian", 1)
	    || me->query("sex/times")
	    || me->query("gender") != "Ů��"
	    || !me->query("reborn"))
                return 0;

        return __DIR__"hongxiu-tianxiang/" + action;
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("hongxiu-tianxiang", 1);
        layer = lvl / 40;

        if ((lvl % 40) == 0 && layer > 9)
        {
                tell_object(me, HIY "��ĺ��������ֽ���һ�㡣\n" NOR);
        } else
        if ((lvl % 40) == 0)
        {
                tell_object(me, HIY "�������˵�" + chinese_number(layer) +
                                "��ĺ������㡣\n" NOR);
        }
}
