// 神照经神功 shenzhaojing.c
// Editd By Vin On 26/4/2001
// Modified By xiner 28/3/2009 设置为转世高级SK，低悟性专用

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
"$N突然间左手一捺，封住$n退路，右手掌力汹涌而出",
"$N身体微侧，突然飞起一脚，踢向$n下三路。脚到中途，猛地一抬，踢向$n面门",
"$N倏然跃近，击出一拳，这一拳无声无影，去势快极，向$n的胸口打去",
"$N丝毫不动声色，右掌平伸，左掌运起神照经神功的劲力，呼的一声拍向$n",
"$N身形微微一展，已然游走至$n跟前，陡然间双掌齐施，向$n猛拍而去",
"$N退后一步，双掌回收，凌空划出一个圆圈，顿时一股澎湃的气劲直涌$n而出",
});

string *parry_msg = ({
"$n不退反进，一股无形气流直把$N副得难以招架，连连退后。\n",
"只见$N移至$n身后，猛然一招朝$n的后心拍去，但不料反被震退数步。\n",
"$N冲破$n的无形真气，接着全力一掌拍在$n身上，可万万无料到另一股气墙直撞\n而出，将$N的攻击硬生生地弹开。\n",
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
                return notify_fail("你先天膂力孱弱，无法修炼神照经神功。\n");

        if ((int)me->query("con") < 42)
                return notify_fail("你先天根骨孱弱，无法修炼神照经神功。\n");

	if ((int)me->query("int") > 14 && (int)me->query_skill("shenzhaojing", 1) > 50)
                return notify_fail("你心中杂念太多，难以领会更高深的神照经神功。\n");

        if ( me->query("gender") == "无性" && me->query("shenzhaojing", 1) > 29)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的神照经神功。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功火候不足，不能学神照经神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳脚火候不足，不能学神照经神功。\n");

        if ((int)me->query("max_neili", 1) < 4000)
                return notify_fail("你的内力修为不足，不能学神照经神功。\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本内功水平不够，难以锻炼更深厚的神照经神功。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本拳脚水平不够，难以锻炼更深厚的神照经神功。\n");

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
		"damage_type" : "内伤",
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
                        result += (["msg" : HIG "$n" HIG "不退反进，一股无形气流直把$N"
                                            HIG "副得难以招架，连连退后。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "只见$N" HIY "移至$n身后，猛然一招朝$n"
                                            HIY "的后心拍去，但不料反被震退数步。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "冲破$n的无形真气，接着全力一掌拍在$n" HIW "身上，可"
                                            "万万无料到另一股气墙直撞\n而出，将$N的攻击硬生生地弹开。\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "$N" HIC "一招拍在$n" HIC "身上，可见$n"
                                            HIC "不闪不避，只是全身迅猛一抖，$N" HIC "的力道反被护体罡气震退了"
                                            "开来。\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" MAG "见$N来势凶凶攻来，不由嘴角轻轻一笑，飞身一跃"
                                            MAG "直往$N的力道撞去，竟把\n$N震个人仰马翻，狼狈不堪!\n" NOR]);
                        break;
                }
                return result;
        }  else
        if (mp >= 100)
        {
                msg = "$n默运互体神功，将上下门户守得严严实实，怎奈$N"
                      "精通阴阳八褂，将$n的神功尽数破解。\n";
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
		return HIR "$n" HIR "一声惨嚎，全身骨骼格格格格爆声不"
                       "绝，肋骨、臂骨、腿骨同时断折。\n" NOR;
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
        return notify_fail("神照经神功只能用学(learn)的来增加熟练度。\n");
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
		return "你思前想后，顾虑太多无法施展神照经的绝招。";

        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}
