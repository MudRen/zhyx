#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"��һ��ˮ"NOR, ({ "tianyi poison", "poison" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
        "����һ����ɫ����ζ���涾�ޱȵ�Һ�壬���Ե���(di)�ھ�ˮ֮�к��ˡ�\n" );
                set("unit", "��");
                set("base_value", 700);
                set("base_unit", "��");
                set("base_weight", 30);
        }
}

