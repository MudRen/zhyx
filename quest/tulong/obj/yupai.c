
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIG "������" NOR, ({ "yupai" }));
        set("long", "\n����һ�����ɫ�����ƣ���Ө��࣬������覣���һ���������\n"+
         "�������Բ״��������"+HIR"����ʯ��"NOR+"�ĸ�׭��С�֡�\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 50000);
                set("material", "��");
                set("armor_prop/armor", 2);
                set("female_only", 1);
        }
        setup();
}

