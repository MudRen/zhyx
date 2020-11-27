// guard.c by yuchang
#include <ansi.h>

inherit NPC;

void create()
{
        string *colors = ({ "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"});
        string color;

        color = colors[random(sizeof(colors))];
        set_name("����"+color, ({ "guarder" }));
        set("gender", "����");
        set("title", HIC "����ɽׯ��ʿ" NOR);
        set("age", 38);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 20);
        set("str", 45);
        set("int", 45);
        set("con", 45);
        set("dex", 45);
        
        set("max_qi", 5500);
        set("max_jing", 2000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 20000000);
        set("score", 20000000);

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("literate", 400);
        set_skill("begging", 400);
        set_skill("checking", 400);
        set_skill("force", 400);
        set_skill("dodge", 400);
        set_skill("unarmed", 400);
        set_skill("parry", 400);
        set_skill("strike", 400);
        set_skill("sword", 400);
        set_skill("feiyan-zoubi", 400);
        set_skill("huntian-qigong", 400);
        set_skill("kuangfeng-jian", 400);
        set_skill("dragon-strike", 400);

        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("parry", "kuangfeng-jian");
        map_skill("sword", "kuangfeng-jian");

        prepare_skill("strike", "dragon-strike");

        setup();
        carry_object("/d/ajszhuang/npc/obj/female2-cloth")->wear();
}
void init()
{
        object me,ob;

        if (interactive(me = this_player()))
        {       
                
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, me);
               
        }
        ::init();
}





