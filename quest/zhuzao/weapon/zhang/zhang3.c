#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name( HIW"������"NOR, ({"liangyin zhang", "zhang" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ���ô����������ӵ������ȣ���������ɷ�Ǻÿ���\n");
                set("value", 30000);   
                set("material", "silver");
                set("wield_neili", 400);
                set("wield_maxneili", 500);
                set("wield_str", 22);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(150);
        setup();
 }
