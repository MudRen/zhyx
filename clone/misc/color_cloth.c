#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(MAG "��"RED"��"BLU"��"HIW"��" NOR, ({ "color cloth", "cloth" }) );
        set_weight(1000);
        set("value", 5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����ۺ�ɫ����������������ֻ��ˣ�ɷ���ԸС�\n");
                set("unit", "��");
                set("material", "cloth");
                set("armor_prop/constitution",20);
                set("armor_prop/personality", 200);
                set("female_only", 1);
        }
        setup();
}

