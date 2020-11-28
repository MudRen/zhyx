//whitlady.c 
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("��̫��", ({ "long taizi","taizi" }) );
        set("gender", "����" );
   set("nickname", HIC"��������" NOR );
    set("title", HIW"����"NOR);
        set("age", 18);
        set("long", "����������������������������С���������ĳ̶Ⱦ�������κ��ˡ�\n");
        set("shen_type", 1);
        set("combat_exp", 10000000);
        set("str", 50);
        set("dex", 18);
        set("con", 50);
        set("int", 20);
        set("attitude", "friendly");
        set("max_qi", 10000);
        set("max_jing",5000);
        set("neili", 9999);
        set("max_neili", 9999);
        set("score", 800);

        set_skill("force", 500);
        set_skill("dodge", 500);
        set_skill("strike", 500);
        set_skill("finger", 500);       
        set_skill("parry", 500);
        set_skill("hand", 500);
        set_skill("whip", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("yinfeng-dao", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("tougu-zhen", 500);
        set_skill("yinlong-bian", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("jiuyang-shengong", 500);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "jiuyin-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("whip", "yinlong-bian");
        map_skill("finger", "tougu-zhen");
        map_skill("strike", "yinfeng-dao");
        map_skill("force", "jiuyang-shengong");

        prepare_skill("strike", "yinfeng-dao");
        prepare_skill("finger", "tougu-zhen");
        

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "whip.chan" :),
                (: perform_action, "hand.zhi" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        carry_object("/u/kyy/obj/guan.c")->wear();
        carry_object("/u/kyy/obj/ring.c")->wear();
        carry_object("/u/kyy/obj/bian.c")->wield();
}
int accept_hit(object ob) 
{ 
        command("say ����ȥ�ɣ�"); 
        kill_ob(ob); 
        command("perform whip.chan"); 
        return 1; 
} 
 
        int accept_kill(object ob) 
{ 
	string str;
	object *ob_list,ob_baobiao;
	int npc_ok,i;

	npc_ok = 0;
        command("say �ߣ�������"); 
        kill_ob(ob); 
	str = "/u/kyy/npc/baobiao.c";
	ob_list = children(str);
	for(i=0; i<sizeof(ob_list); i++) {
		if( environment(ob_list[i]) ) {
			ob_baobiao = ob_list[i];
			npc_ok = 1;
			break;
		}
	}
	if (!npc_ok) ob_baobiao = new(str);
	ob_baobiao->move(environment(this_object()));
	message_vision(HIW "$N��һ�����������ģ���\n" NOR,this_object());
	message_vision(HIW "$N���µ�����С���ڣ�̫���кηԸ�����\n" NOR,ob_baobiao);
	message_vision(HIW "$N�ȵ�����$n���С���˵����Ҷ����Ƭ����\n" NOR,this_object(),ob);
	ob_baobiao->kill_ob(ob);
        command("perform whip.chan"); 
        return 1; 
} 


void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
             say("��̫��˵������λ" + RANK_D->query_respect(ob) +
                 "�����ңԶ�ĵط���������������ʲô����\n");
        return;
}

