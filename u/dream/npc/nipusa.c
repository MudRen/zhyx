#include <ansi.h>
inherit NPC;

int ask_fengyun();
mixed ask_cancel();

void create()
{
        set_name("泥菩萨", ({"ni pusa", "ni", "pusa"}));
        set("title", HIR "神算子" NOR);
        set("long", "他是天下闻名的神算子。"
        );
        set("attitude", "heroism");
        set("class", "eunach");

        set("age", 60);
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 100);
        set("combat_exp", 1500000);
        set("score", 100);
        set("apply/attack",  100);
        set("apply/defense", 100);

        set_skill("force", 800);
        set_skill("unarmed", 800);
        set_skill("sword", 800);
        set_skill("dodge", 800);
        set_skill("parry", 800);
    set("inquiry", ([
                  "fengyun": (: ask_fengyun :),
        ]));
        setup();

}

int ask_fengyun()
{       int mjia;
        object me;

        me = this_player();
        mjia = me->query("data/item/z/zippo-mjia");

        command( "chat " HIW "金麟岂是池中物,一遇风云便化龙 \n"NOR ,);



         return 1;

}





