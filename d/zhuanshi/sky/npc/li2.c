#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("李逍遥", ({ "li xiaoyao", "li", "xiaoyao"}));
        set("long", "仙剑奇侠传中的传奇人物，少年得蜀山剑派\n" 
                    "高人授艺，兼习家传绝学飞龙探云手以及冰\n"
                    "心决，乃一代不世的剑侠。\n"); 
        set("nickname", HIW "蜀山剑神" NOR);
        set("title", HIY "大宗师" NOR);
        set("gender", "男性");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 45000);
        set("max_jing", 30000);
        set("max_neili", 55000);
        set("neili", 55000);
        set("jiali", 150);
        set("combat_exp", 50000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bugui" :),  
                (: perform_action, "unarmed.xiao" :),  				
                (: exert_function, "powerup" :),
        }) );

        set_skill("dodge", 800);
        set_skill("parry", 800);
        set_skill("unarmed", 750);
        set_skill("hand", 700);
        set_skill("sword", 750);
        set_skill("daya-jian", 750);
		set_skill("sad-strike", 750);
        set_skill("taiji-jian", 700);
        set_skill("zhuangzi-wu", 750);
        set_skill("force", 700);
        set_skill("bingxin-jue", 700);
        set_skill("literate", 200);

        map_skill("force", "bingxin-jue");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "taiji-jian");
	    map_skill("unarmed", "sad-strike");
        map_skill("sword", "daya-jian");     
		
		 prepare_skill("unarmed", "sad-strike");     
        
        set_temp("apply/damage", 450);
		set_temp("apply/unarmed_damage", 450);
        set_temp("apply/armor", 300);
        set("apply/dodge", 400); 

       

        setup();

        //carry_object(__DIR__"obj/pangukai")->wear();
        carry_object(__DIR__"obj/chiyoujian")->wield();        
       // set_temp("handing", carry_object("__DIR__"obj/shenjiu"));
}



void greeting(object ob)
{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;
     command("look " + me->query("id"));
     command("say 打赢我才能上去！");     
     return ;
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
            query("jing") < 5000 ||
            query("neili") < 15000)
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
	object *inv;
	int n;
	object ob,room;
         if (! objectp(ob = query_competitor()))
                return; 

	inv = deep_inventory(ob);

	for (n = 0; n < sizeof(inv); n++)
        {
                if (! playerp(inv[n])) continue;
                else
                {
                	command("say 你背的是谁？还不快快放下！");
                  return;
                }
        }

	if (living(this_object()) && present("zhuanshi tongzhi", ob))
	{
		command("gongxi " + ob->query("id"));
		room = find_object("/d/zhuanshi/sky/sky3");
		if (! room) room = load_object("/d/zhuanshi/sky/sky3");
		ob->move(room);	
        }else	command("say 你把转世通知书弄丢了？赶快去找回来！");

        ::lost();
}

void unconcious()
{
        say( HIC"李逍遥说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，李逍遥又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
	lost();
}
void die()
{
        unconcious();
}

