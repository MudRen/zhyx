// tangltt

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER; 
inherit F_COAGENT;  

int do_pull();
string ask_me();
void close(object room);

void create()
{
        set_name("����̫̫", ({ "tang laotai", "tang" }));
        set("nickname", HIW "��������" NOR);
        set("long", 
                "���������ŵڶ�����������̫̫�������ľ�Ӫ�£�\n"
                "�����ڽ��������������Ժա�\n"
                "����Լ��ʮ���࣬һͷ������������档\n");
	set("gender", "Ů��");
	set("age", 72);
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

        set_skill("force", 380);
        set_skill("throwing", 380);
        set_skill("dodge", 380);
        set_skill("parry", 380);
        set_skill("literate", 380);
        set_skill("hand", 380);
        set_skill("sword", 380);
        set_skill("boyun-suowu", 380);
        set_skill("biyun-xinfa", 380);
        set_skill("qiulin-shiye", 380);
        set_skill("wuzhan-mei", 380);
        set_skill("poison", 380);
        set_skill("medical", 280);
        set_skill("medical", 380);
        set_skill("tangmen-throwing", 380);
        set_skill("tangmen-poison", 380);
        set_skill("tangmen-medical", 380);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");
        
        create_family("��������", 2, "����");
	set("inquiry", ([
	        "����ү��" : (:do_pull:),
                "��������" : (: ask_me :)	        
	]));
	
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        set("master_ob", 4);
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

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;
                        
        if ( (string)ob->query ("family/family_name") != "��������" || 
             count_lt(ob->query ("combat_exp"), 600000) )
	{
        	command("say �㻹���Ȱ���ȱΪʦ��ѧЩ���ŵĻ�������ɣ�\n");
                return;
        }

        if ((int)ob->query_skill("biyun-xinfa", 1) < 150) 
        {
                command("say ������Ȼ�԰���Ϊ����������Ҫ����������"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "�Ƿ�Ӧ���ڱ����ķ��϶��µ㹦��");
                return;
        }
        if ((int)ob->query("dex") < 30)
        {
                command("say �������̫���ˣ���Ҫ�����Լ�������\n");
                return;    
        }
        if ((int)ob->query("int") < 28) {
                command("say ��������ע�ص��ӵ���ѧ��Ϊ��");
                command("say ���ɹ���Ҫ���������ã��������������������Զ�⾳�����Բ����ǲ��еġ�");
                command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
                return;
        }
        if ((int)ob->query("str") < 30) {
                command("say " + RANK_D->query_respect(ob) + "����������������������ذɡ�");
                return;
        }

        command("say �ðɣ��ӽ�����������ҵĹ��ŵ����ˡ�\n");
        command("recruit " + ob->query("id"));
}

int do_pull()
{
	object me, room;
	me = this_player();
	room = environment(this_object());
	message_vision(YEL"\n����̫̫һת���ڴ�ͷ�⶯��һ�¡�\nֻ�������̡��������촲�ŵĵ����ƿ���һ�����ڡ�\n"NOR, me);
	room->set("exits/down", "/d/tangmen/didao1");
	remove_call_out("close");
	call_out("close", 3, environment(this_object()));
	return 1;
}

void close(object room)
{
	message("vision",HIR"�����һ�����죬���ǰ����ֱ������ˡ�\n"NOR, this_player());
	room->delete("exits/down");
}

string ask_me()
{
        object me;
        me = this_player();
        if (me->query_temp("marks/��"))
        {
                command("say ������Ʒ��Ǹ���Ѿͷ��̽��Ϣ�𣿿��Ҳ�������");
                command("hit " + me->query("id"));
                return "������̫�ŷǵý�ѵ��һ�²��ɡ�\n";
        }
        if (me->query_temp("marks/��"))
        {
                command("angry " + this_player()->query("id"));
                command("say �ѵ�����������ˮһ����������������\n");
                command("heng " + this_player()->query("id"));
                command("say �Ʒ��Ǹ���Ѿͷ��\n");
                this_player()->set_temp("marks/��", 1);
                me->delete_temp("marks/��");
                return"����ˮ�ѱ��ҹ������ˣ��������ټ��������С���ˣ�\n";
        }
        else
        {       
                return "�����ӣ���˵ɶ�ӣ���̫��������Ŷ��\n";
        }


}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "�ƻ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/hua",
                           "name"    : "�ƻ�",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 180,
                            "gongxian": 1000,
                           "sk2"     : "boyun-suowu",
                           "lv2"     : 180, 
                           "shen"    : 100000, ]));
                break;
                
        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qiulin-shiye/wu",
                           "name"    : "������",
                           "sk1"     : "qiulin-shiye",
                           "lv1"     : 100,
                            "gongxian": 100, 
                           ]));
                break;

        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/boyun-suowu/dian",
                           "name"    : "������",
                           "sk1"     : "boyun-suowu",
                           "lv1"     : 120,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "neili"   : 1400, ]));
                break;

        case "����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/boyun-suowu/meng",
                           "name"    : "����",
                           "sk1"     : "boyun-suowu",
                           "lv1"     : 160,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 160,
                            "gongxian": 1400, 
                           ]));
                break;

        case "������Ӱ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuzhan-mei/liu",
                           "name"    : "������Ӱ",
                           "sk1"     : "wuzhan-mei",
                           "lv1"     : 120,
                            "gongxian": 400,
                           "shen"    : 4000, ]));
                break;

        case "���Ӹ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/biao",
                           "name"    : "���Ӹ���",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "����ǧ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/qian",
                           "name"    : "����ǧ��",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;
                
        case "ɢ����Ů" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tangmen-throwing/san",
                           "name"    : "ɢ����Ů",
                           "sk1"     : "tangmen-throwing",
                           "lv1"     : 140,
                           "sk2"     : "biyun-xinfa",
                           "lv2"     : 120,
                            "gongxian": 600,
                           "shen"    : 60000, ]));
                break;
                                                
        default:
                return 0;
        }
}
