#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("����", ({ "kou zhong", "kou", "zhong"}));
        set("long", "һ���������۵Ŀ������꣬��������˧����ͳ˧���١�\n"); 
        set("nickname", HIR "����˫��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("per", 100);

        set("max_qi", 50000);
        set("max_jing", 40000);
        set("max_neili", 55000);
        set("neili", 55000);
        set("jiali", 250);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "blade.bafa" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 850);
        set_skill("parry", 850);
        set_skill("hand", 850);
        set_skill("unarmed", 850);
        set_skill("shou-yin", 850);
        set_skill("wudu-shu", 850);
        set_skill("force", 850);
        set_skill("changsheng-jue", 850);
        set_skill("blade", 850);
        set_skill("jingzhong-bafa", 850);
        set_skill("literate", 100);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "jingzhong-bafa");
        map_skill("dodge", "wudu-shu");
        map_skill("parry", "jingzhong-bafa");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");

        prepare_skill("hand", "shou-yin");

        setup();

        carry_object(__DIR__"obj/cloth2")->wear();
        carry_object(__DIR__"obj/jingzhongyue")->wield();
     //   carry_object("/kungfu/class/sky/obj/heshibi");
    //    carry_object("/kungfu/class/sky/obj/jue");
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard = present ("xu ziling", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard && !guard->is_fighting())
         {
                 message_vision (CYN "$N��ŭ������������̫������������飡\n" NOR, guard);
                 guard->kill_ob(ob);
         }
}

