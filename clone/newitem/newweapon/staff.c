// hammer.c
#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit STAFF;

void create()
{
        set_name("��", ({"staff"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ѹ�ע���������ȣ����漸�������������죬");
                set("value", 500);
                set("material", "iron");
                set("wield_msg","$N�ó�һ��$n���������С�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }

        init_staff(25);
        setup();
}

