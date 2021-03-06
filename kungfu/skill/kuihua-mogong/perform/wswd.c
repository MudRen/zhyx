//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define WSWD "「" HIR "无"BLU"双"HIM"无"HIW"对" NOR "」"
#define WS "「" HIR "无"BLU"双" NOR "」"
#define WD "「" HIM"无"HIW"对" NOR "」"

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
		return notify_fail("无双无对只能对战斗中的对手使用。\n");

    if (userp(me) && ! me->query("can_perform/kuihua-mogong/ws"))
        return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !weapon 
        ||      weapon->query("skill_type") != "sword"
        ||      me->query_skill_mapped("sword") != "kuihua-mogong" ) 
                return  notify_fail("你现在无法使用绝技。\n");
    if (skill < 300 || (int)me->query_skill("kuihua-mogong", 1) < 300)
        return notify_fail("以你目前的修为来看，还不足以运用"WS"\n");
    if (me->query("max_neili") < 2000)
        return notify_fail("你的内力修为不够运用"WS"所需！\n");
    if (me->query("neili") < 800)
        return notify_fail("你的内力不够运用"WS"所需！\n");
  
    msg =HIM "$N突然身形一转眨眼间使用葵花魔功的终极绝招----"NOR""WSWD""HIM"之"NOR""WS"\n"HIW"$N眼神莹然有光，似乎进入了魔境之中。\n"
                "$N手中" + weapon->name() + "化做无双剑影攻向$n。\n";
        ap = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("parry");
        dp = target->query_skill("parry") + target->query("dex") * 20 + target->query_skill("parry");   
		damage = ap * 2 + random(ap*2);		
        if ( me->query("reborn")){        
			damage = damage * 2;
		}        
			me->add("neili",-400);
           
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
              HIY "$n" HIB "只觉得已经跌入了万劫魔域之中，"HIY"$N手中"+weapon->name()+
              HIB "如同地狱中的鬼火般，从各个方位刺了过来，避无可避！\n" NOR);  			 
       
             
        message_vision(msg, me, target);
		
		if ( me->query("reborn")){   
			nextmsg = HIM "说是迟那时快，$N身形逆转使出了"NOR""WSWD"之"WD""HIM"式，刹那间天空阴云密布，\n"NOR""HIM"$n的心脏几乎停止了跳动，呆呆的望着$N\n"NOR;
			damage = me->query_skill("dodge") + me->query("dex") * 20 + me->query_skill("parry");
			nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100+random(50),
						HIY "$n" BLU "只觉身上如同万剑穿心一般，"HIY"$N"
						HIW "如同死神一般，势必要取$n性命！\n" NOR);    
			
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

                if  (!me->query("can_perform/kuihua-mogong/wd"))        //没学会无对                                
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
                nextmsg =HIM "说是迟那时快，$N身形逆转使出了"NOR""WSWD"之"WD""HIM"式，刹那间天空阴云密布，\n"NOR""HIM"$n的心脏几乎停止了跳动，呆呆的望着$N\n"NOR;
                ap = me->query_skill("kuihua-mogong", 1) + me->query("dex") * 12 +  me->query_skill("martial-cognize", 1);
                dp = target->query_skill("parry", 1) + target->query("dex") * 12 + target->query_skill("martial-cognize", 1);
                if (me->query("family/master_name") == "东方不败")
                ap = ap * 2;
                
                

        if (ap * 4/5 + random(ap) > dp)
        {
        	 me->add("neili",-300);
            damage = ap*3 + random(ap/2) ;
            nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
              HIY "$n" BLU "只觉身上如同万剑穿心一般，"HIY"$N"
              WHT "如同死神一般，势必要取$n性命！\n" NOR);        	
			
        } else
        {
           me->add("neili", -200);
            nextmsg += HIG "这时$n屏住呼吸" HIG "抵挡得法，将$N" HIG
            "的攻势一一化解。\n" NOR;
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
                tell_object(me, HIW "\n你突然若有所悟，对刚才使用过的魔功之"WS""HIW"式反复琢磨，\n对了，这样也可以耶！你学会了"WSWD""HIW"之"WD""HIW"式！\n" NOR); 
                me->set("can_perform/kuihua-mogong/wd",1);
                }
                return 1;
}

