#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( HIW"������"NOR, ({"liangyin bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ���ô����������ӵ������ޣ���������ɷ�Ǻÿ���\n");
                set("value", 30000);   
                set("material", "silver");
                set("wield_neili", 400);
                set("wield_maxneili", 600);
                set("wield_str", 22);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(150);
        setup();
}
