// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;

        if (me->is_chatter())
                return 0;

        if (environment(me)->query("no_fight")
             || environment(me)->query("no_fight1") )
                return notify_fail("���ﲻ׼ս����\n");

        if (! arg || ! objectp(obj = present(arg, environment(me))))
                return notify_fail("���빥��˭��\n");

        if (! obj->is_character())
                return notify_fail("�����һ�㣬�ǲ����������к��Ķ���\n");

        if (! living(obj))
                return notify_fail("�㻹Ҫ�򣿲���ɱ�����ˡ�\n");

        if (obj->is_fighting(me))
                return notify_fail("���ͣ����ͣ����ͣ�\n");

        if (obj == me)
                return notify_fail("���Լ�������ô�벻����\n");

       if ( me->query("special_skill/lonely") )
       {
           if (me->query_condition("killer") && obj->is_player())
           return notify_fail("�������ǹٸ�׽�õ�Ҫ����������Σ�\n");
       }
       else
     /*  if (obj->is_player() && me->query("quest_count") < 300 )    
           return notify_fail("���300�������������Ϯ��һ����ҡ�\n"); 
       if (obj->is_player())  return notify_fail("Ŀǰ����ʱ�ڣ���ʱ�ر�PK��\n"); */ 


        if ((int)obj->query_condition("die_guard"))
                return notify_fail("����������ٸ��������أ����Ǳ�ȥ���ǡ�\n");


        if ( obj->query("age") < 30 && ( obj->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("�������������������δ���꣬���Ǳ�ȥ���ǡ�\n");

        if ( obj->is_player() && me->query("age") < 30 
             && ( me->query("special_skill/emperor")
             || obj->query("special_skill/queen") ) )
                return notify_fail("���ڳ���֮ǰ����Ϯ�����!\n");


        if (me->query("qi") < me->query("max_qi") * 3 / 10)
                return notify_fail("������û������ս���ˡ�\n");

        if (obj->query("can_speak"))
                message_vision(HIW "\n$N" HIW "����$n" HIW "���һ��������"
                               "�У�\n\n" NOR, me, obj);
        else
                message_vision(HIW "\n$N" HIW "���һ������ʼ��$n" HIW "��"
                               "��������\n\n" NOR, me, obj);

        notify_fail("���޴����֡�\n");
        switch (obj->accept_hit(me))
        {
        case 0:
                return 0;
        case -1:
                return 1;
        default:
        }

        me->fight_ob(obj);
        if (obj->query("can_speak"))
        {
                me->want_kill(obj);
                obj->fight_ob(me);
        } else
                obj->kill_ob(me);

        return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : hit <����>
 
���ָ������ֱ����һ��������С���������ʽ��ս���Ǽ�ʱ�ģ�ֻҪ���һ
��������ս���ͻῪʼ��ֱ��ĳһ������50% ����Ϊֹ�����ָ�����Щ��
ϲ��fight��NPC�����ã���Ϊ�ܶ�ʱ����ı���Ҫ��ᱻ�ܾ�������ʹ�������
���п����⵽NPC ��ǿ�ҷ�Ӧ������ҪС��ʹ�á�
 
�������ָ��: fight, kill

HELP
    );
    return 1;
}


