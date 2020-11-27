// dongfang.c
//Updated by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_book();
mixed ask_pfm();

void create()
{
    set_name("��������", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "�����޵�" NOR);
    set("title", HIM "������̽���" NOR);
    set("gender", "����");
    set("shen_type", -1);
    set("age", 42);
    set("long",
        "������������̽������ų����˿ɵУ������һ�ƺ�Ϊ���������ܡ���\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("inquiry", ([
        "����ͤ"   : "���ֱ���Ұ��˵����֣�������ѽ�� \n",
        "��а����" : "�����ж���������Ļ�����ֻ�ж�ͨ�˱��䣬�书�����ɡ�\n",
        "��������" : (: ask_book :),
        "����"     : (: ask_pfm :),
        "��Ӱ"     : (: ask_pfm :),
    ]));

    set("kuihua_count", 1);

    set("qi", 5000);
    set("max_qi", 5000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 3000000);
    set("score", 0);

    set_skill("force", 320);
    set_skill("riyue-xinfa", 300);
    set_skill("riyue-guanghua", 320);
    set_skill("sword", 300);
    set_skill("riyue-jian", 290);
    set_skill("pixie-jian", 300);
    set_skill("dodge", 300);
    set_skill("piaomiao-shenfa", 300);
    set_skill("parry", 290);
    set_skill("cuff", 290);
    set_skill("xuwu-piaomiao", 290);
    set_skill("hand", 290);
    set_skill("huanmo-longtianwu", 290);
    set_skill("literate", 120);

    map_skill("force", "riyue-guanghua");
    map_skill("sword", "pixie-jian");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("hand", "huanmo-longtianwu");

    prepare_skill("cuff", "xuwu-piaomiao");
    prepare_skill("hand", "huanmo-longtianwu");

    create_family("�������", 2, "����");

    set("no_teach", ([
        "pixie-jian" : "��а����ֻ�ܿ��Լ��ж����������䡷�����մ���С�ɣ����Ի�ָ�����㡣",
    ]));


    setup();
    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if((string)ob->query("family/master_name") == "������")
     {
          command("say ��Խ����Խ��˳�ۣ�����ҹ���");
          return;
     }

     if((int)ob->query("combat_exp") < 250000)
     {
          command("say �������΢ĩ���򣬻����ȸ������¸����϶������ɣ�");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
          return;
     }

     command("xixi");
     command("recruit " + ob->query("id")); 
     command("say �ã��ã���������������˲ű�����һͳ������ָ�տɴ���");
     ob->set("title", HIR "������̴󻤷�" NOR);
}

string ask_book()
{
     mapping fam;
     object me, ob;

     me = this_player();
     if (me->query("family/family_name") != query("family/family_name"))
            return "�����" + RANK_D->query_rude(this_player()) +
                   "���������������к�ͼı��";

     if (me->query("family/master_id") != query("id"))
            return "���ַ����״����ӣ�����������ʲô��";

     if (me->query_skill("riyue-guanghua", 1) < 100)
            return "������¹⻪ѧ�û������ң�óȻ�������䣬�к����档";

     if (query("kuihua_count") < 1)
            return "�������ˣ��������Ѿ����ȥ�ˡ�";

     add("kuihua_count", -1);
     ob = new("/clone/book/kuihua");
     ob->move(me);
     return "�Ȿ�������Ҫ�պã�Ū�������������ʡ�";
}

void reset()
{
     set("kuihua_count", 1);
}

mixed ask_pfm()
{
     object me = this_player();

     if (me->query("can_perform/pixie-jian/ying"))
           return "����ָ�����㣬������ʲô���Լ�������ȥ��";

     if (me->query("family/family_name") != query("family/family_name"))
           return "�����书�������֣���λ" + RANK_D->query_respect(me) +
                  "��Ȼ��ѧ�������������������Σ�";

     if (me->query_skill("pixie-jian", 1) < 90)
           return "���������书���������һ�붼û���꣬����ʲô��������ù�ȥ��";

     if (me->query_skill("pixie-jian", 1) < 200)
           return "��ı�а������Ƿ����ٶ�ȥ����һ�±��䣡";

     message_vision(HIC "$n" HIC "��$N" HIC "���˵�ͷ�����ܺã���������һ�У�����ϸ�ˡ���\n" HIR
                    "ֻ��$n" HIR "����΢�Σ���ʱ������Ӱ��$N" HIR
                    "ֻ��������Ӱ�����Ʈ��������������������ȫ��һ���ʹ��\n" NOR,
                    me, this_object());
     command("say ������û�У���"NOR);
     tell_object(me, HIW "��ѧ���ˡ���Ӱ����һ�С�\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     me->set("can_perform/pixie-jian/ying", 1);
     return 1;
}

