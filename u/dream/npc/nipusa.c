#include <ansi.h>
inherit NPC;

int ask_fengyun();
mixed ask_cancel();

void create()
{
        set_name("������", ({"ni pusa", "ni", "pusa"}));
        set("title", HIR "������" NOR);
        set("long", "�������������������ӡ�"
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

        command( "chat " HIW "�������ǳ�����,һ�����Ʊ㻯�� \n"NOR ,);



         return 1;

}





