//真言大师(传授手印和九字真言)

#include <ansi.h>
inherit  NPC;

mixed ask_zhenyan();
mixed learn_skill();
mixed learn_skill2();

void create()
{
	set_name("真言大师", ({ "zhenyan dashi", "dashi" }));
	set("title", "沙门护法");
//	set("nickname", HIR "临兵斗者皆阵列在前" NOR);
	set("gender", "男性");
	set("age", 80);
	set("long", @LONG
这老僧须眉俱白，脸相庄严中透出祥和之气，鼻梁比一般人至少
长上寸许，双目半开半闭，眼神内敛，乃极有道行的高人。
LONG );
        set("gender", "男性" );
        set("attitude", "friendly");

        set("max_neili", 10000);
        set("neili", 10000);
        set("max_jing", 10000);
        set("jing", 10000);
        set("max_qi", 8000);
        set("qi", 8000);
        set("jingli", 8000);
        set("max_jingli", 8000);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12500000);

	set_skill("force", 500);
	set_skill("yijinjing", 500);
        set_skill("dodge", 500);
        set_skill("shaolin-shenfa", 500);
        set_skill("hand", 500);
        set_skill("jiuzi-zhenyan", 500);
        set_skill("shou-yin", 500);
        set_skill("parry", 500);
        set_skill("jingang-buhuaiti", 500);
        set_skill("buddhism", 300);
        set_skill("lamaism", 300);
        set_skill("literate", 300);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand", "jiuzi-zhenyan");
        map_skill("parry", "jingang-buhuaiti");
	prepare_skill("strike", "jiuzi-zhenyan");

        set("jiali", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200); 

        set("inquiry", ([ 
//		"九字真言" : (: ask_zhenyan :), 
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({
			(: random_move :),
			CYN "真言大师深深的叹了口气。\n" NOR,
				}));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
        carry_object("d/city/obj/jiasha")->wear(); 
}

void random_move()
{
	if (time() - query("born_time") > 800)
	{
		message_vision("$N飘然而去。\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

void init()
{
    add_action("do_answer", "answer");
}

int accept_object(object me, object ob)
{
        if (ob->query("id") != "buchen sheli")
        {
                command("say 你给我这种东西干什么？");
                return 0;
        } else
        {
       	        destruct(ob);
       	        command("say 多谢施主返还师兄的舍利！");

		if(!me->query("can_learn/zhenyan/shou-yin") && me->query("reborn"))
		{
	                me->set("can_learn/zhenyan/shou-yin", 1);
			call_out("learn_skill",2);
                	return -1;
		} else
		{
        	        command("thank " + me->query("id"));
	                return -1;
		}
        }
}

mixed learn_skill()
{
	object me = this_player();
	command("buddhi " + me->query("id"));
	message_vision(WHT"真言大师对$N说道：“施主与佛有善缘，可与贫僧论一论佛法！”\n"NOR, me);                
	write(HIG"真言大师对你说道：“施主可知何谓九字真言？ \n"NOR
		"(可用answer xxx 作答)\n" NOR);
	me->set_temp("sun/zhenyan/ask1",1); //问了才能answer
	return 1;
}

mixed do_answer(string arg)
{
	object me = this_player();
	if ( !arg ) return command("say 你要回答什么?");
	if ( !me->query("can_learn/zhenyan/shou-yin") ) return 0;
	if (! me->query_temp("sun/zhenyan/ask1") ) return 0; //还没问呢!

	if ( arg == "临兵斗者皆阵列在前")
	{
		write(HIG"真言大师道：“不错就是这九个字，乃来自东晋葛洪著的道家宝典《抱朴子》\n"
			"内卷的登涉篇，原文曰：『临兵斗者，皆阵列前行。常当视之，无所不辟。』\n" NOR);
		call_out("learn_skill2",2);
		return 1;
	}
	command("sigh");
	command("say 施主与佛门缘分太浅，请回吧！");
	me->delete_temp("sun/zhenyan/ask1"); //答错一次就结束
	return 1;
}

mixed learn_skill2()
{
        object me = this_player();
        int lv;

	me->delete_temp("sun/zhenyan/ask1");

	if (me->query("shou-yin"))
		return command("say 你不是已经学过了么！"); 

        if (!me->query("can_learn/zhenyan/shou-yin"))
		return command("say 施主与佛门缘分太浅，请回吧！"); 

        if (me->query_skill("shou-yin", 1))
		return command("say 我该教的都已经教你了，剩下的就靠你勤加练习了！");

	if (me->query_skill("yinyang-shiertian", 1)||me->query_skill("paiyun-zhang", 1)
		||me->query_skill("lunhui-jian", 1)||me->query_skill("fengshen-tui", 1)
		||me->query_skill("fuyu-shengong", 1))
		return command("say 阁下已经学过了高深的武功，这佛门大手印已经不适合你学习了！");		

	if (me->query("str") < 34)
		return command("say 你的臂力孱弱，无法练习手印。\n");

        if (me->query_skill("hand", 1) < 200)
		return command("say 你基本手法修为不足，无法领悟佛门手印！");

        if (me->query_skill("buddhism") < 100 || me->query_skill("lamaism") < 100)
		return command("say 可惜施主与我佛无缘，难以领悟九字真言大手印！");

        command("nod");
        command("say 既然这样贫僧就将真言大手印传与你，你可看好了！");
        message_vision(HIC "$N" HIC "将九字真言「手印」从头到尾给$n" HIC "演示了一遍！\n" NOR,
                       this_object(), me);
        command("haha");
        tell_object(me, HIG "你学会了「手印」！\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("buddhism"))
                me->improve_skill("buddhism", 1500000);
        if (me->can_improve_skill("lamaism"))
                me->improve_skill("lamaism", 1500000);
        command("say 领会了多少就看你的悟性了，剩下的就靠你自己下去练习！");
        lv = me->query("int");
        if (lv <= 30)
               me->set_skill("shou-yin", lv);
        else
               me->set_skill("shou-yin", 30 + (lv - 30) * 2);
    	me->set("shou-yin",1);
        return 1;
       
}
