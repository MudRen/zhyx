#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
void create()
{
        set_name( HIB"ɥ���"NOR, ({"sanghun gun", "gun" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                  "����һ���þ��ִ���ɥ�������������ġ�\n");
                set("value", 12000);   
                set("material", "iron");
                set("wield_neili", 200);
                set("wield_maxneili", 400);
                set("wield_str", 20);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_club(100);
        setup();
}

