// guojing.c �޵д󽫾�
inherit NPC;
#include <ansi.h>
string * degree_desc = ({
       BLU "ʿ��" NOR,
       BLU "�λ�" NOR,
       HIC "�ν�" NOR,
       HIC "�Խ�" NOR,
       HIY "����" NOR,
       HIY "����" NOR,
       HIR "����" NOR,
       HIR "�ᶽ" NOR,
});               
string clear_degree(string arg);
int ask_degree();
int add_degree(object ob,int lv);
string ask_jianlou();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

void create()
{
        set_name("����", ({"yue fei", "yue", "fei"}));
        set("nickname", HIY"���ұ���"NOR);
        set("gender", "����");
        set("age", 41);
        set("long", 
                "�������˳ƾ��ұ����Ĵ󽫾����ɡ�\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set_temp("no_kill",1);
        set("chat_chance", 1);
        set("chat_msg", ({
                "����̾�˿������������Խ��Խ����...\n",
                "����˵���������ɷ�������һ��ҪΪ��Ϊ��\n",
        }));

        set("inquiry", ([
                 "�س�"  : (: ask_shoucheng :),
                 "����"  : (: ask_fuming :),
                 "����"  : (: ask_chetui :),
//                 "�ѻ�"  : (: ask_jianlou :), 
                ]));

        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 24000);
        set("max_neili", 24000);
        set("jiali", 500);
        
        set("combat_exp", 25000000);
        set("score", 200000);
         
        set_skill("force", 400);                // �����ڹ�
        set_skill("huntian-qigong", 400);        // ��������
        set_skill("unarmed", 400);                // ����ȭ��
        set_skill("xianglong-zhang", 400);        // ����ʮ����
        set_skill("dodge", 400);                // ��������
        set_skill("xiaoyaoyou", 400);                // ��ң��
        set_skill("parry", 400);                // �����м�
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");         
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");
        prepare_skill("unarmed","xianglong-zhang");
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {
                ene=query_enemy();
                
                if(sizeof(ene)>1) return "����"+RANK_D->query_respect(me)+"�Ե�Ƭ�̣����Ⱥ���"+sizeof(ene)+"λ�����д輸�£���\n";
                if(sizeof(ene)==1) return "����"+RANK_D->query_respect(me)+"�Ե�Ƭ�̣����Ⱥ�"+ene[0]->name()+"�д輸�£���\n";
        }

        if(me->query_temp("guo_shoucheng/mark_shadi") || me->query_temp("guo_jianlou/mark_jianlou") )
        return "��"+RANK_D->query_respect(me)+"���������������𣡡�\n";

       if ((int)me->query("combat_exp")<300000)
       return "��"+RANK_D->query_respect(me)+"���޸���֮�������Ǳ��������Ϊ�ã���\n";

       if ( (int)me->query_skill("force") < 20 )
       return "�س��Ǽ�Σ�չ������ҿ�"+RANK_D->query_respect(me)+"�Ļ����������㣡\n";

       if ( !me->query("family/family_name") )
       return "��"+RANK_D->query_respect(me)+"�������ɣ������������������ͣ���\n";

       if ((int)me->query_condition("jobshadi_failed"))
       {
        message_vision("$N����$nҡ��ҡͷ˵������ʧ���˻�������??\n", this_object(), me);
        return "��"+RANK_D->query_respect(me)+"�㻹�Ǳ��������Ϊ�ã���\n";
       }

       if( me->query("guo_shoucheng/failed") )
       {
         me->apply_condition("jobshadi_failed",16);
         return "���������ӣ����һ������ң���������\n";
       } 

       if ((int)me->query_condition("jobshadi_limit")>1)
       {
        message_vision("$N����$nҡ��ҡͷ˵���㲻����������??\n", this_object(), me);
        return "��"+RANK_D->query_respect(me)+"�������ĸ�λ��ȥ����\n";
       }

       if ((int)me->query_condition("guojob2_busy"))
       {
        message_vision(CYN"$N����$nҡ��ҡͷ˵��ƣ��֮ʦ������ս����\n"NOR,
                                                        this_object(), me);
        return "��"+RANK_D->query_respect(me)+"�㻹����Ϣһ�������ɣ���\n";
       }
       
       if (me->query("shen")>0)
       {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",1);
                        me->set_temp("guo_shoucheng/carry_location","eastgate1");                
                return "�����ڽ���ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ�������Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",2);
                        me->set_temp("guo_shoucheng/carry_location","northgate1");                
                return "�����ڽ���ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ�������Ű����ξ��سǰɡ�";

                       break;
                }        
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",3);
                        me->set_temp("guo_shoucheng/carry_location","southgate1");
                return "�����ڽ���ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ��ȸ���Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",4);
                        me->set_temp("guo_shoucheng/carry_location","westgate1");
                return "�����ڽ���ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ�׻����Ű����ξ��سǰɡ�";

                       break;
                }
        }
}



