// yijin-jing ��Ħ�׽
#include <ansi.h>
inherit FORCE;
#include "/kungfu/skill/eff_msg.h";
int valid_enable(string usage)
{
    return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	int nb, nh;
	nb = (int)me->query_skill("buddhism", 1);
	nh = (int)me->query_skill("yijin-jing", 1);

	if ( me->query("gender") != "����" )
		return notify_fail("���ͯ��֮�壬������ϰ�׽�ڹ���\n");

	if ((int)me->query_skill("buddhism", 1) < 100 && nb <= nh )
		return notify_fail("��������ķ���Ϊ�������޷�����������׽�ڹ���\n");

	if ((int)me->query_skill("force", 1) < 15)
		return notify_fail("��Ļ����ڹ���򻹲������޷�����׽�ڹ���\n");

	if ((int)me->query("guilty") > 0 ) 
		return notify_fail("���ŷ�ɮ�����䣬�޷�����������׽�ڹ���\n");

	return valid_public(me);
}

void skill_improved(object me)
{
   	int skill, lit;
   	skill = me->query_skill("yijin-jing", 1);
   	lit = me->query_skill("literate", 1);
   	if(skill >= 200 && !me->query("yjj/200")){
      		tell_object(me, HIW"\n��Ȼ����е�������Ϣ���ߣ�ԽתԽ�죬˲ʱ���Ѿ���ȫ������������һ���죬������ڵ���֮�У�\n"NOR);
     		me->add("max_neili", random(lit + skill));
      		me->set("yjj/200", 1);
      	}
}

int practice_skill(object me)
{
        if(me->query_skill("yijin-jing", 1) < 320)
		return notify_fail("�׽�ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
	if ((int)me->query("jingli") < 80)
		return notify_fail("�������������ϰ�׽��\n");
	if ((int)me->query("neili") < 50)
		return notify_fail("�������������ϰ�׽��\n");
	if ( (int)me->query("potential") < 1)
                return notify_fail("���Ǳ�ܲ�����\n");
                
	me->receive_damage("jingli", 75);
	me->receive_damage("neili", 45);
	me->add("potential", -1);
	return 1;
}

string exert_function_file(string func)
{
	return __DIR__"yijin-jing/" + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"���Ϻ�����֣�����ׯ��" NOR,
    "start_my_msg" : "���������죬�ų�һ�������Ϣ˳��������������\n",
    "start_other_msg" : me->name()+"�������죬һ�Ṥ�򣬴ӿڱǴ������³�����������Խ��ԽŨ������������ȫ��\n",
    "halt_msg" : "$N����һ����������Ϣ�������˻�ȥ��վ��������\n",
    "end_my_msg" : "�㽫��Ϣ���˸�С���죬���ص���չ�վ��������\n",
    "end_other_msg" : "ֻ������"+me->name()+"�İ���������ɢ���ִӿڱǴ����˻�ȥ��\n",
    "heal_msg" : HIY"$N˫�ֺ�ʲ����ϥ�������������������䡱����ʼ�˹����ˡ�\n"NOR,
    "heal_finish_msg" : HIY"$N����վ��ֻ��ȫ��˵������������죬����������գ����գ������׽���������¾�ѧ����\n"NOR,
    "heal_unfinish_msg" : "$N�³���Ѫ������վ�𣬵���ɫ�԰ף���������������\n",
    "heal_halt_msg" : "$Nһ�����������ӷ�˫��Ӷ���ѹ����Ϣ��վ��������\n",
    ]);
}

string *fanzhen_msg = ({
"ֻ���$n���ڸ��У���������һ�뷭ת��\n",
"���ȷ��𣬽�$n��������ֽ��ȫ��Ѫɫ��\n",
"���$n�ķ����ѣ�����������������\n",
"�����Ѳ���ȫ����$n�����������ȥ��\n",
"���$n������ת�������������߰˲���\n",
"��$nһײ��ֻ���$p�ؿ���Ѫ��ӿ��\n",
"$n����ײ��һ���޻����棬����Ϊ��ĺ�ǽ��һ�㣬����������\n",
"$n������$P��ͻȻ����һ�𣬵�ʱ���˳�ȥ��\n",
});

