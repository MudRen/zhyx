#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "���ͷ��" NOR, ({ "fenghuang touguan", "touguan", "fenghuang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ���û�����ë�ͷ�˽����ɵ�ͷ�ڣ�͸���һ���������ǵĹ�â��\n" NOR
                            HIC "��Ч�м�������+ 10        ��Ч�Ṧ������ + 5\n" NOR
                            HIC "����Ч��������+ 5%       ����Ч���ȼ���  10\n" NOR
                            HIC "�����ر�������+ 5%\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 5);
                set("armor_prop/parry", 10);
                set("wear_msg", HIR "$N" HIR "����ذ�$n"
                    HIR "����ͷ�ϣ�ɲ�Ǽ�⻪���䡣\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
