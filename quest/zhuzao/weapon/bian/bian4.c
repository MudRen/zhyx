#include <ansi.h>  
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name( HIY"�Ͻ��"NOR, ({"zijin bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ����Ұ��������ӵ��Ͻ�ޣ���Ŀ���õĹ�â���Ի�����\n");
                set("value", 50000);   
                set("material", "gold");
                set("wield_neili", 500);
                set("wield_maxneili", 800);
                set("wield_str", 22);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(200);
        setup();
}

