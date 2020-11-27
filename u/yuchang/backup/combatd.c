/* combatd.c for 4444����˭���������д
��Ҫ�޸���Ҫ��
һ���Թ���ֵ������븡�����㣬֧�ָ��߾�����skill
����killreward()��������ר�ŵ��ļ�ȥִ��
����do_attack()����������
*/

#pragma optimize all
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

string *guard_msg = ({
        CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�\n" NOR,
        CYN "$N������$n��һ��һ������ʱ׼���������ơ�\n" NOR,
        CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������\n" NOR,
        CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����\n" NOR,
        CYN "$N�������ƶ����Ų����Ż����֡�\n" NOR,
});

string *catch_hunt_msg = ({
        HIW "$N��$n������������ۺ죬���̴���������\n" NOR,
        HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR,
        HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR,
        HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR,
        HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR,
});

string *winner_msg = ({
        CYN "\n$N������Ц������˵���������ˣ�\n\n" NOR,
        CYN "\n$N˫��һ����Ц��˵����֪���ҵ������˰ɣ�\n\n" NOR,
        CYN "\n$Nʤ�����У����Ծ�����ߣ�̾�������ǰν��Ĺ���ãȻ��\n\n" NOR,
        CYN "\n$n������˼�����˵�����ⳡ�����������ˣ��»ؿ�����ô��ʰ�㣡\n\n" NOR,
        CYN "\n$n���һ�ݣ��޺޵�˵�������ӱ���ʮ�겻��\n\n" NOR,
        CYN "\n$n������˼�����˵���������������ˣ��������ղ���������������\n\n" NOR,
});

void create()
{
    seteuid(getuid());
    set("name", "ս������");
    set("id", "combatd");
    set("chat_amount",1000000000);
}

string damage_msg(int damage, string type)
{
    string str;
    if( damage == 0 ) return "���û������κ��˺���\n";
    switch( type )
    {
        case "����":
        case "����":
            if( damage < 10 ) return "���ֻ������ػ���$p��Ƥ�⡣\n";
            else if( damage < 20 ) return "�����$p$l����һ��ϸ����Ѫ�ۡ�\n";
            else if( damage < 40 ) return "������͡���һ������һ���˿ڣ�\n";
            else if( damage < 80 ) return "������͡���һ������һ��Ѫ���ܵ��˿ڣ�\n";
            else if( damage < 160 ) return "������͡���һ������һ���ֳ�������˿ڣ�����$N������Ѫ��\n";
            else return "���ֻ����$nһ���Һ���$w����$p$l����һ������ǵĿ����˿ڣ���\n";
            break;
        case "����":
            if( damage < 10 ) return "���ֻ������ش���$p��Ƥ�⡣\n";
            else if( damage < 20 ) return "�����$p$l�̳�һ�����ڡ�\n";
            else if( damage < 40 ) return "������ۡ���һ��������$n$l����\n";
            else if( damage < 80 ) return "������ۡ���һ���̽�$n��$l��ʹ$p�������������˼�����\n";
            else if( damage < 160 ) return "��������͡���һ����$w����$p$l�̳�һ��Ѫ��ģ����Ѫ������\n";
            else return "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ���\n";
             break;
        case "����":
            if( damage < 10 ) return "���ֻ����������������Ĳ�Ӭ��΢���˵㡣\n";
            else if( damage < 20 ) return "�����$p��$l���һ�����ࡣ\n";
        else if( damage < 40 ) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n";
            else if( damage < 80 ) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n";
         else if( damage < 120 ) return "������项��һ����$n����������\n";
         else if( damage < 160 ) return "�����һ�¡��项��һ�����$n�����˺ü�������һ��ˤ����\n";
         else if( damage < 240 ) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n";
         else return "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ����\n";
         break;
        case "����":
         if( damage < 10 ) return "���ֻ�ǰ�$n������˰벽����������\n";
         else if( damage < 20 ) return "���$nʹ��һ������$p��$l���һ�����ˡ�\n";
         else if( damage < 40 ) return "���һ�����У���$n���ʹ��������ȥ��\n";
         else if( damage < 80 ) return "���$n�ƺ���һ��������һ����һ��ף���Ȼ���˵����ˣ�\n";
         else if( damage < 120 ) return "���$n��ɫһ�±�òҰף��������������˺ü�����\n";
         else if( damage < 160 ) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n";
         else if( damage < 240 ) return "������䡹��һ����$nȫ����Ѫ������������Ѫ���������\n";
         else return "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ����\n";
         break;
      default:
         if( !type ) type = "�˺�";
         if( damage < 10 ) str =  "���ֻ����ǿ���һ����΢";
         else if( damage < 20 ) str = "��������΢��";
         else if( damage < 30 ) str = "������һ��";
         else if( damage < 50 ) str = "������һ������";
         else if( damage < 80 ) str = "��������Ϊ���ص�";
         else if( damage < 120 ) str = "�������൱���ص�";
         else if( damage < 170 ) str = "������ʮ�����ص�";
         else if( damage < 230 ) str = "�����ɼ������ص�";
         else str =  "�����ɷǳ����µ�����";
            return str + type + "��\n";
    }
}

