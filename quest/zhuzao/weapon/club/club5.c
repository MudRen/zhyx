#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
void create()
{
        set_name( BLK"������"NOR, ({"xuantie gun", "gun" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ������������������������������쳣���ء�\n");
                set("value", 80000);   
                set("material", "crystal");
                set("wield_neili", 500);
                set("wield_maxneili", 800);
                set("wield_str", 23);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_club(300);
        setup();
 }
