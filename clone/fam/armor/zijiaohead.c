#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(NOR + MAG "����ͷ­" NOR, ({ "yanlong shenguan", "shenguan", "yanlong" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "һ���������Ǻ�����Ƥ�����ɵ�����ģ��ͷ�ڡ�\n" NOR
                            HIC "��Ч�м�������+ 10       ��Ч�Ṧ������  + 5\n" NOR
                            HIC "����Ч��������+ 5%       ����Ч���ȼ���   10\n" NOR
                            HIC "�����ر�������+ 5%\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", NOR + MAG "$N" NOR + MAG "����ذ�$n"
                    NOR + MAG "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
