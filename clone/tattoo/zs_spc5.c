#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "����ս��ͼ" NOR, ({ "busi tu", "busi", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "һ������ս��ս����ͼ��");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����" }));
                set("tattoo_con", 4);
                set("tattoo_special", "nodie");
                set("tattoo_spcname", "��������");
        }
}