string eff_status_msg(int ratio)
{
        if( ratio==100 ) return HIG "��������Ѫ��ӯ����û�����ˡ�" NOR;
        if( ratio > 95 ) return HIG "�ƺ����˵����ˣ��������������������" NOR;
        if( ratio > 90 ) return HIY "�������������˵����ˡ�" NOR;
        if( ratio > 80 ) return HIY "���˼����ˣ������ƺ��������¡�" NOR;
        if( ratio > 60 ) return HIY "���˲��ᣬ������״������̫�á�" NOR;
        if( ratio > 40 ) return HIR "��Ϣ���أ�������ʼɢ�ң��������ܵ�����ʵ���ᡣ" NOR;
        if( ratio > 30 ) return HIR "�Ѿ��˺����ۣ���������֧����������ȥ��" NOR;
        if( ratio > 20 ) return HIR "�����൱�ص��ˣ�ֻ�»�������Σ�ա�" NOR;
        if( ratio > 10 ) return RED "����֮���Ѿ�����֧�ţ��ۿ���Ҫ���ڵ��ϡ�" NOR;
        if( ratio > 5  ) return RED "���˹��أ��Ѿ�����һϢ�����ڵ�Ϧ�ˡ�" NOR;
            return RED "���˹��أ��Ѿ�������в�����ʱ�����ܶ�����" NOR;
}

string status_msg(int ratio)
{
        if( ratio==100 ) return HIG "����������������һ��Ҳ���ۡ�" NOR;
        if( ratio > 95 ) return HIG "�ƺ���Щƣ����������Ȼʮ���л�����" NOR;
        if( ratio > 90 ) return HIY "������������Щ���ˡ�" NOR;
        if( ratio > 80 ) return HIY "�����ƺ���ʼ�е㲻̫��⣬������Ȼ�������ɡ�" NOR;
        if( ratio > 60 ) return HIY "�������꣬������״������̫�á�" NOR;
        if( ratio > 40 ) return HIR "�ƺ�ʮ��ƣ����������Ҫ�ú���Ϣ�ˡ�" NOR;
        if( ratio > 30 ) return HIR "�Ѿ�һ��ͷ�ؽ����ģ������������֧����������ȥ��" NOR;
        if( ratio > 20 ) return HIR "�������Ѿ����������ˡ�" NOR;
        if( ratio > 10 ) return RED "ҡͷ���ԡ�����бб��վ��վ���ȣ��ۿ���Ҫ���ڵ��ϡ�" NOR;
            return RED "�Ѿ���������״̬����ʱ������ˤ����ȥ��" NOR;
}

varargs void report_status(object ob, int effective)
{
    if( effective )
        message_vision("($N"+eff_status_msg((int)ob->query("eff_qi")*100/(int)ob->query("max_qi"))+")\n",ob);
      message_vision("($N"+status_msg((int)ob->query("qi")*100/(int)ob->query("max_qi"))+")\n",ob);
}

