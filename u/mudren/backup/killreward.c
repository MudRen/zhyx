//����޸�ʱ�䣨���޸���ע����2000-11-25 llm(����������Ƶ�����ط�)

#include <ansi.h>

inherit F_DBASE;

void create()
{
    seteuid(getuid());
    set("name", "��������");
    set("id", "killreward");
    set("chat_amount",1000000000);
}

void killer_reward(object killer, object victim)
{
    string msg,name,vmark,*atk;
    int level,exp,pot,score,i;
    mapping quest;
    float k;
    object pker;
    
    exp = victim->query("combat_exp");
//    killer->killed_enemy(victim);��������Ҳ�����������ע����
    if(userp(victim))//��ұ�ɱ
    {
        if(!killer->is_character())//��������
        {
            name = killer->query("short");
            switch(killer->query("why_die"))//������ھ�����ļ���ӵ�
            {
                case "��": msg="��ĳ����";break;
                case "ˤ": msg="��ĳ��ˤ";break;
                case "��": msg="�ж�";break;
                default: msg="�����";break;
            }
        }
        else//������
        {
            name = killer->name(1);
            switch(killer->query("race"))
            {
                case "Ұ��": msg = "ҧ";break;
                case "����": msg = "��";break;
                case "����": msg = "��";break;
                case "����": msg = "��";break;
                default: msg = "ɱ";
            }
            msg = "��"+name+HIM+msg;
        }
        CHANNEL_D->do_channel(this_object(), "rumor",
            sprintf("��˵%s%s���ˡ�", victim->name(1),msg));  
        victim->add("die/times", 1);              //��һ�α�ɱ���� by llm
        victim->set("die/name",name);  //�������һ������˭�� by llm

        if (userp(killer))//ɱ�������
        {
            victim->add("die/pk", 1);                //��һ�α�PK����  by llm
            victim->set("die/name","ĳλ���");      //����ǰ���name by llm
//-----------by llm about �ж��������� 2000/9/4----------------
            if(pointerp(atk = victim->query_temp("attacker"))//�������б���������������
                 &&member_array(killer->query("id"),atk)!=-1  //��������killer��id
                 &&!killer->query_temp("chaseing")  //������׷��PKer��
            )
            {
                vmark = "";
                for(i=0; i<sizeof(atk); i++)
                {
                    if(atk[i]!=killer->query("id")) vmark += atk[i]+",";//ͳ�������Ĺ�����
//����ʹ��PK������by xker 2001/4/6---------------------------------------------------------
                    if(exp>14999)
                    {       
                        if(objectp(pker=find_player(atk[i])))
                        {
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0) k = 0;
                            pker->add("pk_points", 0-to_int(192*sqrt(k)));
                            pker->save();
                        }
                        else
                        {
                            pker = new(USER_OB);
                            seteuid(atk[i]);
                            export_uid(pker);
                            seteuid(getuid());
                            pker->restore();
                            k=(pker->query("combat_exp")-exp)*1.0/(pker->query("combat_exp")+1000);
                            if(k<0)         k = 0;
                            pker->add("pk_points",0-to_int(192*sqrt(k)));
                            pker->save();
                            destruct(pker);
                        }
                    }
//----------------------------------------------------------------------------------------
                }
                write_file("/log/static/KILL_PLAYER",sprintf("%s(%s)kill%s(%s)in %s on %s(���ף�%s)\n",
                    killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23],vmark ));
                killer->apply_condition("killer", 2000);//��һ��ͨ��ʱ��
                killer->add("PKS", 1);//����������PK��
            }
            else//�����㣬������һ���ļ���
            {
                write_file("/log/static/NOT_PK",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                killer->name(1),killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time())[4..23] ));
            }
