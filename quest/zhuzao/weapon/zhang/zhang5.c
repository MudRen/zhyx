#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name(BLK"������"NOR, ({"xuantie zhang", "zhang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ���������������ӵ������ȣ����������쳣���ء�\n");
                set("value", 80000);   
                set("material", "crystal");
                set("wield_neili", 400);
                set("wield_maxneili", 800);
                set("wield_str", 22);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(300);
        setup();
}

