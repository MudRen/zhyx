//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIB"��������"NOR,({"seraphim hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIC"����һö�����������ܻ���������װ��Ǳ�ܡ�"NOR"
����װ��ָ�"HIG"huanxing"NOR"
����װ����"HIB"[��������]"NOR" "HIR"����֮��"NOR" "HIR"���֮��"NOR" "HIR"����֮��"NOR" "HIR"Ӧ��֮��"NOR"
����Ч����"HIG"��������Ǳ�ڵ���������ʱ���������˺�����Ч�ȼ���"NOR"\n");
		set("value",100000);
		set("no_steal",1);
		set("no_beg",1);
		set("no_sell",1);
		set("material","crystal");
	}
	setup();
}
int query_autoload()
{
	return 1;
}

void init()
{
	add_action("do_hx","huanxing");
}

int do_hx()
{
	object jia,head,shoe,pifeng;
	object me=this_player();
	object ob=this_object();

	if(me->query_temp("seraphimeff"))
		return notify_fail("���Ѿ���Ӧ������������\�\n");

	if(me->is_busy())
		return notify_fail("����æ����!\n");

	if(!jia=present("seraphim armor",me))
		return notify_fail("�㻹ȱ��"HIR"����֮��"NOR"\n");
	if(!head=present("seraphim horn",me))
		return notify_fail("�㻹ȱ��"HIR"���֮��"NOR"\n");
	if(!shoe=present("seraphim foots",me))
		return notify_fail("�㻹ȱ��"HIR"����֮��"NOR"\n");
	if(!pifeng=present("seraphim wing",me))
		return notify_fail("�㻹ȱ��"HIR"Ӧ��֮��"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("��������Я�������ϲ��ܷ������á�\n");

	if(me->query("con")<35)
		return notify_fail("���������ǲ����޷�ʩչ����������\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("��ѧ�����һ���֮�����޷���������֮����������\n");

	if((int)me->query("jingli")<500)
		return notify_fail("�����ھ������������Ի�������֮����������\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("�����Ҫ��������������װ��\n"NOR);

	message_vision(HIG"$N"HIG"����"HIB"��������"HIG"һ������һ����������$N"HIG"�ı���֮�ϣ�\n"NOR,me);
	me->set_temp("seraphimeff",1);
	me->add_temp("apply/club", (int)me->query_con()/5);
	me->add_temp("apply/whip", (int)me->query_con()/5);
	me->add_temp("apply/sword", (int)me->query_con()/5);
	me->add_temp("apply/blade", (int)me->query_con()/5);
	me->add_temp("apply/staff", (int)me->query_con()/5);
	me->add_temp("apply/hammer", (int)me->query_con()/5);
	me->add_temp("apply/damage", 200);
	me->add("jingli",-300);
	call_out("seraphim_ok",me->query_con(),me);

	return 1;
}


void seraphim_ok(object me)
{
	if(!me)return;
	me->delete_temp("seraphimeff");

	me->add_temp("apply/club", - (int)me->query_con()/5);
	me->add_temp("apply/whip", - (int)me->query_con()/5);
	me->add_temp("apply/sword", - (int)me->query_con()/5);
	me->add_temp("apply/blade", - (int)me->query_con()/5);
	me->add_temp("apply/staff", - (int)me->query_con()/5);
	me->add_temp("apply/hammer", - (int)me->query_con()/5);
	me->add_temp("apply/damage", - 200);

	message_vision(HIG"$N"HIG"΢΢һ㶣������ϵ�����������ʧ�����ˣ�\n"NOR,me);
}