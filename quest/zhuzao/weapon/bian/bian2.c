#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( HIB"������"NOR, ({"dulong bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ���þ��ִ������ӵĶ����ޣ������ĵ���������Ŀ��\n");
                set("value", 12000);   
                set("material", "steal");
                set("wield_neili", 200);
                set("wield_maxneili", 400);
                set("wield_str", 20);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(100);
        setup();
}

