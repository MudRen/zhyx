#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( BLK"������"NOR, ({"xuantie bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                 "����һ���������������ӵĳ��ޣ����������쳣���ء�\n");
                set("value", 80000);   
                set("material", "crystal");
                set("wield_neili", 600);
                set("wield_maxneili", 1000);
                set("wield_str", 23);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(300);
        setup();
}
