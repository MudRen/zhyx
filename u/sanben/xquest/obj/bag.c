//С����
//���Ȥζ�����񱦻�ͼ����ĵ���


#include <ansi.h>
inherit ITEM;

int is_bag() { return 1; }

void create()
{
        set_name(NOR + HIY "С����" NOR, ({ "bag" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��С���������治֪������ʲô��\n");
                set("value", 0);
                set("no_drop", "�������������뿪�㡣\n");
                  set("no_put", "�������������뿪�㡣\n");
                  set("no_sell", "�������������뿪�㡣\n");
        }
        setup();
}

void init()
{
     add_action("do_open","open");
     add_action("do_bury","bury");
}

int do_open( string arg )
{

    if ( !arg || arg != "bag")
    return notify_fail("��Ҫ��ʲô��\n");

    write(HIR"���˵Ķ��������ô�򿪲�̫�ðɣ�"
             "��������ŵ��ȥ��������(bury)�ɣ�\n"NOR);
    return 1;

}

int do_bury( string arg )
{
    object me = this_player();

    if ( !arg || arg != "bag")
    return notify_fail("�㵽��Ҫ��ʲô����ѽ��\n");

    if ( me->query("xquest/kind") != "do_drawing" )
    return notify_fail("����û��Ҫ�����Ⲽ��ѽ��\n");

    if ( me->query("xquest/buried") == 1 )
    return notify_fail("����֮ǰ�����Ѿ����һ����������\n");

    if ( me->query("xquest/place2") != environment(me)->short() )
    return notify_fail("����붯���񲼰���ȴͻȻ�������ﲻ��" +
                       me->query("xquest/init_npc") + "˵�ĵط���ֻ�����ա�\n");

    message_vision(CYN "$N" CYN "�������س����������˼��£��ۼ���ûɶ��ע��\n"
                   "�漴Ѹ���ͳ�һ��С�����Ҵ�ææ���˵��\n"NOR,
                    me);
    me->start_busy(4);
    me->set("xquest/buried", 1);

    destruct(this_object());

    return 1;

}
