//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"�׻�֮��"NOR,({"tiger hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIC"����һ��׻�֮�����ܻ��Ѱ׻���װ��Ǳ�ܡ�"NOR"
����װ��ָ�"HIG"huanxing"NOR"
����װ����"HIR"[�׻�֮��]"NOR" "HIW"�׻�ս��"NOR" "HIW"�׻�ս��"NOR" "HIW"�׻�սѥ"NOR" "HIW"�׻�����"NOR"
����Ч����"HIG"��������Ǳ�ڵ���������ʱ���ӿ����˺�����Ч�ȼ���"NOR"\n");
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

	if(me->query_temp("tigereff"))
		return notify_fail("���Ѿ���Ӧ�˰׻�֮����\�\n");

	if(me->is_busy())
		return notify_fail("����æ����!\n");

	if(!jia=present("tiger armor",me))
		return notify_fail("�㻹ȱ��"HIW"�׻�ս��"NOR"\n");
	if(!head=present("tiger helmet",me))
		return notify_fail("�㻹ȱ��"HIW"�׻�ս��"NOR"\n");
	if(!shoe=present("tiger shoes",me))
		return notify_fail("�㻹ȱ��"HIW"�׻�սѥ"NOR"\n");
	if(!pifeng=present("tiger coat",me))
		return notify_fail("�㻹ȱ��"HIW"�׻�����"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("��������Я�������ϲ��ܷ������á�\n");

	if(me->query("str")<35)
		return notify_fail("���������������޷�ʩչ�׻�֮����\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("��ѧ�����һ���֮�����޷����Ѱ׻�֮����������\n");

	if((int)me->query("jingli")<500)
		return notify_fail("�����ھ������������Ի��Ѱ׻�֮����������\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("�����Ҫ�������װ׻���װ��\n"NOR);

	message_vision(HIG"$N"HIG"�������"HIW"�׻�֮��"HIG"��ʱһ�������ӻ���������$N"HIG"��˫�ۣ�\n"NOR,me);
	me->set_temp("tigereff",1);
	me->add_temp("apply/cuff", (int)me->query_str()/5);
	me->add_temp("apply/claw", (int)me->query_str()/5);
	me->add_temp("apply/hand", (int)me->query_str()/5);
	me->add_temp("apply/finger", (int)me->query_str()/5);
	me->add_temp("apply/strike", (int)me->query_str()/5);
	me->add_temp("apply/unarmed", (int)me->query_str()/5);
	me->add_temp("apply/unarmed_damage", 200);
	me->add("jingli",-300);
	call_out("tiger_ok",me->query_str(),me);

	return 1;
}


void tiger_ok(object me)
{
	if(!me)return;
	me->add_temp("apply/cuff", - (int)me->query_str()/5);
	me->add_temp("apply/claw", - (int)me->query_str()/5);
	me->add_temp("apply/hand", - (int)me->query_str()/5);
	me->add_temp("apply/finger", - (int)me->query_str()/5);
	me->add_temp("apply/strike", - (int)me->query_str()/5);
	me->add_temp("apply/unarmed", - (int)me->query_str()/5);
	me->add_temp("apply/unarmed_damage", - 200);
	me->delete_temp("tigereff");
	message_vision(HIG"$N"HIG"����һи��˫���еİ׻�֮��������ʧ��\n"NOR,me);
}