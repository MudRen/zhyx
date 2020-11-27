#include <ansi.h>
inherit NPC;

void create()
{
        set_name("����", ({ "bei chou", "bei", "chou", "xizi" }) );
        set("nickname", HIW "��Ϸ��" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 68);
        set("long", HIC "����һ������Ϸ�Ӵ�����С��ͷ�����ü�\n"
                        "�����������һ�����ࡣ����ǵ���������\n"
                        "�ųơ�" HIR "���ͱ���" HIC "��Ϸ�ӱ���"
                        "\n" NOR);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 55000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 60000);
        set("neili", 60000);
        set("jiali", 200);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("combat_exp", 200000000);

        set_skill("dodge", 850);
        set_skill("unarmed", 850);
        set_skill("force", 850);
        set_skill("parry", 850);
        set_skill("sword", 850);
        set_skill("poison", 850);
        set_skill("medical", 850);
        set_skill("hand", 850);
        set_skill("strike", 850);
        set_skill("staff", 850);
        set_skill("finger", 850);
        set_skill("claw", 850);
        set_skill("blade", 850);
        set_skill("pixie-jian", 850);
        set_skill("literate", 850);
//      set_skill("taoism", 850);
	set_skill("count", 90);
        set_skill("buddhism", 850);
        set_skill("jiuyang-shengong", 850);
        set_skill("lingbo-weibu", 850);
        set_skill("qiankun-danuoyi", 850);
        set_skill("xuanming-zhang", 850);
        set_skill("jiuyin-baiguzhao", 850);
        set_skill("dugu-jiujian", 850);
        set_skill("liumai-shenjian", 850);
        set_skill("qianzhu-wandushou", 850);
        set_skill("ranmu-daofa", 850);
        set_skill("dagou-bang", 850);
        set_skill("shaolin-yishu", 850);
        set_skill("wudu-qishu", 850);
        set_skill("throwing", 850);
        set_skill("mantian-xing", 850);
        set_skill("idle-force", 850);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "liumai-shenjian");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");
		
	set_temp("apply/damage", 400);
	set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 800);
        set("apply/dodge", 400); 

        prepare_skill("finger", "liumai-shenjian");

        create_family("��ң��", 0, "����̩��");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({               
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),               
                (: perform_action, "hand.zhugu" :),  
                (: perform_action, "finger.zong" :),               
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),              
        }) );

        setup();
        carry_object("d/city/obj/cloth")->wear();
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

        if (query("qi") < 25000 ||
            query("jing") < 20000 ||
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
		room = find_object("/d/zhuanshi/sky/heaven");
		if (! room) room = load_object("/d/zhuanshi/sky/heaven");
		ob->move(room);	
        }else	command("say ���ת��֪ͨ��Ū���ˣ��Ͽ�ȥ�һ�����");

        ::lost();
}

void unconcious()
{
        say( HIC"����˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬�����ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
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