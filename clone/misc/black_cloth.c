#include <armor.h>
                
inherit CLOTH;
 
void create()
{
        set_name("ҹ����", ({ "black cloth", "cloth" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ��ҹ���������ڲ����ٵĺ�ɫ�����¡�\n");
                set("unit", "��");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/dodge", 1);
                set("armor_prop/personality", -1);
        }
        setup();
}

