// hupo-milijiu.c ���������
// By Alf, Last Update 2001.11

#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
    set_name(HIY"���������"NOR, ({"hupo milijiu", "milijiu", "jiu"}));
    set_weight(700);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long",
        "���������������ɽ������������ȡѩɽ����\n"
        "������������ɡ��˾���ɫ��ƣ�����΢��\n"
        "��ԣ������˱ǡ�\n");
        set("unit", "��");
        set("value", 200);
        set("max_liquid", 20);
    }

    set("liquid",
    ([
        "type": "alcohol",
        "name": HIY"���������"NOR,
        "remaining": 20,
        "drunk_apply": 20,
    ]));
}