//�ú����ṩÿ�й��߹���ֵap,���ߵ��Ṧ����ֵdp.������ֵpp,����ÿ�ж�˫��������
varargs int skill_power(object ob, string skill, int usage)
{
   int status, level, power,mapped_dodge;
   if( !living(ob) ) return 0;
   level = ob->query_skill(skill);
   switch(usage)
   {
        case SKILL_USAGE_ATTACK:
        level += ob->query_temp("apply/attack");
      break;
    case SKILL_USAGE_DEFENSE:
        level += ob->query_temp("apply/defense");
      if(level < 0) level = 0;
            break;
    }
   if( !level ) return (int)ob->query("combat_exp") / 2;
//�����ǴӺ����do_attack���ص�ȡֵ����
   if(skill=="parry")
         power = (level / 3.0)*level/1000.0*level*(100 + ob->query_temp("down/parry"));
   else if(skill=="dodge")
   {
      if(!ob->query_skill_mapped("dodge"))
         mapped_dodge=0;
      else if(!intp(mapped_dodge=SKILL_D(ob->query_skill_mapped("dodge"))->query_dodge_level()))
         mapped_dodge=0;
      power = (level / 3.0)*level/1000.0*level*(100 + ob->query_temp("down/dodge")+mapped_dodge);
   }
   else
      power = (level / 3.0)*level/10.0*level;

   if (usage == SKILL_USAGE_ATTACK)
      return to_int((power + ob->query("combat_exp")) / 30.0 * (ob->query_str() + ob->query_temp("str")));
   else
      return to_int((power + ob->query("combat_exp")) / 30.0 * (ob->query_dex() + ob->query_temp("dex")));
}

varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
   mapping my, your, prepare, action;
   string limb, *limbs, result;
   string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
   mixed foo;
   int ap, dp, pp;
   int damage, damage_bonus, defense_factor;
   int cost;
   int wounded = 0;

   my = me->query_entire_dbase();//ȡ�����������в�������
   your = victim->query_entire_dbase();

   prepare = me->query_skill_prepare();//���ȭ��
   if (!prepare) prepare = ([]);
   if( objectp(weapon) )
      attack_skill = weapon->query("skill_type");
   else if ( sizeof(prepare) == 0) attack_skill = "unarmed";
   else if ( sizeof(prepare) == 1) attack_skill = (keys(prepare))[0];
   else if ( sizeof(prepare) == 2) attack_skill = (keys(prepare))[me->query_temp("action_flag")];

   me->reset_action();
   action = me->query("actions");
   if( !mapp(action) )
   {
      me->reset_action();
     action = me->query("actions");
      if( !mapp(action) )
      {
         CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s(%s): bad action = %O",
                                me->name(1), me->query("id"), me->query("actions", 1)));
         return 0;
      }
   }

   if (me->query_temp("action_flag") == 0)
    result = "\n" + action["action"] + "��\n";
   else result = "\n" + "������"+action["action"] + "!\n";//���ȭ������������Ϣ

   limbs = victim->query("limbs");     //���干16����λ
   limb = limbs[random(sizeof(limbs))];//���ȡ1��

   ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
   if( ap < 1) ap = 1;
   if (intp(action["dodge"]))
      victim->set_temp("down/dodge", action["dodge"]);//�Ա���������������
   else victim->set_temp("down/dodge",0);

   dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
   if( dp < 1 ) dp = 1;
   if( victim->is_busy() ) dp = dp - dp/5;
