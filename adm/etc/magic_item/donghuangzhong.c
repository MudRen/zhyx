// �Ϲ�ʮ������֮ ������
// Create by Rcwiz for Hero.cn 2003/09
// �� /d/songshan/fengchangtai.c���Դ����֮��

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIC "������" NOR, ({ "donghuang zhong", "donghuang", "zhong" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIC "����һ�ڿ�����ͨ�Ĺ��ӣ�ȴ��һ���������������ǡ�\n"                                
                                "����֮����(qiao)���֮�ţ�����ͨ���š�\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_qiao", "qiao");
}

int do_qiao(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("donghuang zhong", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");

        if (environment(me)->query("short") != "����̨")
                 return notify_fail("��õ�����̨���ܴ����֮�š�\n");

        message_sort(HIC "\n$N" HIC "�������ӷ��ڵ��ϣ�Ȼ������һ�ã�ֻ"
                         "����һ�����죬ɲ�Ǽ䣬��ʳ���һ����ɫ֮�ţ���"
                         "����ǧ�����Ŀ�Ĺ⻪�������ӽ�$N" HIC "���˽�"
                         "ȥ ����\n" NOR, me);

        me->move("/kungfu/class/sky/tianmen0");
        destruct(this_object());

        return 1;
}
