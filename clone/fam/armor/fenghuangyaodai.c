#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIR "�������" NOR, ({ "fenghuang belt", "belt", "fenghuang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ���û���֮�����ɵ�������͸���һ���������ǵĹ�â��\n" NOR
                            HIC "��Ч�м�������+ 10        ��Ч�Ṧ������+ 20\n" NOR
                            HIC "����Ч��������+ 5%        ����Ч���ȼ���  30\n" NOR
                            HIC "�����ر�������+ 5%\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("armor_prop/armor", 40);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 20);
                set("armor_prop/parry", 10);
                set("wear_msg", HIR "$N" HIR "����ذ�$n"
                    HIR "ϵ�����䡣\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
