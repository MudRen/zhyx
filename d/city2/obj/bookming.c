// ��ʷ����

inherit ITEM;

void init()
{
        add_action("do_shake", "doudong");
        add_action("do_shake", "shake");
        add_action("do_shake", "twitter");
}

void create()
{
        set_name("��ʷ����", ({"book ming","book","ming"}));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "һ�������顣\n");
                set("unit", "��");
                set("material", "paper");
        }
        setup();
}


int do_shake(string arg)
{
	object me;
	me = this_player();

        if (! arg || ! id(arg)) return 0;

        if (! query("gotgold"))
	{
	        message("vision","ͻȻ����Ƭ��Ҷ�����е��˳�����\n", environment(me));
                new("/d/city2/obj/goldleaf")->move(environment(me));
                new("/d/city2/obj/goldleaf")->move(environment(me));
                set("gotgold", 1);
        } else
                message_vision("$N����$n���˰��죬ʲôҲû�з��֡�\n",
                               me, this_object());

        return 1;
}
