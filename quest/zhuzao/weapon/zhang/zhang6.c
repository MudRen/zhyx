#include <ansi.h>  
#include <weapon.h>
inherit STAFF;
void create()
{
        set_name(HIG"������"NOR, ({"hanyu zhang", "zhang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ����ǧ�꺮������ĺ����ȣ���ȡ�Ժ�����Ȼ��Ө����\n");
                set("value", 80000);   
                set("material", "crystal");
                set("wield_neili", 500);
                set("wield_maxneili", 1000);
                set("wield_str", 22);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_staff(400);
        setup();
 }
