// �Ϲ�ʮ������֮ �̹Ÿ� 
// Create by Rcwiz for Hero.cn 2003/08

#include <ansi.h>

#include <weapon.h>
inherit HAMMER;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + WHT + "�̹Ÿ�" NOR, ({ "pangu fu", "pangu", "fu" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", NOR + WHT "����һ�Ѿ޴�ĸ�ͷ��������ѣĿ�Ĺ⻪����˵\n"
                                      "�˸����̹ſ���ٵ�ʱ�ٿ��������ʱ���á�\n"
                                      "����֮���ٿ�(pi)̫�飬����̫�龳�硣\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + WHT "$N" NOR + WHT "���̹Ÿ��������У�����"
                                           "�̹����֣��������ݡ�\n" NOR);
                set("unwield_msg", NOR + WHT "$N" NOR + WHT "�������̹Ÿ��ջء�\n" NOR);
                set("stable", 100);

        }
        init_hammer(400);
        setup();
}

void init()
{
        add_action("do_pi", "pi");       
}

int do_pi(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("pangu fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
        
        if (! environment(me)->query("outdoors"))
                 return notify_fail("����ȵ�����ȥ��\n");
                 
        message_sort(NOR + WHT + "\n$N" NOR + WHT "˫�ֻ��������е��̹ž޸����������£�"
                     "ɲ�Ǽ������¶��һ���Ѻۣ��̹Ÿ�����һ������Ĺ�â��$N" NOR + WHT +
                     "���̫��֮�С�\n" NOR, me);
                
        me->move("/kungfu/class/sky/taixu");
        destruct(this_object());

        return 1;
}
