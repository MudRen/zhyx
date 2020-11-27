// hongri.c ���շ���

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("���շ���", ({ "hongri fawang", "fawang" }));
        set("long",  "������ȥ��һ����ɮ����ǰ����һ������̫����\n");
        set("gender", "����");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 33);
        set("int", 36);
        set("con", 34);
        set("dex", 33);
        
        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 7500);
        set("max_neili", 7500);
        set("jiali", 150);
        set("combat_exp", 25000000);
        set("score", 10000000);

        set_skill("lamaism", 520);
        set_skill("literate", 80);
        set_skill("force", 530);
        set_skill("parry", 520);
        set_skill("blade", 525);
        set_skill("xue-dao", 525);
        set_skill("sword", 480);
        set_skill("mingwang-jian", 480);
        set_skill("dodge", 510);
        set_skill("mizong-neigong", 530);
        set_skill("xuehai-mogong", 530);
        set_skill("shenkong-xing", 510);
        set_skill("hand", 500);
        set_skill("dashou-yin", 500);
        set_skill("cuff", 500);
        set_skill("yujiamu-quan", 500);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("Ѫ����", 0, "����");
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.xueyu" :),
                (: perform_action, "hand.jingang" :),
                (: perform_action, "cuff.chen" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/clone/weapon/jiedao")->wield();
}