string ask_fuming()
{
        int job_pot,job_sc,job_exp,job_tihui,reward;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && me->query("guo_shoucheng/failed") )
        {
         me->delete_temp("guo_shoucheng");
         me->delete_temp("guo_jianlou"); 
         me->apply_condition("jobshadi_failed",15);
         return "���������ӣ����һ�����������������\n";
        } 

        if( me->query_temp("guo_shoucheng/help_killed")
            && !me->query_temp("guo_shoucheng/job_over") ) 
        {
                 job_exp=((int)me->query_temp("guo_shoucheng/help_killed"))*40;
                job_pot=job_exp*2/3;
                job_tihui=job_pot/2;
                job_sc=job_pot/2;
                job_exp=job_exp;
                me->add("combat_exp", job_exp);
                me->add("potential",job_pot);
                me->add("experience",job_tihui);
                me->add("score",job_sc);
                tell_object(me,HIW"�㱻������"+chinese_number(job_exp)+"�㾭��ֵ����"+chinese_number(job_pot)+"��Ǳ�ܣ���"+chinese_number(job_tihui)+"�����,"+chinese_number(job_sc)+"��������\n"NOR);
                me->delete_temp("guo_shoucheng/help_killed");        
                me->apply_condition("guojob2_busy",4);
                me->add("guo_shoucheng/reward_exp", job_exp);
                me->add("guo_shoucheng/reward_potential",job_pot);  
                me->add("guo_shoucheng/reward_experience",job_tihui);  
                me->add("guo_shoucheng/reward_potential",job_pot);  
        return "��"+RANK_D->query_respect(me)
               +"��Ϊ��ɱ�У���������\n";
        }
           
        if( (!me->query_temp("guo_shoucheng/mark_shadi")
                || !me->query_temp("guo_shoucheng/job_over")) 
             && (!me->query_temp("guo_jianlou/mark_jianlou")
                || !me->query_temp("guo_jianlou/job_over")) )    
        return "�������û�������ɣ�������ʲô������\n";
        
        if(me->query_temp("guo_shoucheng/killed_mgb")<2 
           && me->query_temp("guo_jianlou/killed_mgb")<2)
        {
         me->delete_temp("guo_shoucheng");

         me->delete_temp("guo_jianlou");  
         return "����ɱ�˼������˰����ʹ�ǰ���ӻ����ˣ�\n";
        }

        message_vision(CYN "$N��$n˵������"+RANK_D->query_respect(me)+"�����ˣ�ȥ��Ϣһ�°ɣ���\n" NOR, this_object(), me);
          job_exp=((int)me->query_temp("guo_shoucheng/killed_mgb"))*30;
         job_exp=job_exp+((int)me->query_temp("guo_jianlou/killed_mgb"))*25; 
        job_pot=job_exp*2/3;
        job_tihui=job_pot/2;
        job_sc=job_pot/2;
        reward=((int)me->query_temp("guo_shoucheng/killed_mgb")
               + (int)me->query_temp("guo_jianlou/killed_mgb"))/5;

        tell_object(me, HIW"�㱻������"+chinese_number(job_exp)+"�㾭��ֵ��"+chinese_number(job_pot)+"��Ǳ�ܼ�"+chinese_number(job_tihui)+"�����,"+chinese_number(job_sc)+"����������\n"NOR);
        me->apply_condition("guojob2_busy",4);
        me->add("combat_exp", job_exp);
        me->add("potential",job_pot);
        me->add("experience",job_tihui);
        me->add("score",job_sc);
        me->add("guo_shoucheng/reward_exp", job_exp);
        me->add("guo_shoucheng/reward_potential",job_pot);  
        me->add("guo_shoucheng/reward",reward);  
        me->delete_temp("guo_jianlou");    
        me->delete_temp("guo_shoucheng"); 
        if (me->query("potential") > me->query_potential_limit()) 
             me->set("potential", me->query_potential_limit()); 
        if (me->query("experience") > me->query_experience_limit()) 
             me->set("experience", me->query_experience_limit()); 
               return "��"+RANK_D->query_respect(me)
               +"��Ϊ��ɱ�У����µ��ȣ������轱��������\n";
}

string ask_chetui()
{
         object me;
         me = this_player();
         if( !me->query_temp("guo_shoucheng/start_job") )
         return "��û��������,������Ϲ����ʲ��?";
         
      if (me->query("experience") < 100+random(20))
            return "����᲻��ȡ������";
       if (me->query("potential") < 100+random(20))
            return "��Ǳ�ܲ���ȡ������";           
         me->apply_condition("jobshadi_limit",0);
         me->add("combat_exp",-100+random(20));
         me->add("potential",-100+random(20));
         me->add("experience",-100+random(20));
         me->apply_condition("jobshadi_failed",6);
         me->delete_temp("guo_shoucheng");
         me->delete("guo_shoucheng/failed");
         return "û��ϵ,�´μ���Ŭ�� ��������ľ���Ǳ�ܺ���ή����!";
}

