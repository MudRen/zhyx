#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("��ʯ", ({"kuangshi"}));
        set_weight(2000);
                set("no_sell",1);
                set("unit","��");
                set("material","metal");
                set("list",0);
         set("changed",1);
                set("value",1);
                set("level",0);
                set("long","һ���ʯ��������ĳ���ط������ᴿ��\n");

       if( clonep() )
              set_default_object(__FILE__);
        setup();
}

