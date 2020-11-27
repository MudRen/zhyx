//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"�����ػ�"NOR,({"xuanwu hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","��");
		set("long",HIC"����һ������������޵Ļ������ܻ���������װ��Ǳ�ܡ�"NOR"
����װ��ָ�"HIG"huanxing"NOR"
����װ����"HIR"[�����ػ�]"NOR" "HIW"����ս��"NOR" "HIW"����ս��"NOR" "HIW"����սѥ"NOR" "HIW"��������"NOR"
����Ч����"HIG"�������ֹ������Ի�ȡ�������Ĵ����������"NOR"\n");
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

	if(me->query_temp("xuanwueff"))
		return notify_fail("���Ѿ���Ӧ�������ػ���\�\n");

	if(me->is_busy())
		return notify_fail("����æ����!\n");

	if(!jia=present("xuanwu armor",me))
		return notify_fail("�㻹ȱ��"BLK"����"HIW"ս��"NOR"\n");
	if(!head=present("xuanwu helmet",me))
		return notify_fail("�㻹ȱ��"BLK"����"HIW"ս��"NOR"\n");
	if(!shoe=present("xuanwu shoes",me))
		return notify_fail("�㻹ȱ��"BLK"����"HIW"սѥ"NOR"\n");
	if(!pifeng=present("xuanwu coat",me))
		return notify_fail("�㻹ȱ��"BLK"����"HIW"����"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("��������Я�������ϲ��ܷ������á�\n");

	if(me->query("dex")<35)
		return notify_fail("��������������޷�ʩչ�����ػ���\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("��ѧ�����һ���֮�����޷����������ػ���������\n");

	if((int)me->query("jingli")<500)
		return notify_fail("�����ھ������������Ի��������ػ���������\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("�����Ҫ��������������װ��\n"NOR);

	message_vision(HIY"$N"HIY"����������"BLK"�����ػ�"HIY"֮�У�$N"HIY"�����ֳ�һ�����ܵ��ۼף�\n"NOR,me);
	me->set_temp("xuanwueff",1);
        me->add_temp("apply/attack", - (int)me->query_dex() / 5);
        me->add_temp("apply/defense", (int)me->query_dex() / 4);
	me->add_temp("apply/armor", (int)me->query_dex() * 2);
	me->add("jingli",-300);
	call_out("xuanwu_ok",me->query_dex(),me);

	return 1;
}


void xuanwu_ok(object me)
{
	if(!me)return;
        me->add_temp("apply/attack", (int)me->query_dex() / 5);
        me->add_temp("apply/defense", - (int)me->query_dex() / 4);
	me->add_temp("apply/armor", - (int)me->query_dex()* 2);
	me->delete_temp("xuanwueff");
	message_vision(HIY"$N"HIY"����һи�������е��ۼ׽�����ʧ�����ˣ�\n"NOR,me);
}