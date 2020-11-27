//caipiao.c
//By haiyan

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "��Ʊ" NOR, ({ "cai piao", "piao", "lottery" }));
        set_weight(10);
        set("long", @LONG
����һ�š���̶���ʡ��н�������Ʊ������ʹ��tianxieָ������д��Ʊ��
LONG);

        set("unit", "��");
        set("value", 0);
        set("lottery", 1);

        setup();
}

void init()
{
        add_action("do_tianxie", "tianxie");
}

int do_tianxie(string arg)
{
        object me = this_player();
        string cost;
        string *numbers;

        if (! arg || ! sscanf(arg, "%s", cost))
                return notify_fail("ָ���ʽ��tianxie <��λ����>��\n");

        if (strlen(cost) != 5 || cost[0..0] < "0" || cost[0..0] > "9" ||
            cost[1..1] < "0" || cost[1..1] > "9" ||
            cost[2..2] < "0" || cost[2..2] > "9" ||
            cost[3..3] < "0" || cost[3..3] > "9" ||
            cost[4..4] < "0" || cost[4..4] > "9")
                return notify_fail("����ĺ�������\n");

        numbers = query("caipiao/numbers");
        if (! numbers)    numbers = ({});

        if (sizeof(numbers) >= 10)
                return notify_fail("���Ų�Ʊ���Ѿ������ˡ�\n");

        numbers += ({ cost });
        tell_object(me, sprintf("���ڲ�Ʊ��%s��������%s�������֡�\n", 
                    chinese_number(sizeof(numbers)), cost));
        set("caipiao/numbers", numbers);
        return 1;
}

