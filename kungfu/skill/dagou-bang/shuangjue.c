//buy gentl
//要求：悟性不小于28，转世前身法不小于47，转世后身法不小于52。
//打狗棒法400级时，能领悟前2招，以后等级每增加100级就多出一招。
//转世前最多能出5招化学连。
//转世后最多能出6招化学连。
//当准备有空手武功时，会自动卸下兵器，在化学连招的基础上，转世前会再出1招普通招，转世后会再出3招普通连招。
//伤害和命中均与本门内功有关。
#include <ansi.h>
#include <combat.h>


#define ZHEN HIR "「" HIW "棒" HIY "掌" HIG "双绝" NOR HIR "」"

inherit F_SSERVER;
inherit F_CLEAN_UP;

mapping valid_types = 
([
	"finger":   "指法",
	"hand":     "手法",
	"cuff":     "拳法",
	"claw":     "爪法",
	"strike":   "掌法",
	"unarmed":  "拳脚",
]);

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴",
"承浆穴", "天突穴", "百会穴", "幽门穴", "章门穴", "大横穴",
"紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", }); 

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, j, ap, bp, dp, str;
		int damage;
	    mapping smap, pmap;
	    string *skill;	
		
	    seteuid(getuid());

	   smap = me->query_skill_map();		
	  pmap = me->query_skill_prepare();
	  if (! pmap) pmap = ([]);
        /*if (userp(me) && ! me->query("can_perform/dagou-bangfa/zhongji"))
                return notify_fail("你所使用的外功中没有这种功能。\n");
                */

        if (! target) target = offensive_target(me);
		
		weapon = me->query_temp("weapon"); 
		
		if (me->query("int") < 28)
		  return notify_fail("你的先天悟性不够，无法施展" ZHEN "！！！\n");		
		
		if (me->query("dex") < 47)
		  return notify_fail("你的先天身法不够，重新来过吧！！！\n");
		  
		if (me->query("reborn") && me->query("dex") < 52)
		  return notify_fail("你的先天身法不够，转世重新来过吧！！！\n");		

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对，难以施展" ZHEN "。\n");			       							

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("你没有激发打狗棒法，难以施展" ZHEN "。\n");

        if(me->query_skill("dagou-bang", 1) < 400 )
                return notify_fail("你的打狗棒法不够娴熟，难以施展" ZHEN "。\n");

        if( (int)me->query_skill("force") < 600 )
                return notify_fail("你的内功修为不够，难以施展" ZHEN "。\n");

        if( (int)me->query("max_neili") < 8000 )
                return notify_fail("你的内力修为太弱，难以施展" ZHEN "。\n");

        if( (int)me->query("neili") < 1200 )
                return notify_fail("你现在的真气太弱，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
			 
			  
			  
        msg = HIW"$N手中的" + weapon->name() + HIW "微微抖动，将“打狗棒法”使得变幻莫测，一顿一挑看似笨拙，却有着无穷的威力！\n\n" NOR;


        bp = me->query_skill("huntian-qigong", 1) + me->query_skill("jiaohua-neigong", 1) + me->query_skill("huimeng-xinfa", 1);
        ap = me->query_skill("staff") * 2 + bp / 3;
                damage = ap + random(ap);        
		
        if (me->query_skill("dagou-bang", 1) > 399)     
	 {
      dp = target->query_skill("dodge") * 2;

	  msg += HBRED"$N冷笑一声，运力于棒端，随即探身向前，向$n双腿扫去。\n" NOR;   
       
                 if (ap * 4 / 5 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "只听噗的一声，这一棒出其不意的正中$n的"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一棒。\n" NOR;
        }	
		
	  dp = target->query_skill("dodge") * 2;
		
	  msg += HBGRN"$N一招使将完毕，招式仍然未老，内力轻吐，那棒竟然长了眼睛一般，向$n面门呼啸而至。\n" NOR;   
       
                 if (ap * 4 / 5 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "只听噗的一声，这一棒出其不意的正中$n的"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一棒。\n" NOR;
        }		
	   }
	   
        if (me->query_skill("dagou-bang", 1) > 499)     
	 {
      dp = target->query_skill("parry") * 2;

	  msg += HBYEL"$N一招未毕次招又至，将手中之棒舞成一圈光影向着$n当胸扎来。\n" NOR;   
       
                 if (ap * 3 / 4 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                   HIR "只听噗的一声，这一棒出其不意的正中$n的"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一棒。\n" NOR;
        }	
	   }	   

        if (me->query_skill("dagou-bang", 1) > 599)     
	 {
      dp = target->query_skill("force") * 2;

	  msg += HBBLU"$N眼中杀气忽现，一改灵巧的棒招，迅雷般的直取$n眉心。\n" NOR;   
       
                 if (ap * 2 / 3 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                   HIR "只听噗的一声，这一棒出其不意的正中$n的"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一棒。\n" NOR;
        }	
	   }

        if (me->query_skill("dagou-bang", 1) > 699)     
	 {
      dp = target->query_skill("martial-cognize", 1) * 3;

	  msg += HBMAG"$N极尽能事，手中之棒似已粘在$n身上一般，将$n笼罩在一片光影之中，实在是精妙绝伦！\n" NOR;   
       
		 if (ap / 2 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                   HIR "只听噗的一声，这一棒出其不意的正中$n的"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "运气抵挡，硬生生接下了$N"
                       CYN "这一棒。\n" NOR;
        }
           }
           message_combatd(msg, me, target);
	   
    if (me->query_skill("dagou-bang", 1) > 799 && (int)target->query("qi") > 0 && me->query("reborn") && me->is_fighting(target))         //转世才能用
	 {
      ap = me->query_skill("staff") * 2 + bp;
      dp = target->query_skill("force") + target->query_skill("dodge")+ target->query_skill("parry") + target->query_skill("martial-cognize", 1);
	  
	  
	  me->add("neili", -800);

          msg = HBCYN"$N眼中一片平静，与手中之棒合二为一，「天下无狗」精髓尽出，刹那间幻作漫天棒影罩住$n，\n使出了打狗棒法不传之密！！当真是匪夷所思！\n" NOR;   
       
                 if (ap * 3 / 4 + random(ap*2) > dp)
        {
		 
                 damage = ap + random(ap);

          target->receive_damage("qi", damage*2, me);
          target->receive_wound("qi", damage, me);  
          str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
          msg += HIR "只听噗的一声，这一棒出其不意的正中$n的" 
                                                 HIY + xue_name[random(sizeof(xue_name))] +  
                                                 HIR "，$n不由得惨叫一声，脸上已是全无血色。\n" NOR;
          msg += "($n"+str+")\n";
        } else
        {
                msg += HIY"$n大惊，但见"+ weapon->name()+HIY"来势如风，挡无可挡，闪无可闪，只得向后避开了这招。\n" NOR;
        }
        message_combatd(msg, me, target);
	   	   
           }

       if (! mapp(pmap) || sizeof(pmap) != 0)   //当准备有空手武功，才出描叙出招
	    {
            msg = YEL "\n你的棒法施展完毕，意犹未尽且自我感觉手上功夫也很是了得，便顺手一收手中的" + weapon->name() + YEL"，赤手空拳\n"
                         YEL"向$n攻出．．．．．．\n" NOR;             
               message_vision(msg, me, target);

	      i=1;
		  if (me->query("reborn")) i=3;
          weapon->move(me, 1);   				
          me->add_temp("apply/attack", ap / 6);

          for (j = 0; j < i; j++)   //转世前出1招，转世后出3招
          {		  		 
                        msg =WHT"\n第" + chinese_number(j+1) + WHT"招．．．．．．"NOR;
                        message_vision(msg, me, target);
               if (! me->is_fighting(target))
                         break;
            COMBAT_D->do_attack(me, target, 0, j*20);	          
		  }
                   me->add_temp("apply/attack", -ap / 6);
                   weapon->wield();
		 }  
		
	 	
		
		me->add("neili", -800);
        me->start_busy(2 + random(4));
        return 1;
}


