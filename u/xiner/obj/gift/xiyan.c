
//ϲ�� (����force,force,dodge,parry)����1��


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "����" NOR, ({ "xi yan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���Ƕ���������һ���ӽ�鷢�ć��̡�\n����ǻƺ�¥��1916��Ŷ��" NOR);
                set("unit", "��");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_chou","chou");
        }
                

int do_chou( string arg )
{       
        if (arg == "xi yan")

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/20090501/eat1") )
        {write(HIR"���Ѿ��Թ������˻���Ҫô��\n"NOR);return 1;}

        message_vision(HIY "$N����һ�ڇ��̣�����ٱ�����æ��������һ��������˵:����ϲ����ϲ��\nף���� �� �� �ϣ�\n" NOR, me);

	message("vision", HIR"��ϲ��ϲ����" + me->query("name") + "ף�����ӷ��޶��ˣ�������ӡ������ͬ�ģ������మ������úϣ�\n"NOR, users());

	log_file("static/wuyi", sprintf("%s(%s) chou ���� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

	me->set("liwu/20090501/eat1", 1);

	me->add("combat_exp", 50000);
        me->add("potential",  50000);

	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 1500000);
	if (me->can_improve_skill("unarmed"))
		me->improve_skill("unarmed", 1500000);
	if (me->can_improve_skill("finger"))
		me->improve_skill("finger", 1500000);
	if (me->can_improve_skill("blade"))
		me->improve_skill("blade", 1500000);
	if (me->can_improve_skill("hand"))
		me->improve_skill("hand", 1500000);
	if (me->can_improve_skill("cuff"))
		me->improve_skill("cuff", 1500000);
	if (me->can_improve_skill("strike"))
		me->improve_skill("strike", 1500000);

	destruct(this_object());
	return 1;
        }
	else
	{return 0;}
}
                
int query_autoload() { return 1; }