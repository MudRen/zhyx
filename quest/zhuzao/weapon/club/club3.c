#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
void create()
{
        set_name(  HIW"������"NOR, ({"liangyin gun", "gun" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                  "����һ���ô����������ӵ�����������������ɷ�Ǻÿ���\n");
                set("value", 30000);   
                set("material", "silver");
                set("wield_neili", 300);
                set("wield_maxneili", 500);
                set("wield_str", 22);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_club(150);
        setup();
}
