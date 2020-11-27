// wuliuqi.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
int ask_weiwang();

void create()
{
	set_name("������", ({"wu liuqi", "wu","liuqi"}));
	set("title", HIR"��ػ��˳��"NOR"����");
	set("nickname", "��ؤ");
	set("gender", "����");
	set("age", 50);
	set("long", 
		"����Ͻл����������������ġ���ؤ�������棬�����������\n"
		"���ڹپӹ㶫�ᶽ֮ʱ������һʡ�ر������˲���諵�Ȱ����\n"
		"�Ĵ淴�帴��֮־��������ػᣬ��ְ��˳��������\n"
	);

	set("attitude", "peaceful");
	
	set("str", 24);
	set("int", 20);
	set("con", 24);
	set("dex", 20);

	set("qi", 1500);
	set("max_qi", 1500);
	set("jing", 100);
	set("max_jing", 100);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 100);
	
	set("combat_exp", 150000);
	set("score", 30000);
	
	set_skill("force", 95);
	set_skill("huntian-qigong", 90);
	set_skill("unarmed", 90);
	set_skill("changquan", 85);
	set_skill("dodge", 90);
	set_skill("xiaoyaoyou", 95);
	set_skill("feiyan-zoubi", 85);
	set_skill("begging", 50);
	set_skill("checking", 50);
	
	map_skill("force", "huntian-qigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "changquan");
	set("chat_chance", 3);
	set("chat_msg", ({
	"�������Ȼ�ſ������������������߽��ߣ���ǻ�ߺ���˭�ԣ���������\n"
	"���������������ζ������¸����̡������Դ��У�������Զ��\n",
	"������˵: ������������Ҫ�������ߴ��кô�����\n",
        "������ͻȻ˵��: �ɰض�֦�����ң��нں黪����ͤ��\n",
        "������ͻȻ˵��: ������ǰ����Ը�����帴���Һ�Ӣ��\n",
	}));
        set("inquiry", ([
		"�½���" :  "\n����ܶ����ɲ����װ���\n",
		"��ػ�" :  "\nֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��\n",
		"���" :  "\nֻҪ��������ػᣬ��������и�λ����ѧ�书��\n",
                "���帴��" : "ȥҩ�̺͹ײĵ���ϸ���ưɣ�\n",
                "����" :  (: ask_weiwang :),
                "��������" : (: ask_weiwang :),
	]) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

int ask_weiwang()
{
command("tell "+this_player()->query("id")+" �����ڵĽ��������� " +(string)(this_player()->query("weiwang")));
say("\n������˵�����������ֵ�ܸߣ���Щ�˼����㲻������ɱ�㣬��������书�����㱦����\n"
+"�����㻹���Լ����ᣬ�������ȥ����Ŀ�꣬����ȥǮׯȡǮҲ������Ϣ ����������\n");
say("\n��������˵��ɱĳЩ���˻��ĳЩ���˿�����߽���������\n");
return 1;
}

void init()
{
	::init();
	add_action("do_skills","skills");
	add_action("do_skills","cha");
	add_action("do_join","join");
}

#include "/kungfu/class/yunlong/tiandihui.h";
