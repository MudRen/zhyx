// p_jiasha.c ��ɫ����
//

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name( MAG "��ɫ����" NOR ,({"jiasha","jia sha","cloth"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("unique", 1);
                set("material", "cloth");
                set("armor_prop/armor", 200);
                set("value",100);
        }
        setup();
}

