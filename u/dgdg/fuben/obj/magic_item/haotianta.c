// �Ϲ�ʮ������֮ �����
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "�����" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIM "����һ��ӵ�����ǻ���֮���ı�������ʱ�ش���Ͷ���\n"
                                "����Ĺ�â��\n"                                
                                "�����ͨʮ������ﵽ��������ܽ��ø���֮������������\n" NOR);

        }
        setup();
}