//------��������end-------by llm about �ж�20���±���----------
            if(victim->query("age")<20)
            {
                if((time()-(int)victim->query("pk_time"))>86400)//��PKʱ����˱����ڣ����¼�ʱ
                    victim->set("pk_time",time());
                else
                {
                    victim->set_temp("newdie",1);//����Ǻſ����Ƶ��ǰ��޳�֮��
                    return;//ֱ�ӷ��أ����û����ʧ��
                }
            }
        }
        else //���ֲ������
	        log_file("static/PLAYER_DIE",sprintf("%s(%s)kill%s(%s)in %s on %s\n",
                name,killer->query("id"),victim->name(1), victim->query("id"),environment(victim)->query("short"),ctime(time()) ));
        if(!killer->query("quest_npc")
            ||(victim->query("quest_dg/name")!=killer->name(1)
            &&victim->query("quest_wg/quest")!=killer->name(1)
            &&victim->query("quest_df/name")!=killer->name(1)//��������ִ��ɱ������
            ))
        {
            victim->skill_death_penalty();//���书
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 50);
        }
        else     //kill clone_npc����ʱ��������skill�����齵����
            victim->add("combat_exp", -(int)victim->query("combat_exp") / 200);
        if(victim->query("jobname")!="���")
            victim->add("shen", -(int)victim->query("shen") / 10);
        if( victim->query("thief") )
            victim->set("thief", (int)victim->query("thief") / 2);
        if( (int)victim->query("potential") > (int)victim->query("learned_points"))
            victim->add("potential",((int)victim->query("learned_points") - (int)victim->query("potential"))/2 );
    }
    else if( interactive(killer))  //npc�����ɱ��npc��npcɱ�Ͳ�������llm 2001/3/30���й���������ж�
    {
		killer->add("MKS", 1);//��MKһ��
        if( stringp(vmark = victim->query("vendetta_mark")) )
			killer->add("vendetta/" + vmark, 1);//�ӳ�޼Ǻţ�����ô�����by llm
		shen = (int)victim->query("shen");//ȡ����ɱ�ߵ�shenֵ����
		if(killer->query("combat_exp") < victim->query("combat_exp"))
		{
	   		if(victim->query("shen") > 0)      //ɱ������NPC
	   		{
	   			if(killer->query("quest_dg/name")!=viticm->name(1)//���Ƕ�������
	   				&&killer->query("quest_wg/name")!=viticm->name(1))//�����������
	   		   	killer->add("shen", -(int)victim->query("shen") / 5);//����
	   		}
    		else
    		{
    			if(killer->query("quest_df/name")!=viticm->name(1)//���Ƕ���ɱ����
                    killer->add("shen", -(int)victim->query("shen") / 10);
            }
        }
// ������������ɱ�˵Ľ���
		if(mapp(quest = killer->query("quest_df")))    //ħ
		{
        	if(quest["desc"] == "��")
        	{
            	if((quest["name"] == "����" && victim->query("gender") == "����" && victim->query("per") >= 25) ||
               		(quest["name"] == "Ů��") && victim->query("gender") == "Ů��"||
                	(quest["type"] == "�ص�" &&  getuid(victim) == quest["dir"]))
            	{
               		if((quest["time"]-time()) < 0)
               		{
                  		killer->delete("quest_df");
                  		return ;
                  	}
               		else if(victim->query("race")=="Ұ��") return;
               		else
               		{
                  		level = (quest["level"]+1)*(60+random(40));
                  		exp = to_int(sqrt(to_float(victim->query("combat_exp"))));
                  		if(exp > level)   exp = level;
                  		pot = exp/(3+random(5));
                  		killer->add("potential",pot);
                  		killer->add("combat_exp",exp);
                  		tell_object(killer,"[1;37m\n�㱻�����ˣ�\n" +
                                  chinese_number(exp) + "��ʵս����\n" +
                                  chinese_number(pot) + "��Ǳ��\n\n[2;37;0m");
                        if(shen > 0&&flag) killer->add("shen", -shen/ 5);
                  		return ;
               		}
            	}
         	}
			if(quest["name"]==viticm->name(1)&&flag)
			{
				if(shen > 0) killer->add("shen", -shen/ 5);
				return;
			}   	
		}
		if(mapp(quest = killer->query("quest_dg")))    //��
		{
        	if(quest["type"] == "ɱ" && victim->name(1) == quest["name"])
        	{
                if((i=killer->query_temp("questdg_times")) < 2)   i = 10-i;
            	else i = 1;
            	level = quest["level"]+1;
            	exp = level*quest["bonus"]*12/(i*(10+random(5)));
            	pot = level*quest["bonus"]/(3+random(3));
            	exp = exp*130/100;
            	pot = pot*130/100;   //ƽ������
            	killer->add("potential",pot);
            	killer->add("combat_exp",exp);
            	tell_object(killer,"[1;37m\n�㱻�����ˣ�\n" +
                            chinese_number(exp) + "��ʵս����\n" +
                            chinese_number(pot) + "��Ǳ��\n\n[2;37;0m");
            	killer->add_temp("questdg_times",1);
            	killer->delete("quest_dg");
            	if(shen < 0)
            		killer->add("shen", shen/10);//ֻ����
            	return ;
         	}
      	}
      	if(mapp(quest = killer->query("quest_wg")))    //��
      	{
			if(quest["type"]=="ɱ"&&quest["quest"]==victim->name(1))
			{
            	tell_object(killer,"��ϲ�㣡����Ϊ��͢����һ����\n");
				i = killer->query_temp("questwg_repeat");
            	if ( i < 2 )
				{
					exp=30+random((killer->query("jobrank")+1))*2;
					score=random((killer->query("jobrank")+1))*4+5;
				}
            	else
            	{
		           	if ( i < 6 ) level = 1;
		           	else if(i < 18 ) level = 2;
		           	else level = 4;
	            	exp=(killer->query("jobrank")+1)*quest["bonus"]*8*level/(10+random(10));
	            	score=((killer->query("jobrank")+1)*6+random(6*(killer->query("jobrank")+1)))*level;
	            }
            	pot = exp/(3+random(3+killer->query("jobrank")));
	         	
    	     	killer->add("combat_exp", exp);
        	 	killer->add("potential",pot);
        		killer->add("score",score);
         		tell_object(killer,HIW"�㱻�����ˣ�\n" +
            		chinese_number(exp) + "��ʵս����\n"+
         			chinese_number(pot) + "��Ǳ��\n" +
         			chinese_number(score)+"��������ۡ�\n"NOR);
       	        killer->add_temp("questwg_repeat",1);
            	killer->set_temp("questwg_giveup_repeat",0);        
	         	killer->delete("quest_wg");
			}
			return;
    	}
    }
}
