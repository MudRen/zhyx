
#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIM "�����" NOR, ({ "weapon card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "ƾ�˿���ȥ���񴦻�ȡʮ������һ�ѡ�\n"NOR);			
                set("unit", "��");
                set("value", 100000000);
                set("weight", 10);
                set("material", "paper");	
                set("no_sell",1);	  		  
             }	         
        setup();
}

int query_autoload() 
     { return 1; } 
		
