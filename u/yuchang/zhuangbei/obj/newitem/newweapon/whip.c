// blade.c

#include <weapon.h>

inherit WHIP;

void create()
{
        set_name("��", ({"whip"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ�ֹ�ע�������ıޣ�");
                set("unit", "��");
                set("value", 500);
        }
        init_whip(15);
        setup();
}

