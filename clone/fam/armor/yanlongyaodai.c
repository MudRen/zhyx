#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIY "��������" NOR, ({ "yanlong belt", "belt", "yanlong" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "һ���ñ�������֮�����ɵ�������͸�������˾�η�Ĺ�â��\n" NOR
                            HIC "��Ч�м�������+  5        ��Ч�Ṧ������+ 15\n" NOR
                            HIC "����Ч��������+ 5%        ����Ч���ȼ���  10\n" NOR
                            HIC "�����ر�������+ 5%\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 15);
                set("armor_prop/parry", 5);
                set("wear_msg", HIY "$N" HIY "����ذ�$n"
                    HIY "ϵ�����䡣\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
