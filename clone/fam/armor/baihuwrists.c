#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIW "�񻢻���" NOR, ({ "baihu huwan", "huwan", "baihu" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ˫�ð׻��ǺͰ׻�Ƥ���ɵĻ���\n" NOR
                            HIC "��Ч�м�������+ 10       ��Ч�Ṧ������  + 5\n" NOR
                            HIC "����Ч��������+ 5%       ����Ч���ȼ���   10\n" NOR
                            HIC "�����ر�������+ 5%\n" NOR);
                set("unit", "˫");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIW "$N" HIW "����ذ�$n"
                    HIW "���������ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n"
                    HIC "��������ȡ��������\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
