// �����ϣ����ϵ�   By Gold
#include <ansi.h> 
#include <combat.h> 
        
inherit F_SSERVER; 
      
#define DAO "��" HIW "�����ϣ����ϵ�" NOR "��" 
  
int can_not_hubo() { return 1;} 
    
int perform(object me) 
{ 
    string msg; 
    object weapon, target; 
    int ap, dp, count; 
    int i, damage; 
    
    if( me->query("family/family_name") != "�������" ) 
            return notify_fail("�㲻��������̵��ӣ��޷�ʹ��" DAO "��\n"); 

    if( !me->query("reborn/times") )         
            return notify_fail("����δת���������޷�ʹ��" DAO "��\n"); 
                      
    if (! target) target = offensive_target(me); 
       
    if (! target || ! me->is_fighting(target)) 
            return notify_fail(DAO "ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 

    if (! objectp(weapon = me->query_temp("weapon")) || 
       (string)weapon->query("skill_type") != "blade") 
            return notify_fail("��ʹ�õ��������ԣ�����ʩչ" DAO "��\n"); 
      
    if ((int)me->query_skill("moon-blade", 1) < 1000) 
            return notify_fail("��Բ���䵶��򲻹�������ʩչ" DAO "��\n"); 
       
    if (me->query_skill_mapped("blade") != "moon-blade") 
            return notify_fail("��û�м���Բ���䵶������ʩչ" DAO "��\n"); 
       
    if ((int)me->query_skill("force") < 1200) 
            return notify_fail("����ڹ���Ϊ����������ʩչ" DAO "��\n"); 
      
    if ((int)me->query("max_neili") < 100000) 
            return notify_fail("���������Ϊ����������ʩչ" DAO "��\n"); 
       
    if ((int)me->query("neili") < 10000) 
            return notify_fail("�����ڵ��������㣬����ʩչ" DAO "��\n"); 
       
    if (! living(target)) 
            return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 
     
    if (objectp(weapon = target->query_temp("weapon"))) 
    {         
            msg = HBYEL "$N" HBYEL "˫�ֳֵ���һԾ���𣬾��˵�������һ�������Ļ��ߣ�һ�ɵ���" 
                  HBYEL "��һ������Ϯ��$n��\n" NOR; 
       
            ap = me->query_skill("blade") + me->query_skill("force") + me->query_skill("xixing-dafa") + me->query_skill("martial-cognize"); 
                        
            if (ap / 2 + random(ap) > dp)
            { 
               me->add("neili", -500); 
               msg += HIR "$n" HIR "���в��ã���æ�������б����ֵ���ȴ���뻢�ھ�ʹ������" + weapon->name() + 
                               HIR "��ס�����ֶ�����\n" NOR; 
                               
               weapon->move(environment(me)); 
             } else 
               { 
                     me->add("neili", -500); 
                     msg += CYN "$n" CYN "����ʮ�ɹ�����ͷ����������������" + weapon->name() +  
                                     CYN "Ӳ�ǽ�$N" CYN "�ľ����ֵ������ˡ�\n" NOR;                         
                } 
                message_combatd(msg, me, target); 
             }  
               
             msg = HBBLU "��ʱ��$N" HBBLU "�����Ʈ������֪��ʱ������$n����ǰ��һ��" HIY "�������ϡ�" NOR +
                   HBBLU "�����������ϻ���һ���������µ���������$n����Ҫ��$nһ������" HBBLU "��\n"NOR;   
       
             ap = me->query_skill("blade") + me->query_skill("force") + me->query_skill("xixing-dafa") + me->query_skill("martial-cognize"); 
             dp = target->query_skill("dodge") + target->query_skill("force") + target->query_skill("blade"); 
             damage = me->query_skill("blade") + me->query_skill("force") + me->query_skill("xixing-dafa") + me->query_skill("martial-cognize");  
               
             if (ap * 2 + random(ap * 2) > dp) 
            {       
                   damage = damage * 4;          
                   target->receive_damage("jing", damage / 4);
                   target->receive_wound("jing", damage / 5);
                   msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200, 
                                              HIR "$n" HIR "ֻ���������ȣ�һ�ɾ�������" 
                                             "�����������������ܣ���$N" HIR "�ľ���Ϯ��"
                                             "ȫ������Ѩ��Ѫ�����ڣ�Ѫ����������\n" NOR); 
                   target->start_busy(5); 
                   me->add("neili", -400);                 
             } else 
              { 
                   msg += CYN "$n" CYN "�ۼ�$N" CYN "������ӿ��˿����" 
                              "��С���æ������һ�ԡ�\n" NOR; 
                   me->add("neili", -200); 
              } 
               
             message_combatd(msg, me, target);     
              
             msg = HBMAG "������$N" HBMAG "Ծ����У���һɱ��" HIB "�����ϵ���" NOR +
                   HBMAG "���е����裬һ˲������ж�������������£�һ����$n" HBMAG "��ȥ��\n" NOR;                       
      
             ap = me->query_skill("blade") + me->query_skill("force") + me->query_skill("xixing-dafa") + me->query_skill("martial-cognize"); 
             dp = target->query_skill("dodge") + target->query_skill("parry") + target->query_skill("force") + target->query_skill("blade"); 
              
             if (ap * 3 / 4 + random(ap) > dp) 
             { 
                     msg += HIR "$n" HIR "���$N" HIR "����ɽ������Ĺ�" 
                            "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR; 
                     count = ap / 5; 
             } else 
             { 
                     msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ" 
                            "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR; 
                     count = 0; 
             } 
              
             message_combatd(msg, me, target); 
      
             me->add_temp("apply/attack", count); 
             me->add_temp("apply/damage", count / 2); 
      
             for (i = 0; i < 12; i++) 
             { 
                     if (! me->is_fighting(target)) 
                             break; 
      
                     if (! target->is_busy()) 
                             target->start_busy(3); 
      
                     if (! objectp(weapon = me->query_temp("weapon")) )
                     COMBAT_D->do_attack(me, target, 0, 120);
                     else
                     COMBAT_D->do_attack(me, target, weapon, 120); 
             } 
             me->add("neili", -2000); 
             me->add_temp("apply/attack", -count); 
             me->add_temp("apply/damage", -count / 2); 
      
             me->start_busy(3 + random(4)); 
             me->add("neili", -400 - random(600)); 
             return 1;         
     } 