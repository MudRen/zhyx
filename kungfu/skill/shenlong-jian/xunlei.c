//xunlei.c Ѹ�׽�

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
          int speed, attack, lv, damage;

           lv = (int)me->query_skill("shenlong-jian", 1); 
           damage = lv + random(lv/2) + (int)me->query_skill("sword",1);
                      attack = lv + random(lv/2);
                         speed = me->query_skill("sword")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
             return notify_fail("��Ѹ�׽���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("xunlei_yushi")|| me->query_temp("xunlei"))
             return notify_fail("�㽣��δ����������ʩչ��Ѹ�׽�����\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
             return notify_fail("��ʹ�õ��������ԡ�\n");

          if( (int)me->query("neili") < 300 )
             return notify_fail("�������������\n");

        if( me->query_skill("shenlong-jian", 1) < 100 )
             return notify_fail("��ġ�����������δ�����磬�޷�ʹ�á�Ѹ�׽�����\n");
        if ((int)me->query_skill("shenlong-xinfa", 1)<100
             && (int)me->query_skill("busi-shenlong", 1)<100) 
             return notify_fail("��������ڹ��ķ�����ȷ�����߹�������������ʹ�á�Ѹ�׽�����\n"); 

        if ( me->query_skill_mapped("force") != "shenlong-xinfa" 
             && me->query_skill_mapped("force") != "busi-shenlong") 
             return notify_fail("��û������������ϵ���ڹ���\n"); 

        msg = HIR "\n$N����"+weapon->query("name")+HIR"����ָ���Լ��ؿڣ�����бб���⣬����֮�������ƻؽ�����һ�㣡\n\n" NOR;
        message_vision(msg, me,target);
        me->start_busy(1);
        ob = me->select_opponent();
        me->set_temp("xunlei",4);
          me->add("neili", -5);
        me->set_temp("xunlei_yushi");
        call_out("checking", 1, me, target);
        return 1;
}


  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
        if ( !objectp( me ) ) return;
        weapon = me->query_temp("weapon");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword") {
                tell_object(me, "\n�������޽�������ֹͣ��Ѹ�׽��ļ��ơ�\n" NOR);
                me->delete_temp("xunlei");
                return;
        }
        else if ( weapon->query("weapon_prop") == 0 ) {
                tell_object(me, "\n���"+weapon->name()+"�ѻ٣��޷�����Ѹ�׽��Ĺ��ƣ�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
          else if ( (int)me->query("neili") < 300  ) {
                  message_vision(HIR"$N���ھ�������������ò�ֹͣѸ�׽��Ĺ��ƣ�\n" NOR, me,target);
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
        else if ( me->query_skill_mapped("sword") != "shenlong-jian" ) {
                tell_object(me, HIR "\n��ת��ʩչ�����������޷�����Ѹ�׽����У�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
        else if ( me->is_busy() ) {
                tell_object(me, HIR "\n�����ڶ����������޷�����ά��Ѹ�׽����ƣ�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
        else if (!me->is_fighting() || !objectp(target)) {
                tell_object(me,  "\n������û�к��˹��У������ջ���Ѹ�׽��Ĺ��ơ�\n" NOR);
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
        if( environment(target) != environment(me) ) {
                tell_object(me, "����Է��Ѿ������������ֹͣ��Ѹ�׽��Ĺ��ơ�\n");
                    call_out("xunlei_end", 6, me);
                me->delete_temp("xunlei");
                return;
        }
        else{
                  me->add_temp("apply/speed", speed*3);
            me->add_temp("apply/damage", damage*2);
              me->add_temp("apply/attack", attack*2);

        if ( me->query_temp("xunlei") ==4 )message_vision(HIY"\n$N�����ǰ��"+weapon->name()+HIY"��Ȼ���䵯��������ֱ��$n������֮������Ϊ�κν�����������\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==3 )message_vision(HIW"\n$N��ָ��"+weapon->name()+HIW"��һ�����������ˣ�����������"+weapon->name()+HIW"�������������������޷���\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==2 )message_vision(HIG"\n$N��Ȼ����һ����"+weapon->name()+HIG"�Ϻ����������ȵ�����"+target->name()+HIG"����С���ˣ���\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==1 )message_vision(HIR"\n����$N���ֻӽ���"+weapon->name()+HIR"������ǰ�����ң�˲Ϣ֮���ѹ���������һʮ���У�\n" NOR, me,target);
            me->add("neili", -30);
                me->start_busy(1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

                 me->add_temp("apply/speed", -speed*3);
              me->add_temp("apply/damage", -damage*2);  
             me->add_temp("apply/attack", -attack*2);
        if ( me->query_temp("xunlei") ==1 ) {
        message_vision(HIY "\n$N˳��Ȧת����"+weapon->name()+HIY"��һʮ���֡�Ѹ�׽�����Ȼ����ʹ����\n" NOR, me, weapon);
                    call_out("xunlei_end", 12, me);
        me->start_busy(2);
        }
        else {
           me->set_temp("xunlei_attack");
        me->set_temp("xunlei", me->query_temp("xunlei")-1);
        call_out("checking", 1, me, target);
           }  
        }


}  
void xunlei_end(object me)
{
        object weapon;
        if ( !objectp( me ) )
                return;
        weapon = me->query_temp("weapon");

        tell_object(me, HIR "\n�㰵�Ե�Ϣ������ƽ����ӿ��������\n\n" NOR);

        me->delete_temp("xunlei");
        me->delete_temp("xunlei_yushi");

}

