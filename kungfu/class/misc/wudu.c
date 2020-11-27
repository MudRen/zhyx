// wudu.c �����
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("�����", ({ "lan fenghuang", "lan" }));
	set("long",  "��������ӡ�׻����㣬Χһ���廨Χȹ��ɫ�ʲ��ã���̻Իͣ�\n���ϴ�һ�Լ���Ļƽ���������оƱ��ڴ�С��\n");
	set("gender", "Ů��");
	set("age", 20);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 37);
	set("int", 32);
	set("con", 35);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", -10000);

        set_skill("force", 560);
        set_skill("xiuluo-yinshagong", 560);
        set_skill("dodge", 540);
        set_skill("jinshe-youshenbu", 540);
        set_skill("hand", 540);
        set_skill("qianzhu-wandushou", 540);
        set_skill("parry", 540);
        set_skill("throwing", 540);
        set_skill("hansha-sheying", 540);
        set_skill("literate", 520);
        set_skill("poison", 300);
        set_skill("wudu-qishu", 300 );
        set_skill("martial-cognize", 540);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "jinshe-youshenbu");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("hand", "qianzhu-wandushou");

        create_family("�嶾��", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.wan" :),
                (: perform_action, "hand.zhugu" :),
                (: exert_function, "recover" :),
        }) );


	setup();
	carry_object("/clone/misc/cloth")->wear();
}
