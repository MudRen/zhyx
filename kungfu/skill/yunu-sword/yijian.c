// yijian by snowyu, 2002/4 snowyu
/*
  �����˳���ʹ���˷���ͻȻ��һ����Х��������˸������
Χ���������Χ���̣�������裬���˿����۶����ˡ��͵���
��һ��ͦ����ֱ��������Ŀڣ������ǽ������磬�������ס�
   ������������ǰ���ͣ�����������������������
�ţ��ۼ���һ�����������϶Դ�������ֱû������
*/

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string weapon;
        int damage, dodge_skill, str, lvl1, lvl2, lvl3, lvl4, ap, dp;
        mapping myfam;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HIY "������һ����ֻ�ܶ�ս���еĶ���ʹ�á�\n"NOR);

        if (userp(me) && me->query("family/family_name") != "��ɽ��")
                return notify_fail(HIY "��ǻ�ɽ���ӣ�����ʹ�û�ɽ������\n"NOR);

        if( me->query_temp("yijian",1) )
                return notify_fail(HIY "���ʹ�ù�������һ������ʵ����̫ƣ���ˣ��ȵ����ðɣ�\n"NOR);

        if( userp(me) && me->query_skill_mapped("force") != "zixia-shengong" )
                return notify_fail(HIY "�����õĲ�����ϼ�񹦣��޷�ʩչ������һ������\n"NOR);
                
        if( userp(me) && (lvl1 = me->query_skill("zixia-shengong", 1 )) < 200 )
                return notify_fail(HIY "�����ϼ�񹦻��δ�����޷�ʩչ������һ������\n"NOR);

        if( (lvl2 = me->query_skill("yunu-sword", 1)) < 200 )
                return notify_fail(HIY "�����Ů����ʮ������Ϊ���㣬������ʹ�á�����һ������\n"NOR);

        if( me->query("neili") <= lvl2*3 )
                return notify_fail(HIY "�����������ʹ�á�����һ������\n"NOR);

        if( me->query("jingli") <= lvl2 )
                return notify_fail(HIY "��ľ�������ʹ�á�����һ������\n"NOR);
        
        lvl3 = (target->query_skill("dodge",1) );
        lvl4 = (target->query_skill("force",1) );

        ap = lvl1 + lvl2 + me->query("kar")*30;
        dp = lvl3 + lvl4 + target->query("kar")*30;

        ap = ap/100;
        dp = dp/100;

        weapon = me->query_temp("weapon");
                
        dodge_skill = target->query_skill_mapped("dodge");

        message_vision(HIY "$NͻȻ��һ����Х��"+ weapon->name() +HIY"������˸������Χ��$n��Χ���̣���â����,�͵���$Nһ��ͦ��\n\n"NOR, me, target);
        message_vision(HIY "ֱ��$n�Ŀڣ������ǽ������磬�������ס������ǽ������磬�������ס���\n\n"NOR, me, target);

        if( me->query_temp("powerup") ) // Ϊ�Ժ�����ϼ����׼��
                message_vision(MAG "$N����ϼ�񹦷��ӵ����£�ֻ��������ԴԴ���ϵ����͵��������Ͻ�������Ѹ���׿���硣\n\n"NOR, me, target);

        me->add("neili" , -(lvl1+lvl2)/3);
        me->add("jingli", -(lvl1+lvl2)/6);

        me->set_temp("yijian",1);
     
        call_out("delay",2000/(lvl1+lvl2),me);

        me->add_temp("yijian",1);

        if (random(ap) < dp && living(target)) {
                message_vision(WHT "$n��״�󾪣���Ҫ�����ʹ˽�Ю�׵�֮����Ȼ�̵���ǰ��������ȫ��ʩչ"+ to_chinese(dodge_skill) +"�ſ����������һ����\n\n" NOR, me,target);
                me->start_busy(3+random(3));
                return 1;
        }

        if (random(ap) > dp*2/3 || !living(target)) {
                damage=(me->query_str()+me->query("jiali")/10)*lvl2/100*random(10);
                                
                me->add("neili" , -(lvl1+lvl2)/3);
                me->add("jingli", -(lvl1+lvl2)/6);
                
                if (damage >= target->query("eff_qi")) {
                        message_vision(HIR "$N������ǰ���ͣ�"+ weapon->name() +HIR"����������$n�����ţ�$nһ���ҽ���һ������$n��ǰ������ֱû��������\n\n" NOR, me,target);
                        target->receive_damage("qi",1,me);
                        target->die();
                        return 1;
                }
                if (damage >= target->query("eff_qi")/2)
                        message_vision(HIR "$næ�������㣬�����Ǳ�$N�������������������ˣ�ֻ�����͡���һ��û���ؿڣ���Ѫ��Ȫӿ���������\n\n" NOR, me,target);

                if (damage < target->query("eff_qi")/2)
                        message_vision(HIR "��һ���Ƶ�֮�������˵��Ƿ�����˼��ֻ�������һ����$n�ѱ��������ţ���Ѫ��Ȫӿ�������\n\n" NOR, me,target);

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi", random(damage), me);
                str = COMBAT_D->status_msg((int)target->query("eff_qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                return 1;
        }

        if (random(ap) > dp/3)
        {
                damage=me->query_str()*me->query("jiali")/target->query_con();
                if (damage<=100) 
                        message_vision(WHT "$n����һ���������ͣ���æ�ܿ�,�����ŵ�һ���亹��\n\n" NOR, me,target);
                else {
                        message_vision(WHT "$n��֪��һ���������������㡣��Ȼ�ܹ�������һ��������$N��һ��������"+MAG"��ϼ��"NOR+WHT"��������$n�ؿڻ���һ���˿ڡ�\n\n" NOR, me,target);
                        target->receive_damage("qi",damage,me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                }
                target->start_busy(3+random(3));
                me->add("neili" , -(lvl1+lvl2)/3);
                me->add("jingli", -(lvl1+lvl2)/6);
                return 1;
        }
}

int delay(object me)
{
        me->delete_temp("yijian");
        return 1;
}