// �� AP/(AP+DP) ��ֵ���ж��Ƿ����жԷ�
// ����AP��DP������0,�������ǼȻ���б���,Ҳ�п��ܱ����˴���
   if( random(ap + dp) < dp )            // �����߶����һ��
   {
      dodge_skill = victim->query_skill_mapped("dodge");
      if( !dodge_skill ) dodge_skill = "dodge";
         result += SKILL_D(dodge_skill)->query_dodge_msg(limb,victim);//��ʾ�����Ϣ
      if( dp < ap && (!userp(victim) || !userp(me))   //DP<AP�Ҳ�����ҶԴ�
          &&random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 )
      {
         your["combat_exp"] += 1;
         victim->improve_skill("dodge", 1);//����ʱ�ṦԽСԽ�׳�exp��skill
      }
      if( (ap < dp) && !userp(me) )//AP<DP�ҹ�������NPC (û���壬NPC����Ҫ,��ȥ��)
      {
          if( random(my["int"]) > 15 ) my["combat_exp"] += 1;
          me->improve_skill(attack_skill, random(my["int"]));
      }
      damage = RESULT_DODGE;
   }
   else //������û�������
   {
      if (intp(action["parry"]))
         victim->set_temp("down/parry", action["parry"]);
      else victim->set_temp("down/parry",0);
      if( victim->query_temp("weapon") ) //������������
      {
         pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
         if( !weapon ) pp *= 2;  //�����߿��֣�parry�ӱ�
      }
      else   //������û������
      {
         if( weapon ) pp = 0;     //��������������parryΪ��
         else pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE); //˫������,Ӧ���м�,ȡparryֵ����ȥ.(by llm)
      }
      if( victim->is_busy() ) pp = pp - pp/5;
      if( pp < 1 ) pp = 1;
      if( random(ap + pp)< pp )    //��ס��һ��
      {
         parry_skill = victim->query_skill_mapped("parry");
         if( !parry_skill ) parry_skill = "parry";            //û�м����м�
// added by xker---------
         else
         {
            if(victim->query_temp("weapon"))    //���������м���Ϣȡ�Ը����������⹥��
               parry_skill =  victim->query_skill_mapped((victim->query_temp("weapon"))->query("skill_type"));
            else parry_skill = "parry";//???����Ϊû����ȡȭ�Ž����м�
         }
         if(!parry_skill) parry_skill = "parry";  //����ʡ����ֹȡ�������⹥��skill��������һ�л�ִ�д�
         if(!SKILL_D(parry_skill)->query_parry_msg(victim))
			 result += SKILL_D("parry")->query_parry_msg(victim,weapon);//ȡparry.c����Ϣ
         else
	         result += SKILL_D(parry_skill)->query_parry_msg(victim);
//--------------
         if( pp < ap && (!userp(victim) || !userp(me))//������ҶԴ�
            &&random(your["jing"]*100/your["max_jing"] + your["int"]) > 50 )
         {
            your["combat_exp"] += random(2);
            victim->improve_skill("parry", 1);//�м�ʱ��Խ��Խ�׳�exp��skill
         }
         damage = RESULT_PARRY;
      }
      else //��������߽Ӳ�ס����
      {
         damage = me->query_temp("apply/damage");
         damage = (damage + random(damage)) / 2;
         if( action["damage"] )
            damage += action["damage"] * damage / 100;//���Ͻ������书���˺�����ֵ
         damage_bonus = me->query_str();//������/inherit/skill/force.c�е�hit_obʵ��(�̳�)
         if( my["jiali"] && (my["neili"] > my["jiali"]) )
         {
            if( force_skill = me->query_skill_mapped("force") )
            {
                foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
                if( stringp(foo) ) result += foo;
                else if( intp(foo) ) damage_bonus += foo;
            }
         }
         if( action["force"] )
            damage_bonus += action["force"] * damage_bonus / 100;//�书��force�ǶԱ���������
         if( martial_skill = me->query_skill_mapped(attack_skill) )
         {
            foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         if( weapon )
         {
            foo = weapon->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         else
         {
            foo = me->hit_ob(me, victim, damage_bonus);
            if( stringp(foo) ) result += foo;
            else if(intp(foo) ) damage_bonus += foo;
         }
         if( damage_bonus > 0 )
            damage += (damage_bonus + random(damage_bonus))/2;
         if( damage < 0 ) damage = 0;
            defense_factor = your["combat_exp"];
         while( random(defense_factor) > my["combat_exp"] )
         {
            damage -= damage / 3;
            defense_factor /= 2;
         }
//damage��ʵ���˺�Ч��
         damage = victim->receive_damage("qi", damage*2/3, me );   //me�Ǽ�ס��˭����˺���ǰ��
         if(random(damage) > (int)victim->query_temp("apply/armor")
            && ( (me->is_killing(victim->query("id")))             //kill״̬��
           && ((!weapon) && !random(4) || weapon && !random(2) )
            || ( (!weapon) && !random(7) || weapon && !random(4) ) )  )
         {
               damage = (damage-(int)victim->query_temp("apply/armor"))*2/3;//��ȥ��damageΪ����BUG
               victim->receive_wound("qi",damage, me);//�˺���Ч��ֵ
               wounded = 1;
         }
         result += damage_msg(damage, action["damage_type"]);

         if( !userp(me) || !userp(victim) ) //����ҶԴ�
         {
            if( (ap < dp)&&(random(my["jing"]*100/my["max_jing"] + my["int"]) > 30) )
            {
               my["combat_exp"] += 1;
               if( my["potential"] - my["learned_points"] < 100 )
               my["potential"] += 1;
               me->improve_skill(attack_skill, 1);//����ʱ����Խ��exp��skillԽ��
            }
            if( random(your["max_qi"] + your["qi"]) < damage )
            {
               your["combat_exp"] += 1;
               if( your["potential"] - your["learned_points"] < 100 )
               your["potential"] += 1;
            }
         }
      }
   }
   if(victim->query_temp("weapon"))
      result = replace_string(result,"$W",(victim->query_temp("weapon")->name())); //�м��ߵ�����
      result = replace_string( result, "$l", limb );
   if( objectp(weapon) )
      result = replace_string( result, "$w", weapon->name() );
   else if( stringp(action["weapon"]) )
      result = replace_string( result, "$w", action["weapon"] );
   else if( attack_skill == "finger" )
      result = replace_string( result, "$w", "��ָ" );
   else if( attack_skill == "leg" )
      result = replace_string( result, "$w", "��" );

   message_vision(result, me, victim );

   if( wizardp(me) && (string)me->query("env/combat")=="verbose" )
   {
    if( damage > 0 )
        tell_object(me, sprintf( GRN "AP��%d��DP��%d��PP��%d���˺�����%d\n" NOR,
            ap/100, dp/100, pp/100, damage));
      else
         tell_object(me, sprintf( GRN "AP��%d��DP��%d��PP��%d\n" NOR,
            ap/100, dp/100, pp/100));
   }

   if( damage > 0 )
   {
      report_status(victim, wounded);
      if( victim->is_busy() ) victim->interrupt_me(me);
      if( (!environment(me)->check_yanwu()&&!me->is_killing(your["id"])) &&
          (!victim->is_killing(my["id"])) &&
          victim->query("qi")*2 <= victim->query("max_qi")) //���ԷǶ�ɱ
      {
         me->remove_enemy(victim);
         victim->remove_enemy(me);
         message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);//�ֳ�ʤ��
   }
   }
   if( functionp(action["post_action"]) )
      evaluate( action["post_action"], me, victim, weapon, damage);
   if( attack_type==TYPE_REGULAR
       &&damage < 1
       &&victim->query_temp("guarding") )
   {
      victim->set_temp("guarding", 0);
      if( random(my["dex"]) < 5 )     //������Ҫ
      {
         message_vision("$Nһ�����У�¶����������\n", me);
         do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);//��������
      }
      else
      {
         message_vision("$N��$n����ʧ�󣬳û�����������\n", victim, me);
         do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);//����һ��
      }
   }
}

