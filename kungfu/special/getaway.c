// getaway.c  ����ѿ�
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "����ѿ�" NOR; }

int perform(object me)
{        	
        int lvl;

        if (! me->query("reborn"))        
            return notify_fail("����δת���������޷�ʹ�ô˼��ܣ�\n");
        if ( ! me->is_busy())
            return notify_fail("����������ʹ�ô����ؼ���\n");
        if ( ! me->is_fighting() )
            return notify_fail("����ѿ�ֻ����ս����ʹ�ã�\n"); 

        if ( time() - me->query("la_sp_tm/getaway") < 2 )        
            return notify_fail("��ո��ù��˼��ܣ���Щʱ�����ðɣ�\n");

        me->set("la_sp_tm/getaway", time());        

        lvl = me->query_int();
        if ( lvl < me->query_dex() ) lvl = me->query_dex();

        if (random(100 - lvl) == 0)
        { 
            message_vision(HIG "\n$N" HIG "��Ȼ����һ��Ť����"
                           "��ʱ�ж����硣\n\n" NOR, me);
            me->interrupt_me();
        } else
            message_vision(CYN "\n$N" CYN "��ͼ�������ƣ�"
                           "���Ǻ������á�\n\n" NOR, me);   
       return 1;
}

