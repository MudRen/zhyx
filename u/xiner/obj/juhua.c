#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(MAG "Ұ�ջ�" NOR, ({ "ye juhua", "juhua" }));
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
		set("value", 100);
                set("long",HIG "һ����Ѽ�����Ұ�ջ��������Ѿ���ժ�����ܳ�ʱ������Ȼ��һ�ɵ�������ζ��\n" NOR);
                set("unit", "��");
                set("material", "wood");
        }
        setup();
}       


