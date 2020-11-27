// Code of ShenZhou
//kane
//maco changed 
#include <ansi.h>
#include <combat.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit F_COMMAND;

int bash_weapon(object me, object victim);

void create()
{
	set_name(YEL"Сʯ��"NOR, ({"xiao shizi", "shizi"}));
	if (clonep())
	set_default_object(__FILE__);
	else {
	set("unit", "��");
	set("base_unit","��");
	set("long", "�����洦�ɼ���Сʯ�ӡ�\n");
	set("value", 0);
	}
	set_amount(1+random(5));
//	init_throwing(5);
	setup();
}

int init()
{
	add_action("do_tanzhi", "tan");      
}

int do_tanzhi(string arg)
{
	int skill, skill2, thr, dod, tz, parr, diff, jiali, exp, exp2;
	string str, dodge_skill, result, *limbs, limb;
	object me = this_player();
	object victim,weapon;

	if (!arg)    
		return notify_fail("��Ҫ��ʲô��\n");

	if (!(victim = present(arg,environment(me))))
		return notify_fail("���ﲢ�޴��ˣ�\n");

	if (!victim)
		return notify_fail("���ﲢ�޴��ˣ�\n");

	if (!living(victim))
		return notify_fail("�ⲻ�ǻ��\n");

	if( me->is_busy() )
		return notify_fail("��ǰһ��������û�����ꡣ\n");

	if (victim == me) return notify_fail("�αض��һ�٣�\n");

	if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if (me->query_skill("tanzhi-shentong", 1) < 120)
		return notify_fail("ѧС����ʯ�ӣ���������\n");

	tz = me->query_skill("tanzhi-shentong", 1);
	dod = (int)victim->query_skill("dodge");
	parr = (int)victim->query_skill("parry");
	skill = tz/10+random(tz)/2;
	skill2 = (dod + parr)/10;
	diff = skill-skill2;
	jiali = me->query("jiali");
	limbs = victim->query("limbs");
	exp = me->query("combat_exp");
	exp2 = victim->query("combat_exp");
	me->add("neili",- jiali/2);
	limb = limbs[random(sizeof(limbs))];

	message_vision(HIW"$N��������һ��Сʯ�ӣ�����Ĵָʳָ֮�䣬���ꡱ��һ�����죬Сʯ����$n�����ȥ......\n" NOR, me, victim);

//	if( exp/3+random(exp/2) > exp2 /2 && skill > skill2){
	if(skill > skill2){
		weapon = victim->query_temp("weapon");

		if( !victim->query_temp("weapon") ) {
			if(jiali >= 240) 
				message_vision(HIY"$n������һ����Ϣ��Сʯ��ת˲�仮�����գ��ѻ���$n"+limb+"���������ˣ������ɵ���\n" NOR, me, victim);
			else if(jiali >= 200) 
				message_vision(HIY"����Сʯ���ƿ�֮�������쳣�����Ʊ���̥����������Ҫ������ת˲���ѻ���$n"+limb+"��\n" NOR, me, victim);
			else 
				message_vision(HIY"$n��������ֲ��������ڵ�ʱ��Ѫ�������ֱ���Ҳ̧��������\n" NOR, me, victim);

			victim->receive_wound("qi", random(jiali) +random(10), me);
			victim->receive_damage("qi", jiali + random(jiali) + random(10), me);
		}
		else
        	{ 
			message_vision(HIY"Сʯ���ƿշ�����ײ��$N���е�" + weapon->name() + HIY"�ϡ�\n"NOR,victim);
			bash_weapon(me,victim);
			victim->receive_wound("qi", random(jiali/5) + 10, me);
			victim->receive_damage("qi", jiali/2 + random(10), me);
		}
	
		victim->start_busy(2+random(3));

		result = COMBAT_D->eff_status_msg((int)victim->query("qi") * 100 /(int)victim->query("max_qi"));

		message_vision("( $N"+result+" )\n", victim);

		if( !victim->is_killing(me) ) victim->kill_ob(me);

		if( victim->query("combat_exp") > me->query("combat_exp"))
			me->add("combat_exp", 1);

		me->start_busy(1+random(2));
	}
	else {
	        dodge_skill = victim->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                str = SKILL_D(dodge_skill)->query_dodge_msg(limb);
                message_vision(str, me, victim);

		me->start_busy(2 + random(2));

		if( !victim->is_fighting(me) )
		{
                	me->fight_ob(victim);
                	victim->fight_ob(me);
		}
	}
        if (query_amount() > 1)
                add_amount(-1);
        else 
		destruct(this_object());
	return 1;
}    

int bash_weapon(object me, object victim)
{
        object ob;
        int wap, wdp, jiali;
	jiali = me->query("jiali");

        if( (me->query("neili") > 100)
        &&      ob = victim->query_temp("weapon") ) {
                wap = (int)me->query("neili")
                        + (int)me->query_str()
                        + (int)me->query_skill("tanzhi-shentong",1);
                wdp = (int)ob->weight() / 500
                        + (int)ob->query("rigidity")
                        + (int)victim->query_str()
                        + (int)victim->query_skill("parry")/2;
                wap = random(wap);
                if( wap > 2 * wdp && ob->query("weapon_prop/damage") < 90 ) {
			if (jiali < 200) message_vision(HIW "ֻ������ž����һ����$N���е�" + ob->name() + HIW"�Ѿ���Ϊ���أ�\n" NOR, victim );
			else message_vision(HIW"Сʯ��һײ֮�£���ʱ�����Ľ���ʯ����Ƭ�˷����䣬��ž����һ����"+ob->name()+HIW"��Ϊ���أ�\n"NOR, victim);
                        ob->unequip();
                        ob->move(environment(victim));
                        ob->set_name("�ϵ���" + ob->name());
                        ob->set("value", 0);
                        ob->set("weapon_prop", 0);
                        victim->reset_action();
                } else if( wap > wdp ) {
                
                        if(jiali < 200) message_vision(HIW"$Nֻ��������" + ob->name() + HIW"�ѳֲ��������ַɳ���\n"NOR, victim);
			else message_vision(HIW"Сʯ��һײ֮�£�ը�÷��飬���$N������ʹ��"+ ob->name() + HIW"ˤ�ڵ��£�\n"NOR, victim);
	
                        ob->unequip();
                        ob->move(environment(victim));
                        victim->reset_action();
                } else if( wap > wdp / 2 ) {
			message_vision("$Nֻ��������" + ob->name() + "һ����Щ���֣�\n",
                                victim);
                } else {
                        message_vision("$N�����Сʯ�Ӻ�$n��"+ob->name()+"�����ð�����Ļ��ǡ�\n", me, victim);
                }
        }
}

