// tiejia.c ����
//
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name( HIG"������"NOR, ({ "donghuang zhong","zhong" }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", HIW"һ����ͭ���ӣ��ഫΪ����̫һ�ı��������Ͽ��������Ϲ����֣�ɢ���Ż�ɫ�ĺ��⡣���м�ǿ�ķ���������\n" NOR);
                set("material", "steel");
		set("value", 2000);
                set("armor_prop/armor", 500 + random(100)); 
                set("armor_prop/dodge", 200 + random(100));
                set("armor_prop/parry", 200 + random(100));

        }
        setup();
}

