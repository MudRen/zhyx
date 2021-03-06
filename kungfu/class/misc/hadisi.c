// beihai.c

#include <ansi.h>

inherit NPC;

void random_move();
void random_attack();

void create()
{
	set_name("哈迪斯", ({ "ha disi", "ha" }));
	set("title", HIR "冥王" NOR);
	set("gender", "男性");
	set("age", 3000);
	set("long", @LONG
他身边冤魂环绕，似幻似真，远远望去让人不寒而粟。
LONG );
	set("combat_exp", 2000000000);
	set("score", 10000000);
        set("shen_type", 0);
	set("attitude", "friendly");
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 5000000);
        set("qi", 5000000);

        set("str", 400);
        set("int", 400);
        set("con", 400);
        set("dex", 400);set("chat_chance_combat", 150);
 
set("chat_msg_combat", ({
                (: perform_action, "finger.zongheng" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
	set_skill("finger", 4000);
	set_skill("parry", 4000);
	set_skill("freezing-force", 4000);
	set_skill("liumai-shenjian", 4000);
        set_skill("zhuangzi-wu", 4000);		
        set_skill("dodge", 4000);
	set_skill("force", 4000);	
        set_skill("qiankun-danuoyi", 4000);

        map_skill("finger", "liumai-shenjian");
	map_skill("force", "freezing-force");
 	map_skill("dodge", "zhuangzi-wu");
 	map_skill("parry", "qiankun-danuoyi");
        prepare_skill("finger", "liumai-shenjian");
                set("jiali", 5000);

        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 150);
                set("chat_msg", ({ (: random_move :) }));
		set("chat_chance_combat", 120);
		set("chat_msg_combat", ({ (: random_attack :) }));
                set("born_time", time());
                keep_heart_beat();
        }

	setup();
}



void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;

        message_vision(HIC "$N" HIC "一声尖啸，四周"
                       "登时冤魂四舞。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
	if (! is_killing(ob->query("id")))
        	kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N似乎没有听见$n在说什么。\n",
                       this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 1000 + random(500), me);
        me->set("neili", me->query("max_neili"));
        return HIC "$N" HIC "“嘿”的一声吹出一口黑气，登时令$n"
               HIC "魂飞体外。\n" NOR;
}
void unconcious()
{
        die();
}

void die()
{
        string *ob_list = ({
                "/clone/fam/max/derive-emblem",
                "/clone/fam/max/hupo",
                "/clone/fam/max/noname",
                "/clone/fam/max/shihun",
                "/clone/fam/max/taixu",
                "/clone/fam/max/xuanyu",
        });
        object ob;

        ob = new(ob_list[random(sizeof(ob_list))]);

        command("chat 不可能！我堂堂冥王居然败在凡人手里！"
		"你们会为此付出代价！");
        message_sort(HIG "$N" HIG "默念法咒，忽然间天空电闪雷鸣，你只"
		     "觉得眼前忽然无数冤魂在飘舞，眼见着哈迪斯化烟雾而去。\n" NOR,
		     this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
	if (time() - query("born_time") > 7200)
	{
		message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + name() + HIM "获宙斯赦免，返回冥界去了。" NOR);
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

void random_attack()
{
	object ob;

	set("qi", query("eff_qi"));
	set("jing", query("eff_jing"));
	if (query("qi") < query("max_qi") * 3 / 5 ||
	    query("jing") < query("max_jing") * 3 / 5)
	{
		if (query_temp("recover_times") >= 3)
		{
			die();
			return;
		}

		message_combatd(HIR "$N" HIR "瞬间分化成无数凶灵，随即这些凶灵又重新合而为一，哈迪斯得到了全面的恢复！\n" NOR,
				this_object());
		add_temp("recover_times", 1);
		set("eff_qi", query("max_qi"));
		set("qi", query("max_qi"));
		set("eff_jing", query("max_jing"));
		set("jing", query("max_jing"));
		return;
	}

	clean_up_enemy();
	ob = select_opponent();
	if (! objectp(ob))
		return;
    
        switch (random(10))
	{
	case 0:
		message_combatd(HIY "$N突然发出一声尖啸，无数面目狰狞的凶灵，"
			        "瞬间从$N身上涌出，似潮水般铺天盖地\n"
			        "漫天飞舞！\n" NOR,
			        this_object());
		set_temp("apply/name", ({ "凶灵" }));
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		delete_temp("apply/name");
		break;

	case 1:
		message_combatd(HIY "$N" HIY "冷笑一声，右手向天空一抬"
				"顿时乌云密布，一股闪电向$n" HIY "直劈下去！\n只见$n"
		                "登时被闪电劈中，浑身冒出缕缕黑烟！\n" NOR,
				this_object(), ob);
		ob->receive_damage("qi", 20000 + random(50000), this_object());
		ob->receive_wound("qi", 10000 + random(40000), this_object());
		ob->interrupt_busy(ob, 20 + random(20));
		break;

	case 2:
		if (ob->is_busy())
			break;
		message_combatd(HIY "$N" HIY "对$n" HIY "狠狠瞪了一眼，"
				"$n" HIY "似乎顿时被这冰冷的眼神带走了灵魂一般，变得行尸走肉一般！\n" NOR,
				this_object(), ob);
		ob->start_busy(20 + random(20));
		break;
	}
}


