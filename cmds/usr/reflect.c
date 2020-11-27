// reflect.c
// ڤ˼ָ���ȡ���������Ǳ��
// ��Աר��ָ�� Create by Rcwiz for HERO.CD

#include <ansi.h>
#define MEMBER_D     "/adm/daemons/memberd"

inherit F_CLEAN_UP;

void end_reflect(object me)
{
         int exp, pot;

         if (me->query_temp("reflect"))
         {
               message_vision(HIY "$N" HIY "ڤ˼��ϣ������������۾����ƺ���������\n" NOR, me);
 
               me->delete_temp("reflect");

               exp = me->query("combat_exp");               
               exp /= 50000;
               pot = exp / 5;

               exp = exp + random(exp / 2);
               pot = pot + random(pot / 2);

               me->add("combat_exp", exp);
               me->add("potential", pot);

               write(HIG "ͨ�����ڤ˼��������" HIC + chinese_number(exp) + HIG 
                     "��ʵս�����" HIC + chinese_number(pot) + HIG "��Ǳ�ܡ�\n");

         }

         if (me->is_busy())me->start_busy(1);
         return;
}

int main(object me)
{
         object ob;


         if (me->is_busy() || me->is_fighting())
                 return notify_fail("����æ����˵�ɣ�\n");

         if (me->query_temp("reflect"))
                 return notify_fail("������ڤ˼��\n");

         if (! wizardp(me) && ! MEMBER_D->is_valib_member(me->query("id")))
                 return 0;

         if (! me->query("doing"))
                 return notify_fail("ֻ�мƻ�ʱ����ڤ˼��\n");

         if (me->query("combat_exp") < 1000000)
                  return notify_fail("��ʵս���飬�޷�ڤ˼��\n");

         if (me->query_skill("martial-cognize", 1) < 160)
                  return notify_fail("����ѧ�������㣬�޷�ڤ˼��\n");
 

         me->set_temp("reflect", 1);

         me->start_busy(30);

         me->start_call_out((: call_other, __FILE__,
                             "end_reflect", me:), 28 + random(6));

         message_vision(HIY "$N" HIY "��ϥ��������Ŀڤ˼ ����\n" NOR, me);

         return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : reflect

��ָ������ڼƻ�ʱʹ����������������Ǳ�ܡ�
��ָ��ֻ�޻�Աʹ�á�

HELP
);
    return 1;
}
 
