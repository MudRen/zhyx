#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(BLU"���ǵ���"NOR, ({ "daoqiao" }) );
        set_weight(8000);
        set_max_encumbrance(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("for_bandit2",1);
                set("long", "һ������ɽ��ǧ�꺮�����ɵĵ��ʡ�\n");
        }
}

