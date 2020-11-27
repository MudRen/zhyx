// tangfang.c �Ʒ�

#include <ansi.h>
#include "tangmen.h"

string ask_me();
int carry_qian();

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�Ʒ�", ({ "tang fang", "tang" }));
	set("long", 
"�Ʒ���Ľ�С�����ļ�Ϊ���㣬�ִ�����Ӣ�����徢����������\n"
"�������ų���������Ң˴֮Ů���ƴ�֮�ã����ֵ�����̫̫�����²��������ŵ�λ�ĸߡ�\n"
"�����ݲ԰ף������㲣����������ӷ·𻹴�����ۡ�\n");		
	set("gender", "Ů��");
	set("age", 20);
	set("class", "tangmen");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 20);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 800);
	set("max_jing", 2000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 60);
	set("combat_exp", 900000);
	set("level", 15);
	set("score", 80000);

	set_skill("force", 200);
	set_skill("biyun-xinfa", 200);
	set_skill("dodge", 200);
	set_skill("qiulin-shiye", 200);
	set_skill("hand", 200);
	set_skill("boyun-suowu", 180);
	set_skill("parry", 200);
	set_skill("throwing", 200);
	set_skill("sword", 200);
	set_skill("wuzhan-mei", 200);
	set_skill("tangmen-throwing", 200);
	set_skill("literate", 100);
        set_skill("poison", 200);
        set_skill("medical", 200);
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

	map_skill("force", "biyun-xinfa");
	map_skill("dodge", "qiulin-shiye");
	map_skill("hand", "boyun-suowu");
	map_skill("parry","boyun-suowu");
	map_skill("sword", "wuzhan-mei");
	map_skill("throwing","tangmen-throwing");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");
        	
        create_family("��������", 3, "����");
	
        set("chat_chance" , 20);
        set("chat_msg", ({
        	"�ҵ�����絽�Ķ�ȥ�������ڻ��������ң�\n",
		"�Ʒ�����̾���������ᰴס���ң�����ÿ���Զ���ĺ��档\n",
		"�Ʒ��������ĵز�Ū�˼������ң������������Ҳ��֪������������������....��\n",
		"�Ʒ����ᴵ��һ�����������̴�㣬�������Ỻ��������ա� \n",        	
        	( : command("shy") : ),
        	( : command("sigh") : ),
        	( : command("drop qianqian") : ),
        	( : command("wield all") : ),
        	( : command("drop qianqian") : ),
        }) );
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
        	( : command("yun recover") : ),
        	( : command("yun recover") : ),
        	( : carry_qian : ),
        	( : carry_qian : ),
        	( : command("use qian") : ),
        	( : command("use qian") : ),
        	( : command("wield all") : ),
        	( : command("wield all") : ),
        }) );

        set("inquiry", ([
        	"ǧǧ��" : "������̫̫ȥ����\n",
        	"ǧǧ"   : "������̫̫ȥ����\n",
        	"����" : (: ask_me :),
        ]) );	 	

	set("master_ob", 2);
	setup();
        carry_object("/d/tangmen/obj/mcloth")->wear();
        carry_object("/d/tangmen/obj/mshoe")->wear();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;

        if ( ob->query("family/family_name") != "��������" )
        {
                command("say �����Ĵ����������������ң��������������ˣ��Ҳ�������Ϊͽ����\n");
                return;
        }
                                        
        if ((int)ob->query_skill("biyun-xinfa", 1) < 80) {
		command("say ������Ȼ�԰���Ϊ����������Ҫ����������"); 
		command("say " + RANK_D->query_respect(ob) + 
			"�Ƿ�Ӧ���ڱ����ķ��϶��µ㹦��");
		return;
	}

        if ( ob->query_skill("biyun-xinfa", 1) < 80 && ob->query_skill("tangmen-throwing", 1) < 80 )
        {
        	command("say ������ķ��Ͱ�����̫������Ҫ���Ͱ�����\n");
        	return;
        }	        	   	
	if (ob->query("int") < 28) {
		command("say ��������ע�ص��ӵ���ѧ��Ϊ��");
		command("say ���ɹ���Ҫ���������ã��������������������Զ�⾳�����Բ����ǲ��еġ�");
		command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	command("say �ðɣ��Ҿ��������...");
	command("recruit " + ob->query("id"));
}
string ask_me()
{
        object me;
        me = this_player();
        
	if (me->query_temp("marks/��"))
	{
	        return "���˰ɣ�������Ҳ��֪�����ɵ���Ϣ�����߰ɡ�\n";
        }
	command("ah " + this_player()->query("id"));
	command("say ��֪�������𣡣��Դ����ϴδ������ź��ʧȥ����Ϣ��\n");
	command("sigh");
	this_player()->set_temp("marks/��",1);
	return "��̫̫Ϊ���·ǳ���������Ҳ�����Ҽ����ˡ�\n";
	   

}
	
int accept_object(object who, object ob)
{
	object book;
	book = new("/d/tangmen/obj/throwbook");
        if ((string)ob->query("name")=="����") 
        {
                if(!query("yl_trigger")) 
                {
		        say(
"�Ʒ�˵�����ⲻ�����ɵ�������̫лл���ˣ���Ȼû�м������ɣ�\n"
"�ܼ�����������,���Ѿ�����ο�ˡ�\n"
"�Ʒ����Ƶ�̾��һ������������һ�������ܾ��������Ǹ���ĳ�л�ɡ�\n"
"�Ʒ���" + book->query("name") + "������" + who->query("name") + "��\n");
		        book->move(who);
                        set("yl_trigger", 1);
                }
                else say("�Ʒ���ĿԲ����˵�������������ô�������ᰡ��\n");
                call_out("destroy", 1, ob);
	        return 1;
	}
        return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

int carry_qian()
{
	object ob;

        ob = new("/kungfu/class/tangmen/obj/jie.c");
	ob->move(this_object());
	return 1;
}	
