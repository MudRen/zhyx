#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
#define SHELI "/u/xiner/obj/sheli"

void create()
{
        set_name("徐子陵", ({ "xu ziling", "xu", "ziling"}));
        set("long", "一个俊俏的白衣少年。\n"); 
        set("title", HIY "大唐双龙" NOR);
        set("gender", "男性");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 30);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 25000);
	set("jiali",150);
        set("neili", 25000);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 500);
        set_skill("hand", 500);
        set_skill("parry", 500);
        set_skill("unarmed", 500);
        set_skill("shou-yin", 500);
        set_skill("zhuangzi-wu", 500);
        set_skill("force", 500);
        set_skill("changsheng-jue", 500);
        set_skill("blade", 500);
        set_skill("badao-daofa", 500);
        set_skill("literate", 200);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "badao-daofa");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "shou-yin");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");
		
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 600);

        prepare_skill("hand", "shou-yin");

        setup();

        carry_object("/d/zhuanshi/sky/npc/obj/cloth1")->wear();
        carry_object("/d/zhuanshi/sky/npc/obj/hands")->wear();

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({(: random_move :)}));
                set("born_time", time());
                keep_heart_beat();
        }
}

void random_move()
{
	if (time() - query("born_time") > 600)
	{
		message_vision("$N飘然而去。\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "对$n" CYN "叫道：你先别急"
                               "，我打完这架就来领教你的。\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 10000 ||
            query("jing") < 10000 ||
            query("neili") < 10000)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }
  

        message_vision(HIW "$N" HIW "大喜道：好好好！我正手痒痒，咱们"
                       "来比划比划！\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "看了看$n" CYN "，嘿嘿笑道：你的水"
                       "平太菜了，要好好练功，好好练功。\n" NOR,
                       this_object(), ob);
        ::win();
}


void lost()
{
        object me;
        object ob;
	object owner;

        if (! objectp(me = query_competitor()))
                return;

	if (me->query("shen") < 0)
	{
		tell_object(me, HIC "\n徐子陵说道：“今日我虽不是你的对手，来日定当为武林除害！\n" NOR);
		return;
	}

	if (me->query_skill("yinyang-shiertian", 1)||me->query_skill("paiyun-zhang", 1)
		||me->query_skill("lunhui-jian", 1)||me->query_skill("fengshen-tui", 1)
		||me->query_skill("fuyu-shengong", 1))
	{
		tell_object(me, HIC "\n徐子陵说道：“阁下武功高深，小子不是对手！\n" NOR);
		return;
	}

        ob = find_object(SHELI);
        if (! ob) ob = load_object(SHELI);

        if (!environment(ob))
	{
	        ob->move(this_object());
        	command("say 这颗舍利子就转赠与你吧，如果能找到真言大师或许还有一番际遇。");
	        command("say 不过一切都要讲个“缘”字！");
	        command("give sheli to " + me->query("id"));
		::lost();
        }
        tell_object(me, HIC "\n徐子陵说道：“你功夫不错，人品也还可以。可惜舍利子已经不在我手中了。”\n\n" NOR);
        ::lost();
}

void unconcious()
{
        say( HIC"徐子陵说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，徐子陵又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
}

void die()
{
        unconcious();
}