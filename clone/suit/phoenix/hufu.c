// ����װ��
// update by kasumi
#include <ansi.h>
inherit ITEM;



void create()
{
 
        set_name( HIR"��ȸ֮��"NOR, ({ "phoenix hufu","hufu" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC"����һ����ȸ֮�����ܻ�����ȸ��װ��Ǳ�ܡ�"NOR"
����װ��ָ�"HIG"huanxing"NOR"
����װ����"HIR"[��ȸ֮��]"NOR" "RED"��ȸ֮��"NOR" "YEL"��ȸ֮��"NOR" "GRN"��ȸ֮צ"NOR" "HIC"��ȸ֮��"NOR"
����Ч����"HIG"��������Ǳ�ڵ�����,��ʱ���Ӷ��ټ��������ԡ�"NOR"\n");
                set("value", 100000);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_sell", 1);   
                set("material", "crystal");
                
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

  object me = this_player();
  object ob = this_object();
  
        if (me->query_temp("phoenixeff"))
           return notify_fail("���Ѿ���Ӧ����ȸ֮�裡\�\n");
       
        if(me->is_busy())
           return notify_fail("����æ����!\n");
        if(!jia = present("phoenix armor",me))
           return notify_fail("�㻹ȱ��"RED"��ȸ֮��"NOR"\n");   
        if(!head = present("phoenix eye",me))
           return notify_fail("�㻹ȱ��"YEL"��ȸ֮��"NOR"\n");
        if(!shoe = present("phoenix shoes",me))
           return notify_fail("�㻹ȱ��"GRN"��ȸ֮צ"NOR"\n");
         if(!pifeng = present("phoenix wing",me))
           return notify_fail("�㻹ȱ��"HIC"��ȸ֮��"NOR"\n");
         if(environment(this_object())!=me)
            return notify_fail("��������Я�������ϲ��ܷ������á�\n");

	if(me->query("int") < 35)
		return notify_fail("����������Բ����޷�������������֮����\n");
            
	if(me->query_skill("zuoyou-hubo")>1)
		return notify_fail("��ѧ�����һ���֮�����޷�������ȸ֮���������\n");

	if(me->query_skill("count")>1)
		return notify_fail("�㱾��ѧ����������֮�����޷�������ȸ֮���������\n");

	if ((int)me->query("jingli") < 400)
		return notify_fail("�����ھ������������Ի�����ȸ֮���������\n");

	if ((jia->query("equipped")!="worn") || (head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")  || (shoe->query("equipped")!="worn") )   
           return notify_fail("�����Ҫ����������ȸ��װ��\n"NOR);
        
	message_vision(HIG"$N"HIG"�������"HIR"��ȸ֮��"HIG"��ʱ�е�ͷ���ޱ�����������Ϊ������������������\n"NOR,me);
	me->set_temp("phoenixeff",1);
	me->set_skill("count", 150);
	me->add("jingli", -300);
	call_out("phoenix_ok",me->query_int(),me);
	return 1;
}


void phoenix_ok(object me)
{ 
	if (!me) return;
	me->delete_skill("count", 150);
	me->delete_temp("phoenixeff");
	message_vision(HIG"$N"HIG"������и��΢΢һ㶣���ʱΪ����������\n"NOR,me);
}