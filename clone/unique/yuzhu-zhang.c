#include <ansi.h>
#include <weapon.h>
inherit F_UNIQUE;

inherit STAFF; 

void create()
{
        set_name(HIG "������" NOR, ({"yuzhu zhang", "zhang", "staff"}));
        set_weight(5000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG"һ������������������ȡ�\n"NOR);
                set("value", 8000000);
                set("material", "bamboo");
                set("rigidity", 3000);
                set("replica_ob","/clone/weapon/zhubang");
                set("wield_msg", "$N���һ�������������������ץ�����С�\n");
                set("unwield_msg", "$N�����е������Ȳ�����С�\n");
        }
        init_staff(200); 
        setup();
}       

