//By baqukq for 2004.08.28

#include <ansi.h>
#include <combat.h>
#define SHA "��" HIR "�����޻�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg, number, *limbs;
        string ba;
        int ap, dp, a, b, i, lmt;
        int damage, extra, skill, forcee;
        int count, times;
        int lvl, num;
 
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/baqukq-sword/sha"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHA "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ���Ϊ����������ʩչ" SHA "��\n");

        if (me->query_skill("baqukq-sword", 1) < 180)
                return notify_fail("������콣����Ϊ����������ʩչ" SHA "��\n");

        if (me->query_skill_mapped("sword") != "baqukq-sword")
                return notify_fail("��û�м������콣��������ʩչ" SHA "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����������������ʩչ" SHA "��\n");

        /*if (! me->query("aaaa"))
                return notify_fail("��ѧ��ûѧ����ôʩչ" SHA "��\n");*/

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        a = me->query("aaaa");
        b = random(a);
//��һ�� ����       
        if (b == 0)
         {
         msg = HIR "$N" HIR "������ģ�����ȫ�����ڽ���Я������֮�Ʒ�����$n"
              HIR "��ǰ��ȥ��\n" NOR;

        if (random(me->query_skill("sword")) > target->query_skill("parry") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("sword");
                damage = damage / 2 + random(damage);
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "���$p" HIR "�мܲ�������$P" HIR
                                           "һ�������ؿڣ������̶��������߹ǣ����"
                                           "һ�����Ѫ��\n" NOR);
        } else
        {
                me->start_busy(3);
                me->add("neili", -100);
                msg += CYN "����$p" CYN "�����мܣ���¶�����������$P"
                       CYN "��һ����֮�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);
        	
         return 0;	
}
//�ڶ��� ʮ����
        if (b == 1)
         {
        extra = me->query_skill("baqukq-sword",1);
        msg = HIR  "$N���赭д���ӳ����⣬һ˲�����ʹ������ʮ��ʽ�����е�"+ weapon->name()+  NOR+HIR"��������.\n�����Ǻ�ˮ�����$n�̳�,��ؼ��ݷ������ɱ����\n\n" NOR;
        message_vision(msg,me,target);
	me->add_temp("apply/attack",extra/10);
	me->add_temp("apply/damage",extra/10);
	lmt = random(13)+1;
	for(i=1;i<=lmt;i++)
	{
        message_vision(BLINK HIR"------>>>>>>��"HIC+chinese_number(i)+HIR"��<<<<<<------"NOR,me,target);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
	}
        msg = CYN "\n\n$N�ĵ�"+chinese_number(i-1)+"���̳������еı仯���������������ˮ�ѵ���ͷ������Ҳ���ˣ�������\n\n"NOR;
	message_vision(msg,me,target);
        me->add_temp("apply/attack",-extra/10);
        me->add_temp("apply/damage",-extra/10);
	me->start_busy(2);

        return 0;
}
//������ ������
        if (b == 2)
         {
        skill = me->query("neili");
        forcee = target->query("neili")/5-50;
        if (forcee < 50) forcee = 50;
        me->add("neili", -400);

        me->start_busy(random(3));
	message_vision(HIR "\n$N������ϣ����������ָ���������һָ�������������������ڼ��ã�\n��ʱ���ذ��������޹⣬��صߵ���\n��һ����������ġ���תǬ������\n\n"
        NOR, me);
        if( skill +random(skill) > target->query("max_neili"))
        {
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));


        lvl = me->query("eff_qi")/(3+random(4));
	me->receive_damage("qi", 50);
