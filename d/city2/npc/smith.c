// smith.c

inherit NPC;
inherit F_DEALER;

string ask_me();
int do_gu(string arg);
int do_dapi(string arg);
int do_cuihuo(string arg);
void reward(object me);

void create()
{
        set_name("����", ({ "tiejiang", "smith" }));
	set("title", "�������ϰ�");
	set("shen_type", 1);

        set("gender", "����" );
        set("age", 33);
        set("long", "����������ǯ��סһ����ȵ�����Ž�¯�С�\n");

        set("combat_exp", 400);
	set("attitude", "friendly");
        set("vendor_goods",({
                   "/clone/weapon/changjian",
                   "/clone/weapon/hammer",
                   "/clone/weapon/tudao",
		   "/clone/weapon/dagger",
                   "/clone/weapon/tiegun",
                   "/clone/weapon/gangdao",
                   "/clone/cloth/tiejia",
        }));

        set("inquiry", ([
                "����" : (: ask_me :),
                "job"  : (: ask_me :),
        ]));

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_gu", "gu");
        add_action("do_dapi", "dapi");
        add_action("do_cuihuo", "cuihuo");
}

string ask_me()
{
        object me = this_player();

        if (me->query("combat_exp") > 50000)
                return "�����ϸ����δ�������˰ɣ�";

        if (me->query("qi") < 50)
                return "�㻹��Ъ����ɣ�Ҫ�ǳ��������ҿɳе�����";

        if (me->query_temp("smith/gu"))
                return "����ķ��䣬����ô��ĥ��(gu)��";

        if (me->query_temp("smith/dapi"))
                return "�������������û��(dapi)��";

        if (me->query_temp("smith/cuihuo"))
                return "�ɻ���ô��͵��������Ҵ��ȥ(cuihuo)��";

        switch(random(3))
        {
        case 0:
                me->set_temp("smith/gu", 1);
                return "�ã�����ҹ�һ�������(gu)��";

        case 1:
                me->set_temp("smith/dapi", 1);
                return "�����ɣ�����Ҵ�һ������(dapi)��";

        case 2:
                me->set_temp("smith/cuihuo", 1);
                return "ȥ���Ұ���Щ�ճ�¯�Ĵ�һ�»�(cuihuo)��";
        }
}

int do_gu(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/gu"))
        {
                message_vision("$n��͵͵������ķ�������˼���硣"
                               "������$N��$n��ȵ����������Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n����ķ��ƴ������������$N���˵��˵�ͷ��\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_dapi(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/dapi"))
        {
                message_vision("$n���𼸿���������������˵ࡣ"
                               "������$N��$n��ȵ������£��Ҹ�ʲô��\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n���Ŵ��ӶԸճ�¯�Ļ��ȵ����������ô��ţ�"
                        "$N���š���һ��������ȥ��Щ���⡣\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_cuihuo(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ��\n");

        if (! me->query_temp("smith/cuihuo"))
        {
                message_vision("$n�ճ���һ������õ����ӣ�"
                               "������$N��$n��ȵ������£�����Ҹ㻵�ˡ�\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N����ǯ����һ��������ӣ������ˮ"
                       "�أ����ꡱ��һ��������ð��\n",
                       me);
        reward(me);
        return 1;
}

void reward(object me)
{
        object coin;

        me->delete_temp("smith/gu");
        me->delete_temp("smith/dapi");
        me->delete_temp("smith/cuihuo");

        coin = new("/clone/money/coin");
        coin->set_amount(10 + random(10));
        coin->move(this_object());
        message_vision("$N��$n�������Ǹ���Ĺ�Ǯ��\n",
                       this_object(), me);
        command("give coin to " + me->query("id"));
        if (me->query("combat_exp") < 250)
        {
                if (me->query("potential") < me->query_potential_limit())
                        me->add("potential", 1);
                me->add("combat_exp", 1 + random(2));
        }
        me->receive_damage("qi", 50);
        me->start_busy(3);
}
