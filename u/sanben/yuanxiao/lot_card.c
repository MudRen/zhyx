
#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIG "抽奖卡" NOR, ({ "lot card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "这是一张抽奖用的卡片。\n"NOR);			
                set("unit", "张");
                set("value", 100000000);
                set("weight", 10);
                set("material", "paper");	
                set("no_sell",1);	  		  
             }	         
        setup();
}
/*
int query_autoload() 
     { return 1; } 
*/		
