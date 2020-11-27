inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include <ansi.h>
#include "gumu.h"

#define SHUNV    "/clone/lonely/shunvjian"
#define YINSUO    "/clone/lonely/yinsuo"


string ask_zhen();

void create()
{
        object ob;

        set_name("С��Ů", ({ "xiao longnv", "xiao", "longnv" }));
        set("gender", "Ů��");
        set("age", 22);
        set("long", @LONG
��һ���������£���������������ѩ�������
��֮�������䣬ʵ��������������¡�����
�ݡ�
LONG);
        set("attitude", "friendly");
        set("str", 21);
        set("int", 30);
        set("con", 25);
        set("dex", 26);
        set("per", 30);
        set("shen_type", 1);

        set("qi", 7000);
        set("max_qi", 7000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 100);

        set("combat_exp", 3000000);

        set_skill("force", 250);
        set_skill("suxin-jue", 220);
        set_skill("yunv-xinjing", 250);
        set_skill("sword", 350);
        set_skill("yunv-jian", 220);
        set_skill("suxin-jian", 350);
        set_skill("quanzhen-jian", 200);
        set_skill("whip", 220);
        set_skill("yinsuo-jinling", 250);
        set_skill("dodge", 250);
        set_skill("yunv-shenfa", 200);
        set_skill("parry", 250);
        set_skill("unarmed", 200);
        set_skill("meinv-quan", 200);
        set_skill("strike", 220);
        set_skill("tianluo-diwang", 220);
        set_skill("zuoyou-hubo", 200);
        set_skill("literate", 200);
        set_skill("throwing", 220);
        set_skill("yufeng-zhen", 220);
        set_skill("martial-cognize", 230);

        map_skill("force", "yunv-xinjing");
        map_skill("whip", "yinsuo-jinling");
        map_skill("sword", "suxin-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("strike", "tianluo-diwang");
        prepare_skill("unarmed", "meinv-quan");

        create_family("��Ĺ��", 3, "����");

        set("yfzhen_count", 3);

        set("inquiry", ([
                "�����"   : (: ask_zhen :),
        ]));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({                
                (: exert_function, "recover" :),
				(: exert_function, "wang" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.hui" :),
				(: perform_action, "sword.hebi" :),
        }) );

        setup();
        if (clonep())
        {
                ob = find_object(SHUNV);
                if (! ob) ob = load_object(SHUNV);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/gangjian");                        
                        ob->move(this_object());
                        ob->wield();
                }
                ob = new("/clone/weapon/gangjian"); 
                //ob = new("/d/death/obj/weapon74");
                ob->move(this_object());
                set_temp("handing", ob);                
        }
        carry_object("/clone/cloth/baipao")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob) )
                return;

     /*   if (ob->query("per") < 26)
        {
                command("say ����ʵ�ڲ��ҹ�ά���ҿ��㻹�����˰ɡ�\n");
                return;
        }*/

        command("say �ðɣ��Ҿ����������ͽ���ˡ�\n");
        command("recruit " + ob->query("id"));
}

string ask_zhen()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();

        if (! (fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
                return RANK_D->query_respect(me) + "�뱾�ɺ��޹ϸ𣬺�����"
                "���ɰ�����\n";

        if (me->query_skill("yufeng-zhen", 1) < 100)
                return RANK_D->query_respect(me) + "��������ַ���򻹲�����"
                "�����������Ҳû��ʲô�á�\n";

        if (query("yfzhen_count") < 1)
                return "�������ˣ�����ͷ��������Ѿ������ˡ�\n";

        add("yfzhen_count", -1);
        
        message_vision(HIY "$N�ó�һ�������ݸ�$n��\n" NOR, this_object(), me);

        ob = new("/d/gumu/obj/yufeng-zhen");
        ob->move(me, 1);

        return "�ðɣ���������������ȥ�ðɡ�\n";
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "��������" :
                return MASTER_D->give_item(me, this_object(),
                        ([ "item"    : YINSUO,
                           "master"  : 1,
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 150, ]));
                break;

        case "ǧ�˰���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-jian/mei",
                           "name"    : "ǧ�˰���",
                           "sk1"     : "yunv-jian",
                           "lv1"     : 35,
                           "dodge"   : 30,
                           "gongxian": 50, ]));
                break;

        case "���޵�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianluo-diwang/wang",
                           "name"    : "���޵�����",
                           "sk1"     : "tianluo-diwang",
                           "lv1"     : 60,
                           "dodge"   : 30,
                           "gongxian": 60, ]));
				break;
		
		case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/quanzhen-jian/ding",
                           "name"    : "������",
                           "sk1"     : "quanzhen-jian",
                           "lv1"     : 100,
                           "dodge"   : 100,
                           "gongxian": 500, ]));
				break;
				
		case "���־�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/quanzhen-jian/chan",
                           "name"    : "���־�",
                           "sk1"     : "quanzhen-jian",
                           "lv1"     : 80,
                           "dodge"   : 80,
                           "gongxian": 200, ]));
				break;


        case "��Ĺ�ľ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meinv-quan/you",
                           "name"    : "��Ĺ�ľ�",
                           "sk1"     : "meinv-quan",
                           "lv1"     : 70,
                           "force"   : 70,
                           "gongxian": 160, ]));
                break;

        case "���յ�Ѩ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinsuo-jinling/dian",
                           "name"    : "���յ�Ѩ",
                           "sk1"     : "yinsuo-jinling",
                           "lv1"     : 70,
                           "force"   : 90,
                           "gongxian": 260, ]));
                break;

        case "��Ӱ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yufeng-zhen/ying",
                           "name"    : "��Ӱ��",
                           "sk1"     : "yufeng-zhen",
                           "lv1"     : 90,
                           "force"   : 100,
                           "gongxian": 300, ]));
                break;

        case "˫���ϱ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/suxin-jian/hebi",
                           "name"    : "˫���ϱ�",
                           "sk1"     : "suxin-jian",
                           "lv1"     : 130,
                           "force"   : 120,
                           "dodge"   : 100,
                           "gongxian": 1000, ]));

                break;
		case "�����ľ�" :
			
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yunv-xinjing/wang",
                           "name"    : "�����ľ�",
                           "sk1"     : "yunv-xinjing",
                           "lv1"     : 200,
                           "force"   : 300,
                           "gongxian": 1000, ]));
			
                break;
		case "���콣��" :
			
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/suxin-jian/hui",
                           "name"    : "���콣��",
                           "sk1"     : "suxin-jian",
                           "lv1"     : 250,
                           "force"   : 350,
                           "gongxian": 2500, ]));
			
                break;
		
        default:
                return 0;
        }
}

void reset()
{
        set("yfzhen_count", 4 + random(2));
}

void unconcious()
{
        die();
}


void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard = present ("yang guo", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard && !guard->is_fighting())
         {
                 message_vision (CYN "$N��ŭ������������̫������������飡\n" NOR, guard);
                 guard->kill_ob(ob);
         }
}
