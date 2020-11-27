#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("������", ({ "xu ziling", "xu", "ziling"}));
        set("long", "һ�����εİ������꣬�������������µ������ꡣ\n"); 
        set("nickname", HIR "��������" HIY "��ղ�����" NOR);
        set("title", HIY "½�ۼ�" NOR);
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 30);

        set("max_qi", 50000);
        set("max_jing", 40000);
        set("max_neili", 20000);
        set("neili", 20000);
        set("jiali", 100);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: perform_action, "parry.jingang" :),
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
        }) );

        set_skill("dodge", 600);
        set_skill("hand", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("shou-yin", 600);
        set_skill("jiuzi-zhenyan", 600);
        set_skill("jingang-buhuaiti", 600);
        set_skill("jinzhong-zhao", 600);	
        set_skill("zhuangzi-wu", 600);
        set_skill("force", 600);
        set_skill("changsheng-jue", 600);
        set_skill("blade", 600);
        set_skill("badao-daofa", 600);
        set_skill("literate", 500);
//      set_skill("count", 200);
        set_skill("buddhism", 350);
        set_skill("lamaism", 350);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "badao-daofa");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "jingang-buhuaiti");
        map_skill("hand", "jiuzi-zhenyan");
		
	set_temp("apply/damage", 300);
	set_temp("apply/unarmed_damage", 350);
        set_temp("apply/armor", 700);
        set("apply/dodge", 400); 

        prepare_skill("hand", "jiuzi-zhenyan");

        setup();

        carry_object("/d/zhuanshi/sky/npc/obj/cloth1")->wear();
        carry_object("/d/zhuanshi/sky/npc/obj/hands")->wear();
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

        if (query("qi") < 200 ||
            query("jing") < 100 ||
            query("neili") < 250)
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

        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        set("neili", query("max_neili"));
	remove_all_enemy(1);

        ::win();
}


void lost()
{
	command("say ���Ѿ���ǿ�˰���");
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
        set("neili", query("max_neili"));
	remove_all_enemy(1);
	lost();
}
void die()
{
        unconcious();
}

