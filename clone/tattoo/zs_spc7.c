#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "��ʿ��˫ͼ" NOR, ({ "wushuang tu", "wushuang", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "��˫��ʿ����ս�ĺ���ƽ������");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����", "����", "����" ,"��" }));
                set("tattoo_int", 2);
                set("tattoo_con", 2);
                set("tattoo_str", 2);
                set("tattoo_dex", 2);
                set("tattoo_special", "shuang");
                set("tattoo_spcname", "��ʿ��˫");
        }
}
