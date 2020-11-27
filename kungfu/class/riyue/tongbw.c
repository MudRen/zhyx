//tongbw.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

string ask_zijinchui();
string ask_zijinchuifa();

void create()
{
        set_name("ͯ����", ({ "tongbai xiong","xiong"}) );
        set("gender", "����" );
        set("age", 75);
        set("title", "������̷����ó���");
        set("long", "���׷���ɢ, �������, ���ϵļ���ǣ��, \n"
                    "Բ��˫��, ���ϵ���Ѫ��Ȼ����, �������ǿɲ���\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        set("combat_exp", 350000);
        set("score", 30000);

        set_skill("force", 130);
        set_skill("riyue-xinfa", 130);
        set_skill("dodge", 130);
        set_skill("piaomiao-shenfa", 130);
        set_skill("hand", 130);
        set_skill("huanmo-longtianwu", 130);
        set_skill("cuff", 130);
        set_skill("xuwu-piaomiao", 130);
        set_skill("parry", 130);
        set_skill("literate", 80);
        set_skill("sword", 130);
        set_skill("riyue-jian", 130);
        set_skill("blade", 150);
        set_skill("tianmo-dao", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "tianmo-dao");
        map_skill("blade", "tianmo-dao");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("�������",2,"���� �����ó���");

        set("chat_chance", 2);
        set("chat_msg", ({
            "ͯ����ŭ��˫�۵�: ����û��, ��û���ѽ�! �����ֵ��㲻��ԩ����ѽ! ��\n",
            "ͯ����̾��һ����˵�����ҺͶ����ֵܳ�������, �������ѵ�ʱ��, ���ǻ�û��������!��\n"
        }));

        set("inquiry",([
            "�Ͻ�"   : (: ask_zijinchui :),
            "�Ͻ𴸷�" : (: ask_zijinchuifa :),
            "�ؼ�"     : (: ask_zijinchuifa :),
        ]));
        set("zijin_book", 1);

        setup();
        carry_object("/d/heimuya/npc/obj/zijinchui");
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
        carry_object("/d/heimuya/npc/obj/card1");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 80)
    {
         command("say ����ڹ��ķ���Ƿ��򣬶�����ȥ�ɣ�");
         return;
    }

    command("recruit " + ob->query("id"));
    ob->set("title", HIM "�������" HIY "�����ý���" NOR);
}

string ask_zijinchui()
{
    this_player()->set_temp("zijin_chuifa", 1);
    message_vision("ͯ����̾�˿�����˵����������Ͻ��ǵ���һλ"
                   "����ǰ���͸��ҵġ���\n", this_object());
    return "����ֻ��ϧ��δ�ܽ��������ɡ�";
}

string ask_zijinchuifa()
{
    object ob = new("/clone/book/zijin_book");
    object me = this_player();
    string msg;

    if (me->query_temp("zijin_chuifa") && !me->query("couple") &&
        me->query("combat_exp") > 10000)
    {
        if (query("zijin_book"))
        {
            message_vision("ͯ����̾�˿�����˵��������ϰ���Ͻ𴸷����꣬�Բ���"
                           "�������Ҫ�죬ֻϰ��ʮ֮һ������\n", me);
            msg = "��λ" + RANK_D->query_respect(me) + "������һ����ʣ���" +
                  "�����Ҿ�����ɣ�ϣ�������������о�Ҫ��";
            ob->move(this_object());
            set("zijin_book", 0);
            command("give zijin_book to " + me->query("id"));
        }
        else   msg = "�������ˣ����Ͻ𴸷���һ���������ˡ�";

        me->delete_temp("zijin_chuifa");
        return msg;
    }
    else
        return "�Ͻ𴸷���ֻ����Ե֮�ˣ���ϧ�㲻̫�ʺϡ�";
}

void reset()
{
    set("zijin_book", 1);
}

