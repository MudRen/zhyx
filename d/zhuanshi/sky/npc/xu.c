#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("������", ({ "xu ziling", "xu", "ziling"}));
        set("long", "һ�����εİ������꣬�������������µ������ꡣ\n"); 
        set("nickname", HIR "����˫��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("per", 100);

        set("max_qi", 50000);
        set("max_jing", 40000);
        set("max_neili", 55000);
        set("neili", 55000);
        set("jiali", 10);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "parry.zhao" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
        }) );

        set_skill("dodge", 850);
        set_skill("hand", 850);
        set_skill("parry", 850);
        set_skill("unarmed", 850);
        set_skill("shou-yin", 850);
        set_skill("jiuzi-zhenyan", 850);
        set_skill("jingang-buhuaiti", 800);
        set_skill("jinzhong-zhao", 800);	
        set_skill("zhuangzi-wu", 850);
        set_skill("force", 850);
        set_skill("changsheng-jue", 850);
        set_skill("blade", 850);
        set_skill("badao-daofa", 850);
        set_skill("literate", 100);
        set_skill("count", 150);
        set_skill("buddhism", 400);
        set_skill("lamaism", 400);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "badao-daofa");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "jinzhong-zhao");
        map_skill("hand", "jiuzi-zhenyan");
		
	set_temp("apply/damage", 300);
	set_temp("apply/unarmed_damage", 350);
        set_temp("apply/armor", 700);
        set("apply/dodge", 400); 

        prepare_skill("hand", "jiuzi-zhenyan");

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/hands")->wear();
      //  carry_object("/kungfu/class/sky/obj/yishu");
      //  carry_object("/kungfu/class/sky/obj/sheli");
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

        if (query("qi") < 28000 ||
            query("jing") < 8000 ||
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
		room = find_object("/d/zhuanshi/sky/sky5");
		if (! room) room = load_object("/d/zhuanshi/sky/sky5");
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

