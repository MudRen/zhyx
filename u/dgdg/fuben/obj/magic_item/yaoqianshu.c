// �Ϲ�ʮ������֮ ҡǮ�� 
// ��ʹ������
// Create by Rcwiz for Hero.cn 2003/08

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "ҡǮ��" NOR, ({ "yaoqian shu", "yaoqian", "shu" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");               
                set("long", NOR + YEL "����һ��ҡǮ�����а��˸ߣ���֧�Ϲ����˸���\n"
                                      "����ͭǮ��\n"
                                      "���Խ����ϵ�Ǯ��ҡ(yao)������\n" NOR);                
        }
        setup();
}

void init()
{
        add_action("do_yao", "yao");
}

int do_yao(string arg)
{
        object me, g;
        int i;
        
        me = this_player();
        
        if(! objectp(present("yaoqian shu", me)))return 0;

        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
       
        if (this_object()->query("count") >= 3)
                 return notify_fail("���ҡǮ���Ѿ�������ҡ���κζ����ˣ�\n");

         message_sort(NOR + YEL + "\n$N" NOR + YEL "˫�ֱ���ҡǮ��ʹ����ҡ���ţ�"
                      "һʱ�䣬����Ԫ���׷����ڵ��ϣ����������������Ȼ�Ķ���\n" NOR, me);

        i = 500 + random(500);
        g = new("/clone/money/gold");
        g->set_amount(i);
        g->move(environment(me));

        this_object()->add("count", 1);
        if (this_object()->query("count") >= 3)
        {
        	tell_object(me, HIG "������һ����â������ҡǮ��������£���ʧ�ˣ�\n" NOR);
        	destruct(this_object());
        }
        
        return 1;
}
