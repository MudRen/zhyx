#include <weapon.h>
#include <ansi.h>

inherit SWORD;
void create()
{
        set_name(MAG"���潣"NOR,({ "xuanzhen jian", "xuanzhen", "sword", "jian" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 80000);
                set("material", "steel");
                set("weapon_prop/dodge", -5);
                set("weapon_prop/parry", 5); 
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);
                set("wield_msg", HIY"$N��ৡ���һ�����һ����潣��\n"NOR);
                set("long", "����һ���ĳ������ĹŽ���\n");                
                set("unwield_msg", HIY "��潣����һ���׹⣬��ৡ��ط��뽣�ʡ�\n" NOR);                
        }
        init_sword(250);
        setup();
}

