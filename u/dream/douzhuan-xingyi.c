inherit SKILL
int valid_enable(string usage) { return usage==parry; }
int valid_learn(object me) { return 1; }
int practice_skill(object me)
{
        if( (int)me->query(kee) < 30
        ||      (int)me->query(force) < 3 )
                return
notify_fail(�����������������û�а취��ϰ��ת���ơ�\n)
        me->receive_damage(kee, 30)
        me->add(force, -3)
        write(�㰴����ѧ����һ�鶷ת���ơ�\n)
        return 1
}
int parry_action(object me,object target,object target_weapon,int attack_type,mapping action,string limb)
{
        string msg
        object weapon,*enemy
        int dp,ap,attack_power,i,nb
        if((string)target->query(race)==Ұ��)       return 0
        if( !living(me))        return 0
        if( me->is_busy())      return 0
        if( (int)me->query_temp(oldsix/have_dz))      return 0
        if(target_weapon)       ap=target->query_skill(target_weapon->query(skill_type))
        else    ap=target->query_skill(unarmed)
        if(target_weapon)       {
                if(! weapon)    return 0
        }
        if( sizeof(enemy))              {
                for(i=0;i<sizeof(enemy);i++)    {
                        if( !objectp(enemyi)) continue
                        if( !living(enemyi))  continue
                        if( (int)enemyi->query(combat_exp) (int)me-query(combat_exp)/5 )        continue
                        nb++
                }
        }
        if( nb<1)       nb=1
        if((random(dp)/nb)<ap/2)        return 0
        me->set_temp(oldsix/have_dz,1)
        call_out(do_reset,5,me)
        msg+=HIW$n����һ�Σ�ʹ������ת���ơ��񹦣��Ա�֮�����Ʊ���NOR
        if(target_weapon)
        message_combat(msg,target,me)
        attack_power/=nb
        target->start_busy(1)
        COMBAT_D->do_attack_now(me,target,weapon,2,action,limb,attack_power)
return 1
}
int power_point()       {       return 2;       }
int hard_point()        {       return 2.5;     }
void do_reset(object me)
{
        if( !objectp(me))       return
        me->delete_temp(oldsix/have_dz)
}

