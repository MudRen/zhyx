// huoji. 

inherit NPC;
#include <ansi.h>
inherit F_DEALER;

void create()
{
	set_name("���", ({ "qing er", "qing" }));
	set("title", HIM"��ɪ����"NOR);
	set("nickname",HIR"����纽�"NOR);
	set("shen_type", 1);

	set("str", 30);
	set("gender", "Ů��");
	set("age", 17);
 	set("per", 30);
	set("long",
"һ����פ������������С�����һЩϡ
���Ķ���������Ź֣���˵������Ե��\n"
);
	set("combat_exp", 2500);
	set("attitude", "friendly");
	set("chat_chance", 1);
	set("chat_msg", ({
		"���Ц���е�˵����������Ե���������������Ķ����ɣ���\n",
	}));

	set("vendor_goods", ({
		__DIR__"obj/yuelao-xianshui.c",
		__DIR__"obj/sansheng-youyue.c",
		__DIR__"obj/ruyi-su.c",
		__DIR__"obj/tongxin-jie.c",
		__DIR__"obj/xuannv-lingfu.c",
		__DIR__"obj/huangtong-suo.c",
	}));

	setup();
	carry_object(__DIR__"obj/sahua-qun.c")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
