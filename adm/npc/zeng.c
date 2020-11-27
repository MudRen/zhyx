// zeng.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;


string ask_job();
int ask_sew();
int ask_sew2();
int ask_sew3();

int working(object me);
int halt_working(object me);

void create()
{
	set_name("����", ({ "zeng rou", "zeng", "rou" }));
	set("gender", "Ů��");
	set("age", 16);
	set("per", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);
	set("str", 25);
	set("long",
"����Τ��ү��֪���ڼ�����С檣������￪�������̣���Щ��֪��
�������·�������˵�Ƕ���Τ��ү�ӹ���Ū�����Ľ�Ʒ������ô˵��
����������\n");
	set_skill("unarmed", 60);
	set_skill("changquan", 60);
	map_skill("unarmed", "changquan");
	set_temp("apply/damage", 15);

	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/d/city/npc/cloth/belt",
		"/d/city/npc/cloth/boots",
		"/d/city/npc/cloth/bu-shoes",
		"/d/city/npc/cloth/cloth",
		"/d/city/npc/cloth/color-dress",
		"/d/city/npc/cloth/fu-cloth",
		"/d/city/npc/cloth/gui-dress",
		"/d/city/npc/cloth/hat",
		"/d/city/npc/cloth/jade-belt",
		"/d/city/npc/cloth/liu-dress",
		"/d/city/npc/cloth/marry-dress",
		"/d/city/npc/cloth/mini-dress",
		"/d/city/npc/cloth/moon-dress",
		"/d/city/npc/cloth/pink-dress",
		"/d/city/npc/cloth/qi-dress",
		"/d/city/npc/cloth/red-dress",
		"/d/city/npc/cloth/scarf",
		"/d/city/npc/cloth/sha-dress",
		"/d/city/npc/cloth/shoes",
		"/d/city/npc/cloth/xian-cloth",
		"/d/city/npc/cloth/xiu-cloth",
		"/d/city/npc/cloth/xiu-scarf",
		"/d/city/npc/cloth/yan-dress",
		"/d/city/npc/cloth/zi-dress",
	}));
	
        set("inquiry", ([
            "����" : (: ask_job :),
            "job"  : (: ask_job :),
            "��������"  : (: ask_sew :),
            "Ů��"  : (: ask_sew2 :),
            "����Ϊ��"  : (: ask_sew3 :),
        ]));

	setup();
	carry_object("/d/city/npc/cloth/feature")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sew", "sew");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if (me->query_temp("job/sew"))
                return "���������·���Ū����ô��";

        if (me->query("gender") != "Ů��")
                return "��Ů���ӼҵĻ���Ҳ���ɣ�";

        if (me->query("combat_exp") < 50)
                return "������������ɻ��һ����е㲻���ġ�";

        if (me->query("combat_exp") > 15000)
                return "�������ã������ǿ���ʲô�õ��Լ�ѡ���ɣ������ɻ�Ҳ̫ί���ˣ�";

        if (me->query("qi") < 30)
                return "����ɫ��ô�������Ъ����ɡ�";

        if (me->query("jing") < 30)
                return "�㾫��ͷ���а�������ҵ�������̤�ˣ�";

        if (me->query_int() < 20)
                return "����...����ô���ֱ��ŵģ�Ҳ�����·���";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              $1->query_temp("job/sew") &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "�����Ѿ���" + obs[0]->name() + "�ڰ��������������ˡ�";

        me->set_temp("job/sew", 1);
        return "�ã���Ͱ�������÷�(sew)��С��ɣ������������������";
}

int ask_sew()
{
        object me;

        me = this_player();

	if (!me->query("mask/freequest/sew"))
        	tell_object(me, "��������㣺����ѧ�������㰡����Ů��һ��Ҫ�������С���\n");

	if (me->query("mask/freequest/sew") < 300 )
        	tell_object(me, "��������㣺�����Ů�컹��������Ŷ����\n");

	if (me->query("mask/freequest/sew") > 299 && me->query_skill("literate",1) < 200 )
        	tell_object(me, "��������㣺�����Ů���Ѿ��������ˣ���ȥѧ��֪ʶ�ɡ���\n");

	if (me->query("mask/freequest/sew") > 299 && me->query_skill("literate",1) > 199 )
		tell_object(me, "��������㣺�����Ů���Ѿ��������ˣ�֪ʶҲ���ˣ���Ҫ�������Ϊ�ֲ���Ŷ����\n");

        return 1;
}

