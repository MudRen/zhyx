#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
void create()
{
        set_name( HIY"��ͭ��"NOR, ({"shutong gun", "gun" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                  "����һ���þ�ͭ�������ͭ����\n");
                set("value", 8000);   
                set("material", "copper");
                set("wield_neili", 100);
                set("wield_maxneili", 300);
                set("wield_str", 18);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_club(50);
        setup();
}
