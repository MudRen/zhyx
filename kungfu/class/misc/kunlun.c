// kunlun.c
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("���ؽ���", ({ "kunlun jianxian", "kunlun" }));
	set("long",  "�������������صĽ��ɣ�ƮƮ���ɡ�\n");
	set("gender", "����");
	set("age", 85);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 32);
	set("int", 33);
	set("con", 32);
	set("dex", 31);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", 10000000);
		      
        set_skill("force", 580);
        set_skill("kunlun-xinfa", 580);
        set_skill("liangyi-shengong", 580);
        set_skill("dodge", 580);
        set_skill("chuanyun-bu", 580);
        set_skill("strike", 580);
        set_skill("kunlun-zhang", 580);
        set_skill("hand", 580);
        set_skill("sanyin-shou", 580);
        set_skill("cuff", 580);
        set_skill("zhentian-quan", 580);
        set_skill("parry", 580);
        set_skill("sword", 580);
        set_skill("daya-jian", 580);
        set_skill("throwing", 580);
        set_skill("kunlun-qifa", 580);
        set_skill("tanqin-jifa", 320);
        set_skill("jian-jia", 320);
        set_skill("qiuyue-lai", 320);
        set_skill("tieqin-yin", 300);
        set_skill("chess", 320);
        set_skill("literate", 280);
        set_skill("martial-cognize", 300);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "daya-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("strike", "kunlun-zhang");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "jian-jia");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("hand", "sanyin-shou");

        create_family("������", 0, "ǰ��");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
                (: perform_action, "sword.feng" :),
                (: perform_action, "sword.bugui" :),
                (: perform_action, "cuff.shi" :),
                (: perform_action, "hand.sun" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}
