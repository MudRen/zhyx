// Code of JHSH
// /kungfu/skill/chousui-zhang/sandu  pfm ɢ��
// Summer, 12/28/96.
// modified by sdong 7/16/1999. Let ppl can sandu on NPC with exp 1/3 higher than self
// modified by wsky, let ppl can sandu, san some poison out to npc or player if they are
// poisoned. and after sandu will be able to maxsuck for a certain time. desigened this
// so there is no wangding conflit btw xx ppl  4/3/00

//wzfeng cut sandu npc add exp 2000 11
                
#include <ansi.h>
//#include <string.h>

inherit F_SSERVER;

#include "/kungfu/skill/chousui-zhang/poison_list.h" //blush

int perform(object me, object target)
{
        object room, mengzhu;
        
        string poi_name, poison, poi_color, col_ansi;
        int i, poi_lvl,poi_amount, cure_amount, cure, hgdf, dp;
        mapping myfam,my_poison;
        
        my_poison = ([]);
        if( !target ) target = offensive_target(me);
        
        if( base_name(environment(me)) == "/d/city/leitai" )
                return notify_fail("������̨�ϲ�����ɢ����\n");

        if( getuid(environment(me)) == "pk" )
                return notify_fail("���˳��ﲻ��ɢ����\n");

        if (me->query_temp("weapon"))
                return notify_fail("��ֻ�п��ֲ���ʹ�ó����ơ�\n");

        if (!(me->query_skill_mapped("strike") == "chousui-zhang"))
                return notify_fail("�㲢û�м��������ƣ������ɢ����\n");

        if (!(me->query_skill_prepared("strike") == "chousui-zhang"))
                return notify_fail("�㲢û��׼�������ƣ������ɢ����\n");


        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ��ɢ����\n");

        if( !target || !target->is_character() || !me->is_fighting(target))
                return notify_fail("�㲻��ս���С�\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        if( (int)me->query_skill("chousui-zhang", 1) < 30 )
                return notify_fail("��ĳ�������Ϊ������\n");

        if( (int)me->query_skill("poison", 1) < 50 )
                return notify_fail("��Ļ���������Ϊ������\n");

        if ( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("��û���˻����󷨣�\n");

        if( me->query("neili") <= 100 )
                return notify_fail("�������������\n");

        if( target->query_condition("poisoned") > 0 || ( me->query("last_sandu") == target->query("id") && userp(target) ) )
                return notify_fail("���������о綾���й������ã��ڴ�������ɢ����ʹ�㷴���亦��\n");


        for( i=0; i < sizeof(poison_list); i++ )
        {
             poison = poison_list[i]["poison"];
             if( mapp( my_poison = me->query_condition(poison)) &&
                 my_poison["remain"] > 0)
                break;
        }

        hgdf = (int)me->query_skill("huagong-dafa",1);  

        poi_lvl = (int)me->query_condition(poison, 1);


        message_vision(MAG "$N�����ƻ���̧��������ɫ������ϣ�ð��һ���ƺ��������Ŵ��һ����������$n���Ĺ�ȥ��\n\n" NOR, me,target);
        me->add("neili", -150);

        if( !userp(target) ) target->kill_ob(me);

        if (living(target))
                  dp = target->query("combat_exp")*5/12;
        else      dp = 0;
        if(me->query("combat_exp") > dp)
        {
                  if(((int)target->query("combat_exp")>me->query("combat_exp")*3/2 && userp(target)) ||
                    ((int)target->query("combat_exp")>me->query("combat_exp")*2/3 && !userp(target)))
                  {
                        if( me->query_skill("poison", 1) < random(target->query_skill("poison", 1) * 2))
                        {
                                tell_object(me, BLU "��һ������" +target->query("name") +"�ؿڣ����ϴ������ھ۶����ͣ��㲻�ܰѶ�ɢ���������亦��\n"NOR);
                                tell_object(target, BLU "��ֻ��һ�ɺ���Ϯ�棬�ƺ�һ�����ؿ����ơ�\n" NOR);
                                me->add("max_neili", - 1);
                                me->affect_by("xx_poison",
                                        ([ "level" : (int)me->query_skill("chousui-zhang") + random((int)me->query_skill("chousui-zhang")),
                                           "id"    : me->query("id"),
                                           "duration" : (int)me->query_skill("chousui-zhang")/20 ]));
                                target->receive_damage("qi", me->query_skill("chousui-zhang"),me);
                                target->affect_by("xx_poison",
                                        ([ "level" : (int)me->query_skill("chousui-zhang") + random((int)me->query_skill("chousui-zhang")),
                                           "id"    : me->query("id"),
                                           "duration" : (int)me->query_skill("chousui-zhang")/20 ]));
                                me->want_kill(target);
                                target->kill_ob(me);
                                return 1;
                        } else {
                                tell_object(me, BLU "��һ������" +target->query("name") +"�ؿڣ������������ֿ���˳�ư������������ƽ�" +target->query("name") +"���ڡ�\n"NOR);
                                tell_object(target, BLU "��ֻ��һ�ɺ���Ϯ�棬�н��������ֿ�������" +me->name() +"���綾��һ��һ���������ؿ��ϡ�\n"NOR);
                                          
                                me->add("max_neili", - 1 - (int)me->query_skill("huagong-dafa", 1)/15);
                                if (me->query_skill("poison", 1) < 101)
                                me->set("body_poison",me->query_skill("poison", 1)/10+1);
                                if (me->query_skill("poison", 1) > 100)
                                me->set("body_poison", me->query_skill("poison", 1));

                                target->receive_damage("qi",random((int)me->query_skill("chousui-zhang")),me);
                                target->receive_wound("jing", (int)me->query_skill("chousui-zhang"),me);
                                target->affect_by("xx_poison",
                                        ([ "level" : (int)me->query_skill("chousui-zhang") + random((int)me->query_skill("chousui-zhang")),
                                           "id"    : me->query("id"),
                                           "duration" : (int)me->query_skill("chousui-zhang")/20 ]));
                                target->apply_condition("poisoned", me->query_skill("poison", 1)*3);

                                if(me->query("maxsuck")<400) me->set("maxsuck",400);
                                me->set("last_sandu", target->query("id"));
                                log_file("POISON", sprintf("%s(%s) ɢ�� on %s.\n", me->query("name"), getuid(me), target->query("name")));
                                me->want_kill(target);
                                target->kill_ob(me);
                                return 1;
                        }
                } 
              
                tell_object(me, BLU "��һ������" +target->query("name") +"�ؿڣ�����" +target->query("name") +"����̫�����㷴���ܰѶ����Ƴ�ȥ����������\n"NOR);
                tell_object(target, BLU "��ֻ��һ�ɺ���Ϯ�棬�ƺ�һ�����ؿ����ơ�\n" NOR);
                target->receive_damage("qi",random((int)me->query_skill("chousui-zhang")),me);
                target->receive_wound("jing", (int)me->query_skill("chousui-zhang"),me);
                target->affect_by("xx_poison",
                        ([ "level" : (int)me->query_skill("chousui-zhang"),
                           "id"    : me->query("id"),
                           "duration" : (int)me->query_skill("chousui-zhang")/30 ]));
                target->start_busy(1+random(3));

                myfam=me->query("family");
                
                if (mapp(my_poison) && my_poison["remain"] > 0 && myfam["family_name"] == "������") {
                        tell_object(me, HIG "������ʹ��ھ������������е�"+my_poison["name"]+HIG"����������ڡ�\n"NOR);
                        tell_object(target, HIR "������ؿ�һ�ۣ������еĲ�ֻ�����޶���\n"NOR);                     
                        me->apply_condition(poison, 0);
                        my_poison["id"] = me->query("id");
                        target->apply_condition(poison, my_poison);     
                }
 
       } else message_vision(HIY "$p�Ͻ�����Ծ�����ɣ��㿪$P�Ĺ�����\n" NOR, me, target);

        me->start_busy(1+random(5));
        me->want_kill(target);
        target->kill_ob(me);
        return 1;
}

