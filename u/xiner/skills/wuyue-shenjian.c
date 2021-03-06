// wuyue-shenjian.c 五岳神剑
// 由五岳剑派的华山剑法、嵩山剑法、泰山剑法、恒山剑法、衡山剑法法合一。
// 定位：转世技能

#include <ansi.h>
inherit SKILL;

string *parry_msg = ({
        "$n以攻为守，以进为退，凝神运气向$P猛攻快打地挥出方位大异的泰山「快活三」三剑。\n",
        "$n剑法突变，剑势伸缩不定，奔腾矫夭，逆使嵩山剑法的「天外玉龙」迫使$P变招。\n",
        "$n不闪不避，举剑闪电般使出「叠翠浮青」反削$P的手腕，挡过了此招。\n",
        "$n挺剑一招象是「白云出岫」回刺$P的手腕，顿时将$P的攻势化解。\n",
        "只见$n不退反进，身如飘风，一式「天柱云气」动向无定，挡住了$P的\n进攻。\n",
        "$n不退反进，使出恒山剑招「绵里藏针」，森森剑气充溢四周！架开了$P的这招。\n",
});

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string *msg = ({
"$N使一招华山剑法「有凤来仪」，手中$w剑光暴长，向$n的$l刺去",
"$N剑随身转，一招华山剑法「无边落木」罩向$n的$l",
"$N舞动$w，一招华山剑法「鸿飞冥冥」挟著无数剑光刺向$n的$l",
"$N手中$w龙吟一声，祭出华山剑法「平沙落雁」往$n的$l刺出数剑",
"$N手中$w剑光暴长，一招华山剑法「金玉满堂」往$n$l刺去",
"$N手中$w化成一道光弧，直指$n$l，一招华山剑法「白虹贯日」发出虎哮龙吟刺去",
"$N右手$w一立，举剑过顶，弯腰躬身，使一招「万岳朝宗」正是嫡系正宗的嵩山剑法",
"$N手中$w突然间剑光一吐，化作一道白虹，端严雄伟，端丽飘逸，正是嵩山剑法的精要所在，一招「千古人龙」向$n$l直刺过来",
"$N手中$w突然间剑光一吐，一招嵩山剑法「叠翠浮青」化成一道青光，气壮雄浑，向$n$l直刺过来",
"$N手中$w剑光一吐，一招嵩山剑法「玉进天池」威仪整肃，端严雄伟，向$n$l直刺过来",
"$N左手向外一分，右手$w向右掠出，使的是嵩山派剑法「开门见山」",
"$N手中$w自上而下的向$n直劈下去，一招「独劈华山」，真有石破天惊的气势，将嵩山剑法之所长发挥得淋漓尽致",
"$N手中$w刷的一剑自左而右急削过去，正是一招嵩山派正宗剑法「天外玉龙」。但见$w自半空中横过，剑身似曲似直，长剑便如一件活物一般",
"$N手中$w一晃，向右滑出三步，一招泰山剑法「朗月无云」，转过身来，身子微矮，$w向$n斜斜刺去",
"$N手中$w圈转，一招泰山剑法「峻岭横空」去势奇疾，无数剑光刺向$n的$l",
"$N展开剑势，身随剑走，左边一拐，右边一弯，越转越急。猛地$w剑光暴长，一招泰山剑法「泰山十八盘」往$n$l刺去",
"$N手中$w倏地刺出，一连五剑，每一剑的剑招皆苍然有古意。招数古朴，内藏奇变，正是泰山剑法「五大夫剑」",
"$N手中$w寒光陡闪，手中的$w，猛地反刺，直指$n胸口。这一下出招快极，抑且如梦如幻，正是「百变千幻衡山云雾十三式」中的绝招",
"$N不理会对方攻势来路，手中$w刷的一剑衡山剑法「泉鸣芙蓉」，向$n小腹刺去",
"$N不理会对方攻势来路，手中$w刷的一剑衡山剑法「鹤翔紫盖」，向$n额头刺去",
"$N手中$w倏地刺出，剑势穿插迂回，如梦如幻，正是一招衡山剑法「石廪书声」，向$n$l刺去",
"$N手中$w倏地刺出，极尽诡奇之能事，动向无定，不可捉摸。正是一招衡山剑法「天柱云气」，指向$n$l",
"$N飞身跃起，使出衡山剑法「雁回祝融」！，$w发出一声龙吟从半空中洒向$n的$l",
"$N意带神闲，一式恒山剑法「苍松迎客」，$w轻轻飞动，幻起一片剑光，围掠$n全身",
"$N使一招恒山剑法「拨云见日」，身形向上飘起，手中$w虚虚实实幻出点点寒光射向$n$l",
"$N仰天长笑，身形飘然而起，在半空中身子一旋，一式恒山剑法「轻云蔽月」狂风般地击向$n",
"$N左手捏着剑诀，右足踏开一招恒山剑法「星划长空」向上斜刺，长剑锵然跃出倏的化作几点星光射向$n的$l",
"$N向前迈去一大步，使出恒山剑法「织女穿梭」，手中$w舞成一个光球，迅若奔雷击向$n的$l",
"$N大喝一声，一招恒山剑法「曲径通幽」，$w闪电般划出一道大圆弧劈向$n的$l",
"$N忽然身形高高跃起，使出恒山剑法「云里乾坤」，$w幻出漫天花瓣，迅如雷霆射向$n的$l",
});