void fight(object me, object victim)
{
    object ob;
   if( !living(me) ) return;

   if( victim->is_busy() || !living(victim) )
   {
    me->set_temp("guarding", 0);
      if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);

      if( me->is_fighting(victim) && victim->is_fighting(me))
        if( (!objectp(me->query_temp("weapon"))
        && sizeof(me->query_skill_prepare()) > 1)
         ||( objectp(me->query_temp("weapon"))
         &&(me->query_temp("weapon"))->query("skill_type") == "sword"
         && me->query_skill("pixie-jian", 1) >= 60
         && me->query_skill_mapped("sword") == "pixie-jian") )
      {
        me->set_temp("action_flag",1);
         do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
         me->set_temp("action_flag",0);
      }
   }
   else if( random( (int)victim->query_dex() * 3 ) > (int)me->query_str())
   {
    me->set_temp("guarding", 0);
      if( !victim->is_fighting(me) ) victim->fight_ob(me);
        do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);

      if( me->is_fighting(victim) &&victim->is_fighting(me))
      if( (!objectp(me->query_temp("weapon"))
        && sizeof(me->query_skill_prepare()) > 1)
         ||( objectp(me->query_temp("weapon"))
         &&(me->query_temp("weapon"))->query("skill_type") == "sword"
         && me->query_skill("pixie-jian", 1) >= 60
         && me->query_skill_mapped("sword") == "pixie-jian") )
      {
        me->set_temp("action_flag",1);
         do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
         me->set_temp("action_flag",0);
      }
    }
   else if( !me->query_temp("guarding"))
   {
    me->set_temp("guarding", 1);
        message_vision( guard_msg[random(sizeof(guard_msg))], me, victim);
         return;
   }
   else return;
}

