#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( HIG"寒玉鞭"NOR, ({"hanyu bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", 
                 "这是一柄用千年寒铁打造的寒玉鞭，虽取自寒铁，然晶莹如玉。\n");
                set("value", 100000);   
                set("material", "crystal");
                set("wield_neili", 600);
                set("wield_maxneili", 1000);
                set("wield_str", 24);
                set("wield_msg", "$N「唰」的一声抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n卷回腰间。\n");
        }
        init_whip(400);
        setup();
}