int ob_hit(object ob, object me, int damage)
{
        string msg;
        int p, skill, neili, neili1;
        object weapon;
        skill = me->query_skill("yijin-jing", 1);
        neili = me->query("neili") + 1 ;
        neili1 = ob->query("neili") + 1;

   	if(living(me) 
   	&& me->query_temp("fanzhen") 
      	&& random(skill)+30 > ob->query_skill("parry", 1)/2 
      	&& me->query("combat_exp") > ob->query("combat_exp")/2 
      	&& skill > 199 
      	&& neili > 500 
      	&& living(ob) 
      	&& !ob->query("env/invisibility"))
      	{
        	if(!objectp(weapon = ob->query_temp("weapon"))){
            		me->add("neili", -(10+random(70)));
            		msg = random(2)?HIR"$N��������һ�ɷ���֮����":HIR"$N���Ͻ�ղ����������Ķ���";         
              		if(neili1 > neili*4 || random(damage) > (5000 + me->query_con() * 40)){
                		msg += "��ȴ��$n�ľ���һ�����飡\n"NOR;
                		me->delete_temp("fanzhen");
                		damage = random(damage/2);
                	}
            		else if(neili1 > neili*3) {
            			msg += "��ȴ�����޷��赲$n�ľ�����\n"NOR;
            			damage = 0;
            		}
            		
            		else if(neili1 > neili*3/2){
                   		msg += "��������˲���$n�ľ�����\n"NOR;
                   		damage = -damage/2;
                   	}
            		else{
                		msg += fanzhen_msg[random(sizeof(fanzhen_msg))]+NOR;             
                		p = (neili / neili1);
                		if( p < 1) p = 1;
                		p *= damage/2;
                		if(ob->query_skill("force") > me->query_skill("force")*3/2) p = p*2/3;
                		if(p < 10) p = 10;
                
                		ob->receive_damage("qi", p, me);
                		ob->receive_wound("qi", p/5, me);
                		
                		if(wizardp(me)) tell_object(me, "Fanzhen damage: "+p+"��\n");
                		
                		p = ob->query("qi")*100/ob->query("max_qi");
                		msg += "( $n"+eff_status_msg(p)+" )\n";
                		
                		damage = -8000+(-damage);
                	}       
            		message_vision(msg, me, ob);
            	}
       		else{
            		msg = HIR"������һ�����ε�ǽ��$N��ǰ�赲�ţ�";
            		switch(weapon->query("skill_type")) {
                        	case "whip"   : p = 10; break;
                        	case "sword"  : p = 8; break;
                        	case "hook"   : p = 6; break;
                        	case "blade"  : p = 5; break;
                        	case "club"   : 
                        	case "stick"  : p = 2; break;
                        	case "staff"  : 
                        	case "axe"    : 
                        	case "hammer" : p = 1; break;
                        	default       : p = 3; break;
                	}
                	p *= weapon->query("rigidity");
                        if( random(me->query("str") + p) > p && neili > neili1*2/3) {
                        	message_vision(HIR"���$N��������һ�ɷ���֮����$nֻ������һ�ȣ�" + weapon->name() + HIR"��ʱ���ֶ������ɳ����⣡\n\n"NOR, me, ob);
                        	weapon->unequip();
                        	weapon->move(environment(ob));
                        	ob->reset_action();
                        	ob->start_busy(1+random(3));
                		return -8000+(-damage);
			}
            		else if(neili > neili1*2){ 
                		msg += "���$n"HIR"һ���ӱ����������"+ob->name()+HIR"�ֱ۷��飡\n"NOR;
                		ob->start_busy(1+random(3));
                		damage = -8000+(-damage);
                	}
            		else if(neili > neili1*3/2){ 
                		msg += "���$n"HIR"����ǰ��һ˿һ����\n"NOR;
                		damage = -5000+(-damage);
                	}
            		else if(neili > neili1){
                		msg += "���������$n"HIR"ǰ�����ٶȣ�\n"NOR;
                		damage = -damage*3/2;
                	}
            		else if(neili*2 > neili1){
                		msg += "����û����ʲô���ã�\n"NOR;
                		damage = 0;
                	}
            		else{
                		msg += "��ȴ��$n"HIR"һ�´��ƣ�\n"NOR;
                		me->delete_temp("fanzhen");
                		damage = random(damage/2);
                	}
            		message_vision(msg, me, weapon);
            	}
        	return damage;
       	}
}
