// light.c

#include <ansi.h>

inherit F_SSERVER;

int bbqthem(object me, object obj);
int perform(object me, object target)
{
        int lvl,i;
        object env, *inv;
        string *can_perform;

        can_perform = me->query("can_perform/martial-cognize");

        if(!can_perform || 
           !arrayp(can_perform) || 
           !sizeof(can_perform) || 
           member_array("light",can_perform) == -1)
                return notify_fail("�㻹û��ѧ��ʹ�ã�����֮��ݣ�\n");

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮�⡣\n");

        lvl = (int)me->query_skill("martial-cognize",1);

        if (lvl < 250)
                return notify_fail("�����ѧ������Ϊ������\n");

        if( me->query("jingli") < 500 )
                return notify_fail("��ľ���������\n");

        if( me->query("max_jingli") < 1000 )
                return notify_fail("��ľ�����û�дﵽ�㹻�Ĳ�Σ�\n");

        if( me->query("jing") <= 300 )
                return notify_fail("��ľ���״�����ã�\n");

        if (environment(me) && environment(me)->query("no_fight"))
                return notify_fail("���ﲻ��ʹ�ã�����֮���!\n");

        me->add("jingli", -400);
        me->receive_damage("jing", 250);

        message_vision(HIY "$N��Ȼ������һ�����춯�ص�ŭ����������������峺������������\n" NOR, me);

        if ( lvl <= random(500) )
        {
                env = environment(me);
                inv = all_inventory(env);
                for(i=0; i<sizeof(inv); i++) 
                {
                        if( inv[i]==me ) continue;
                        if( inv[i]->is_corpse() ) continue;
                        if( !inv[i]->is_character()) continue;
                        if (userp(me) && 
                            userp(inv[i]) && 
                            !inv[i]->is_want_kill(me->query("id")))
                                me->want_kill(inv[i]);
                        me->kill_ob(inv[i]);
                        if (living(inv[i]) && ! userp(inv[i]))
                                inv[i]->kill_ob(me);
                        else
                                inv[i]->fight_ob(me);
                }
                me->start_busy(5);
                return notify_fail("����Ϊ��ѧ��������������ʧ���ˣ�\n");
        }
        message_vision(HIR "������$N�û���һ��ģ������Ӱ��ȫ�����ǧ������ȵ�Ѫ���â������\n" NOR, me);
        env = environment(me);
        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
                if( inv[i]==me ) continue;
                if( inv[i]->is_corpse() ) continue;
                if( !inv[i]->is_character()) continue;
                bbqthem(me, inv[i]);
        }
        me->start_busy(5);
        return 1;
}

int bbqthem(object me, object obj)
{
        int magic;
        string msg;
        magic = (int) me->query_skill("martial-cognize",1)*5;  
        message_vision(HIR "\n���ȵĺ��������������$N��\n" NOR, obj);
        obj->receive_wound("jing", magic*2/3, me);
        if(obj->is_ghost()) 
        {
                message_vision(YEL "$N�ҽ���һ������Ϊ�˻ҽ���\n" NOR, obj);
                obj->die();
                return 1;
        }
        magic = random(magic) + magic;
        if (!wizardp(obj))
        {
                if (!obj->query("env/invisible"))
                {
                        obj->receive_damage("qi",magic,me);
                        obj->receive_wound("qi",magic*2/3,me);
                }
                else
                {
                        obj->receive_wound("jing",magic/2,me);
                        obj->receive_damage("qi",magic*2,me);
                        obj->receive_wound("qi",magic*4/3,me);
                }
                msg = obj->name() + COMBAT_D->status_msg(obj->query("qi") * 100 / obj->query("max_qi"));
                message("vision",msg,environment(obj));
                if (userp(me) && 
                    userp(obj) && 
                    !obj->is_want_kill(me->query("id")))
                        me->want_kill(obj);
                me->kill_ob(obj);
                if (living(obj) && ! userp(obj))
                        obj->kill_ob(me);
                else
                        obj->fight_ob(me);
                obj->start_busy(2);
        }
        return 1;
}
