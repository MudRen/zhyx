#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name( WHT"��"NOR+CYN"��"NOR+HIW"ذ��"NOR,  ({ "bi shou", "sword", "jian" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ�����������ذ�ף������ޱȡ�\n");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_put", "�����������ܷ����Ƕ���\n");
                set("no_steal", "�������������뿪�Ƕ���\n");
                set("no_beg", "�������������뿪�Ƕ���\n");
                set("no_sell", "��������֪�����񽣵�������\n");
                set("value", 100000);
                set("material", "gold");
                set("wield_msg", HIR"$N���һ���������˵�"NOR+WHT"��"NOR+CYN"��"NOR+HIW"ذ��"NOR+HIR"�������У�ֻ�е�һ��"NOR+HIW"����"NOR+HIR"���������\n"NOR);
                set("unwield_msg", HIR"$N�����е�"NOR+WHT"��"NOR+CYN"��"NOR+HIW"ذ��"NOR+HIR"���ѥ�С�\n"NOR);
        }
        init_sword(200);
        setup();
}


