// shusheng
// by ruri
inherit NPC;
#include <ansi.h>;
inherit F_DEALER;

void create()
{
	set_name("��������", ({ "yuexia shusheng","shusheng","sheng" }));
	set("str", 27);
	set("title", HIC"���Ƹ���"NOR);
	set("nickname", HIG"��÷����"NOR);
	set("shen_type", 1);
	set("gender", "����");
	set("age", 28);
	set("per", 28);
	set("long", "һ��üĿ������������������������˽�ǩ����Щ��ߡ�\n");
	set("combat_exp", 15000);
	set("attitude", "friendly");
	set("chat_chance", 1);
	set("chat_msg", ({
		"��������ҡͷ���Ե������������Գ���˼��Ե�Խ᲻�⣿ͬ�Ķ���ӣ����������ϡ���\n"
	}));

	set("inquiry", ([
		"��ǩ" : "��ʦ��ûд���أ���ȥ�ʽ�����С��Ƥ�ɣ�\n"
		]));

	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);

	setup();
	// carry_object(__DIR__"obj/baibu-qingshan.c")->wear();
}
