#include <weapon.h>
#include <ansi.h>
inherit BLADE;
void create()
{
        set_name(MAG"���ֵ�"NOR, ({ "lindao" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("jungle",1);
                set("material", "iron");
                set("long", "����һѰ���Ŀ��ֵ���ר��������С���͹�ľ��\n");
                set("wield_msg", "$N���һ�Ѻ����͵�$n�������С�\n");
                set("unequip_msg", "$N�����е�$n�������䡣\n");
        }
        init_blade(5);
        setup();
}

