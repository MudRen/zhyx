#include <ansi.h>
inherit NPC;
int ask_me();
//#include "/clone/guard/party.h"
void create()
{
    set_name("无名居士", ({"noname", "man"}));
    set("title", HIW "一代宗师" NOR);
    set("long",
        "他就是无名居士，没有人知道他的来历。\n"
        "如果你想收集神书，你可以问问他(book)和(shi).\n");
    set("age", 57);
    set("class", "beggar");
    set("attitude", "friendly");
    set("shen_type", 1);
    set("str", 700);
    set("int", 40);
    set("con", 40);
    set("dex", 700);
    set("no_kill", 1);
    set("qi", 99999999);
    set("jing", 99999999);
    set("eff_qi", 99999999);
    set("eff_jing", 99999999);
    set("max_qi", 99999999);
    set("max_jing", 99999999);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 0);
    set("combat_exp", 25000000);
    set("score", 50000);
    set_skill("strike", 200);
    set_skill("unarmed", 200);
    set_skill("dodge", 200);
    set_skill("force", 200);
    set_skill("parry", 210);
    set_skill("literate", 200);
    //	set_skill("canzhi-duanhun",300);
    //     map_skill("unarmed", "canzhi-duanhun");
    //     map_skill("parry", "canzhi-duanhun");

    set("inquiry", ([
        "book":"神书共有四十二本，你可以用help tasks获得有关方面知识！",
        "shi":"只有靠" HIR "七" + HIC + "彩" + HIY + "向" + HIM + "导" + HIG + "石" NOR + CYN "才能找到神书，灵石二十两一块！",
        "mengzhu":(: ask_me :),
        // "任务":(: ask_job :),
        // "job":(: ask_job :),
    ]));
    setup();
}
void init()
{
    add_action("do_answer", "answer");
}
int accept_object(object me, object ob)
{
    object shi;
    if (ob->query("money_id") && ob->value() >= 2000)
    {
        if (!present("xdshi", me))
        {
            shi = new ("/clone/misc/findbook");
            command("say 好吧," + me->query("name") + "既然给了钱，我就给你一块！\n");
            shi->move(me);
            message_vision("$N将一块" HIR "七" + HIC + "彩" + HIY + "向" + HIM + "导" + HIG + "石" NOR "交给了$n。\n", this_object(), me);
        }
        else
            command("say 你不是有了一块嘛，还想要？钱我没收！\n");
        return 1;
    }

    command("say 谢谢，但我不要这东西！");
    return 0;
}
int ask_me()
{
    if (this_player()->query("combat_exp") < 1500000)
        tell_object(this_player(), "无名居士说道：你经验太低，想要做盟主，必死无疑！\n");
    else
    {
        tell_object(this_player(), "无名居士说道： 好吧，里面危险重重，千万别乱来，否则有生命危险。自己小心吧！\n");
        this_player()->move("/d/biwu/hole");
    }
    return 1;
}
void unconcious()
{
    reincarnate();
    set("eff_qi", query("max_qi"));
    set("qi", query("max_qi"));
    set("eff_jing", query("max_jing"));
    set("jing", query("max_jing"));
    set("jingli", query("eff_jingli"));
    say("无名居士笑着说：动武对我没有用！\n");
    command("hehe");
}

void die()
{
    unconcious();
}
