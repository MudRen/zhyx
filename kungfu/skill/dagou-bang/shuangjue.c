//buy gentl
//Ҫ�����Բ�С��28��ת��ǰ����С��47��ת��������С��52��
//�򹷰���400��ʱ��������ǰ2�У��Ժ�ȼ�ÿ����100���Ͷ��һ�С�
//ת��ǰ����ܳ�5�л�ѧ����
//ת��������ܳ�6�л�ѧ����
//��׼���п����书ʱ�����Զ�ж�±������ڻ�ѧ���еĻ����ϣ�ת��ǰ���ٳ�1����ͨ�У�ת������ٳ�3����ͨ���С�
//�˺������о��뱾���ڹ��йء�
#include <ansi.h>
#include <combat.h>


#define ZHEN HIR "��" HIW "��" HIY "��" HIG "˫��" NOR HIR "��"

inherit F_SSERVER;
inherit F_CLEAN_UP;

mapping valid_types = 
([
	"finger":   "ָ��",
	"hand":     "�ַ�",
	"cuff":     "ȭ��",
	"claw":     "צ��",
	"strike":   "�Ʒ�",
	"unarmed":  "ȭ��",
]);

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ",
"�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ", "����Ѩ", "����Ѩ", "���Ѩ",
"�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", }); 

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
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
                */

        if (! target) target = offensive_target(me);
		
		weapon = me->query_temp("weapon"); 
		
		if (me->query("int") < 28)
		  return notify_fail("����������Բ������޷�ʩչ" ZHEN "������\n");		
		
		if (me->query("dex") < 47)
		  return notify_fail("������������������������ɣ�����\n");
		  
		if (me->query("reborn") && me->query("dex") < 52)
		  return notify_fail("���������������ת�����������ɣ�����\n");		

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHEN "��\n");			       							

        if (me->query_skill_mapped("staff") != "dagou-bang")
                return notify_fail("��û�м����򹷰���������ʩչ" ZHEN "��\n");

        if(me->query_skill("dagou-bang", 1) < 400 )
                return notify_fail("��Ĵ򹷰���������죬����ʩչ" ZHEN "��\n");

        if( (int)me->query_skill("force") < 600 )
                return notify_fail("����ڹ���Ϊ����������ʩչ" ZHEN "��\n");

        if( (int)me->query("max_neili") < 8000 )
                return notify_fail("���������Ϊ̫��������ʩչ" ZHEN "��\n");

        if( (int)me->query("neili") < 1200 )
                return notify_fail("�����ڵ�����̫��������ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
			 
			  
			  
        msg = HIW"$N���е�" + weapon->name() + HIW "΢΢�����������򹷰�����ʹ�ñ��Ī�⣬һ��һ�����Ʊ�׾��ȴ���������������\n\n" NOR;


        bp = me->query_skill("huntian-qigong", 1) + me->query_skill("jiaohua-neigong", 1) + me->query_skill("huimeng-xinfa", 1);
        ap = me->query_skill("staff") * 2 + bp / 3;
                damage = ap + random(ap);        
		
        if (me->query_skill("dagou-bang", 1) > 399)     
	 {
      dp = target->query_skill("dodge") * 2;

	  msg += HBRED"$N��Цһ���������ڰ��ˣ��漴̽����ǰ����$n˫��ɨȥ��\n" NOR;   
       
                 if (ap * 4 / 5 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "ֻ���۵�һ������һ�����䲻�������$n��"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һ����\n" NOR;
        }	
		
	  dp = target->query_skill("dodge") * 2;
		
	  msg += HBGRN"$Nһ��ʹ����ϣ���ʽ��Ȼδ�ϣ��������£��ǰ���Ȼ�����۾�һ�㣬��$n���ź�Х������\n" NOR;   
       
                 if (ap * 4 / 5 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                   HIR "ֻ���۵�һ������һ�����䲻�������$n��"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һ����\n" NOR;
        }		
	   }
	   
        if (me->query_skill("dagou-bang", 1) > 499)     
	 {
      dp = target->query_skill("parry") * 2;

	  msg += HBYEL"$Nһ��δ�ϴ���������������֮�����һȦ��Ӱ����$n����������\n" NOR;   
       
                 if (ap * 3 / 4 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                   HIR "ֻ���۵�һ������һ�����䲻�������$n��"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һ����\n" NOR;
        }	
	   }	   

        if (me->query_skill("dagou-bang", 1) > 599)     
	 {
      dp = target->query_skill("force") * 2;

	  msg += HBBLU"$N����ɱ�����֣�һ�����ɵİ��У�Ѹ�װ��ֱȡ$nü�ġ�\n" NOR;   
       
                 if (ap * 2 / 3 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                   HIR "ֻ���۵�һ������һ�����䲻�������$n��"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һ����\n" NOR;
        }	
	   }

        if (me->query_skill("dagou-bang", 1) > 699)     
	 {
      dp = target->query_skill("martial-cognize", 1) * 3;

	  msg += HBMAG"$N�������£�����֮������ճ��$n����һ�㣬��$n������һƬ��Ӱ֮�У�ʵ���Ǿ�����ף�\n" NOR;   
       
		 if (ap / 2 + random(ap) > dp)
        {
          msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                   HIR "ֻ���۵�һ������һ�����䲻�������$n��"
								   HIY + xue_name[random(sizeof(xue_name))] + 
								   HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR);	
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һ����\n" NOR;
        }
           }
           message_combatd(msg, me, target);
	   
    if (me->query_skill("dagou-bang", 1) > 799 && (int)target->query("qi") > 0 && me->query("reborn") && me->is_fighting(target))         //ת��������
	 {
      ap = me->query_skill("staff") * 2 + bp;
      dp = target->query_skill("force") + target->query_skill("dodge")+ target->query_skill("parry") + target->query_skill("martial-cognize", 1);
	  
	  
	  me->add("neili", -800);

          msg = HBCYN"$N����һƬƽ����������֮���϶�Ϊһ���������޹������辡����ɲ�Ǽ���������Ӱ��ס$n��\nʹ���˴򹷰�������֮�ܣ��������Ƿ�����˼��\n" NOR;   
       
                 if (ap * 3 / 4 + random(ap*2) > dp)
        {
		 
                 damage = ap + random(ap);

          target->receive_damage("qi", damage*2, me);
          target->receive_wound("qi", damage, me);  
          str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
          msg += HIR "ֻ���۵�һ������һ�����䲻�������$n��" 
                                                 HIY + xue_name[random(sizeof(xue_name))] +  
                                                 HIR "��$n���ɵòҽ�һ������������ȫ��Ѫɫ��\n" NOR;
          msg += "($n"+str+")\n";
        } else
        {
                msg += HIY"$n�󾪣�����"+ weapon->name()+HIY"������磬���޿ɵ������޿�����ֻ�����ܿ������С�\n" NOR;
        }
        message_combatd(msg, me, target);
	   	   
           }

       if (! mapp(pmap) || sizeof(pmap) != 0)   //��׼���п����书���ų��������
	    {
            msg = YEL "\n��İ���ʩչ��ϣ�����δ�������Ҹо����Ϲ���Ҳ�����˵ã���˳��һ�����е�" + weapon->name() + YEL"�����ֿ�ȭ\n"
                         YEL"��$n����������������\n" NOR;             
               message_vision(msg, me, target);

	      i=1;
		  if (me->query("reborn")) i=3;
          weapon->move(me, 1);   				
          me->add_temp("apply/attack", ap / 6);

          for (j = 0; j < i; j++)   //ת��ǰ��1�У�ת�����3��
          {		  		 
                        msg =WHT"\n��" + chinese_number(j+1) + WHT"�У�����������"NOR;
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


