
//ϲ�� (����force,force,dodge,parry)����1��


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "����" NOR, ({ "xi tang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���Ƕ���������һ���ӽ�鷢�ć��ǡ�\n" NOR);
                set("unit", "��");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_eat","eat");
        }
                

int do_eat( string arg )
{       
        if (arg == "xi tang")

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/20090501/eat") )
        {write(HIR"���Ѿ��Թ������˻���Ҫô��\n"NOR);return 1;}

        message_vision(HIY "$N������һ�����ˣ���������һ��������˵:����ϲ����ϲ��\nף���� �� �� �֣�\n" NOR, me);

	message("vision", HIM"��ϲ��ϲ����" + me->query("name") + "ף�����ӷ��޶��ˣ��ɲ�Ůò��������Բ�������మ����ͷ���ϣ�\n"NOR, users());

	log_file("static/wuyi", sprintf("%s(%s) eat ���� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

	me->set("liwu/20090501/eat", 1);

	me->add("combat_exp", 50000);
        me->add("potential",  50000);

	if (me->can_improve_skill("force"))
		me->improve_skill("force", 1500000);
	if (me->can_improve_skill("parry"))
		me->improve_skill("parry", 1500000);
	if (me->can_improve_skill("dodge"))
		me->improve_skill("dodge", 1500000);

	destruct(this_object());
	return 1;
        }
	else
	{return 0;}
}

int query_autoload() { return 1; }
