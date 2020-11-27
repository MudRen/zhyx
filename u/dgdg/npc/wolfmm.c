#include "/kungfu/class/emei/emei.h"
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_ml();
string ask_meinv();
string ask_gf09tangyuan();
string ask_childgift();
string ask_ydgift();



void create()
{
        set_name("������", ({ "wolfmm","wolf","mm"}));
        set("nickname", HIG "��ͯ�ڴ�ʹ" NOR);
        set("long", HIR "���������ʥŮ�������ǵ�ͽ�ܡ��ĸ��������Ͱ��ϴ���ʦ��\n");
        set("gender", "Ů��");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "fighter");

        set("str", 100);
        set("int", 22);
        set("con", 21);
        set("dex", 19);
        set("per",40);
        
        set("vendor_goods", ({
                "/u/dgdg/book/secretbook.c",      
        }));

        set("max_qi", 1200);
        set("max_jing", 600);
        set("neili", 1500);
        set("max_neili", 1500);
        set("combat_exp", 70000);

        set_skill("force", 120);
        set_skill("emei-xinfa", 120);
        set_skill("dodge", 100);
        set_skill("zhutian-bu", 100);
        set_skill("strike", 100);
        set_skill("sixiang-zhang", 100);
        set_skill("jinding-zhang", 100);
        set_skill("parry", 100);
        set_skill("blade", 100);
        set_skill("yanxing-dao", 100);
        set_skill("literate", 100);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);
        set_skill("martial-cognize", 20);

        map_skill("force","emei-xinfa");
        map_skill("dodge","zhutian-bu");
        map_skill("strike", "jinding-zhang");
        map_skill("blade", "yanxing-dao");
        map_skill("parry","yanxing-dao");

        prepare_skill("strike", "jinding-zhang");

        create_family("����", 2, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huan" :),
                (: perform_action, "strike.bashi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));


set("inquiry", ([ 
                //    "��Ů" : (: ask_meinv :),                   
                  //  "��Բ" : (: ask_gf09tangyuan :),
                      "��������" :(: ask_childgift :), 
               //     "makelove"  : (: ask_ml :),
                  //  "make love" : (: ask_ml :), 
                  //    "Ԫ������"  : (: ask_ydgift() :),                                
                ]));    

        setup();

        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_buy", "buy");
        
       

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
}


                
                
string ask_ydgift()
{
        object me;
        object ob;

        me = this_player();
        if (me->query("gift2010_yd/get") >= 2 )
      
        {
            return "����ô���˻�Ҫ,������!Ҫ�˻���Ҫ������̰�ģ�û��������\n";
        }      
                
        message_vision(HIY "$N�ó�һ��ð�������ĺ����ݸ�$n��\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/hanbao2.c");
        ob->move(me, 1);
        me->add("gift2010_yd/get", 1);

        return "�ðɣ������������ȥ�԰ɡ�ף��Ԫ������!\n";
      }
           
                
                
                
                
                
                
                
string ask_gf09tangyuan()
{
        object me;
        object ob;

        me = this_player();
        if (me->query("gf09tangyuan/get") >= 3 )
      
        {
            return "����ô���˻�Ҫ,������!Ҫ�˻���Ҫ������̰�ģ�û��������\n";
        }      
                
        message_vision(HIY "$N�ó�һ����Բ�ִ����Բ�ݸ�$n��\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/tangyuan");
        ob->move(me, 1);
        me->add("gf09tangyuan/get", 1);

        return "�ðɣ������Բ����ȥ�԰ɡ�\n";
      }
      
      string ask_childgift()
{
        object me;
        object ob;

        me = this_player();
       /*  me->add("childgift/yao",1);
        if (me->query("childgift/yao") >= 1 )
      
        {
            return "Ҫ�˻���Ҫ������̰�ģ�û��������С����Ҫ��ʵŶ��\n";
      }      
                
        message_vision(HIY "$N�ó�һ����Բ�ִ�ĵ��ݸ�$n��\n" NOR, this_object(), me);

        ob = new("/u/dgdg/obj/childgift");
        ob->move(me, 1);
        me->add("gf09tangyuan/get", 1);

        return "�ðɣ�������������ȥ�ɡ�\n";
            }
      
string ask_ml()
{
//object me;
//me = this_player();
return "����!�������ɫ��,�һ����������˵�,�������!\n";

}

string ask_meinv()
{
//object me;
//me = this_player();
return "�ð�,������ô��,����һ������Բ��\n";
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
}
void die()
{
        unconcious();
}

varargs int receive_damage(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, HIR "�㷢��" + name() +
                    HIR "����һЦ����Ȼ����һ���ļ£�����һ���㱡�\n" NOR);
        return who->receive_damage(type, n, this_object());
}

varargs int receive_wound(string type, int n, object who)
{
        if (! objectp(who) || ! interactive(who) || who == this_object())
                return 0;

        tell_object(who, RED "�����" + name() +
                    RED "�����Ц��ֻ���û�����һʹ��ֱ��������\n" NOR);
        return who->receive_wound(type, n, this_object());
}
}