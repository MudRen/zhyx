// baihong-jian.c �׺罣
#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW"�׺罣"NOR, ({ "baihong sword", "baihong", "sword" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���ǰ��ֱ����������������������͸���׹⣬��������ޱȡ�\n");
                set("value", 10000);
                set("material", "blacksteel");
                set("weapon_prop/dodge", 2);
                set("treasure",1);
                set("wield_msg", "ֻ�������ˡ���һ�����׹���֣�$N��������µ�$n���ñ�ֱ��\n");
                set("unequip_msg", "$N�����е�$n�������䡣\n");
        }
        init_sword(100);

        setup();
}

