inherit ITEM;

void create()
{
	set_name( "������", ({ "wulin ling", "ling"}) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ������ͬ��ʹ�õ����������������� �ɻ���ǩ������������ͬ��һӦ����\n");
		set("value", 0);
		set("material", "iron");
	}
	setup();
}

void init()
{
        add_action("do_chushi","chushi");
}

int do_chushi(string arg)
{
        object thing,obj,me,who;
        mapping quest;
        me = this_player();
        if (! quest = me->query("quest_hs")) 
            return notify_fail("��û�нӵ����յ�������������Ӣ����ΰ��εĸ�ɶ��\n");
        if (!arg) return notify_fail("��Ҫ��˭��ʾ�����");
        if (! objectp(who = present(arg, environment(me))))
            return notify_fail("����û������ˡ�\n");
        if (who->query_temp("quester") != me->query("id") || quest["target"] != who->query("id")) 
            return notify_fail("�㲻Ҫ��������ͬ�˵�����������ҡײƭ��\n");
        message_vision("$N�߾����������$n����˵����������һ׼����������������ã�\n"
                       "���ڽ��������ҵ����㣡�ƴ�����������ȡ"+quest["name"]+"����͹ԹԵĽ������ɣ�\n",me,who);
        message_vision("$N����$n���е����������һ����̾����������ô�ã����Ǹ������ҵ��ˣ�Ҳ��Ҳ�գ�\n"
                       "��Ҫ�Ķ����������У��ͽ������ˡ�\n",who,me);
        thing = new(quest["object"]);
        thing->set_temp("zheng",me->query("id"));
        if (!thing->move(me))
            message_vision("$N��"+thing->name(1)+"���ڵ��ϡ�\n",who);
        else
            message_vision("$N��"+thing->name(1)+"������$n��\n",who,me);

        message_vision("$N���˻��֣�ת���뿪�ˡ�\n",who);
        destruct(who);
        return 1;
}
            
     
