#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( HIG"�����"NOR, ({"hanyu bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                 "����һ����ǧ�꺮������ĺ���ޣ���ȡ�Ժ�����Ȼ��Ө����\n");
                set("value", 100000);   
                set("material", "crystal");
                set("wield_neili", 600);
                set("wield_maxneili", 1000);
                set("wield_str", 24);
                set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_whip(400);
        setup();
}
