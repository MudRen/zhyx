// liumang.c ��å��ȭ
// By Alf, Last Update 2001.11

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg;

        if(!target) target = offensive_target(me);

        if(!target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("��ֻ����ս����ʹ����һ���С�\n");

    if((int)me->query_skill("liumang-shenquan", 1) < 80)
                return notify_fail("�����å��ȭ���������죬�޷�ʹ����һ���С�\n");

        if((int)me->query("neili") < 200)
                return notify_fail("���������Ϊ�������ߡ�\n");

        msg = HIG"$N�������˿��������˵����Ȼ������һ����ȣ�\n"NOR;
        msg += HIC"
I@@L      @@@@       I@@@ ezz,_zzzzzz_     @@@L     I@@I       zzzL  @@@' Izzz  
`@@@_I--zz@@~~-----  I@@@ I@@I     I@@I    `~~~ ezz_a@@bzz_,   `~~~,I@@@ I~~~'  
 `~~~ _@@@' `-@@L   zzzzzzI@@I     I@@I  '~~@@@ I@@'I@@II@@I  ~~~~~=@@@~~~~~~~~'
I@@L I@@@_____@@@L   @@@  I@@M~~@@@@~~     I@@P I@@ I@@II@@I ~~~~@@@@~~~-@@@~~~~
`-@@_ =@@~=== _=@~'  @@@  I@@I  I@@I      I@@@@bI@@~@@@@-@@I  ._a@@@=__d@@@@@L, 
  ==='I@@ I@@ @@@    @@@  I@@I--I@@I---  I@@@@M@a@@ I@@II@@I '~~~'   I@@I  ~~~~'
 d@@' I@@ I@@ @@@    @@@  I@@I  I@@L       I@@I I@@_I@@II@@P  `~~~~~~I@@I~~~~~' 
I@@@  I@@ I@@ @@@ .  @@@  I@@I  I@@I  _    I@@I '~~'I@@I~~'  ~~~~~~~~@@@@~~~~~~~
I@@I  a@@ I@@ @@@_%  ~-@bz`@@@zz-I@@zd~    I@@I     I@@I        I-z_z@@@P       \n"NOR;

        msg += HIY"\n����ȭ�����������缱������һ�㣬��ֱ����$n���ظ�Ҫ��������\n"NOR;  

        if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2)
        { 
                me->start_busy(2+random(2));
                target->start_busy(4);

                damage = (int)me->query_skill("liumang-shenquan", 1)/3+(int)me->query_skill("unarmed",1)/3;
                damage = damage + random(damage);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                me->add("neili", -200);
                msg += HIR"$n�����������꣬��Ȼ��֪���ܣ���$N�������ػ�ʵ�����ɵó����Һ���\n"NOR;
        }

        else
        {
                msg += YEL"$n��æ����б�ˣ�һ���͵�ʮ�˹����Ǳ���״�Ķ㿪��$N���С�\n"NOR;
                me->start_busy(1);
        }

        message_vision(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        if(userp(target)) target->fight_ob(me);
        else if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}


