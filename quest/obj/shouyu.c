#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG"��ɽ����"NOR,({ "tianshan-shenzhang" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                set("long", "����һ��������������ɵ��ں����ȡ�\n");
        }
}

