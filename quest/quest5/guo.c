// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// guojing.c ����

inherit NPC;
#include <ansi.h>

string *degree_desc = ({
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
string ask_canjun();
string ask_jianlou();
string ask_lianzhu();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

int ask_degree();
int add_degree(object ob,int lv);

void create()
{
        set_name("����", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "����" NOR);
        set("gender", "����");
        set("age", 41);
        set("long", 
                "�������˳Ʊ����Ĺ����������ɹųɼ�˼���Ľ���������\n"
                "�����߹֡�ȫ�������ڵ���������ؤ�����߹��͡�����ͯ����\n"
                "��ͨ���˵�ͽ�ܣ���������书��������һ����ɫ���ۣ���̬\n"
                "���࣬�غ����Ŀ��͸��һ�����ϡ�\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "����̾�˿����������ɹű��ù��������£�һ�����ٳ���ƣ��ض��ֲ�����ߣ���....\n",
                "����˵���������ݹ���������֪�ɺã����һ��Ҫ�ش�Įȥ��������\n",
        }));

        set("inquiry", ([
                "�ܲ�ͨ" : "��������ܴ���ˣ������ڿɺã�\n",
                "����ͯ" : "�ܴ��һ��������û��������\n",
                "���߹�" : "ʦ�����˳ԣ�����ϲ���档�����棬����Ϊ���ҳԵġ�\n",
                "��ҩʦ" : "������̩ɽ���ˡ��������ĺ����������ײ���β�ġ�\n",
                "һ�ƴ�ʦ" : "���¶Դ�ʦ�����м���\n",
                "ŷ����" : "����϶����������λʦ����һ���������ˣ������������ݡ�\n",
                "����"   : "�ض����ҵİ��ޣ�������������\n",
                "�ض�"   : "�ض������ض��ˡ�������ô����\n",
                "��ܽ"   : "���Ů�����ֱ��ֲ�������\n",
                "����"   : "��������������Ⱳ���ֶ��򡣵�Ը���ܿ���һ����\n",
                "����²" : "�����ҵ�С���ӡ�\n",
                "���"   : "����ȷʵ�г�Ϣ��\n",
                "����"   : "����������а�ʦ֮�ꡣ\n",
                "�𴦻�" : "������屡���죬������ܡ�\n",
                "�����" : "�����Ҵ�ʦ����\n",
                "���"   : "�����Ҷ�ʦ����\n",
                "������" : "��������ʦ����\n",
                "��ϣ��" : "��������ʦ����\n",
                "�Ű���" : "��������ʦ����\n",
                "ȫ��" : "��������ʦ����\n",
                "��СӨ" : "��������ʦ����\n",
                "ؤ��"   : "ؤ��Ӣ�ۼ������ˣ�����������������ǡ�\n",
                "��ʦ"   : "�����ɹ���Χ��������������������ͽ����\n",
                "�س�"   : (: ask_shoucheng :),
                "����"   : (: ask_fuming :),
                "����"   : (: ask_chetui :),
                "�ѻ�"   : (: ask_jianlou :), 
                "�������":   (: ask_lianzhu :),
                "�߷�"   :   (: ask_degree :),  
                "�ξ�"   :   (: ask_canjun :), 
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
        set_skill("huntian-qigong", 400);       // ��������
        set_skill("strike", 400);               // ����ȭ��
        set_skill("dragon-strike", 400);        // ����ʮ����
        set_skill("dodge", 400);                // ��������
        set_skill("xiaoyaoyou", 400);           // ��ң��
        set_skill("parry", 400);                // �����м�
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");         
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if (is_fighting()) 
        {
                ene = query_enemy();
                
                if (sizeof(ene) > 1) 
                	return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ���" + 
                		sizeof(ene) + "λ�����д輸�£���\n";
                if (sizeof(ene) == 1) 
                	return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ�" +
                		ene[0]->name() + "�д輸�£���\n";
        }

        if (me->query_temp("guo_shoucheng/mark_shadi"))
                return "��" + RANK_D->query_respect(me) + "���������س��������𣡡�\n";
                
        if (me->query_temp("guo_shoucheng/mark_jianlou"))
                return "��" + RANK_D->query_respect(me) + "�������оѻ��������𣡡�\n";

       	if ((int)me->query("combat_exp") < 3000000)
       		return "��" + RANK_D->query_respect(me) + "���޸���֮�������Ǳ��������Ϊ�ã���\n";

       	if ((int)me->query_skill("force", 1) < 60)
       		return "�س��Ǽ�Σ�չ������ҿ�" + RANK_D->query_respect(me) + "�Ļ����������㣡\n";

       	if ((int)me->query_condition("jobshadi_failed"))
       	{
        	message_vision("$N����$nҡ��ҡͷ˵������ʧ���˻�������??\n", this_object(), me);
        	return "��" + RANK_D->query_respect(me) + "�㻹�Ǳ��������Ϊ�ã���\n";
       	}

       	if (me->query_temp("guo_shoucheng/failed"))
       	{
         	me->delete_temp("guo_shoucheng");
         	me->apply_condition("jobshadi_failed", 4);
         	return "���������ӣ����һ������ң���������\n";
       	} 

      	if ((int)me->query_condition("jobshadi_limit"))
       	{
        	message_vision("$N����$nҡ��ҡͷ˵���㲻���������س�������??\n", this_object(), me);
        	return "��" + RANK_D->query_respect(me) + "�������ĸ�λ��ȥ����\n";
       	}

       	if ((int)me->query_condition("guojob2_busy"))
       	{
        	message_vision(CYN "$N����$nҡ��ҡͷ˵��ƣ��֮ʦ������ս����\n" NOR,
                    	this_object(), me);
        	return "��" + RANK_D->query_respect(me) + "�㻹����Ϣһ�������ɣ���\n";
       	}
       
       	if (me->query("shen") > 0)
       	{
        	switch (random(2)) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi", 1);
                        me->set_temp("guo_shoucheng/carry_location", "eastgate1");                
                	return "�������ɹ������ַ���ԭ����λ" + 
                		RANK_D->query_respect(me) + "ȥ�������Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi", 2);
                        me->set_temp("guo_shoucheng/carry_location", "northgate1");                
                	return "�������ɹ������ַ���ԭ����λ" + RANK_D->query_respect(me) + "ȥ�������Ű����ξ��سǰɡ�";

                       	break;
                }        
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",3);
                        me->set_temp("guo_shoucheng/carry_location","southgate1");
                return "�������ɹ������ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ��ȸ���Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",4);
                        me->set_temp("guo_shoucheng/carry_location","westgate1");
                return "�������ɹ������ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ�׻����Ű����ξ��سǰɡ�";

                       break;
                }
        }
}