void auto_fight(object me, object obj, string type)
{
    if( !userp(me) && !userp(obj) ) return;//����NPC�Լ�������
   if( me->query_temp("looking_for_trouble") ) return;
       me->set_temp("looking_for_trouble", 1);

      // This call_out gives victim a chance to slip trough the fierce guys.
    call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
    int shen;
    if( !me || !obj ) return;                 // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)              // Are we busy fighting?
        ||      !living(me)                       // Are we capable for a fight?
        ||      environment(me)!=environment(obj) // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight"))// Are we in a peace room?
            return;
    shen = (int)me->query("shen");
    if(shen < 0)
        shen = 0 - shen;
        message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);
    if( !userp(me) || (int)me->query("neili") > (random(shen) + shen) / 2 )
        return;
   if( shen > ((int)me->query("neili") * 5)&&!wizardp(obj) )
    {
        message_vision("$N����$n�ȵ���"+ RANK_D->query_self_rude(me)+"����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n",me,obj);
      me->kill_ob(obj);
   }
   else
   {
    message_vision("$N����$n�ȵ���ι��"+RANK_D->query_rude(obj)+"��"+RANK_D->query_self_rude(me)
        +"�������˴�ܣ����������ְɣ�\n",me,obj);
      me->fight_ob(obj);
   }
}

void start_hatred(object me, object obj)
{
    if( !me || !obj ) return;                      // Are we still exist( not becoming a corpse )?
    me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)                  // Are we busy fighting?
        ||      !living(me)                        // Are we capable for a fight?
        ||      environment(me)!=environment(obj)  // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight"))// Are we in a peace room?
            return;
	if(me->query("can_speak"))
        message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    else
        message_vision( catch_hunt_msg[random(2)], me, obj);
	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
    if( !me || !obj ) return;                   // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if(     me->is_fighting(obj)                  // Are we busy fighting?
    ||      !living(me)                         // Are we capable for a fight?
    ||      environment(me)!=environment(obj)   // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
    ||      environment(me)->query("no_fight")) // Are we in a peace room?
        return;
      me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
    if( !me || !obj ) return;                      // Are we still exist( not becoming a corpse )?
        me->set_temp("looking_for_trouble", 0);
    if( me->is_fighting(obj)                       // Are we busy fighting?
        ||      !living(me)                         // Are we capable for a fight?
        ||      environment(me)!=environment(obj)   // Are we still in the same room?
        ||      environment(me)->query("sleep_room")
        ||      environment(me)->query("no_fight")) // Are we in a peace room?
        return;
      me->kill_ob(obj);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    switch(event)
   {
        case "dead":
            message_vision("\n$N���ˡ�\n\n", ob);
            break;
        case "unconcious":
            message_vision("\n$N����һ�����ȣ����ڵ���һ��Ҳ�����ˡ�\n\n", ob);
            break;
        case "revive":
            message_vision("\n$N���������۾��������˹�����\n\n", ob);
            break;
   }
}

void winner_reward(object killer, object victim)
{
        killer->defeated_enemy(victim);
}


