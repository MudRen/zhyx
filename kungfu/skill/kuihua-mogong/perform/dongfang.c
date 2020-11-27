//created by kasumi
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
#define DF "��" HIR "��"HIW"������" NOR "��"


inherit F_SSERVER;
int dongfang_hit(object me);
int perform(object me, object target)
{    
string msg = "";
    int damage, count, i;
    object weapon = me->query_temp("weapon");
    
    if (! target)
    {
        me->clean_up_enemy();
        target = me->select_opponent();
    }

    if (! target || ! me->is_fighting(target))
		return notify_fail(DF"ֻ�ܶ�ս���еĶ���ʹ�á�\n");	
	  

    if ( me->query_skill_mapped("unarmed") != "kuihua-mogong" || me->query_skill_prepared("unarmed") != "kuihua-mogong" )
                return notify_fail("�㼤������ħ��Ϊȭ�ţ����ұ��ò���ʹ��"DF"��\n");

    if (!weapon || weapon->query("skill_type") != "sword" || me->query_skill_mapped("sword") != "kuihua-mogong" ) 
                return  notify_fail("����Ҫװ�����ͼ�������Ϊ����ħ������ʹ��"DF"��\n");
    
    if ((int)me->query_skill("kuihua-mogong", 1) < 500)
        return notify_fail("����Ŀǰ����Ϊ������������������"DF"\n");
    
    if (me->query("max_neili") < 6000)
        return notify_fail("���������Ϊ��������"DF"���裡\n");
    
    if (me->query("neili") < 2000)
        return notify_fail("���������������"DF"���裡\n");
		
    if (! living(target))
        return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
		
	weapon = me->query_temp("weapon");
  
msg += HIM "$N�����ɨ��$nһ�ۣ���������һ��ʧȥ����Ӱ����֮���������籩�������콣Ӱ��������$N�ĸ���......\n";
	msg += HIG "\n                              ���·��Ƴ��ұ���\n\n";
	message_combatd(msg, me, target);
	
	count = me->query_skill("kuihua-mogong", 1);
    me->add_temp("apply/attack", count);  
    me->add_temp("apply/damage",count);  
    
	for (i = 0; i < 5; i++)
	{
	   if (! me->is_fighting(target))
            break;
       if (random(2)==1 && ! target->is_busy())
            target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
		me->add("neili", -50);
	}
	me->add_temp("apply/attack", -count);  
    me->add_temp("apply/damage",-count);  
    

	msg = HIG "\n                              һ�뽭�����´ߡ�\n\n";
	msg += HIM"���꽥С����Ȼһ����������һ������������$n......\n";
    damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("sword", 1);
	damage = damage*3 + random(damage*2);
	msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   HIR "$n" HIR "���ܲ������������ض�������ѪƮɢ��֮ǰ�Ľ�����������Ѫ�ꡣ\n" NOR);   
    message_combatd(msg, me, target);
	me->add("neili", -250);


    weapon->move(me, 1);
    msg = HIG "\n                              ��ͼ��ҵ̸Ц�У�\n\n";
    msg += HIM"$N��ת�����������������������������Ӱ����$nȫ��Ҫ��$n......\n";	
	message_combatd(msg, me, target);
	me->add_temp("apply/attack", count);  
    me->add_temp("apply/damage",count);  
	for (i = 0; i < 5; i++)
	{
	   if (! me->is_fighting(target))
            break;
       if (random(2)==1 && ! target->is_busy())
            target->start_busy(1);
		COMBAT_D->do_attack(me, target, 0, 0);
		me->add("neili", -50);
	}
	me->add_temp("apply/attack", -count);  
    me->add_temp("apply/damage",-count);
	

	msg = HIG "\n                              ��ʤ�˼�һ����\n\n";
	msg += HIM"$N������֮�У�ͻȻ���һָ��ֱ����$n�ؿ�ҪѨ......\n";	
	damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("unarmed", 1);
	damage = damage*3 + random(damage*2);	
	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                   HIR "$n" HIR "���ܲ������ؿ�ҪѨ���У����ۡ����³�һ�����Ѫ��\n" NOR);   
    message_combatd(msg, me, target);
	me->add("neili", -250);
	weapon->wield();
	
	me->start_busy(3+random(3));  


	if( (int)me->query("neili") > 1000
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  me->query("reborn")
                &&  !me->is_ghost()
				)
	{
	   remove_call_out("dongfang_hit");
           if (me->query("family/master_name") == "��������")
                call_out("dongfang_hit",1, me);
           else call_out("dongfang_hit",1+random(2), me);
	}
return 1;
}

int dongfang_hit(object me)
{
     
     object target;
     string msg;
     int damage,i,p;
	 object weapon = me->query_temp("weapon");
	 if( !target ) target = offensive_target(me);   
        if(!living(target))     return 1;

	 msg = HIY "ͻȻ���������Ĺ���ͻȻֹͣ�ˣ���Χһ�ж����������ţ��·�����������ᡣ\n"
	       HIY "$N���е�"+ weapon->name()+ HIY "����������Ŀ������⻪�����������̫���������ǣ�\n"
		   HIR "\n                              �ճ�������Ψ�Ҳ��ܣ���\n\n" NOR;
     message_combatd(msg, me);
	 
	 damage = (int)me->query_skill("kuihua-mogong", 1) + (int)me->query_skill("force");
	 damage = damage*4 + random(damage*2);

	 target->receive_wound("qi", damage, me);
	 target->set("neili",0);
	 target->set("jingli",0);
	 p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
		
	msg = HIR "�⻪������$nȴ�Ǵ���������������Ѫ������Ť����ȫ����������ʧ��\n" NOR;
	msg += "( " + target->name() + eff_status_msg(p) + " )\n\n";
	message("vision", msg, environment(me), target); 
	 
	 me->add("neili", -500);
	 me->start_busy(2);  
}





