#include <ansi.h>
#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name(MAG "���Ǵ�����а" NOR, ({ "zhen xie","hammer","chui" }));
        set_weight(28000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 2600000);
                set("material", "steel");
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_sell",1); 
                set("no_drop",1); 
                set("no_give",1); 
                set("long", HIW "\n���Ǵ�����а�˾���������֮һ��\n" NOR);
                set("wield_msg", HIR "$N���ᶶ��$n" HIR "��ɲʱ����������һ��ɱ��ֱ��������\n" NOR);
        }
        init_hammer(175);
        setup();
}

