#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIW "�׻���" NOR, ({ "tiger vein", "vein" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ���׻�������¼�Ʒ�����亱�С����Խ���ϵ(wear)�����䡣\n" NOR
                            HIC "��Ч�м�������+ 10        ��Ч�Ṧ������+ 10\n" NOR
                            HIC "����Ч��������+ 3%        ����Ч���ȼ���  10\n" NOR
                            HIC "�����ر�������+ 2%\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 2);
                set("armor_prop/reduce_poison", 3);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "����ذ�$n"
                    HIC "ϵ�����䡣\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