string ask_jianlou()
{
        object *ene;
        object me = this_player();

        if (is_fighting()) 
        {    
                ene = query_enemy(); 

                if (sizeof(ene) > 1)
                        return "����"+RANK_D->query_respect(me) +
                               "�Ե�Ƭ�̣����Ⱥ���" + sizeof(ene) + "λ�����д輸�£���\n";
                if (sizeof(ene) == 1)
                        return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ�"
                                + ene[0]->name() + "�д輸�£���\n";
        }

        if (me->query_temp("guo_shoucheng/mark_shadi"))
                return "��"+RANK_D->query_respect(me)+"���������س��������𣡡�\n";
                
        if (me->query_temp("guo_shoucheng/mark_jianlou"))
                return "��"+RANK_D->query_respect(me)+"�������оѻ��������𣡡�\n";

        if ((int)me->query_condition("jobshadi_failed"))
        {
                message_vision(
                        "$N����$nҡ��ҡͷ˵������ʧ���˻�������??\n", this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�㻹�Ǳ��������Ϊ�ã���\n";
        }

        if (me->query_temp("guo_shoucheng/failed"))
        {
                me->delete_temp("guo_shoucheng");
                me->apply_condition("jobshadi_failed",4);
                return "���������ӣ����һ������ң���������\n";
        } 

        if ((int)me->query_skill("arrow", 1) < 50)
        {
                message_vision(CYN"$N����$nҡ��ҡͷ˵����Ļ�������̫���ˣ�\n"NOR,
                               this_object(), me);
                return "��"+RANK_D->query_respect(me)+"������������ʤ�ΰ�����\n";
        }                                               

        if ((int)me->query_condition("jobjianlou_limit"))
        {
                message_vision("$N����$nҡ��ҡͷ˵���㲻����������������𣿣�\n", 
                                this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�����������ĸ�λ��ȥ����\n";
        }
        
        if ((int)me->query_condition("guojob2_busy"))
        {
                message_vision(CYN"$N����$nҡ��ҡͷ˵��ƣ��֮ʦ������ս����\n"NOR,
                                this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�㻹����Ϣһ�������ɣ���\n";
        }

        me->set_temp("guo_shoucheng/mark_jianlou", 2);
        me->set_temp("guo_shoucheng/where", "east_out");
        return "���Ǿ�������λ"+RANK_D->query_respect(me) +
               "ǰ���������ŵĶ��Ǽ�¥������ѻ��ɹż��ֵ�����ɡ�\n��";
}

string ask_fuming()
{
        int job_pot, job_exp, job_sco, reward;
        object me = this_player();

        if (! me->query_condition("jobshadi_failed") && me->query_temp("guo_shoucheng/failed"))
        {
                me->delete_temp("guo_shoucheng");
                me->apply_condition("jobshadi_failed",4);
                return "���������ӣ����һ�����������������\n";
        } 

        if (me->query_temp("guo_shoucheng/help_killed")
            && ! me->query_temp("guo_shoucheng/job_over")) 
        {
                job_exp = ((int)me->query_temp("guo_shoucheng/help_killed")) * 100;
                job_pot = job_exp / 2;
                job_sco = job_pot / 2;
                
                if (job_exp > 3000) job_exp = 3000;
                if (job_pot > 1500) job_pot = 1500;
                
                me->add("combat_exp", job_exp);
                me->add("potential", job_pot);
                if (me->query("potential") > me->query_potential_limit()) 
                        me->set("potential", me->query_potential_limit());                 
                me->add("score", job_sco);
                me->add("experience", random(2));
                
                tell_object(me, HIW "�㱻������" + chinese_number(job_exp) + "�㾭��ֵ��" + 
                                chinese_number(job_pot) + "��Ǳ�ܺ�" + chinese_number(job_sco) + "��������\n" NOR);
                                
                me->delete_temp("guo_shoucheng");        
                me->apply_condition("guojob2_busy", 2);
                me->add("guo_shoucheng/reward_exp", job_exp);
                me->add("guo_shoucheng/reward_potential", job_pot);  

                return "��"+RANK_D->query_respect(me) + "��Ϊ��ɱ�У���������\n";
        }
           
        if (! me->query_temp("guo_shoucheng/mark_shadi")
                && ! me->query_temp("guo_shoucheng/mark_jianlou")
                || ! me->query_temp("guo_shoucheng/job_over")) 
                return "�������û�������ɣ�������ʲô������\n";
        
        if (me->query_temp("guo_shoucheng/killed_mgb") < 1)
        {
                me->delete_temp("guo_shoucheng"); 
                return "����ɱ�˼������˰����ʹ�ǰ���ӻ����ˣ�\n";
        }

        message_vision(CYN "$N��$n˵������"+RANK_D->query_respect(me)+"�����ˣ�ȥ��Ϣһ�°ɣ���\n" NOR, this_object(), me);
        
        job_exp = ((int)me->query_temp("guo_shoucheng/killed_mgb")) * 150;
        job_exp = job_exp + ((int)me->query_temp("guo_jianlou/killed_mgb")) * 150; 
        job_pot = job_exp / 2;
        job_sco = job_pot / 2;
        if (job_exp > 5000) job_exp = 5000;
        if (job_pot > 3000) job_pot = 3000;
        
        reward = (int)me->query_temp("guo_shoucheng/killed_mgb") / 10 + 1;

        tell_object(me, HIW "�㱻������" + chinese_number(job_exp) + "�㾭��ֵ��" + 
                        chinese_number(job_pot) + "��Ǳ�ܺ�" + chinese_number(job_sco) + "��������\n" NOR);
                                
        me->apply_condition("guojob2_busy", 2);
        me->add("combat_exp", job_exp);
        me->add("potential", job_pot);
        if (me->query("potential") > me->query_potential_limit()) 
                me->set("potential", me->query_potential_limit()); 
        me->add("score", job_sco);
        me->add("experience", random(2));
        
        me->add("guo_shoucheng/reward_exp", job_exp);
        me->add("guo_shoucheng/reward_potential",job_pot);  
        me->add("guo_shoucheng/reward", reward);  
    
        me->delete_temp("guo_shoucheng"); 
               
        return "��" + RANK_D->query_respect(me) + "��Ϊ��ɱ�У����µ��ȣ����Ǿ���" HIY + 
                chinese_number(reward) + NOR + CYN "�ߣ�������\n" NOR;
}

string ask_chetui()
{
        object me;
         
        me = this_player();
         
        if (! me->query_temp("guo_shoucheng/start_job") 
                && ! me->query_temp("guo_shoucheng/mark_jianlou") 
                && ! me->query_temp("guo_shoucheng/mark_shadi"))                
                return "��û��������,������Ϲ����ʲ�᣿";
                
        me->apply_condition("jobshadi_limit", 0);
        me->apply_condition("jobjianlou_limit", 0);
        me->add("combat_exp", -100 + random(20));
        me->apply_condition("jobshadi_failed", 4);
        me->delete_temp("guo_shoucheng");
        
        return "û��ϵ���´μ���Ŭ�� ��";
}

string ask_lianzhu()
{
        object me = this_player(), ob = this_object();

        if (me->query("guo_shoucheng/reward") > 100)
        {
                message_sort(HIC "$N������Ц�����������������(lianzhu-arrow)�Ҿ�" +
                             "�������ˣ��������ɱ�У�����ս������Ҳ�޺��ˣ�\n" NOR, ob);
                return "ʱ����ȣ����ھͿ�ʼѧ��(qingjiao lianzhu-arrow)��\n";
        } else
        {
                message_sort(HIC "$N΢΢��ͷ�����������������(lianzhu-arrow)���ҵ�" +
                             "������Ѫ֮����\n���������ഫ����\n" NOR, ob);
                return "���������з���ɱ�У����Ҵ���֮�ģ��պ�ؿ������ͣ�\n";
        }
}

void init()
{
        object me = this_player();
        
        if (me->query("guo_shoucheng/reward") > 100)
                add_action("do_study","qingjiao");
}

int do_study(string arg)
{
        string skill; 
        object me = this_player(), ob = this_object();

        if (! arg || arg != "lianzhu-arrow")
                return notify_fail("��Ҫ��������(qingjiao)ʲô��\n"); 
      
        if (me->query_skill("lianzhu-arrow", 1) > me->query_skill("arrow", 1))
                return notify_fail("��Ļ�������̫���ˣ��޷�����ѧϰ���������\n"); 

        if (me->query_skill("lianzhu-arrow", 1) * me->query_skill("lianzhu-arrow", 1)
                > me->query("guo_shoucheng/reward") * 50)
                return notify_fail("����سǾ��������࣬������Ը���������ˣ�\n"); 

        if (me->query("learned_points") >= me->query("potential"))
                return notify_fail("���Ǳ�ܲ����ˣ�\n"); 

        if (me->query("jing") < 100 || me->query("qi") < 100)
                return notify_fail("������̫���ˣ�����Ϣһ�°ɣ�\n"); 

        me->receive_damage("qi", 10 + random(40));
        me->receive_damage("jing", 10 + random(40));        
        me->add("learned_points", 1);
        message_vision(HIC "$Nָ����$nһЩ�й�" HIW "�����������" HIC "�����⣬" +
                       "$n�ƺ���Щ�ĵá�\n" NOR, ob, me);
                       
        me->improve_skill("lianzhu-arrow", random(me->query_skill("arrow", 1)));

        return 1;
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if (ob->query_temp("degree_jungong"))
        {
                command("say " + RANK_D->query_respect(ob) + "�԰����꣬" +
                        "���Ѿ�����ǰ������ˣ�\n");
                return 1;
        }

        if (ob->query("guo_shoucheng/reward") > 
            (100 * (1 + ob->query("degree_jungong")) * (1 + ob->query("degree_jungong"))))
                lv = ob->query("degree_jungong") + 1;

        if (lv > sizeof(degree_desc))
        {
                command("say �������Ϊ������⣬����������ǰ�����٣�ǰ;�Բ�������\n");
                return 1;   
        }

        if (lv <= ob->query("degree_jungong"))
        {
                command("say " + ob->query("name") + "��Ҫ��ø��ߵĲ߷⣬������������ſ��԰���\n");
                return 1;
        }
        
        command("say " + RANK_D->query_respect(ob) + "���Ժ��Ҽ�������ǰ������Ϊ" + 
                RANK_D->query_respect(ob) + "��⣡\n");

        call_out("add_degree", 10, ob, lv);
        ob->set_temp("degree_jungong", 1);
        message("channel:rumor", MAG "������������" + CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                "��һƥ���������������ֱ�����ξ��ǣ�\n" NOR, users());

        return 1;
}

int add_degree(object ob,int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv-1];

        if (ob->query("degree")) 
                old_degree = ob->query("degree");
        else old_degree = "";

        message("channel:rumor", HIY "�����ξ��ǡ�����������ʵ�گԻ��" +
                "�߷� " + old_degree + " " + HIW + ob->query("name") +
                HIY " Ϊ���� " NOR + degree + HIY "���մˣ�\n" NOR, users());
                
        ob->delete_temp("degree_jungong");

        if (ob->query("degree"))
        {
                if (ob->query("degree_ask"))
                        degree = HIM " �� " NOR + clear_degree(ob->query("degree")) +
                                 HIM " �� " NOR + degree + HIM " �� " NOR;
                else
                        degree = HIM " �� " NOR + clear_degree(ob->query("degree")) +
                                 degree + HIM " �� " NOR;
        } else
                degree = HIM " �� " NOR + degree + HIM " �� " NOR;   

        ob->set("degree_jungong", lv);
        ob->set("degree", degree);
        ob->add("weiwang", lv * 200); 
        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, BLU "ʿ��" NOR) >= 0) ||
            (strsrch(arg, BLU "�λ�" NOR) >= 0) ||
            (strsrch(arg, HIC "�ν�" NOR) >= 0) ||
            (strsrch(arg, HIC "�Խ�" NOR) >= 0) ||
            (strsrch(arg, HIY "����" NOR) >= 0) ||
            (strsrch(arg, HIY "����" NOR) >= 0) ||
            (strsrch(arg, HIR "����" NOR) >= 0) ||
            (strsrch(arg, HIR "�ᶽ" NOR) >= 0) ||
            (strsrch(arg, HIM " �� " NOR) >= 0))
        {
                arg = replace_string(arg, BLU "ʿ��" NOR,"");
                arg = replace_string(arg, BLU "�λ�" NOR,""); 
                arg = replace_string(arg, HIC "�ν�" NOR,"");
                arg = replace_string(arg, HIC "�Խ�" NOR,"");   
                arg = replace_string(arg, HIY "����" NOR,"");
                arg = replace_string(arg, HIY "����" NOR,"");   
                arg = replace_string(arg, HIR "����" NOR,"");
                arg = replace_string(arg, HIR "�ᶽ" NOR,"");   
                arg = replace_string(arg, HIM " �� " NOR,"");
        }
        return arg;
}

string ask_canjun()
{
        object me = this_player(); 
        object king = WAR_D->query_king();
        int jungong;

        if (me->query_temp("jun_quest"))
                return "�����Ѿ����������ˣ��쵽ǰ��ȥ�ɣ���\n";
        
        if (me->query("age") < 18)
                return RANK_D->query_respect(me) + "���㻹С���Ժ�����Ϊ��Ч���ɣ�\n";

        if (me->query("combat_exp") < 1000000)
                return RANK_D->query_respect(me) + "��־�ɼΣ��������޸���֮����������ذɣ�\n";

        if (me->query("combat_exp") > 200000000)
                return "��͢���ż������ԣ����������������ܽ��������췴���㻹�ǻ�ȥ�ɣ�\n";

        jungong = me->query("degree_jungong");
        if (jungong < 4)
                return "���ľ���̫��΢�ˣ���ǰ������ûʲô�ð���\n";

        if (! objectp(king))
                 return "����ǰ��û��ս�£������Ժ������ɣ�\n";

        if (me == king) return "�㲻Ҫ����Ц�ˣ�\n";

        if (WAR_D->join_war(me))
                return "������������ʱ�������ϳ�������ǰ��֧Ԯ�ɣ�\n";
}

