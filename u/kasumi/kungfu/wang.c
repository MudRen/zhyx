// wang.c ��Ů�����ľ�
// looo/2001/6/23
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);



int exert(object me, object target)
{
        string msg;
		string picture;

		string *pictures=({
  HIY"��˼��"YEL"���"HIC"������"HIR"���¡�"HIB"���"MAG"��Ц"HIW,
  YEL"�ٳ"CYN"���֡�"HIG"��ϲ��"HIR"��ŭ��"HIY"�ٺá�"RED"�ٶ�"HIW,
  HIC"��˼"HIG"��"HIW"�񵡣�"HIB"����"MAG"��"HIY"��ɢ"HIW,
  HIR"����"YEL"��"BLU"����"MAG"����"RED"��"HIG"��ƣ"HIW,
  HIB"����"CYN"��"RED"���٣�"HIR"��Ц"HIC"��"BLU"����"HIW,
  MAG"���"YEL"��"HIR"���壬"RED"����"BLU"��"HIY"����"HIW,
  HIW"��ϲ"HIG"��"HIY"����"MAG"���ң�"HIC"��ŭ"HIR"��"HIB"����"HIG"����"HIW,
  HIG"���"RED"��"BLU"ר��"HIG"���Σ�"HIW"���"HIB"��"MAG"����"CYN"����"HIW
});

        int skill;

        if( target != me )
                return notify_fail("��ֻ�������Լ���ս������\n");

		if (userp(me) && ! me->query("can_perform/yunv-xinjing/wang"))
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");


        if (me->query("gender") == "����")
                return notify_fail("Ů���ҵ��������������ף�\n");


        if (me->query("neili") < 200)
                return notify_fail("�������������\n");

        if (me->query_temp("wang"))
                return notify_fail("���Ѿ����롸"HIW"����"NOR"���ľ����ˡ�\n");

        if (me->query_skill("yunv-xinjing",1) < 200)

                return notify_fail("�����Ů�ľ����������졣\n");

        
       skill = (int) ( me->query_skill("force") + me->query("per") * 20 ) / 5;
       

       picture = pictures[random(sizeof(pictures))];

       message_vision(HIW "$N" HIW "��Ȼ���ף�������������ˮ������Ĭ�"+picture+ "������Ů�ľ���Ҫ����������������龳�硣\n" NOR, me);
                      
        me->add_temp("apply/sword", skill); 

        me->set_temp("wang", 1);
        me->add("neili", -100);

		me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

		if( me->is_fighting() ) me->start_busy(2);       

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("wang"))
        {
                me->add_temp("apply/sword", -amount);

                me->delete_temp("wang");
                tell_object(me, "һ����ʹ���ֹ����������ĵ����£�����֮�����.\n");
        }
}