//        lvl->receive_damage("qi",lvl,me,"perform"); 
//        target->receive_wound("qi", lvl,me,"perform");
	target->add("neili",-(forcee));
	me->add("neili", -100);
	message_vision(HIW"$n�����ڵء��������أ�ȫ��������ʧ��\n"NOR,me, target);
	target->start_busy(1);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
         }
         }
         else 	message_vision(HIY"����$p������$P����ͼ����û���ϵ���\n" NOR, me, target);

        return 0;
}
//������
        if (b == 3)
         {
        msg = HIR "$N" HIR "������Х������" + weapon->name() +
              HIR "б����һ���뻡�����������ʱ���������ޱȵ�"
              "ɱ����ֱ��$n" HIR "��ȥ��\n" NOR;

        ap = me->query_skill("sword") + me->query_str() * 10;
        dp = target->query_skill("force") + target->query_con() * 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                me->add("neili", -200);
//                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "ֻ��$n" HIR "һ���ҽУ�$N" HIR +
                                           weapon->name() + HIR "����һ��������Ƕ"
                                           "��$p" HIR "���ڳ�������һ��Ѫ�ꡣ\n"
                                           NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(4);
                msg += CYN "$n" CYN "��$P" CYN "������ӿ���������׵�"
                       "������æ������Ų������������\n" NOR;
        }
        message_combatd(msg, me, target);

        return 0;
}
//������
        if (b == 4)
         {
        skill = (int)me->query_skill("baqukq-sword", 1);
        if(skill < 60)
                return notify_fail("������콣�����𻹲�����\n");
        else 
            if(skill <60){
                times = 1;        
                number = "һ";}
            else
                if (skill <80){
                    times = 2;
                    number = "��";}
                else
                    if(skill <120 ){
                           times = 3;
                           number = "��";}
                else
                    if(skill <160 ){
                           times = 4;
                           number = "��";}
                else
                    if(skill <200 ){
                           times = 5;
                           number = "��";}
                     else{ 
                           times = 6;
                           number = "��";}

        me->delete("env/brief_message");
        target->delete("env/brief_message");
        damage = random((int)me->query_skill("sword")/3);

       message_vision(HIM"\n$NͻȻ����һ�䣬���е�"+ weapon->query("name")+ HIB"��Ӱ���٣������籡�������Ľ������������$n������"+number+"����\n"NOR,me,target, "");

        for(int q=1;q<=times;q++)
        COMBAT_D->do_attack(me, target, weapon);
        COMBAT_D->report_status(target, 0);
        me->receive_damage("jing", 20,target);
        me->add("neili", -(times*30+10));

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
        if(me->is_fighting() && target->is_fighting() &&
        environment(me) == environment(target) && times>5)
        {

        target->receive_damege("jing", damage,me,"pfm");
        target->receive_wound("jing", random(damage),me,"pfm");
        target->receive_damege("qi", damage+1,me,"pfm");
        target->receive_wound("qi", random(damage),me,"pfm");
        message_vision(HIR"\n���$n��$N�ġ����졻�������ģ���ǰһ�ڣ��������ɳ�������\n\n $n���Ͻ�����Ѫӿ��......\n" NOR,me,target,"");
                COMBAT_D->report_status(target, 0);
        }
        me->start_busy(1+random(2));
        me->set_temp("sky_end",time());

        return 0;
}
//������
        if (b == 6)
         {
        me->add("neili", -60);
        msg = WHT"ʹ�����һ�С��ޱ䡽��������������������������������������������������\n"NOR;
        message_combatd(msg,me,target,"");
        me->start_busy(1+random(1));

        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/8 ) 
        {
                        
                limbs=target->query("limbs");                   
                lvl=(int)(me->query_skill("baqukq-sword")/5);
                damage=random(lvl)+lvl;
                damage=damage+me->query_str()+random(me->query_temp("apply/damage"));
                num=random(lvl/2)+lvl/2;
                for(i=0;i<=num;i++)
                {
                        msg =HIR"$NͻȻ���һֻ�׻�ҧ��$p"+limbs[random(sizeof(limbs))]+"��\n"NOR;
                        message_combatd(msg,me,target,"");
                   target->receive_damage("qi",damage,me,"pfm");
                   target->receive_wound("qi",damage,me,"pfm");
                   
                }
                COMBAT_D->report_status(target);
                
        }

        return 0;
}
        if (b == 5)
         {
        msg = HIC "$N���һ����ȫ���Ĵ��ζ���$nֻ����$N����������Ӱ�����콣��ϯ�������\n $n����һ�ܣ���$N������·��$nֻ��סһ����\n"NOR;
    if (random(me->query_skill("force")) > target->query_skill("force")/3||
   random((int)target->query("combat_exp")) < (me->query("combat_exp")) )
    {
   //me->start_busy(2);
  // target->start_busy(random(3));
   damage = (int)me->query_skill("baqukq-sword", 1);
   damage = damage + random(damage);
   target->receive_damage("qi", damage);
   target->receive_wound("qi", damage/3);
   target->add("eff_qi", -damage);
   target->receive_damage("jing", damage);
   target->add("eff_jing", -damage);
   msg += HIC"$n����û����ܣ���ʱ����������$n��ͷ��\n"+HIR"$n��Ѫ����$n�Ծ���ǰһƬ�ʺ죬��ס���ߣ�\n"NOR;
   me->add("neili", -damage/5);
     me->start_busy(random(3));
   if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
                                  } 
    }else
    {
   me->start_busy(2);
   msg += HIY"����$p���Կ����������У����������̹Ȼ��ԣ�����ֻ�м�ס����ʵ�С�\n"NOR;
    }
    message_vision(msg, me, target);

        return 1;
}
        return 1;

}
