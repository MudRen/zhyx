
inherit ITEM;
inherit F_NOCLONE;

int do_tear(string arg);

void init()
{
        add_action("do_tear", "tear");
}

void create()
{
        set_name("��ʮ���¾�һ", ({"book1"}));
        set_weight(1000);
        set("long", "\nһ�������ľ��飬��Ƥ(binding)�ܾ��¡�\n");
        set("unit", "��");
        set("material", "paper");
        setup();
        set("startroom", "/d/city2/aobai9");
        check_clone();
}


int do_tear(string arg)
{
	object me;
	string dir;
	me = this_player();

        if( !arg || arg=="" ) return 0;

	if(arg=="book1")
	{
	message_vision("$Nһ�°Ѿ���˺�÷��顣\n", this_player());
	destruct(this_object());
	return 1;
	}

	if( sscanf(arg, "book1 %s", dir)==1 ) {
	if( dir=="binding" ) {
		if(this_object()->query("hasgot"))
		message_vision("$N����Ƥ˺��,������Ƥ�Ѿ���ȡ���ˡ�\n", this_player());
		else
		{
		message_vision("$N����Ƥ˺����������Ƥ����������\n", this_player());
		message_vision("$N�Ƚ���Ƥ�ϵĵ�ͼ����������Ȼ��������յ��ˡ�\n", this_player());
	        me->set("huanggong/haspi1", 1);
                this_object()->set("hasgot",1);  
        	}
	}
        else
	{
	message_vision("$Nһ�°Ѿ���˺�÷��顣\n", this_player());
	destruct(this_object());
	}
	return 1;
        }	
}