#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "������̬ͼ" NOR, ({ "baitai tu", "baitai", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "ܿܿ������������̬�����ڴ�ͼ�С�");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����" }));
                set("tattoo_int", 4);
                set("tattoo_special", "selfstudy");
                set("tattoo_spcname", "��ʦ��ͨ");
        }
}
