// jingubang.c

#include <ansi.h>
#include <weapon.h>

inherit F_UNIQUE; 
inherit STICK;

void create()
{
        set_name( HIY "�𹿰�" NOR, ({ "jin gu bang", "bang" }) );
        set_weight(50000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 500);
		set("material", "gold");
		set("replace_file", "/d/obj/weapon/stick/bintiegun");
		set("long", "�˰���ͷ�Խ�Ϊ�����м���һ������������һ��С�֣�������𹿰�����\n");
		set("wield_msg", "$Nһ���֣����ȼ������󣡴󣡴����к�Ȼ����һ��$n��\n");
		set("unwield_msg", "$Nһ������������ȣ�С��С��С��$n��$N����ת�˼�ת����Ȼ�����ˡ�\n");
	}
	init_stick(250);
     set("no_sell",1);
	setup();
}

void init()
{
	object me=this_player();
	me->delete_temp("jgb_haven");
	call_out("jgb_check_idle",60);
	return ::init();
}

void jgb_check_idle()
{
	object me=this_player();
	remove_call_out("jgb_check_idle");
	if (me->is_fighting()) 
	{
	  call_out("jgb_check_idle",60);
	  return;
	}
	if (living(me)) {
	  if (me->in_input() || file_name(environment(me))==me->query_temp("jgb_haven/env"))
	 {
	   me->add_temp("jgb_haven/count",1);
	   if (me->query_temp("jgb_haven/count")>=20)
	   {	
	    message_vision("ֻ��������һ��,$n��$N�����ϵ�����,������ﲻ����.\n",me,this_object());
	    destruct(this_object());
	    return;
	   }
	 }
	else {
		me->set_temp("jgb_haven/env",file_name(environment(me)));
		me->set_temp("jgb_haven/count",0);
	     }
	}
	call_out("jgb_check_idle",60);
	return;
}
