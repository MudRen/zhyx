// yufeng-zhen.c ��Ĺ�����
// by April 2001.09.28

#include <ansi.h>
#include <weapon.h>

inherit THROWING;

void create()
{
	set_name("�����", ({ "yufeng zhen", "zhen", "needle" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һöϸ��ţë�Ľ��룬ɢ���������Ļ��㡣\n");
		set("unit", "��");
		set("base_unit", "ö");
		set("value", 0);
		set("damage", 5);
		set("armor_type", "embed");
		set("armor_prop/armor",1);
		set("armor_prop/attack", -30);
		set("armor_prop/defense", -30);
		set("armor_prop/unarmed", -30);
		set("no_sell", 1);
		set("unequip_msg", HIR"$Nһҧ����$n���˿��ϰ���������һ����Ѫ�͵�ӿ�˳�����\n"NOR);
	}
	set_amount(15);
	setup();
}

int wear() { return 0; }

int do_embed()
{
	::wear();
	set("no_drop", 1);
	set("no_get", 1);
	environment()->apply_condition("embedded", 100);
        environment()->affect_by("yf_zhen_poison",
                ([ "level" : 400,
                   "id"    : "yufeng zhen",
                   "duration" : 20]));
	return 1;
}

int unequip()
{
	::unequip();
	set("no_drop", 0);
	set("no_get", 0);
	set("embedded", 0);
	environment()->apply_condition("embedded", 0);
	environment()->receive_damage("qi", 200+random(1000));
	return 1;
}

int throw_ob(object me, object victim)
{
	int ap, dp;
	string limbs, dodge_skill, str;
	object ob2, ob = this_object();

	message_vision(HIG"$N����һ�һ�������$n�����ȥ�������������ŵ����Ļ��㡣\n" NOR, me, victim);
	ap = (int)me->query_skill("yufeng-zhen", 1)+(int)me->query("jiali");
	dp = (int)victim->query_skill("dodge");
	ap *= me->query("combat_exp")/1000;
	dp *= victim->query("combat_exp")/1000;
	
	ap = random(ap);
	limbs = victim->query("limbs");

        if (ap > dp && !victim->query_temp("armor/embed")){
                message_vision(CYN"\n���$Nһ�����£��������Ȼ������$N��"+limbs[random(sizeof(limbs))]
                          +"��\n"NOR, victim, ob);
                                 ob2=new(__FILE__);
                                 ob2->set_amount(1);
                                 ob2->set("embedded", 1);
                                 ob2->move(victim);
                                 ob2->do_embed();
                                 victim->receive_wound("qi", me->query_str()
                                 *ob->query("damage"), me);
	                         victim->kill_ob(me);
				 ob->add_amount(-1);
   }
   else{
	if (victim->query("neili") > me->query("neili"))
        message_vision(RED"$n����һ����һ���ھ����������ǽ��뼤��б��һ�ԣ����ڵ��ϡ�\n" NOR, me, victim);

	else {
	dodge_skill = victim->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                str = SKILL_D(dodge_skill)->query_dodge_msg();
                message_vision(str, me, victim);
	}
	if( !victim->is_killing(me) ) victim->kill_ob(me);
	me->start_busy(1+random(3));
	ob2=new(__FILE__);
        ob2->set_amount(1);
	ob2->move(environment(me));
	ob->add_amount(-1);
        }
        return 1;
}    

string query_autoload()
{
        if( query("equipped") )
        return query_amount() + "";
}

void autoload(string param)
{
        int amt;

        if( sscanf(param, "%d", amt)==1 )
                set_amount(amt);
        set("embedded", 1);
        set("no_drop", 1);
        set("no_get", 1);
        ::wear();
}
