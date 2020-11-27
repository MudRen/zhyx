// �Ϲ�ʮ������֮ ���ӡ
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIR "���ӡ" NOR, ({ "kongtong yin", "kongtong", "yin" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIR "�����Ϲ�����֮һ�����ӡ��ӵ����ʹ�˲��ϵ�������\n"
                                "ʹ��(use)�������һ��������һ����ò������ò�ﵽ\n"
                                "��ʮ��������䡣\n" NOR);
        }
        setup();
}

void init()
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("kongtong yin", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
                         
        message_sort(HIR "\n$N" HIR "�������е����ӡ��һ����⽫$P" HIR "���� ����\n" NOR, me);
                        
        if (me->query("per") >= 30)
        {
               me->add("mud_age", -86400);
               write(HIW "�㿴�������������ˡ�\n");
        }
        else 
        {
        	switch(random(2))
        	{
        		case 0:
        		   me->add("mud_age", -86400);
                           write(HIW "�㿴�������������ˡ�\n" NOR);
                           break;
                           
        		case 1:
        		   me->add("per", 1);
        		   write(HIG "�㿴���������ݹ�����ˣ�\n" NOR);
        		   break;
        		   
        		default: break;
        	}
        }
        me->save();

        destruct(this_object());

        return 1;
}
