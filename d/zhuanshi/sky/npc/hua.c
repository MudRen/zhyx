#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("��Ӣ��", ({ "hua yingxiong", "hua", "yingxiong"}));
        set("long", "һ�����ε��������ӣ����ų����������ǻ�Ӣ�ۡ�\n"
                    "��˵��������ɷ���ǣ�һ��Ư����������ء�����\n"
                    "ϰ��һ����������������л�����������ܡ�����\n"
                    "ս���޵С�\n"); 
        set("nickname", HIW "�л�Ӣ��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 120);
        set("int", 120);
        set("con", 120);
        set("dex", 120);
        set("per", 120);

        set("max_qi", 55000);
        set("max_jing", 20000);
        set("max_neili", 65000);
        set("neili", 65000);
        set("jiali", 200);
        set("combat_exp", 80000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "sword.aoqi" :),
                (: perform_action, "sword.jianqi" :),
				(: perform_action, "strike.zhangzhen" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

		
        set_skill("dodge", 700);
        set_skill("strike", 700);
        set_skill("parry", 700);
        set_skill("unarmed", 700);
        set_skill("force", 700);
        set_skill("sword", 800);
        set_skill("siji-jianfa", 700);
        set_skill("china-aojue", 800);
        set_skill("idle-force", 700);
        set_skill("literate", 200);

        map_skill("force", "china-aojue");
        map_skill("sword", "china-aojue");
        map_skill("dodge", "china-aojue");
        map_skill("parry", "china-aojue");
        map_skill("strike", "china-aojue");
        map_skill("unarmed", "china-aojue");
		
	    set_temp("apply/damage", 350);
		set_temp("apply/unarmed_damage", 350);
        set_temp("apply/armor", 300);
        set("apply/dodge", 400); 

        prepare_skill("strike", "china-aojue");       

        setup();

        carry_object(__DIR__"obj/cloth3")->wear();
        carry_object(__DIR__"obj/chijian")->wield();        
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

        if (query("qi") < 20000 ||
            query("jing") < 5000 ||
            query("neili") < 25000)
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
		room = find_object("/d/zhuanshi/sky/sky4");
		if (! room) room = load_object("/d/zhuanshi/sky/sky4");
		ob->move(room);	
        }else	command("say ���ת��֪ͨ��Ū���ˣ��Ͽ�ȥ�һ�����");

        ::lost();
}

void unconcious()
{
        say( HIC"��Ӣ��˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬��Ӣ���ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
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


