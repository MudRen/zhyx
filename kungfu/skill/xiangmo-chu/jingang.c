//by tracy 1/2002/
//xiangmo.c ��ս�ħ 
#include <ansi.h>
inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int lxbr,nec,damage,amount,quick,ap,dp;
string str = @TEXT
                                                |\
                .-':'"": - -   -  -   : -  \ (1\.`-.  
              .'`.  `.  :  :  :   :   : : : : : :  .';
             :-`. :   .  : :  `.  :   : :.   : :`.`.o ;
             : ;-. `-.-._.  :  :   :  ::. .' `. `., =  ;
             :-:.` .-. _-.,  :  :  : ::,.'.-' ;-. ,'''"
           .'.' ;`. .-' `-.:  :  : : :;.-'.-.'   `-'
    :.   .'.'.-' .'`-.' -._;..:---'''"~;._.-;
    :`--'.'  : :'     ;`-.;            :.`.-'`. 
     `'"`    : :      ;`.;             :=; `.-'`.
             : '.    :  ;              :-:   `._-`.
              `'"'    `. `.            `--'     `._;  
                        ''''   
TEXT;
        if (!target) target = offensive_target(me);
        if (!target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("����ս�ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        weapon = me->query_temp("weapon");
        if (!objectp(weapon) || weapon->query("skill_type") != "staff" )
                return notify_fail("���������ƣ���ν�ħ��\n");
        if (me->query_skill("longxiang", 1) < 150 && me->query_skill("mizong-neigong",1) < 150 )
                return notify_fail("����ڹ����δ�����޷�ʩչ��ħ������\n");
        if (me->query_skill("xiangmo-chu", 1) < 150)
                return notify_fail("��Ľ�ħ�ƻ��δ�����޷�ʩչ��ħ������\n");
        if (me->query_skill("necromancy",1) < 200)
                return notify_fail("�㽵������Ϊ��������ν������ˣ�\n");
        if (me->query("neili") <= 1000)
                return notify_fail("�����������ʹ�á���ս�ħ����\n");
        if (me->query("jingli") <= 500)
                return notify_fail("��ľ�������ʹ�á���ս�ħ����\n");
        if( me->query_temp("xiangmo_busy",1) )
                return notify_fail("������ʹ�ý����󷨣�ȴ��ôҲʹ��������\n");  
        if( target->is_busy() ) 
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n"); 
        nec = me->query_skill("necromancy",1);
        quick = (int)(me->query_skill("longxiang",1)/100);
        if (quick < 2) quick = 2;
        amount = (int)me->query_skill("staff")/4;
        if (amount < 60) amount = 60;
        if (amount > 100) amount = 100;  
        me->add_temp("apply/damage", amount);
        me->add_temp("apply/attack", amount*2);
        me->set_temp("xiangmo_busy",1);
        message_vision(HIR"\n$N�����ս���������ڲ����������ԣ�ʹ������ս�ħ���󷨡�\n"NOR,me,target);
        message_vision("$Nһ���ߺ������ζ�ת������ѩ����ɽ��\n",me,target);
        message_vision(HIW+str+NOR,me,target);
        ap = nec + quick*100+amount;
        dp = target->query_skill("force");
        damage = 0;
          if(random(ap)>dp/2 || !living(target))
          {     
                damage=me->query_skill("xiangmo-chu",1)*(random(4)+5);     
                if (damage<500) damage=500;
                if (weapon->query("id")=="xiangmo chu") damage*=3/2;              
                if (random(ap)>dp/2 || !living(target))
                {   
     message_vision(HIR"\n$n�����龰���Ѳ�֪���룬ֻ��ͷ���ۻ�����ȫ��$N������\n"NOR, me,target); 
                        target->receive_wound("qi", damage/3 + random(damage/3), me);
                        target->receive_wound("jing", damage/5 + random(damage/3), me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                        target->start_busy(2);
                }   
                else
                {                    message_vision(HIR"\n$n�����龰���������ѣ����������Ĳ�����$N�Ľ�ħ��Ӱ��\n"NOR,me,target);                       
                        target->receive_damage("jing", damage/5 + random(damage/3), me);
                        target->receive_wound("qi", damage/4 + random(damage/3), me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                        target->start_busy(random(4));
     message_vision(HIR"\n$N��$n©���������߾�����"+weapon->query("name")+HIR"��$nϮ����\n"NOR,me,target);
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                }                         
                me->start_busy(3 + random(2));
          } 
          else 
          {
     message_vision(HIR"$n�����龰��ڤ˼һ��������ʶ����$N�Ľ�ħ��Ӱ��\n"NOR, me, target);  
     message_vision("ֻ��$n���˷���������Ʈ�磬������$N�������,$N��ʱ��֪���롣\n",me,target);
                        me->start_busy(4+random(2));
          }
                 me->add_temp("apply/damage", -amount);
                 me->add_temp("apply/attack", -amount*2);
                 me->add("neili", -me->query("jiali")-500);
                 me->add("jingli", -me->query("jiajin")-400);     
                 call_out("remove_effect", random(9-quick), me);
                 if (wizardp(me)) write(sprintf("quick=%d ap=%d dp=%d damage=%d\n",quick,ap,dp,damage)); 
                 return 1;
}
void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("xiangmo_busy");
        tell_object(me, HIY"\n���ϢƬ�̣��������ֿ��շ������ˡ�\n"NOR); 
}

