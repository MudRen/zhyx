// ghost_sword.c
// Modified by haiyan

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIM"��ľ��"NOR, ({ "taomu jian", "jian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200);
                set("no_sell", 1);
                set("material", "bamboo");
        set("long", "����һ�ѵ�ʿ������������ħ����ľ�����������һЩ���š�\n");
                set("wield_msg", HIY"$N���һ�ѽ��������$n"HIY"�������С�\n"); 
                set("unequip_msg", "$N�������е�$n��\n");
        }
        init_sword(10);
        setup();
}