mapping query_action(object me, object weapon)
{
	int lvl = me->query_skill("wuyue-shenjian", 1);
	if (lvl > 600) lvl = 600;

	if (lvl > 300)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 250+random(lvl/2),
			"force"  : 200+random(lvl/2),
			"dodge"  : 200,
			"parry"  : 200,
			"damage" : 200+random(lvl/2),
			"damage_type" : "刺伤",
			]);
	}else
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 100+random(lvl/4),
			"force"  : 100+random(lvl/4),
			"dodge"  : 100,
			"parry"  : 100,
			"damage" : 100+random(lvl/4),
			"damage_type" : "刺伤",
			]);
	}

}

string main_skill()
{
        return "wuyue-shenjian";
}

mapping sub_skills = ([
        "huashan-sword"  : 200,
        "songshan-sword" : 200,
        "taishan-sword"  : 200,
        "hengshan-sword" : 200,
        "henshan-sword"  : 200,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        me = this_player();

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
        {
                tell_object(me, "你空手舞了半天，发现如果不用剑实在难以演练。\n");
                return 0;
        }

        if (me->query("int") < 40)
        {
                tell_object(me, "你演练完毕，只感五种剑法毫无牵连，看来依你的悟"
                                "性，无法将其合一。\n");
                return 0;
        }

        if (me->query("dex") < 40)
        {
                tell_object(me, "你演练完毕，只觉依自己的身法灵动性，根本无法将"
                                "五种剑法合一。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 150)
        {
                tell_object(me, "你演练完毕，发现自己的武学修养尚待提高，暂且无"
                                "法将五种剑法合一。\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 3200)
        {
                tell_object(me, "你突然觉得真气不继，看来依自己的内力修为，无法"
                                "将五种剑法合一。\n");
                return 0;
        }

        if (random(20) < 17)
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通，将"
                                "五种剑法合一。\n");
                return 0;
        }

        tell_object(me, HIY "\n一阵凡尘往事涌上心头，你几欲放声长叹。霎那间五岳"
                        "剑派的剑法不断在\n你的脑海里交替闪现，最后终于融会贯通"
                        "，合为一体。你终于通晓了五岳\n神剑的诀窍。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

	if (me->query("family/family_name") != "华山派"
		|| me->query("family/family_name") != "嵩山派"
		|| me->query("family/family_name") != "衡山派"
		|| me->query("family/family_name") != "恒山派"
		|| me->query("family/family_name") != "泰山派")
		return notify_fail("你非五岳剑派中人哪里能领悟其中精妙的招式。\n");;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("你必须先找一柄剑才能够练习。\n");

        if (me->query("int") < 40)
                return notify_fail("你的先天悟性不足，没有办法练五岳神剑。\n");

        if (me->query("dex") < 40)
                return notify_fail("你的先天身法孱弱，没有办法练五岳神剑。\n");

        if (me->query_skill("martial-cognize", 1) < 180)
                return notify_fail("你觉得五岳神剑极其深奥，依照自己的武学修养"
                                   "难以理解。\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("你的内力修为不够，没有办法练五岳神剑。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的基本剑法太差，没有办法练五岳神剑。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wuyue-shenjian", 1))
                return notify_fail("你的基本剑法火候有限，无法领会更高深的五岳神剑。\n");

        return 1;
}

int practice_skill(object me)
{
        int cost;

        if ((int)me->query_skill("wuyue-shenjian", 1) < 300)
                return notify_fail("你对五岳神剑的领悟不足已自行练习。\n");

        cost = me->query_skill("wuyue-shenjian", 1);
	cost = cost + random(cost);

        if ((int)me->query("neili") < cost)
                return notify_fail("你的内力不够练五岳神剑。\n");

        if ((int)me->query("qi") < cost / 2)
                return notify_fail("你的体力不够练五岳神剑。\n");

        me->receive_damage("qi", cost / 2);
        me->add("neili", -cost);
        return 1;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("wuyue-shenjian", 1);

        if (damage_bonus < 120
		|| me->query("neili") < 500
		|| me->query_skill_mapped("sword") != "wuyue-shenjian"
		|| random(4) == 0)
                     return 0;

	tell_object(me, HIG "【测试精灵】：HIT判定门派开始 "+me->query("family/family_name")+me->query_skill_mapped("force")+" 。\n" NOR);

	if (me->query("family/family_name") != "华山派"
		&& me->query("family/family_name") != "嵩山派"
		&& me->query("family/family_name") != "衡山派"
		&& me->query("family/family_name") != "恒山派"
		&& me->query("family/family_name") != "泰山派")
                     return 0;


	if (me->query_skill_mapped("force") == "zixia-shengong") //华山 紫霞神功
	{
		me->add("neili", -100);
		victim->receive_damage("qi", damage_bonus / 2, me);
		victim->receive_wound("qi", damage_bonus / 3, me);
		return HIM "但见$N" HIM "面上紫气大盛，全身劲气贯于剑中，剑气源源不断扑向$n" HIM "！\n" NOR;
	}
	if (me->query_skill_mapped("force") == "hanbing-zhenqi") //嵩山 寒冰真气
	{
		me->add("neili", -100);
		victim->start_busy(random(2));
		victim->receive_damage("jing", damage_bonus / 4, me);
		return HIB "$N"HIB"将寒冰真气功力运于剑端，源源不断的侵入$n"HIB"经脉！\n" NOR;
	}
	if (me->query_skill_mapped("force") == "zhenyue-jue") //衡山 镇岳决
	{
		me->add("neili", -100);
		victim->receive_damage("qi", damage_bonus / 3, me);
		victim->receive_damage("jing", damage_bonus / 3, me);
		return HIW "$N"HIW"将镇岳诀提升至极至，一股中正平和的剑气弥漫$n"HIW"周身！\n" NOR;
	}
	if (me->query_skill_mapped("force") == "baiyun-xinfa") //恒山白云心法待开发
	{
		me->add("neili", -100);
		victim->receive_damage("jing", damage_bonus / 2, me);
		victim->receive_wound("jing", damage_bonus / 3, me);
		return HIW "$N"HIG"的白云心法透过剑身，不断涌出，干扰着$n"HIG"精神！\n" NOR;
	}
	if (me->query_skill_mapped("force") == "panshi-shengong") //泰山磐石神功待开发
	{
		me->add("neili", -100);
		victim->start_busy(1 + random(lvl / 80));
		victim->receive_wound("qi", damage_bonus / 4, me);
		victim->receive_wound("jing", damage_bonus / 4, me);
		return HIW "$N"HIG"将磐石神功运于剑身，$n"HIW"顿时压力俱增！\n" NOR;
	}
	
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp, mp;

	if ((int) me->query_skill("wuyue-shenjian", 1) < 300 ||
            me->query_skill_mapped("sword") != "wuyue-shenjian" ||
            me->query_skill_mapped("parry") != "wuyue-shenjian" ||
            ! living(me))
		return;

	if (me->query("family/family_name") != "华山派"
		|| me->query("family/family_name") != "嵩山派"
		|| me->query("family/family_name") != "衡山派"
		|| me->query("family/family_name") != "恒山派"
		|| me->query("family/family_name") != "泰山派")
		return;

	mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry",1) + mp;
        dp = me->query_skill("wuyue-shenjian", 1);

	if (ap / 2 + random(ap) < dp)
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$P", "$P" HIW);
                msg = replace_string(msg, "$l", "$l" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = "$n提剑正欲招架$P的攻击，怎奈$P理也不理，突然提速抢先攻向$n。\n";
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}



string perform_action_file(string action)
{
        return __DIR__"wuyue-shenjian/" + action;
}
