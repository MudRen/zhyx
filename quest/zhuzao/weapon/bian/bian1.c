#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name(HIW"���Ʊ�"NOR, ({ "duanyun bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���þ�ͭ�������ӵĶ��Ʊޡ�\n");
                set("value", 8000);   
                set("material", "copper");
                set("wield_neili", 100);
                set("wield_maxneili", 300);
                set("wield_str", 18);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(50);
        setup();
}

