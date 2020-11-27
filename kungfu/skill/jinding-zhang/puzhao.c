// Code of JHSH
// �������
// sdong 11/11/98

#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
  object ob;
  string msg;
  int damage;
  int finger, skill, jiali, my_rate, your_rate;

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) )
	 return notify_fail("�������ֻ����ս�����á�\n");

  if( me->query_temp("weapon"))
	 return notify_fail("�㲻���±������ʹ�ý����ƣ�\n");

  if( target->query("eff_qi") < target->query("max_qi")/4 )
	 return notify_fail("��Ķ��������˺����ۣ�ʹ�÷��������Υ��Ҵȱ�Ϊ���ı��⡣\n");

  if( target->query("qi") < target->query("max_qi")/6 )
	 return notify_fail("��Ķ��������˺����ۣ�ʹ�÷��������Υ��Ҵȱ�Ϊ���ı��⡣\n");

  if( (skill = (int)me->query_skill("jinding-zhang", 1)) < 150 )
	 return notify_fail("��Ľ����Ʋ�����죬����ʹ������ա�\n");

  if( (int)me->query_skill("linji-zhuang", 1) < 120 )
	 return notify_fail("����ټ�׮����Ϊ����������ʹ�÷�����ա�\n");

  if( me->query_skill_mapped("force") != "linji-zhuang" )
	 return notify_fail("�����õĲ����ټ�׮��ʹ����������գ�\n");

  jiali=(int)me->query("jiali");
  if( jiali < 50 )
	 return notify_fail("������������ڼҹ������ϲ�������ʹ��������\n");

  if( me->query("neili") < 800 ) 
	 return notify_fail("������������ڼҹ����������������㣬ʹ������һ�С�\n");

  msg = HIY "\n$NͻȻ��ȫ������з����������ĵ���΢����֮���������������δ������������$n�ؿڻ�ȥ��\n\n"NOR;
  msg += HIG"��һ���Ƕ����ɵľ�ѧ��������������ա����⡰������ա����Ʒ���ֻһ�У�������\n";
  msg += HIG"һ��Ҳ�������仯����ʽƽƽ������һ�ɲ��䣬����������֮Դ���������Զ����ɾ���\n";
  msg += HIG"�ڹ���Ϊ������һ�Ƽȳ�����������ɽ����һ��Ϯ�������˵��޿ɵ������޿ɱܡ�\n\n";


  if( random( me->query("combat_exp") ) > random( target->query("combat_exp")*2 ) || 
      !living(target) )
  {
	damage = me->query_skill("force"); 
	damage += me->query_skill("strike"); 
        damage += me->query("jiali"); 
        damage += random(damage);

	if(damage > 3000) damage = 3000;
	if(damage < 500) damage = 500;

	me->add("neili", -damage );

	target->receive_damage("qi", damage,  me);
	target->receive_wound("qi", random(damage), me);
	target->start_busy(1+random(3));

	msg += HIR"��������Ȼһ�����죬$N�Ѵ�����$p�ؿ�.\n"NOR;
	if ( damage < 600) {
		msg += HIR"$n����һ�Σ����㲻����������Ҫˤ����\n"NOR;
	}else if ( damage < 800) {
		msg += HIR"$n������ˤ����������۵�һ�������һ����Ѫ��\n"NOR;
	}else if ( damage < 1200) {
		msg += HIR"$n�۵�һ�������һ����Ѫ��ί���ڵأ�����һ�����ࡣ\n"NOR;
	}else if ( damage < 1800) {
		msg += HIR"$n���ӱ���һ�����ݰ㣬�ڿ���ƽƽ�ķ��˳�ȥ������ˤ�ڵ��£�������Ѫ���磮\n"NOR;
	}else if ( damage < 2500) {
		msg += HIR"ֻ��һ�����죬$n������Ѫ���磬ȫ������������顣\n"NOR;
	}else {
		msg += HIR"ֻ��һ�����죬$nȫ�����һƬ����֮������������ɽ�������һ�������Ӳ�����������ء�\n"NOR;
	}
	msg += NOR;
	me->start_busy(2+random(2));
  }
  else if( random( me->query("combat_exp")*3/2 ) > random( target->query("combat_exp") )
       &&  random(target->query_skill("dodge")) < random( me->query_skill("strike") )  )
  {
	damage = me->query_skill("force"); 
	damage += me->query_skill("strike"); 
        damage += me->query("jiali"); 
	damage /= 2;
	damage += random(damage);

	if(damage > 2000) damage = 2000;
	if(damage < 300) damage = 300;

	me->add("neili", -damage );

	target->receive_damage("qi", damage,  me);
	target->receive_wound("qi", random(damage), me);
	target->start_busy(1+random(3));

	msg += HIY"$p�ۿ���һ���������ڣ�֪�����ڶԸ�����æ�����ֿ�����������Ȼһ�����죬$N�Ѵ�����$p�ؿ�.\n"NOR;
	if ( damage < 400) {
		msg += HIR"$n����һ�Σ����㲻����������Ҫˤ����\n"NOR;
	}else if ( damage < 600) {
		msg += HIR"$n������ˤ����������۵�һ�������һ����Ѫ��\n"NOR;
	}else if ( damage < 1000) {
		msg += HIR"$n�۵�һ�������һ����Ѫ��ί���ڵأ�����һ�����ࡣ\n"NOR;
	}
	else msg += HIR"$n���ӱ���һ�����ݰ㣬�ڿ���ƽƽ�ķ��˳�ȥ������ˤ�ڵ��£�������Ѫ���磮\n"NOR;
	msg += NOR;
	me->start_busy(2+random(2));
  }
  else if( random( me->query("combat_exp")*3/2 ) > random( target->query("combat_exp") ) &&
	  random( target->query_skill("dodge")*3/2 ) > random( me->query_skill("strike") ) )
  {
	damage = me->query_skill("force"); 
	damage += me->query_skill("strike"); 
        damage += me->query("jiali"); 
	damage /= 3;
	damage += random(damage);

	if(damage > 1000) damage = 1000;
	if(damage < 200) damage = 200;

	me->add("neili", -damage );

	target->receive_damage("qi", damage,  me);
	target->receive_wound("qi", random(damage), me);
	target->start_busy(1+random(3));

	msg += HIM"$p�ۿ���һ���������ڣ���æʹ�������������Ծ�����ɣ��������������̲ض�ü�ڼ��ϳ��ڹ���\n";
	msg += "��Բ���ɶ��������𺳣�$pֻ���ú���һ���ѱ�������������.\n"NOR;
	if ( damage < 300) {
		msg += HIR"$n����һ�Σ����㲻����������Ҫˤ����\n"NOR;
	}else if ( damage < 500) {
		msg += HIR"$n������ˤ����������۵�һ�������һ����Ѫ��\n"NOR;
	}else if ( damage < 800) {
		msg += HIR"$n�۵�һ�������һ����Ѫ��ί���ڵأ�����һ�����ࡣ��\n"NOR;
	}
	else msg += HIR"$n���ӱ���һ�����ݰ㣬�ڿ���ƽƽ�ķ��˳�ȥ������ˤ�ڵ��£�������Ѫ���磮\n"NOR;

	msg += NOR;

	me->start_busy(2+random(2));
  }
  else {
	 msg += HIC"$n�ۿ���һ���������ڣ�ʹ��������������Ծ�����ɣ�\n\n"NOR;
	 msg += HIW"$N��һ������ʹ����ȫ����˿��������ء�û�뵽ȫ���ô��������������ң�����΢΢������\n" NOR;
	 me->add("neili", -jiali*2 );
	 me->start_busy(2 + random(2));
	 message_vision(msg+"\n", me, target);
	 return 1;
  }

  message_vision(msg+"\n", me, target);
  COMBAT_D->report_status(target);
  return 1;
}


