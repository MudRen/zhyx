#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name(  HIW"��ɥ��"NOR, ({"kusang zhang", "zhang" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                  "����һ���þ�ͭ����Ŀ�ɥ�ȡ�\n");
                set("value", 8000);   
                set("material", "copper");
                set("wield_neili", 100);
                set("wield_maxneili", 300);
                set("wield_str", 18);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(50);
        setup();
}

