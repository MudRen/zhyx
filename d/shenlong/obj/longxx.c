#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("������", ({"long xianxiong" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��������,��������Ч���ܺá�\n");
                set("value", 1000);
        }
        setup();
}

int do_effect(object me)
{
        return notify_fail("�������������㲻�ܳԡ�\n");
}
