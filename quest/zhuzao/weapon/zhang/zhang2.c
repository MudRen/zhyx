#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name(   HIB"׷����"NOR, ({"zhuihun zhang", "zhang" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ���þ��ִ���ϻ��ȣ���ͷ����һ��������\n");
                set("value", 12000);   
                set("material", "iron");
                set("wield_neili", 200);
                set("wield_maxneili", 400);
                set("wield_str", 20);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(100);
        setup();
}
