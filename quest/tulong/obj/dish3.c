#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"ԧ��������"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "���Ǵ�˵�е����ţ�һ��һѼ�����Ŀ��ˣ������Ը������ţ����׳Ե�Ŷ��\n");
                set("unit", "��");
                set("value", 120);
                set("food_remaining", 30);
                set("food_supply", 30);
        }
}

