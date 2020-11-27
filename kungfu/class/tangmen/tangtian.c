// tangtian.c
#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

int give_job();

void create()
{
	set_name("����", ({ "tang tian", "tang", "tian"}));
	set("long", "�������������ӵĴ����ˣ���������һ������֮�У���������Ҳ��ȻΪһ��֮�ۡ���\n");
	set("gender", "Ů��");
	set("age", 25);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1500);
        set("max_douzhi", 500);
        set("douzhi", 500);
        set("neili", 4000);
        set("max_neili", 4000);
        set("yanli",200);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("level", 15);
        set("shen",3000);
        set("score", 7000);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("poison", 180);
        set_skill("medical", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("medical", "tangmen-medical");
        map_skill("poison", "tangmen-poison");
        
        prepare_skill("hand", "boyun-suowu");
        
	create_family("��������", 3, "����");

	set("inquiry", ([
		"job" : ( : give_job  : ),
	]));
	
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        set("master_ob", 2);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        carry_object("/d/tangmen/obj/fhshi")->wield();
        carry_object("/d/tangmen/obj/tiejili")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
}

int give_job()
{
        object me;
        string msg;
        int whose;

        me = this_player();

        if ( (string)me->query("family/family_name") != "��������" )
        {
                command("say ������ʲô�ˣ�Ϊʲô���������\n");
                return 1;
        }

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                say("����˵��:��������û��������ɻ���һ����Ƹ���˵�ɣ���\n");
                return 0;
        }

        if ( (int)me->query_temp("tangmen/yao") || (int)me->query_temp("tangmen/biao") || (int)me->query_temp("tangmen/duyao"))
                command("say �����Ѿ������������ˣ���Ҫʲô���񣿡�\n");
        else
        {
//                if ( me->query("combat_exp") <= 20000 )
                if ( count_le(me->query("combat_exp"), 20000) )
                {
                        command("say ����...������ҩ����ȱ���֣���ȥ���ʰɣ���\n");
                        me->set_temp("tangmen/yao",1);
                }
                else if ( count_le(me->query("combat_exp"), 50000) )
                {
                        command("say ����...�������ڷ���ȱ���֣���ȥ���ʰɣ���\n");
                        me->set_temp("tangmen/biao",1);
                }
//                else if ( me->query("combat_exp") <= 100000 )
                else if (count_le( me->query("combat_exp"), 100000) )
                {
                        command("say ����...�����ƶ�����ȱ���֣���ȥ���ʰɣ���\n");
                        me->set_temp("tangmen/du",1);
                }
                else
                {
                        command("say �����Ѿ���һЩ�书�����ˣ�����ȥ����ĥ��ĥ���ˣ���\n");
                }
        }
        return 1;
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
//        if ( count_lt(ob->query("combat_exp"), 500000) )
        if ( count_lt(ob->query("combat_exp"), 500000) )
        {
        	command("say ����ľ���̫�٣��������õĹ���ģ���\n");
        	return;
        }	

        if ( ob->query_skill("biyun-xinfa", 1) < 80 && ob->query_skill("tangmen-throwing", 1) < 80 )
        {
        	command("say ������ķ��Ͱ�����̫������Ҫ���Ͱ�����\n");
        	return;
        }	
        

        command("say ���ðɣ��ӽ��������������ĵ����ˡ���\n");
        command("recruit " + ob->query("id"));
}


