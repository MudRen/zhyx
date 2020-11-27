// beihai.c

#include <ansi.h>

inherit NPC;

void random_move();
void random_attack();

void create()
{
	set_name("����˹", ({ "ha disi", "ha" }));
	set("title", HIR "ڤ��" NOR);
	set("gender", "����");
	set("age", 3000);
	set("long", @LONG
�����ԩ�껷�ƣ��ƻ����棬ԶԶ��ȥ���˲������ڡ�
LONG );
	set("combat_exp", 2000000000);
	set("score", 10000000);
        set("shen_type", 0);
	set("attitude", "friendly");
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 5000000);
        set("qi", 5000000);

        set("str", 400);
        set("int", 400);
        set("con", 400);
        set("dex", 400);set("chat_chance_combat", 150);
 
set("chat_msg_combat", ({
                (: perform_action, "finger.zongheng" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
	set_skill("finger", 4000);
	set_skill("parry", 4000);
	set_skill("freezing-force", 4000);
	set_skill("liumai-shenjian", 4000);
        set_skill("zhuangzi-wu", 4000);		
        set_skill("dodge", 4000);
	set_skill("force", 4000);	
        set_skill("qiankun-danuoyi", 4000);

        map_skill("finger", "liumai-shenjian");
	map_skill("force", "freezing-force");
 	map_skill("dodge", "zhuangzi-wu");
 	map_skill("parry", "qiankun-danuoyi");
        prepare_skill("finger", "liumai-shenjian");
                set("jiali", 5000);

        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 150);
                set("chat_msg", ({ (: random_move :) }));
		set("chat_chance_combat", 120);
		set("chat_msg_combat", ({ (: random_attack :) }));
                set("born_time", time());
                keep_heart_beat();
        }

	setup();
}



void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;

        message_vision(HIC "$N" HIC "һ����Х������"
                       "��ʱԩ�����衣\n" NOR, this_object(), ob);

        ::fight_ob(ob);
	if (! is_killing(ob->query("id")))
        	kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N�ƺ�û������$n��˵ʲô��\n",
                       this_object(), ob);
        return 0;
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
        ob->receive_wound("qi", 1000 + random(500), me);
        me->set("neili", me->query("max_neili"));
        return HIC "$N" HIC "���١���һ������һ�ں�������ʱ��$n"
               HIC "������⡣\n" NOR;
}
void unconcious()
{
        die();
}

void die()
{
        string *ob_list = ({
                "/clone/fam/max/derive-emblem",
                "/clone/fam/max/hupo",
                "/clone/fam/max/noname",
                "/clone/fam/max/shihun",
                "/clone/fam/max/taixu",
                "/clone/fam/max/xuanyu",
        });
        object ob;

        ob = new(ob_list[random(sizeof(ob_list))]);

        command("chat �����ܣ�������ڤ����Ȼ���ڷ������"
		"���ǻ�Ϊ�˸������ۣ�");
        message_sort(HIG "$N" HIG "Ĭ��䣬��Ȼ����յ�����������ֻ"
		     "������ǰ��Ȼ����ԩ����Ʈ�裬�ۼ��Ź���˹�������ȥ��\n" NOR,
		     this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
	if (time() - query("born_time") > 7200)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + name() + HIM "����˹���⣬����ڤ��ȥ�ˡ�" NOR);
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

void random_attack()
{
	object ob;

	set("qi", query("eff_qi"));
	set("jing", query("eff_jing"));
	if (query("qi") < query("max_qi") * 3 / 5 ||
	    query("jing") < query("max_jing") * 3 / 5)
	{
		if (query_temp("recover_times") >= 3)
		{
			die();
			return;
		}

		message_combatd(HIR "$N" HIR "˲��ֻ����������飬�漴��Щ���������º϶�Ϊһ������˹�õ���ȫ��Ļָ���\n" NOR,
				this_object());
		add_temp("recover_times", 1);
		set("eff_qi", query("max_qi"));
		set("qi", query("max_qi"));
		set("eff_jing", query("max_jing"));
		set("jing", query("max_jing"));
		return;
	}

	clean_up_enemy();
	ob = select_opponent();
	if (! objectp(ob))
		return;
    
        switch (random(10))
	{
	case 0:
		message_combatd(HIY "$NͻȻ����һ����Х��������Ŀ���������飬"
			        "˲���$N����ӿ�����Ƴ�ˮ������ǵ�\n"
			        "������裡\n" NOR,
			        this_object());
		set_temp("apply/name", ({ "����" }));
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		delete_temp("apply/name");
		break;

	case 1:
		message_combatd(HIY "$N" HIY "��Цһ�������������һ̧"
				"��ʱ�����ܲ���һ��������$n" HIY "ֱ����ȥ��\nֻ��$n"
		                "��ʱ���������У�����ð�����ƺ��̣�\n" NOR,
				this_object(), ob);
		ob->receive_damage("qi", 20000 + random(50000), this_object());
		ob->receive_wound("qi", 10000 + random(40000), this_object());
		ob->interrupt_busy(ob, 20 + random(20));
		break;

	case 2:
		if (ob->is_busy())
			break;
		message_combatd(HIY "$N" HIY "��$n" HIY "�ݺݵ���һ�ۣ�"
				"$n" HIY "�ƺ���ʱ��������������������һ�㣬�����ʬ����һ�㣡\n" NOR,
				this_object(), ob);
		ob->start_busy(20 + random(20));
		break;
	}
}


