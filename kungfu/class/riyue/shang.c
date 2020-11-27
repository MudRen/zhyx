//shang.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("ɣ����", ({ "sang sanniang", "sang", "sanniang"}) );
        set("gender", "Ů��" );
        set("age", 45);
        set("title", "������������ó���");
        set("long", "����Ź֣�����˿��΢Ц������ȴ�൱���㡣 \n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 24);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 29);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("combat_exp", 350000);
        set("score", 30000);
        set("jiali", 200);

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
        set_skill("throwing", 150);
        set_skill("xinghui-canlan", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "riyue-jian");
        map_skill("throwing", "xinghui-canlan");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("�������",2,"���� �����ó���");

        setup();
        carry_object("/d/heimuya/npc/obj/changjian")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
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
    ob->set("title", HIM "�������" HIG "�����ý���" NOR);
}

