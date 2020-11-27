#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("����ң", ({ "li xiaoyao", "li", "xiaoyao"}));
        set("long", "�ɽ��������еĴ�������������ɽ����\n" 
                    "�������գ���ϰ�Ҵ���ѧ����̽�����Լ���\n"
                    "�ľ�����һ�������Ľ�����\n"); 
        set("nickname", HIW "��ɽ����" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
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
     command("say ��Ӯ�Ҳ�����ȥ��");     
     return ;
}


int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�е������ȱ�"
                               "���Ҵ�����ܾ��������ġ�\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 10000 ||
            query("jing") < 5000 ||
            query("neili") < 15000)
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "��������"
                               "��̫���ˣ�����Ъ�����˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }
  

        message_vision(HIW "$N" HIW "��ϲ�����úúã�����������������"
                       "���Ȼ��Ȼ���\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "���˿�$n" CYN "���ٺ�Ц�������ˮ"
                       "ƽ̫���ˣ�Ҫ�ú��������ú�������\n" NOR,
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
                	command("say �㱳����˭�����������£�");
                  return;
                }
        }

	if (living(this_object()) && present("zhuanshi tongzhi", ob))
	{
		command("gongxi " + ob->query("id"));
		room = find_object("/d/zhuanshi/sky/sky3");
		if (! room) room = load_object("/d/zhuanshi/sky/sky3");
		ob->move(room);	
        }else	command("say ���ת��֪ͨ��Ū���ˣ��Ͽ�ȥ�һ�����");

        ::lost();
}

void unconcious()
{
        say( HIC"����ң˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬����ң�ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
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

