//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define WSWD "��" HIR "��"BLU"˫"HIM"��"HIW"��" NOR "��"
#define WS "��" HIR "��"BLU"˫" NOR "��"
#define WD "��" HIM"��"HIW"��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
    int skill = (int)me->query_skill("kuihua-mogong", 1), i;
    string msg,nextmsg;
    int ap, dp;
    int damage;
    int x,a;
        object weapon = me->query_temp("weapon");
   if (! target)
   {
       me->clean_up_enemy();
       target = me->select_opponent();
   }

   if (! target || ! me->is_fighting(target))
		return notify_fail("��˫�޶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (userp(me) && ! me->query("can_perform/kuihua-mogong/ws"))
        return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !weapon 
        ||      weapon->query("skill_type") != "sword"
        ||      me->query_skill_mapped("sword") != "kuihua-mogong" ) 
                return  notify_fail("�������޷�ʹ�þ�����\n");
    if (skill < 300 || (int)me->query_skill("kuihua-mogong", 1) < 300)
        return notify_fail("����Ŀǰ����Ϊ������������������"WS"\n");
    if (me->query("max_neili") < 2000)
        return notify_fail("���������Ϊ��������"WS"���裡\n");
    if (me->query("neili") < 800)
        return notify_fail("���������������"WS"���裡\n");
  
    msg =HIM "$NͻȻ����һתգ�ۼ�ʹ�ÿ���ħ�����ռ�����----"NOR""WSWD""HIM"֮"NOR""WS"\n"HIW"$N����ӨȻ�й⣬�ƺ�������ħ��֮�С�\n"
                "$N����" + weapon->name() + "������˫��Ӱ����$n��\n";
        ap = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("parry");
        dp = target->query_skill("parry") + target->query("dex") * 20 + target->query_skill("parry");   
		damage = ap * 2 + random(ap*2);		
        if ( me->query("reborn")){        
			damage = damage * 2;
		}        
			me->add("neili",-400);
           
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
              HIY "$n" HIB "ֻ�����Ѿ����������ħ��֮�У�"HIY"$N����"+weapon->name()+
              HIB "��ͬ�����еĹ��㣬�Ӹ�����λ���˹��������޿ɱܣ�\n" NOR);  			 
       
             
        message_vision(msg, me, target);
		
		if ( me->query("reborn")){   
			nextmsg = HIM "˵�ǳ���ʱ�죬$N������תʹ����"NOR""WSWD"֮"WD""HIM"ʽ��ɲ�Ǽ���������ܲ���\n"NOR""HIM"$n�����༸��ֹͣ������������������$N\n"NOR;
			damage = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("parry");
			nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100+random(50),
						HIY "$n" BLU "ֻ��������ͬ�򽣴���һ�㣬"HIY"$N"
						HIW "��ͬ����һ�㣬�Ʊ�Ҫȡ$n������\n" NOR);    
			
			message_vision(nextmsg, me, target);
			me->start_busy(2);  
        return 1;
		}
		me->start_busy(2);  
		

                if( (int)me->query("neili") > 1000
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  me->query("can_perform/kuihua-mogong/wd")
                &&  !me->is_ghost()
                &&  me->query_skill_mapped("sword") == "kuihua-mogong"
                &&  (string)weapon->query("skill_type") == "sword")
                {
                        remove_call_out("perform2");
                        call_out("perform2", 1, me);
                }
                else

                if  (!me->query("can_perform/kuihua-mogong/wd"))        //ûѧ���޶�                                
                {
                        remove_call_out("check_wd");
                        call_out("check_wd",3,me);
                }

return 1;
}
int perform2(object me)

{               int ap, dp;
        string nextmsg;
        int damage;   
        object target;
        object weapon = me->query_temp("weapon");
                if( !target ) target = offensive_target(me);   
        if(!living(target))     return 1;
                nextmsg =HIM "˵�ǳ���ʱ�죬$N������תʹ����"NOR""WSWD"֮"WD""HIM"ʽ��ɲ�Ǽ���������ܲ���\n"NOR""HIM"$n�����༸��ֹͣ������������������$N\n"NOR;
                ap = me->query_skill("kuihua-mogong", 1) + me->query("dex") * 12 +  me->query_skill("martial-cognize", 1);
                dp = target->query_skill("parry", 1) + target->query("dex") * 12 + target->query_skill("martial-cognize", 1);
                if (me->query("family/master_name") == "��������")
                ap = ap * 2;
                
                

        if (ap * 4/5 + random(ap) > dp)
        {
        	 me->add("neili",-300);
            damage = ap*3 + random(ap/2) ;
            nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
              HIY "$n" BLU "ֻ��������ͬ�򽣴���һ�㣬"HIY"$N"
              WHT "��ͬ����һ�㣬�Ʊ�Ҫȡ$n������\n" NOR);        	
			
        } else
        {
           me->add("neili", -200);
            nextmsg += HIG "��ʱ$n��ס����" HIG "�ֵ��÷�����$N" HIG
            "�Ĺ���һһ���⡣\n" NOR;
        }
		me->start_busy(2+random(3));
        message_vision(nextmsg, me, target);
        return 1;
}
int check_wd(object me)
{       int a;
        object target;

        a = random(10);

        if( !target ) target = offensive_target(me);   
    if(living(target))  return 1;
        if (me->is_fighting())  return 1;
        if(a >= 8){
                tell_object(me, HIW "\n��ͻȻ�������򣬶Ըղ�ʹ�ù���ħ��֮"WS""HIW"ʽ������ĥ��\n���ˣ�����Ҳ����Ү����ѧ����"WSWD""HIW"֮"WD""HIW"ʽ��\n" NOR); 
                me->set("can_perform/kuihua-mogong/wd",1);
                }
                return 1;
}

