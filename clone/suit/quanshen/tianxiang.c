// jixiang armor.c
// 龙凤战甲 [吉祥]
// 成套装备
// by yuchang
#include <ansi.h>



inherit ITEM;
//int do_jixiang();


void create()
{
	set_name( HIC"[天祥护符]"NOR, ({ "tianxiang hufu", "hufu" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
		set("long", HIC"这是一块天祥护符，虽然本身没什么用，但是能唤醒天祥护具的潜能。"NOR"
成套装备指令："HIG"huanxing"NOR"
成套装备："HIC"[天祥防具]"NOR" "HIR"龙凤战甲"NOR" "YEL"锦云护心"NOR" "HIG"天灵护腕"NOR" "HIY"金锦披风"NOR" "HIW"云盘护腰"NOR"
成套效果："HIG"气脉顺畅，内力充沛"NOR"\n");
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
           return notify_fail("这张护符已经用了很多次了！\n");
        if(!me->is_fighting())
           return notify_fail("你不在战斗啊！\n");
        if(me->is_busy())
           return notify_fail("你正忙着呢!\n");
        if(!zhanjia = present("longfeng zhanjia",me))
           return notify_fail("你还缺少"HIR"龙凤战甲"NOR"\n");   
        if(!huyao = present("yunpan huyao",me))
           return notify_fail("你还缺少"HIW"云盘护腰"NOR"\n");
        if(!huxin = present("jinyun huxin",me))
           return notify_fail("你还缺少"YEL"锦云护心"NOR"\n");
        if(!huwan = present("tianling huwan",me))
           return notify_fail("你还缺少"HIG"天灵护腕"NOR"\n");
        if(!pifeng = present("jinjin pifeng",me))
           return notify_fail("你还缺少"HIY"金锦披风"NOR"\n");
        if ((zhanjia->query("equipped")!="worn") || (huyao->query("equipped")!="worn") || (huxin->query("equipped")!="worn") || (huwan->query("equipped")!="worn") || (pifeng->query("equipped")!="worn"))   
           return notify_fail("你必须要穿上一整套[天祥防具]\n");
        if (me->query_temp("jixiangeff"))
           return notify_fail("你已经开始呼应[天祥防具]的威力了！\n");


message_vision(HIG
      "$N将"HIC"[天祥护符]"NOR""HIG"贴在"HIC"[天祥防具]"HIG"上，五件装备各自呼应起来。$N顿时感到浑身内力充沛！！\n"NOR,me);
me->add_temp("jixiangeff",1);
ob->add("power",-1);
call_out("jixiangeff",3,me);
  return 0;
}



void jixiangeff(object me)
{ 
message_vision(HIY"$N的一套"HIC"[天祥防具]"HIY"突然放出光芒，$N只感到浑身血脉通畅，精神百倍。\n"NOR,me);
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