// thousand.c

#include <ansi.h>

inherit MONEY;

void create()
{
        set_name(YEL "һǧ����Ʊ" NOR, ({"thousand-gold", "thousand-gold_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "thousand-gold");
                set("long", "һ�����ֵһǧ�����ӵĽ�Ʊ��\n");
                set("unit", "��");
                set("base_value", 10000000);
                set("base_unit", "��");
                set("base_weight", 1);
        }
        set_amount(1);
}

