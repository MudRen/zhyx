// gaoyanchao.c ���峬

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();

void create()
{
	set_name("���峬", ({ "gao yanchao", "gao", "yanchao" }));
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����");
	set("gender", "����");
	set("age", 32);
	set("str", 25);
	set("dex", 20);
	set("long", "��������ʮ��ͷ��ȴ�Ե��쳣������һ�Բ��������Ƕ�һվ��\n"
            "�����������ݡ�\n");
	set("combat_exp", 40000);
	set("score", 5000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("force", 70);
	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("club", 80);
	set_skill("parry", 70);
	set_skill("literate", 50);
	set_skill("hunyuan-yiqi", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("zui-gun", 70);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("club", "zui-gun");
	map_skill("parry", "zui-gun");

	set_temp("apply/attack", 25);
	set_temp("apply/defense", 25);
	set_temp("apply/armor", 5);
	set_temp("apply/damage", 25);
	set("qi", 400);
	set("max_qi", 400);
	set("jing", 300);
	set("max_jing", 300);
	set("neili", 250); 
	set("max_neili", 250);
	set("jiali", 35);
        set("inquiry", ([
		"�½���" :  "\n����ܶ����ɲ����װ���\n",
		"��ػ�" :  "\nֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��\n",
		"����" :  "\nֻҪ��������ػᣬ��ҾͿ���һ���ิ����\n",
		"���" :  "\nֻҪ��������ػᣬ��ҾͿ���һ���ิ����\n",
                "���帴��" : "ȥ�ײĵ�������ϸ���ưɣ�\n",
                "����" : "�����£�\n",
                "�п�" : "�����£�\n",
                "����" :  (: ask_weiwang :),
                "��������" : (: ask_weiwang :),
       	]));
	setup();
        carry_object("/d/shaolin/obj/qimeigun")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("gold", 1);
}

int ask_weiwang()
{
command("tell "+this_player()->query("id")+" �����ڵĽ��������� " +(string)(this_player()->query("weiwang")));
say("\n���峬˵�������������ֵ�ܸߣ���Щ�˼����㲻������ɱ�㣬��������书�����㱦����\n"
+"�����㻹���Լ����ᣬ�������ȥ����Ŀ�꣬����ȥǮׯȡǮҲ������Ϣ ����������\n");
say("���峬��˵��ɱĳЩ���˻��ĳЩ���˿�����߽���������\n");
return 1;
}

void init()
{
::init();
add_action("do_join","join");
}

#include "/kungfu/class/yunlong/tiandihui.h";
