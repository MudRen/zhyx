// killer.c
// by doing

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("ɱ��", ({ "killer", "sha shou" }) );
	set("gender", "����" );
	set("age", 20 + random(20));

	set("long",
	        "����һ�����ĸߴ�Ľ����ˣ����۴�׳������"
                "��Բ���������ƺ��������⡣\n"
        );

	set("str", 25);
	set("con", 25);
	set("dex", 25);
	set("int", 25);

	set("combat_exp", 150000);
	set("attitude", "heroism");
	set("chat_chance_combat", 15);
	set("chat_msg_combat", ({
		"ɱ������������̵ģ��Һ��Ҷ�����֪��������ôд��ô��\n",
		"ɱ�ֺȵ�����ѱ��ｻ������������������С����\n",
		"ɱ�ֺǺǴ�Ц���������������ң������ǵ�ù�ˣ�\n"
	}) );

	set_skill("blade", 100 + random(200));
	set_skill("dodge", 100 + random(200));
	set_skill("feiyan-zoubi", 100 + random(200));
	set_skill("unarmed", 100 + random(200));
	set_skill("parry", 100 + random(200));
        set_skill("wuhu-duanmendao", 100 + random(200));
        set_skill("feiyan-zoubi", 100 + random(200));

        map_skill("dodge", "feiyan-zoubi");
        map_skill("blade", "wuhu-duanmendao");
        map_skill("parry", "wuhu-duanmendao");

        set_temp("apply/damage", 25);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);

	setup();

	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/cloth/cloth")->wear();

        call_out("do_flee", 60);
}

void do_flee()
{
        if (! living(this_object()) || is_fighting())
                call_out("do_flee", 60);

        if (environment())
                message_vision("$N���������Ŀ���һ��������������ˡ�\n",
                               this_object());

        destruct(this_object());
}

void unconcious()
{
        message_vision(HIR "$N" HIR "����������ô����������ϵ��׻�"
                       "���б��Һݵģ���\n" NOR, this_object());
        ::unconcious();
}