// by dubei
#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{

        set_name(HIR"Ѫ��"NOR, ({ "xue dao","blade","dao" }));
        set_weight(15000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��������嵶������ס�������������һ�㡣������ȥ������ȫ�ǰ���֮ɫ����
Ѫ������,���ǿɲ�.\n");
                set("value", 60000);
                set("weapon_prop/dodge", 2);
                set("weapon_prop/parry", 2);
                set("material", "steel"); 
                set("wield_neili", 120);
                set("wield_maxneili", 1000);
                set("wield_maxneili", 1000);
                set("wield_str", 26);
                set("wield_msg", RED"ֻ����ৡ���һ����Ѫ�����ʷɳ���$N����������סһ�����߷��ź�⣬������һƬѪ������\n"NOR);            
                set("unwield_msg", RED"ֻ��$N����һ��,Ѫ����һ�����߷������ʡ�\n"NOR);
                set("treasure",1);
        }
        init_blade(250);
        setup();
}

