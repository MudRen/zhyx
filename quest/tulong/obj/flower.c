#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        string *names=({HIW"�ٺ�"NOR,HIR"õ��"NOR,HIB"ܽ��"NOR,HIY"����"NOR,HIM"Ǿޱ"NOR,HIG"����"NOR,HIC"����"NOR,
                       HIY"��÷"NOR,HIR"�¼�"NOR,HIW"ѩ��"NOR});
        set_name(names[random(sizeof(names))], ({"flower", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��������"+this_object()->query("name")+NOR"��\n");
                set("value", 0);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/personality", random(2)+1);
                set("wear_msg", "$N����ذ�һ��$n����ͷ�ϡ�\n");
                set("unequip_msg", "$N����ذ�$n��ͷ��ժ��������\n");
        }
        setup();
}