int ask_sew2()
{
        object me;

        me = this_player();

	if (!me->query("mask/freequest/sew"))
	{
        	tell_object(me, "��������㣺���������߶�û������̸ʲôŮ��Ŷ����\n");
	} else
	{
        	tell_object(me, "��������㣺����������������"+chinese_number(me->query("mask/freequest/sew"))+"�η��һ������\n");	
	}

        return 1;
}

int ask_sew3()
{
        object me;

        me = this_player();
	command("laugh "+me->query("id"));
       	tell_object(me, "��������㣺����ȥ���С�����һЩ�����������Ϊ�����\n");
	command("comfort "+me->query("id"));

        return 1;
}

int do_sew(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if (! me->query_temp("job/sew"))
        {
                message_vision("$N͵͵������һ�����룬$nһ����߸����"
                               "����ҷ��£���ʲô����ģ�\n",
                               me, this_object());
                return 1;
        }

        me->set_temp("job/step", 1);
//	me->start_busy(bind((: call_other, __FILE__, "working" :), me));
	me->start_busy(bind((:call_other, __FILE__, "working" :), me),
                       bind((:call_other, __FILE__, "halt_working" :), me));

        tell_object(me, "�㿪ʼ���ҡ�\n");
        return 1;
}

int working(object me)
{
        string msg;
        int finish;
        int b;
	int quest_count;

        if (! me->query_temp("job/step"))
                me->set_temp("job/step", 1);

        if (! living(me))
        {
                me->delete_temp("job/sew");
                me->delete_temp("job/step");
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 1);
        me->receive_damage("qi", 2);
        switch (me->query_temp("job/step"))
        {
        case 1:
                msg = "$N����һ�����룬�������ߡ�";
                break;
        case 2:
                msg = "$Nչ�����ϣ��������ӱȻ��˰��졣";
                break;
        case 3:
                msg = "$N��������������ӣ����¼�����ӡ��";
                break;
        case 4:
        case 6:
                msg = "$Nר����־��һ��һ�ߵķ��ҡ�";
                break;
        case 5:
                msg = "$N��ü���˿����ӣ�������˼��";
        case 7:
                msg = "$N�ᶯ����ϸָ���������´����·���ģ�������ĳ����ˡ�";
                break;
        default:
                msg = "$N���·���ã�������ϣ����õݸ�$n��";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                msg += "$n����$N��������·�����ͷ���������е���˼��\n";
                me->delete_temp("job/sew");
                me->delete_temp("job/step");

                b = 5 + random(5);
                me->add("combat_exp", b);
                me->improve_potential((b + 2) / 3);

                ob = new("/clone/money/coin");
                ob->set_amount(60);
                ob->move(me, 1);
        }

	msg = replace_string(msg, "$N", "��");
	msg = replace_string(msg, "$n", name());
	tell_object(me, msg);

        if (finish)
        {
                if (b > 0)
                {
                        tell_object(me, HIC "\n������" +
                                    chinese_number(b) +
                                    "�㾭���" +
                                    chinese_number((b + 2) / 3) +
                                    "��Ǳ�ܡ�\n\n" NOR);

			if (!me->query("mask/freequest/sew"))
				quest_count = 1;
			else
				quest_count = me->query("mask/freequest/sew") + 1;
			me->set("mask/freequest/sew", quest_count);
                }
                return 0;
        }

        me->add_temp("job/step", 1);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N�����е�����һ�ӣ��ֹ�����"
                       "û���������ﲻ���ˣ�\n", me);
        me->delete_temp("job/sew");
        me->delete_temp("job/step");
        return 1;
}

