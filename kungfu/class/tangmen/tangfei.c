#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

string ask_tanghua();

void create()
{
        set_name("�Ʒ�", ({ "tang fei","tang"}));
        set("nickname", HIC "��Ҳ��֪��" NOR);
        set("long", "��������֮һ����������һ������֮�У���ʹ�еİ������ƻ��������ž��Ű���֮һ��\n");
        set("gender", "Ů��");
        set("age", 28);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 26);
        set("con", 24);
        set("dex", 23);
        set("max_qi", 7000);
        set("max_jingli", 1400);
        set("max_douzhi", 450);
        set("douzhi", 450);
        set("neili", 3500);
        set("max_neili", 3500);
        set("yanli", 200);
        set("jiali", 100);
        set("combat_exp", 750000);
        set("score", 7000);
        set("level", 10);

        set_skill("force", 150);
        set_skill("throwing", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("literate", 150);
        set_skill("hand", 150);
        set_skill("sword", 150);
        set_skill("boyun-suowu", 150);
        set_skill("biyun-xinfa", 150);
        set_skill("qiulin-shiye", 150);
        set_skill("wuzhan-mei", 150);
        set_skill("poison", 150);
        set_skill("medical", 150);
        set_skill("tangmen-throwing", 150);
        set_skill("tangmen-poison", 150);
        set_skill("tangmen-medical", 150);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");

        set("chat_chance_combat",  20);
        set("chat_msg_combat",  ({
        	(: exert_function, "recover" :),  
        	(: perform_action, "throwing.san" :),   
                ( : command("use hua") : ),
                ( : command("use hua") : ),
        }) );   
        
        set("inquiry", ([
                "�ƻ�"    : ( : ask_tanghua : ),
                "tanghua" : ( : ask_tanghua : ),
        ]) );           
        
        create_family("��������", 3, "����");
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  
        
        set("master_ob", 2);
	setup();
        carry_object("/d/tangmen/obj/mcloth")->wear();
        carry_object("/d/tangmen/obj/mshoe")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/qinglianzi"));  
        carry_object("/d/tangmen/obj/qinglianzi");
        carry_object("/kungfu/class/tangmen/obj/hua")->wield();
        
}

string ask_tanghua()
{
        object me,ob,her;
        
        me = this_player();
        her = this_object();
                
        if ( !me->query_temp("thua2") )
        { 
                command("laugh "+me->query("id") );
                me->add_temp("thua2", 1);
                return HIC "����Ϊ���а����һ�Ҫ����Ҫ�أ�\n" NOR;      
        }
        
        if ( me->query("family/family_name") != "��������" )
        {
                command("hmm "+me->query("id") );
                her->kill_ob(me);
                return HIR"����һ����Ҫ����,����......\n"NOR;
        }
        
        command("addoil "+ me->query("id") );
        command("pat "+ me->qurey("id") );
        command("say ���ðɣ�������ƻ��������ˡ��� \n");
        ob = new("/kungfu/class/tangmen/obj/hua.c");
        ob->move(me);
//           message("channel:rumor", HIM "��ҥ������" HIM " ��..." + me->query("name") + HIM "�ҵ������Ű���" ;118                                  HIG "�ƻ�" HIM "�ˣ�\n" NOR, users());
        return "�ðɣ�\n";
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
                                        
	if ((int)ob->query_skill("biyun-xinfa", 1) < 100) {
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
