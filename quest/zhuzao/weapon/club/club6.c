#include <ansi.h>  
#include <weapon.h>
inherit CLUB;
void create()
{
        set_name(  HIG"�����"NOR, ({"hanyu gun", "gun" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
                "����һ������ǧ�꺮������ĺ��������ȡ�Ժ�����Ȼ��Ө����\n");
                set("value", 100000);   
                set("material", "crystal");
                set("wield_neili", 600);
                set("wield_maxneili", 1000);
                set("wield_str", 24);
                set("wield_msg", "$N��������һ���ͳ�һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ر���\n");   
        }
        init_club(400);
        setup();
 }
