// qimeigun.c ��ü��
// modified by xingyun 22/5/2001
#include <weapon.h>
inherit CLUB; 

void create()
{
        set_name("��ü��" , ({ "qimeigun" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ü�������ֵ��Ӷ�Я�������߽�����\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_club(100, TWO_HANDED);
        setup();
}

