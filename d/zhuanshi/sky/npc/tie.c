#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("������", ({ "tie chuanjia", "tie", "chuanjia" }) );
        set("nickname", WHT "���׽��" NOR);
        set("title", "���Ļ���");
        set("gender", "����");
        set("age", 42);
        set("long", "һ����Ŀ���ĺ��ӡ�\n");
        set("attitude", "peaceful");

        set("str", 80);
        set("con", 60);
        set("int", 20);
        set("dex", 65);

        set("max_qi", 15000);
        set("max_jing", 10000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 300);

        set("combat_exp", 26000000);
        set("shen_type", 1);
        set("score", 5000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.yin" :),
                	(: perform_action, "strike.juesha" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 600);
        set_skill("force", 600);
        set_skill("parry", 600);
        set_skill("dodge", 600);
        set_skill("strike", 600);
        set_skill("jinzhong-zhao", 600);
        set_skill("yijinjing", 600);
        set_skill("tie-zhang", 600);
        set_skill("feiyan-huixiang", 600);

        map_skill("parry", "jinzhong-zhao");
        map_skill("force", "yijinjing");
        map_skill("strike", "tie-zhang");        
        map_skill("dodge", "feiyan-huixiang");
        prepare_skill("strike", "tie-zhang");   

         set_temp("apply/damage", 300);
		set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 300);
        set("apply/dodge", 400); 

        setup();

        //carry_object("/kungfu/class/sky/obj/miji1");
        carry_object("/clone/cloth/cloth")->wear();
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

        if (! interactive(ob))
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
		room = find_object("/d/zhuanshi/sky/sky2");
		if (! room) room = load_object("/d/zhuanshi/sky/sky2");
		ob->move(room);	
        }else	command("say ���ת��֪ͨ��Ū���ˣ��Ͽ�ȥ�һ�����");
        ::lost();
}

void unconcious()
{
        say( HIC"������˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬�������ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
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

