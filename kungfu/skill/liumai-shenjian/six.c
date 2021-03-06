#include <ansi.h>
#include <combat.h>

#define SIX "「" HIY "六脉剑气" NOR "」"

inherit F_SSERVER;


int perform(object me, object target)
{
        mapping prepare;
        string msg;
        int skill,delta,delta2;        
		int damage;       
        int ap, dp;

        if (! target) target = offensive_target(me);
        	
        if (userp(me) && ! me->query("can_perform/liumai-shenjian/six"))
                return notify_fail("你所使用的外功中没有这种功能。\n");        

        if (! target || ! me->is_fighting(target))
                return notify_fail(SIX "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("你没有准备使用六脉神剑，无法施展" SIX "。\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 350)
                return notify_fail("你的六脉神剑修为有限，无法使用" SIX "！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的内功火候不够，难以施展" SIX "！\n");

        if (me->query("max_neili") < 7000)
                return notify_fail("你的内力修为没有达到那个境界，无法运转内"
                                   "力形成" SIX "！\n");

        if (me->query("neili") < 1000)
                return notify_fail("你的真气不够，现在无法施展" SIX "！\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能施展" SIX "！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "摊开双手，手指连弹，霎时间空气炙热，几"
              "欲沸腾，六道剑气分自六穴，一起冲向$n" HIY "！\n\n" NOR;   

		  delta = (me->query_skill("jingluo-xue", 1) + me->query_skill("lamaism", 1)  + me->query_skill("buddhism", 1)) / 2;
		  delta2 =  (target->query_skill("jingluo-xue", 1) + target->query_skill("lamaism", 1)  + target->query_skill("buddhism", 1)) / 2;
		  damage = (int)me->query_skill("finger") + (int)me->query_skill("canhe-zhi", 1) + (int)me->query_skill("yiyang-zhi", 1) + delta;
		  damage = damage + random(damage/2);
			  
      

       

       //少商剑
        ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("parry",1) + delta2;

	    msg += HIW "$N" HIW "双手拇指同时捺出，嗤嗤两声急响，「"+ HIY "少商剑"+ HIW "」有如石破天惊、风雨大至。\n" NOR ; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "奋力抵挡，却哪里招架得住，被$N"
                                           HIR "这一指戳得鲜血迸流！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指架开，丝毫无损。\n" NOR;
        }

        // 商阳剑
        ap = me->query_skill("liumai-shenjian",1) + delta;
        dp = target->query_skill("parry",1)+ delta2;

	    msg += HIW "\n接着" HIW "$N" HIW "拇指一屈，食指随即点出，嗤的一声，变成商阳剑法，「" HIR "商阳剑" HIW "」激射刺出。\n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "试图抵挡，只听哧的一声，"
                                           HIR "无形剑气已破体而入，透体而出！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指躲开，丝毫无损。\n" NOR;
        }

        //中冲剑
        ap = me->query_skill("liumai-shenjian",1)+delta;
        dp = target->query_skill("dodge",1)+delta2;

	    msg += HIW "\n只见" HIC "$N" HIW "右手中指一点，「" HIG "中冲剑" HIW "」向前刺出。真气鼓荡，嗤然声响，无形剑气直指$n。 \n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "一愣，只听哧啦的一声，"
                                           HIR "已被剑气划得鲜血飞溅！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "使出浑身解数，终于将$N"
                       CYN "这一指架开，丝毫无损。\n" NOR;
        }

        //关冲剑
        ap = me->query_skill("liumai-shenjian",1)+delta;
        dp = target->query_skill("dodge",1)+delta2;

	    msg += HIW "\n$N" HIW "无名指轻轻一挥，「嗤啦」一声，拙滞古朴的「" MAG "关冲剑" HIW "」剑气向" HIW"$n" HIW"直射而出。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "躲闪不及，被戳了碗口大个血窟窿，"
                                           HIR "鲜血喷涌而出！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "左闪右跳，终于将$N"
                       CYN "这一指避开，丝毫无损。\n" NOR;
        }
      

        //少泽剑
        ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("force",1)+delta2;

	    msg += HIW "\n忽见$N" HIW "左手小指一伸，一条气流从少冲穴中激射而出，一股「" HIB "少泽剑" HIW "」登时射向$n。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "运气抵挡，只觉得一股透体凉意"
                                           "袭了上来，一个激凌，丹田立刻变得空空荡荡！\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一指。\n" NOR;
        }
		//少冲剑
		ap = me->query_skill("liumai-shenjian",1)+ delta;
        dp = target->query_skill("force",1)+delta2;

	    msg += HIW "\n最后"HIW "$N" HIW"右手小指一挥，一招「" HIC "少冲剑" HIW "」点点刺刺破空刺出，宛如雕花刺画一般。\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "已然放弃抵抗，任凭气流摧袭"
                                           "只盼望一切早点结束....\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，终于接下了$N"
                       CYN "这一指，已是狼狈不堪。\n" NOR;
        }

		message_combatd(msg, me, target);
	    me->add("neili", -800);
        me->start_busy(3 + random(5));

        return 1;
}

