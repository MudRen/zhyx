// baihong-jian.c �׺罣
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIG "��ˮ��" NOR, ({ "bishui jian", "bishui", "jian", "sword" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���ǰ��ֱ����������������������͸���׹⣬��������ޱȡ�\n");
                set("value", 30000);
                set("material", "blacksteel");
                set("treasure",1);
                set("long","���ǰ��ֱ����������������������͸���̹⣬��������ޱȡ�\n");
                set("wield_msg", "ֻ�������ˡ���һ�����׹���֣�$N��������µ�$n���ñ�ֱ��\n");
                set("unequip_msg", "$N�����е�$n�������䡣\n");
        }
        init_sword(150);
        setup();
}
