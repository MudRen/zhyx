#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"



void create()
{
        set_name("���س���", ({ "shenmi zhanglao", "zhanglao" }));
        set("long", @LONG
һλ���ص�ؤ�ﳤ�ϣ�û����֪������������
LONG);

        set("title", "ؤ��Ŵ�����");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 40000);
        set("max_jing", 30000);
        set("neili", 43000);
        set("max_neili", 43000);
        set("jiali", 1800);
        set("combat_exp", 22000000);
        set("score", 30000000);
        set("shen_type", 1);
        
        set_skill("force", 600);
		set_skill("huimeng-xinfa", 600);
        set_skill("dodge", 600);
        set_skill("feiyan-zoubi", 600);
        set_skill("unarmed", 600);
        set_skill("nap-unarmed", 600);     
        set_skill("parry", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "huimeng-xinfa");
        map_skill("unarmed", "nap-unarmed");
        map_skill("parry", "nap-unarmed");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("unarmed", "nap-unarmed");

        create_family("ؤ��", 18, "����");


        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 500);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 500);

        setup();
        carry_object("/d/gaibang/npc/obj/cloth")->wear();

}

void attempt_apprentice(object ob)
{
        string title = ob->query("title");
        int lvl = ob->query("family/beggarlvl");

        if (! permit_recruit(ob))
                return;

        if (ob->query("combat_exp") < 1000000)
        {
                command("say ��Ľ������鲻����������������ʦ��ѧϰ�ɡ�");
                return;
        }

        if (ob->query("shen") < 20000)
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }

        if (ob->query("family/beggarlvl") < 9)
        {
                command("say ���ڱ���ĵ�λ̫�ͣ�������������ʦ��ѧϰ�ɡ�");
                return;
        }


        command("nod");
        command("say �ұ������㣬ϣ���պ�Ŭ���Ͻ�����������Ϊ��");
        command("recruit " + ob->query("id"));

        if (ob->query("class") != "beggar")
                ob->set("class", "beggar");

        if (lvl > 0)
        {
                ob->set("family/beggarlvl", lvl);
                ob->set("title", title);
        }
}
