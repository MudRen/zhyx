// zhang1.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

int shang_ya();
mixed ask_pfm();

void create()
{
    set_name("�ų˷�", ({"zhang chengfeng", "zhang", "chengfeng"}));
    set("nickname", HIY "�����ħ" NOR );
    set("title", "������̳���");
    set("gender", "����");
    set("age", 42);
    set("shen_type", -1);
    set("long", "����������̳��ϡ�\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);
    set("inquiry", ([
        "��ľ��"   : "���̵��ӻ�ֽ������Ʒ������£�\n",
        "�������" : "���̵��ӻ�ֽ������Ʒ������£�\n",
        "��ľ��"   : "���Ǳ��̽������ƣ���������������٣�\n",
        "����"     : (: shang_ya :),
        "����"     : (: ask_pfm :),
        "������ת" : (: ask_pfm :),
    ]) );

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("club", 180);
    set_skill("tianmo-gun", 180);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "tianmo-gun");
    map_skill("club", "tianmo-gun");

    prepare_skill("hand", "huanmo-longtianwu");
    prepare_skill("cuff", "xuwu-piaomiao");

    create_family("�������", 2, "����");

    setup();
    carry_object("/d/heimuya/npc/obj/shutonggun")->wield();
    carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 120)
    {
         command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
         return;
    }

    command("recruit " + ob->query("id"));
    ob->set("title", HIM "�������" HIY "��ﻤ��" NOR);
}

int shang_ya()
{
    object ob, myenv ;
    ob = this_player ( ) ;
    if (ob->query("family/family_name") == "�������")
    {
        message_vision("�ų˷�һ���֣���������һ���������\n",ob);
        message_vision("$Nһ�������˵��������������ؽ�����ȥ......\n", ob);
        myenv = environment (ob) ;
        ob->move ("/d/heimuya/basket");
        call_out("goto_heimuya", 10, ob) ;
        return 1;
    }
    else  
    message_vision("�ų˷��������´�����$Nһ�£�ʲô�����£���ĺ�ľ���أ���\n",ob);
    return 1;
}

int accept_object(object who, object ob)
{
    object myenv ;
    if (ob->query("id") == "heimu ling")
    {
        message_vision("�ų˷��$N˵���ã���λ" + RANK_D->query_respect(who) + "�����Ǿ���ɣ�\n" , who);
        message_vision("�ų˷�һ���֣���������һ���������\n", who);
        message_vision("$Nһ�������˵��������������ؽ�����ȥ......\n", who);
        myenv = environment (who) ;
        who->move ("/d/heimuya/basket");
        call_out("goto_heimuya",10,who) ;
        return 1;
    }
    else  
    {
        message_vision("�ų˷��$N˵�����ˣ�ң���\n", who);
        this_object()->kill_ob(who);
    }
    return 0;
}

void goto_heimuya (object ob)
{
    tell_object(ob , "����ǰһ����һ������ɫ����������ǰ�����ǻԻ͡�\n");
    ob->move ("/d/heimuya/chengdedian") ;
}

mixed ask_pfm()
{
     object me = this_player();

     if (me->query("can_perform/tianmo-gun/tian"))
           return RANK_D->query_respect(me) + "������Ϸ��д�һ�����գ�";

     if (me->query("family/family_name") != query("family/family_name"))
           return "�����书�������֣���λ" + RANK_D->query_respect(me) +
                  "��Ȼ��ѧ�������������������Σ�";

     if (me->query_skill("tianmo-gun", 1) < 150)
           return "�����ħ����Ƿ����ٶ�����ȥ�ɣ�";

     message_vision(HIY "$n" HIY "��$N" HIY "���˵�ͷ����ϸ������ˡ�\n" HIY
                    "ֻ��$n" HIY "����������������ͭ��б�����ϣ���������һ��" HIY
                    "Ѹ�������$N" HIY "ֻ����������������������߰�������衣" NOR,
                    me, this_object());
     command("say ������û�У�");
     tell_object(me, HIC "��ѧ���ˡ�������ת����һ�С�\n" NOR);
     if (me->can_improve_skill("club"))
             me->improve_skill("club", 160000);
     me->set("can_perform/tianmo-gun/tian", 1);
     return 1;
}

