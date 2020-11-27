// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("�Ϻ�����", ({ "monster dragon", "dragon", "nanhai ejiao" }) );
	set("title", HIC "����" NOR);
	set("gender", "����");
	set("age", 23);
	set("long", @LONG
����һ���������ڵĶ��ԣ����������������ɫ��������顣
LONG );
	set("combat_exp", 10000000);
        set("shen_type", 0);
	set("attitude", "heroism");
        set("max_neili", 50000);
        set("neili", 50000);
        set("max_jing", 30000);
        set("jing", 30000);
        set("max_qi", 45000);
        set("qi", 45000);
        set("jingli", 40000);
        set("max_jingli", 40000);

	set("chat_chance_combat", 150);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );

        set("str", 100);
        set("int", 30);
        set("con", 100);
        set("dex", 100);

	set_skill("unarmed", 1200);
	set_skill("sword", 1200);
	set_skill("parry", 1200);
	set_skill("dodge", 1200);
	set_skill("force", 1200);
	set_skill("huntian-baojian", 600);
	set_skill("tianluo-diwang", 1000);
	map_skill("force", "huntian-baojian");
	map_skill("unarmed", "huntian-baojian");
	map_skill("parry", "tianluo-diwang");

	prepare_skill("unarmed", "huntian-baojian");

        set("jiali", 200);

        set_temp("apply/attack", 300);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

	setup();
}

void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;

        message_vision(HIW "$N" HIW "���һ��������������ʢ��"
                       "����������\n" NOR, this_object(), ob);

        ::fight_ob(ob);
	if (! is_killing(ob->query("id")))
        	kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N΢һҡͷ����һ��β��ɨ��������\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 500 + random(200), me);
        me->set("neili", me->query("max_neili"));
        return HIY "$N" HIY "��Χ�������ƣ��⻪���䣬��ʱ��$n"
               HIY "�Ի��ѣ������԰Ρ�\n" NOR;
}

void unconcious()
{
        die();
}

void die()
{
	object ob;
	string gift;
	string *ob_list = ({
		"/clone/suit/xuanwu/armor",
		"/clone/suit/xuanwu/head",
		"/clone/suit/xuanwu/hufu",
		"/clone/suit/xuanwu/pifeng",
		"/clone/suit/xuanwu/shoe",
		"/clone/money/coin",
		"/clone/money/silver",
		"/clone/money/gold",
		"/clone/money/cash",
		"/clone/gift/ccrystal",
	});
	gift = ob_list[random(sizeof(ob_list))];
	ob = new(gift);
        command("chat ��ѽ�����ã�������γ�ʦ���������һ��Ϻ������ϼ�����˵��");
        message_sort(HIR "$N" HIR "����һŤ����ʧ�������У�"
                     "ֻ���������һ������$N" HIR "���ϵ�����һ" +
                     ob->query("unit") + ob->name() +
                     HIR "��\n" NOR, this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
	if (time() - query("born_time") > 1800)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + name() + HIM "��ң������Ϊ���˼�����"
                        "���ŷ����Ϻ������ձ���ݱ����" NOR);
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}
