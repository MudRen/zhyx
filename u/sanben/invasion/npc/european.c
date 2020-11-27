// european.c ŷ��������

#include <ansi.h>

inherit __DIR__"invader";

void create()
{
        set_name("������", ({ "european" }));
        set("long", "һ�������ˡ�\n");
        set("gender", "����");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);
        set("shen", -1000);

        set("combat_exp", 3000000);
        set("scale", 100);

        set_skill("force", 1);
        set_skill("xiyang-neigong", 1);
        set_skill("dodge", 1);
        set_skill("xiyang-boji", 1);
        set_skill("parry", 1);
        set_skill("european-gun", 1);
        set_skill("hammer", 1);

        map_skill("hammer", "european-gun");
        map_skill("force", "xiyang-neigong");
        map_skill("dodge", "xiyang-boji");
        map_skill("parry", "european-gun");

        set("rank_info/rude", "��ë��");
        set("chat_chance", 10);
        set("chat_msg", ({ (: do_leave :) }));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "hammer.she" :),
        }));        

        setup();
        if (clonep()) keep_heart_beat();
        set("born_time", time());

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/u/xiner/obj/gun")->wield();
}