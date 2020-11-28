#include <ansi.h>
inherit NPC;
inherit F_HEIDIAN_HUOJI;

void create()
{
        set_name("���", ({"huoji"}));
        set("gender", "����");
        set("age", random(10) + 20);
        set("str", 25);
        set("con", 25);
        set("spi", 25);
        set("dex", 25);
        set("int", 25);
        set("long", "���Ǻڵ�Ļ�ơ�\n");
        set("combat_exp", 1000000);
        set("class", "fighter");
        set("attitude", "herosim");
        set_skill("unarmed", 200);
        set_skill("force", 200);
        set_skill("sword", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set("max_qi", 1200);
        set("max_jing", 1200);
        set("max_neili", 2000);
        set("neili", 2000);
        set("jiali", 150);
        set("max_jingli", 2000);
        set("jingli", 2000);
        set("shop_id", "chengdu");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        restore();
}

void init()
{
        if (this_player()->query("id") == query("owner"))
        {
                add_action("do_stock", "stock");
                add_action("do_value", "value");
                add_action("do_unstock", "unstock");
                add_action("do_jiezhang", "jiezhang");
                add_action("do_modify", "modify");
                add_action("do_vip", "vip");
                add_action("do_unwelcome", "unwelcome");
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void die()
{
        return;
}

void unconcious()
{
        die();
}
