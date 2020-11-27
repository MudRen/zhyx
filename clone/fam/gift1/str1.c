#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIG "神力丹" NOR, ({ "shenli dan", "shenli", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "这是一颗通体浑圆的药丸，据说吃了可以增强膂力。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 0);
                set("base_weight", 50);
                set("only_do_effect", 1);
                              set("no_get", 1); 
                      set("no_put", 1); 
                      set("no_drop", 1); 
                      set("no_beg", 1);                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 40);
                set("gift_msg", HIY "突然间你只觉双臂几乎爆裂，充满了力量。\n" NOR);
        }
        setup();
}

