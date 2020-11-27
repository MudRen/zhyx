#include <ansi.h>

inherit ITEM;

inherit F_NOCLONE;

void create()
{
	set_name( HIY "转世通知" NOR, ({ "zhuanshi tongzhi" }));
	set_weight(100);
	set("long", NOR + HIW "这是一张由馨儿签发的通知书，上面写着：\n\n"
		"      “准许进行转世比武！”\n\n\n"
		"带着通知书去找［隐藏BOSS］就可以进行转世任务了！" NOR);
	set("unit", "张");
	set("value", 0);
	set("no_sell", "这东西你也卖钱！滚一边去！");
	set("no_steal",1);
	set("no_put", 1);
	set("no_drop", 1);
        set("no_light", "这东西你也想烧？你找死啊！"); 
	set("material", "paper");
        setup();
        check_clone();
}
