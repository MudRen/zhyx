// jixiang armor.c
// ����ս�� [����]
// ����װ��
// by yuchang
#include <ansi.h>



inherit ITEM;
//int do_jixiang();


void create()
{
	set_name( HIC"[���黤��]"NOR, ({ "tianxiang hufu", "hufu" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIC"����һ�����黤������Ȼ����ûʲô�ã������ܻ������黤�ߵ�Ǳ�ܡ�"NOR"
����װ��ָ�"HIG"huanxing"NOR"
����װ����"HIC"[�������]"NOR" "HIR"����ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"����˳������������"NOR"\n");
		set("value", 10000);
		set("material", "crystal");
		set("power",100);
	}
	setup();
}

  void init()
{
  add_action("do_jx","huanxing");
}
int do_jx()
{
  object zhanjia,huyao,huxin,huwan,pifeng;

  object me = this_player();
  object ob = this_object();

        if(ob->query("power")<1)
           return notify_fail("���Ż����Ѿ����˺ܶ���ˣ�\n");
        if(!me->is_fighting())
           return notify_fail("�㲻��ս������\n");
        if(me->is_busy())
           return notify_fail("����æ����!\n");
        if(!zhanjia = present("longfeng zhanjia",me))
           return notify_fail("�㻹ȱ��"HIR"����ս��"NOR"\n");   
        if(!huyao = present("yunpan huyao",me))
           return notify_fail("�㻹ȱ��"HIW"���̻���"NOR"\n");
        if(!huxin = present("jinyun huxin",me))
           return notify_fail("�㻹ȱ��"YEL"���ƻ���"NOR"\n");
        if(!huwan = present("tianling huwan",me))
           return notify_fail("�㻹ȱ��"HIG"���黤��"NOR"\n");
        if(!pifeng = present("jinjin pifeng",me))
           return notify_fail("�㻹ȱ��"HIY"�������"NOR"\n");
        if ((zhanjia->query("equipped")!="worn") || (huyao->query("equipped")!="worn") || (huxin->query("equipped")!="worn") || (huwan->query("equipped")!="worn") || (pifeng->query("equipped")!="worn"))   
           return notify_fail("�����Ҫ����һ����[�������]\n");
        if (me->query_temp("jixiangeff"))
           return notify_fail("���Ѿ���ʼ��Ӧ[�������]�������ˣ�\�\n");


message_vision(HIG
      "$N��"HIC"[���黤��]"NOR""HIG"����"HIC"[�������]"HIG"�ϣ����װ�����Ժ�Ӧ������$N��ʱ�е������������棡��\n"NOR,me);
me->add_temp("jixiangeff",1);
ob->add("power",-1);
call_out("jixiangeff",3,me);
  return 0;
}



void jixiangeff(object me)
{ 
message_vision(HIY"$N��һ��"HIC"[�������]"HIY"ͻȻ�ų���â��$Nֻ�е�����Ѫ��ͨ��������ٱ���\n"NOR,me);
         me->add("neili",me->query_con()*10);
         me->add("jingli",me->query_con()*10);
         if (me->query("neili")>me->query("max_neili"))
         {
                 me->set("neili",me->query("max_neili"));
         }     
                  if (me->query("jingli")>me->query("eff_jingli"))
         {
                 me->set("jingli",me->query("eff_jingli"));
         }     
me->delete_temp("jixiangeff");
}