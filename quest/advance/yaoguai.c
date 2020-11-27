inherit NPC;

#include <ansi.h>
#include "/quest/advance/reward.c";

void _invocation(object who, int level);
int exp_reward, pot_reward;
int other_kee=0, other_sen=0;
int announced=0;
static int tick;

object offensive_target(object me)
{
        int sz;
        object *enemy;

        if( !me || !me->query_enemy() || !arrayp(me->query_enemy()) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}


string *death_msg= ({
"$N�ȵ����ҿ������һ�ȥ�ٺú���������ɣ�\n$n�ۼ����Σ�ֻ�û���������ˡ�\n",
"$nһ������$N�Ķ��֣�ֻ�þ͵�һ�������˼���ת������ʵʵ���߿��ˡ�\n",
"$n���һ�����ҷ��ˣ��ҷ��ˣ���Ͷ���������ԹԵط���$N���²����ˡ�\n$N��һ�ӣ�$n���ɴ��⣬�ԹԵ��߿��ˡ�\n",
});


string *names1 = ({
  "��","chen",
  "��","wang",
  "��","zhao",
  "��","xiong",
  "Ѧ","xue",
  "��","zhang",
  "��","wu",
  "��","sun",
  "��","li",
	"��","zhou",
	"��","wu",
	"֣","zheng",
	"��","guo",
	"��","ma",
	"��","du",
	"��","bai",
	"��","yue",
});

string *names2 = ({
  "��","da",
  "��","tian",
  "��","guo",
  "��","jian",
  "��","pei",
  "��","jun",
  "Ԫ","yuan",
  "��","cong",
  "С","xiao",
  "��","hai",
  "��","ze",
  "��","en",
  "��","xiao",
});

string *names3 =({
"��","hui",			"��","hai",
"��","long",		"��","jiao",
"��","li",			"��","hu",
"��","qing",		"ң","yao",
"��","juan",		"��","gang",
"��","lei",			"��","jing",
"��","xiao",		"��","lian",
"��","feng",		"��","yu",
"��","jun",			"�","niu",
"��","qing",		"��","fu",
"��","peng",		"��","hong",
"��","ming",		"ʢ","sheng",
"Ӣ","ying",		"��","zhen",
"��","zhao",		"ϲ","xi",
"��","tao",			"��","min",
"��","ling",		"��","pao",
"��","zi",			"��","dong",
"��","xuan",		"��","bo",
"��","rong",		"ΰ","wei",
"ܿ","yun",
});



int yaoguai_type=0;

int random_place(object me, string* dirs);
void _leave();
void leave();
void leave2();
void set_skills(int,int);

void setname1()
{
        int i,j,k;
	string name, *id;

	i=(random(sizeof(names1)/2))*2;
	j=(random(sizeof(names2)/2))*2;
	k=(random(sizeof(names3)/2))*2;

	name=names1[i]+names2[j]+names3[k];
	id=({names1[i+1]+names2[j+1]+" "+
	    names3[k+1], names3[k+1]});

	set_name(name,id);

	set("race", "����");
	if (random(2) > 0 ) {
	  set("gender", "����");
	} else {
	  set("gender", "Ů��");
	}
	yaoguai_type=1;
}


int cast_chance(int level) 
{
    return 5+level/2;
}

void create()
{
	    setname1();

	set("chat_chance", 5);
	set("chat_msg", ({
	     (: random_move :)
	}) );

	set("chat_chance_combat", 5);

	set("age", 20+random(80));
	set("class", "yao");
	set("combat_exp", 3000);
	set("attitude", "heroism");
	set("lijingguai", 1);
	set_skill("unarmed", 10);
	set_skill("dodge", 10);
	set_temp("apply/armor", 25);
	setup();
}

void copy_status(object me,object ob, int lv)
{
        int lvl,k,m,temp;
        mapping skill_status;
        string *sname;

        object qm=new("/quest/advance/qianmian.c");
	 int base=20;

	 lvl=lv+base-2;

        if(qm) {
            mapping skill=ob->query_skills();
            int i=sizeof(skill);
            int *level, max_level;
	     int max_sen, max_kee;

	    if(i>0) {
		level=values(skill);
		max_level=level[0];
		while(i--) { // find out victim's maximum level
		    if(level[i]>max_level)
			max_level=level[i];
		}
                max_level=max_level*(lvl+20)/(base+20);

	    } else max_level=1;

            qm->copy_status(this_object(), ob, lvl*5/6);
            destruct(qm);

	    k=query("combat_exp");
	    for(m=1;m<300;m=m+10) {
		if(m*m*m/10>k) break;
	    }
	    m=m*lvl/base/3;
	    if(max_level<m) max_level=m;

	    // skill level will be set to the maximum level
	    // of the player.

            //huarong 2004/12
            if (mapp(skill_status = me->query_skills()))//�ж��Լ��Ƿ��й������н����������ȫ��ɾ��
               {
                  skill_status = me->query_skills();
                  sname = keys(skill_status);//���������Լ��Ĺ�������
                  temp = sizeof(skill_status);
                  for (i = 0; i < temp; i++)
                  me->set_skill(sname[i],max_level);
                }
	    set_skills(max_level, lv);
	    
      max_sen=query("max_jing")/2;
      max_kee=query("max_qi")/2;
	    add("eff_jing",max_sen);
	    add("eff_qi",max_kee);
	    add("jing",max_sen);
	    add("qi",max_kee);
	    add("max_jing",max_sen);
	    add("max_qi",max_kee);

	} else { // sth goes wrong.
	    leave();
	    return;
	}

	if(query("combat_exp")>10000000)
	  add("neili",query("neili")); // double force.
	                               // because players have fabao.
	                               // mana is doubled when copying.
        set("jiali", query_skill("neili")/2);
	
}

int random_place(object me, string* dirs)
{
        int  i, j, k;
        object  newob;
        mixed*  file, exit;

        if( !sizeof(dirs) )  return 1;

        i = random(sizeof(dirs));    // pick up one directory

        file = get_dir( dirs[i]+"/*.c", -1 );
        if( !sizeof(file) )             return 1;

				for(k=0;k<30;k++) { // try 20 times
           j = random(sizeof(file));
           if( file[j][1] > 0 ) {
             newob=load_object(dirs[i]+"/"+file[j][0]);
             if (newob) {  
               if(newob->query("no_fight") ||
		       newob->query("no_magic") ||
		       newob->query("no_mieyao") ||
		       !(exit=newob->query("exits")) ||
		       sizeof(exit)<1)
		   continue;

               if(me->move(newob)) {
		   message_vision("$N���˹�����\n",me);
		   return 1;
	       }
	     }
	   }
	}

        return 0;
}

void _leave()
{
    object me=this_object();
    
    // if in fighting, then don't disappear.
    if(me->is_fighting() || me->is_busy())
	return;
    leave();
}

void leave()
{
      if(this_object()) { 
        if(environment())
          message("vision",HIB + name() + 
		  "����һ��Ц��:��û������?�������ˡ�\n" NOR,environment());
	this_object()->move("/u/yuchang/workroom");
	call_out("leave2",1);
      }
      return;
}

void leave2()
{
    if(this_object()) {
	destruct(this_object());
    }
}

void invocation(object who, int level)
{
        object me=this_object();

       if(level<9)
         copy_status(me,who, level-2);
       else
        copy_status(me,who, level);	
	return _invocation(who, level); 
}

void _invocation(object who, int level)
{       

	object me=this_object();
        int exp, i, lvl;
        set("owner", who->query("id"));
        set("owner_ob", who);
				lvl=level;
			// choose npc type.
	i=random(1000);
	if(i<10) {
	    set("type","aggressive");
	} else if(i<20) {
	    set("type","blocker");
	} else if(i<220) {
	    set("type","aggressive_on_owner");
	} else if(i<320) {
	    set("type","aggressive_on_owner1");
	} else 
	    set("type","normal");
	
	if(random(10)==0) {
	    set("env/wimpy",40);
	    if(lvl<11) lvl=lvl+1; // as more difficult to kill.
	} else {
	    set("env/wimpy",1);
	}

	// determine reward
	exp=who->query("combat_exp");
	        
        if(exp<1000000) {
            exp_reward=200+(exp/2000);
	    pot_reward=100+(exp/20000);
	}
       else if(exp<12500000) {
            exp_reward=200+((to_int(sqrt(to_float(exp))))/2);
	    pot_reward=50+((to_int(sqrt(to_float(exp))))/10);
	} 
	else {
	    exp_reward=2000;
	    pot_reward=400;
	}

      
	pot_reward=pot_reward*(lvl+1)/10;
	exp_reward=exp_reward*(lvl+1)/10;

	me->set("stay_time", time()+1800);

	return ;

}

int accept_object (object who, object ob)
{
  object me;
  me = this_object();

  if ((! ob) ||
       ob->value() < 100000)
  {
    message_vision ("$Nһ���ۣ�����㶫����������ˣ�����\n", me);
    return 1;
  }
  who->set_temp("mieyao/allow_to_go", 1);
  message_vision ("$N�ٺٺټ�����Ц���������ˣ������"
	  +"�ɱ������ٿ����㣡\n",me);
  return 1;
}

void check_room()
{
    object me=this_object();
    object env=environment(me);
    if(!living(me)) return;
    if(env && (env->query("no_fight")))  
    random_move();
    
}

void init()
{
    object me=this_object();
    object who=this_player();
    string type;
    object *bianobj;
    string npcid;
    int t;
    object env=environment(me);

    ::init();
    t=query("stay_time");
    
    // if overtime too long, then destroy. mon 7/14/99
    if(t && time()>(t+3600)) {
	remove_call_out("leave");
	call_out("leave",1);
	return;
    }

    if(t && time()>t) {
	remove_call_out("_leave");
	call_out("_leave",300);
    }
    
    if(!userp(this_player())) return;
    if(!living(this_object())) return;
    type=query("type");
    switch (type) {
	case "aggressive": {
	    object leader=query_leader();
	    int exp, myexp;
	    if(leader && present(leader, environment(me))) {
		if(!is_fighting()) kill_ob(leader);
		break;
	    }
	    exp=who->query("combat_exp");
	    myexp=query("combat_exp");
	    if(exp>myexp*3 || exp<myexp)
		break;

	    set_leader(who);
	    message_vision("$N����$n������ֱ����ˮ���ٺ٣�����\n",
		    this_object(), who);
	    kill_ob(who);
	    break;
	}
	case "aggressive_on_owner1":
	    if(query("owner")==this_player()->
		    query("id")) {
		if(!announced) {
		  message_vision("$N����$n�����һ���������������������⣡\n",
			this_object(), who);
		  announced=1;
		}
		kill_ob(this_player());
		if(random(4)>0)
		    set_leader(who);
		else
		    set_leader(0);
		this_player()->kill_ob(this_object());
	    }
	    break;
	case "aggressive_on_owner":
	    if(query("owner")==this_player()->
		    query("id")) {
		if(!announced) {
		  message_vision("$N����$n�����һ���������������������⣡\n",
			this_object(), who);
		  announced=1;
		}
		kill_ob(this_player());
		this_player()->kill_ob(this_object());
	    }
	    break;
	case "blocker": {
	    add_action("do_block","",1);
	    break;
	}
    }
    remove_call_out("check_room");
    call_out("check_room",2);
}

int do_block(string arg)
{	
    object me=this_object();
    object who=this_player();
    string verb=query_verb();
    int t;
    
    if(wizardp(who) && !visible(who)) return 0;
    if(me->is_fighting()) return 0;

    if(verb!="go" &&
	    verb!="fly" &&
	    !(environment() && environment()->query("exits/" + verb)))
	return 0;

    if(who->query_temp("mieyao/allow_to_go")) {
	who->delete_temp("mieyao/allow_to_go");
	who->delete_temp("mieyao/leave_time");
	return 0;
    }
    t=who->query_temp("mieyao/leave_time");
    if(t>0 && time()>t) {
	who->delete_temp("mieyao/leave_time");
	message_vision("$n��$Nһ����ע�⣬��æ���˹�ȥ��\n",me,who);
	return 0;
    }
    if(t==0) {
        t=time()+30+random(90);
        who->set_temp("mieyao/leave_time",t);
	message_vision("$N�͵�����������$n��ǰ�������е���\n"+
		"          ��ɽ���ҿ������������ԣ�\n"+
		"          Ҫ���·����������·�ƣ�\n\n",me,who);
    } 
    
    tell_object(who,me->name()+"һ��ץס���㣡\n");
    return 1;
}

void unconcious()
{
  if (query("qi")<0 || query("jing")<0) die();
   else ::unconcious();
}

void die()
{
        string owner;
        string skill;
        object owner_ob,newitem,silver,gold;
        object me=this_object();
	 string str,err;
	 string msg;
         int max_kee, max_sen, ratio, exp_r, pot_r, gx_r, tihui_r, sc_r;
        int i ,myexp,level,quest_x;

	object killer = query_last_damage_from();
       
        owner = query("owner");
				owner_ob = find_player(owner);
				
   if( owner = killer->query("id")) 
     {
		    max_kee=query("max_qi");
		    max_sen=query("max_jing");
		    ratio=66*(max_kee-other_kee)/max_kee;
		    if(ratio<0) ratio=0;
		    ratio=ratio*(max_sen-other_sen)/max_sen;
		    if(ratio<0) ratio=0;
                   //����������ϵ�� add by wsw  20051015
					QUESTS_D->add_quest("li",1);
                   quest_x = QUESTS_D->query_quest_x("li");
                   
                    exp_r=(exp_reward*ratio/100)*quest_x/1000;
                    pot_r=(pot_reward*ratio/100)*quest_x/1000;
                    tihui_r=(pot_reward*ratio/200)*quest_x/2000; 
                    sc_r=(pot_reward*ratio/100)*quest_x/1000;                                                        
    
	    
//�����Ǯ huarong 2004/3
        myexp=this_object()->query("combat_exp",1);
        if(myexp <  500000) i=0;
        else i=(to_int(sqrt(to_float(myexp/100000-1))))-1;
        if (i>10) i=10;
        silver=new("/clone/money/silver");
        level=owner_ob->query_temp("mieyao/level",1);
        if (i<1)
        {
          silver->set_amount(random(20+myexp/50000)+5);
        }
        else if (i<2)
        {
          silver->set_amount(random(40+myexp/50000)+5);
        }
        else
        {
          silver->set_amount(random(i*5)+20+(level-5)*5);   
      if (random(10)>7)
        {
          gold=new("/clone/money/gold");
          gold->set_amount(1+random(random(random(i+1))));
          if ( gold->move(environment(owner_ob)) )
          message_vision("$N������һ"+gold->query("unit")+gold->query("name")+"��\n",me);
       }
        }
        if ( silver->move(environment(owner_ob)) )
        message_vision("$N������һ"+silver->query("unit")+silver->query("name")+"��\n",me);
        
         message_vision(death_msg[random(sizeof(death_msg))],owner_ob,this_object());
		    
		    str=" got "+exp_r+"/"+exp_reward+" exp "+
			pot_r+"/"+pot_reward+" pot "+
			" in level "+ owner_ob->query_temp("mieyao/level")+
			".\n";
                    if (owner_ob->query_temp("mieyao/level")==9 && ratio>50) {
                       skill=give_reward(owner_ob);
                       str+= "and rewarded 1 lvl of "+skill+".\n";
                 if(skill != "none"){
			msg="��˵"+HIB+ owner_ob->query("name")+HIM+ "��"+HIY+ to_chinese(skill)+HIM+"�����������ˣ�\n"NOR;
     			CHANNEL_D->do_channel(me,"rumor",msg);
    			}
                    }
//ɱһ��������һ����ֵ��wsw 2004/2
		if (owner_ob->query_temp("mieyao/level")==9) owner_ob->add("PKSS",-1);
                    owner_ob->add("combat_exp",exp_r*8);
                    owner_ob->add("potential",pot_r*5);
                    owner_ob->add("experience",exp_r*3);                
		    owner_ob->add("score",exp_r*5);	
                    owner_ob->add("gongxian",exp_r*2);  
		    tell_object(owner_ob, "��õ���"+chinese_number(exp_r*8)
			    +"����ѧ�����"+chinese_number(pot_r*5)+
			    "��Ǳ��!��������,����Ҳ�������\n");
	            owner_ob->set("mieyao/done",1);

	//����װ��
	if (owner_ob->query_temp("mieyao/level")>3)
	 {
	     if (killer) err=catch(newitem=NEWITEMS_OB->get_item(me,killer));
	     if (!err&&newitem) 
	     {
		message_vision("$N������һ"+newitem->query("unit")+newitem->query("name")+"��\n",me);
		newitem->move(environment(me));
	     }
	 }	    
    }
  else
   {
   	message_vision("$N���ˡ�\n",this_object());
   }

	destruct(this_object());

}

varargs int receive_wound(string type, int damage, object who)
{
    string owner=query("owner");
    object inv;
    
    if(who && who->query("id")!=owner)
    {
       if(userp(who) || ((inv=who->query_temp("invoker")) && inv->query("id")!=owner))
       {
	   // can't use other's NPC to help kill.
	 if(damage>0) 
           {
	     switch(type)
              {
		  case "qi": other_kee+=damage; break;
		  case "jing": other_sen+=damage; break;
	        }
	     }
       }
    }
    return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
    string owner=query("owner");
    object inv;
    
    if(who && who->query("id")!=owner) 
    {
       if(userp(who) || ((inv=who->query_temp("invoker")) && inv->query("id")!=owner))
       {
	   // can't use other's NPC to help kill.
	 if(damage>0) 
          {
	    switch(type) 
             {
		case "qi": other_kee+=damage; break;
		case "jing": other_sen+=damage; break;
	       }
	    }
       }
    }
    return ::receive_damage(type, damage, who);
}

// This is called in heart_beat() to perform attack action.
int attack()
{
	object opponent;

	clean_up_enemy();

	opponent = select_opponent();
	if( objectp(opponent) ) {
	        string owner=query("owner");
		
		// if the owner faints, then will not attack
		// and leave. -- mon 3/8/99
		if(opponent->query("id")==owner 
			&& userp(opponent)
                        && !living(opponent) ) {
//huarong 2004/7
//                        && environment()==environment(opponent)) {
                    remove_all_killer();
                    call_out("leave",0);
		    return 0;
		}

		set_temp("last_opponent", opponent);
		COMBAT_D->fight(this_object(), opponent);
		return 1;
	} else
		return 0;
}


void heart_beat()
{
        object ob=this_object(),newnew;
        object me=ob->query("owner_ob");
        int i,k,myexp;
        int j=0;

        ::heart_beat();

        if( ! me )
            me=offensive_target(ob);
        if( ! me ) return;
        if(!is_fighting()) return;

        myexp=(int)me->query("combat_exp",1);
        if(myexp <  500000) i=0;
        else i=(to_int(sqrt(to_float(myexp/100000-1))))-1;
        if (i<1) return;
        if (i>8) i=8;
	if ( tick--  ) return;
	else
	 {  
	   if (i<5) tick = 5;
	   else tick=5-(i-4);
	 }

        k=random(i+j);
	if (wizardp(me) && me->query("env/combat")=="verbose")
           tell_object(me, sprintf(HIM+BLINK+"i: %d  k: %d\n" NOR, i,k));
/*
exp(��)  lvl
  50      0
 100      1
 170      2
 260      3
 370      4
 500      5
 650      6
 820      7
1010      8
         
*/
        if( i>=5 && random(4)==1) command("exert recover");//���500��exp�Ժ󣬹ֿ�ʼ������� 
                  
if(query("family/family_name") == "ŷ������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform zhen "+me->query("id"));
		command("perform zhen");break;
	  case 1:
		command("perform puji "+me->query("id"));
		command("perform puji");break;
          case 2:                     
		command("perform hama "+me->query("id"));
		command("perform hama");break;
	  case 3:
                command("perform puji "+me->query("id"));
                command("perform puji");break;
          case 4:                     
                command("perform hama "+me->query("id"));
                command("perform hama");break;
          case 5:
                command("perform zhen "+me->query("id"));
                command("perform zhen");break;
          case 6:  
                command("perform hama");break;
          default: return 0;
	}

   }
if(query("family/family_name") == "����")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.lian "+me->query("id"));
		command("perform sword.lian");break;
	  case 1:
		command("perform sword.xi "+me->query("id"));
		command("perform sword.xi");break;
          case 2:                     
		command("perform sword.hua "+me->query("id"));
		command("perform sword.hua");break;
	  case 3:
                command("perform sword.can "+me->query("id"));
                command("perform sword.can");break;
          case 4:                     
                command("perform cuff.shang "+me->query("id"));
                command("perform cuff.shang");break;
          case 5:
                command("perform cuff.fei "+me->query("id"));
                command("perform cuff.fei");break;
          case 6:  
                command("perform sword.can");break;
          default: return 0;
	}

   }   
if(query("family/family_name") == "������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.sanjue "+me->query("id"));
		command("perform sword.sanjue");break;
	  case 1:
		command("perform sword.shang "+me->query("id"));
		command("perform sword.shang");break;
          case 2:                     
		command("perform sword.luan "+me->query("id"));
		command("perform sword.luan");break;
	  case 3:
                command("perform sword.sanjue "+me->query("id"));
                command("perform sword.sanjue");break;
          case 4:                     
                command("perform strike.san "+me->query("id"));
                command("perform strike.san");break;
          case 5:
                command("perform sword.zhe "+me->query("id"));
                command("perform sword.zhe");break;
          case 6:  
                command("perform sword.sanjue");break;
          default: return 0;
	}

   }   
if(query("family/family_name") == "�һ���")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.tian "+me->query("id"));
		command("perform sword.tian");break;
	  case 1:
		command("perform sword.bihai "+me->query("id"));
		command("perform sword.bihai");break;
          case 2:                     
		command("perform sword.qing "+me->query("id"));
		command("perform sword.qing");break;
	  case 3:
                command("perform finger.ding "+me->query("id"));
                command("perform finger.ding");break;
          case 4:                     
                command("perform finger.xiao "+me->query("id"));
                command("perform finger.xiao");break;
          case 5:
                command("perform sword.tian "+me->query("id"));
                command("perform sword.tian");break;
          case 6:  
                command("perform sword.tian");break;
          default: return 0;
	}

   }      
if(query("family/family_name") == "��Ĺ��")
   {                              
      if(!ob->query_temp("powerup")&& me->query_skill("force")>249) command("yun powerup");
        if (k>7) k=7;
        switch(k)
      	{
          case 0: 
		command("perform sword.lian "+me->query("id"));
		command("perform sword.lian");break;
          case 1:
                command("perform sword.he "+me->query("id"));
                command("perform sword.he");break;
          case 2:
		command("perform sword.he");break;
	  case 3:
                command("perform throwing.wuying "+me->query("id"));
                command("perform throwing.wuying");break;
	  case 4:
                command("perform sword.lian "+me->query("id"));
                command("perform sword.lian");break;
          case 5:                     
                command("perform unarmed.you "+me->query("id"));
                command("perform unarmed.you");break;
          case 6:                     
                command("perform strike.wang "+me->query("id"));
                command("perform strike.wang");break;
          case 7: 
                command("perform sword.he "+me->query("id"));
                command("perform sword.he");break;
          default: return 0;
	}

   }
if(query("family/family_name") == "�䵱��")
   {                              
      if(!ob->query_temp("powerup")&& me->query_skill("force")>149) command("yun powerup");
        if (k>7) k=7;
        switch(k)
      	{
          case 0:                     
                command("perform sword.chan "+me->query("id"));
                command("perform sword.chan");break;
          case 1: 
		command("perform sword.chan");break;
	  case 2:
		command("perform sword.jia "+me->query("id"));
		command("perform sword.jia");break;
          case 3:                     
		command("perform sword.zhuan "+me->query("id"));
		command("perform sword.zhuan");break;
          default: return 0;
	}

}

if(query("family/family_name") == "��ɽ��")
   {                              
      if(!ob->query_temp("powerup")&& me->query_skill("force")>249) command("yun powerup");
        if (k>7) k=7;
        switch(k)
      	{
          case 0: 
		command("perform sword.jie "+me->query("id"));
		command("perform sword.jie");break;
          case 1:
                command("perform sword.jie "+me->query("id"));
                command("perform sword.jie");break;
          case 2:
		command("cast townportal");break;
	  case 3:
                command("sword.jianzhang "+me->query("id"));
                command("sword.jianzhang");break;
	  case 4:
                command("cuff.leidong "+me->query("id"));
                command("cuff.leidong");break;
          case 5:                     
                command("cuff.poshi "+me->query("id"));
                command("cuff.poshi");break;
          case 6:                     
                command("perform sword.jie "+me->query("id"));
                command("perform sword.jie");break;
          case 7: 
                command("perform sword.jianzhang "+me->query("id"));
                command("perform sword.jianzhang");break;
          default: return 0;
	}

   }
if(query("family/family_name") == "������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.mie "+me->query("id"));
		command("perform sword.mie");break;
	  case 1:
		command("perform sword.jue "+me->query("id"));
		command("perform sword.jue");break;
          case 2:                     
		command("perform sword.mie "+me->query("id"));
		command("perform sword.mie");break;
	  case 3:
                command("perform sword.jue "+me->query("id"));
                command("perform sword.jue");break;
          case 4:                     
                command("perform sword.mie "+me->query("id"));
                command("perform sword.mie");break;
          case 5:
                command("perform finger.ling "+me->query("id"));
                command("perform finger.ling");break;
          case 6:  
                command("perform sword.mie");break;
          default: return 0;
	}

   } 
if(query("family/family_name") == "Ľ������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform blade.feng "+me->query("id"));
		command("perform blade.feng");break;
	  case 1:
		command("perform blade.feng "+me->query("id"));
		command("perform blade.feng");break;
          case 2:                     
		command("perform cuff.zhai "+me->query("id"));
		command("perform cuff.zhai");break;
	  case 3:
                command("perform blade.feng "+me->query("id"));
                command("perform blade.feng");break;
          case 4:                     
                command("perform cuff.zhai "+me->query("id"));
                command("perform cuff.zhai");break;
          case 5:
                command("perform blade.feng "+me->query("id"));
                command("perform blade.feng");break;
          case 6:  
                command("perform cuff.zhai");break;
          default: return 0;
	}

   } 
if(query("family/family_name") == "��ң��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.sheng "+me->query("id"));
		command("perform sword.sheng");break;
	  case 1:
		command("perform sword.liu "+me->query("id"));
		command("perform sword.liu");break;
          case 2:                     
		command("perform hand.hai "+me->query("id"));
		command("perform hand.hai");break;
	  case 3:
                command("perform strike.huan "+me->query("id"));
                command("perform strike.huan");break;
          case 4:                     
                command("perform sword.liu "+me->query("id"));
                command("perform sword.liu");break;
          case 5:
                command("perform sword.sheng "+me->query("id"));
                command("perform sword.sheng");break;
          case 6:  
                command("perform sword.sheng");break;
          default: return 0;
	}

   }  
if(query("family/family_name") == "ؤ��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform staff.chuo "+me->query("id"));
		command("perform staff.chuo");break;
	  case 1:
		command("perform staff.chan "+me->query("id"));
		command("perform staff.chan");break;
          case 2:                     
		command("perform staff.ban "+me->query("id"));
		command("perform staff.ban");break;
	  case 3:
                command("perform staff.ban "+me->query("id"));
                command("perform staff.ban");break;
          case 4:                     
                command("perform staff.chan "+me->query("id"));
                command("perform staff.chan");break;
          case 5:
                command("perform staff.feng "+me->query("id"));
                command("perform staff.feng");break;
          case 6:  
                command("perform staff.feng");break;
          default: return 0;
	}

   }    
if(query("family/family_name") == "���ϻ���")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform finger.dian "+me->query("id"));
		command("perform finger.dian");break;
	  case 1:
		command("perform finger.jian "+me->query("id"));
		command("perform finger.jian");break;
          case 2:                     
		command("perform finger.qian "+me->query("id"));
		command("perform finger.qian");break;
	  case 3:
                command("perform finger.dian "+me->query("id"));
                command("perform finger.dian");break;
          case 4:                     
                command("perform finger.qian "+me->query("id"));
                command("perform finger.qian");break;
          default: return 0;
	}

   }     
if(query("family/family_name") == "�컨��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform whip.qian "+me->query("id"));
		command("perform whip.qian");break;
	  case 1:
		command("perform whip.fu "+me->query("id"));
		command("perform whip.fu");break;
          case 2:                     
		command("perform dodge.hua "+me->query("id"));
		command("perform dodge.hua");break;
	  case 3:
                command("perform unarmed.hong "+me->query("id"));
                command("perform unarmed.hong");break;
          case 4:                     
                command("perform unarmed.luan "+me->query("id"));
                command("perform unarmed.luan");break;
          case 5:
                command("perform unarmed.yi "+me->query("id"));
                command("perform unarmed.yi");break;
          case 6:  
                command("perform dodge.hua");break;
          default: return 0;
	}

   }     
if(query("family/family_name") == "������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform staff.fugu "+me->query("id"));
		command("perform staff.fugu");break;
	  case 1:
		command("perform staff.xue "+me->query("id"));
		command("perform staff.xue");break;
          case 2:                     
		command("perform strike.shi "+me->query("id"));
		command("perform strike.shi");break;
	  case 3:
                command("perform strike.dan "+me->query("id"));
                command("perform strike.dan");break;
          case 4:                     
                command("perform claw.zhua "+me->query("id"));
                command("perform claw.zhua");break;
          case 5:
                command("perform strike.shi "+me->query("id"));
                command("perform strike.shi");break;
          case 6:  
                command("perform staff.fugu");break;
          default: return 0;
	}

   }      
if(query("family/family_name") == "ѩɽ��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform hammer.po "+me->query("id"));
		command("perform hammer.po");break;
	  case 1:
		command("perform hammer.yuan "+me->query("id"));
		command("perform hammer.yuan");break;
          case 2:                     
		command("perform hammer.lian "+me->query("id"));
		command("perform hammer.lian");break;
	  case 3:
                command("perform unarmed.tun "+me->query("id"));
                command("perform unarmed.tun");break;
          case 4:                     
                command("perform unarmed.ji "+me->query("id"));
                command("perform unarmed.ji");break;
          case 5:
                command("perform unarmed.die "+me->query("id"));
                command("perform unarmed.die");break;
          case 6:  
                command("perform hammer.lian");break;
          default: return 0;
	}

   }     
if(query("family/family_name") == "Ѫ����")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform blade.shi "+me->query("id"));
		command("perform blade.shi");break;
	  case 1:
		command("perform blade.chi "+me->query("id"));
		command("perform blade.chi");break;
          case 2:                     
		command("perform blade.xue "+me->query("id"));
		command("perform blade.xue");break;
	  case 3:
                command("perform blade.ying "+me->query("id"));
                command("perform blade.ying");break;
          case 4:                     
                command("perform cuff.jiang "+me->query("id"));
                command("perform cuff.jiang");break;
          case 5:
                command("perform hand.yin "+me->query("id"));
                command("perform hand.yin");break;
          case 6:  
                command("perform blade.ying");break;
          default: return 0;
	}

   }    
if(query("family/family_name") == "�������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform blade.zhui "+me->query("id"));
		command("perform blade.zhui");break;
	  case 1:
		command("perform blade.xian "+me->query("id"));
		command("perform blade.xian");break;
          case 2:                     
		command("perform blade.cang "+me->query("id"));
		command("perform blade.cang");break;
	  case 3:
                command("perform dodge.fei "+me->query("id"));
                command("perform dodge.fei");break;
          case 4:                     
                command("perform throwing.shan "+me->query("id"));
                command("perform throwing.shan");break;
          case 5:
                command("perform throwing.xin "+me->query("id"));
                command("perform throwing.xin");break;
          case 6:  
                command("perform dodge.fei");break;
          default: return 0;
	}

   }    
if(query("family/family_name") == "������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform strike.hua "+me->query("id"));
		command("perform strike.hua");break;
	  case 1:
		command("perform hand.xian "+me->query("id"));
		command("perform hand.xian");break;
          case 2:                     
		command("perform strike.hua "+me->query("id"));
		command("perform strike.hua");break;
	  case 3:
                command("perform hand.xian "+me->query("id"));
                command("perform hand.xian");break;
          case 4:                     
                command("perform strike.hua "+me->query("id"));
                command("perform strike.hua");break;
          case 5:
                command("perform hand.xian "+me->query("id"));
                command("perform hand.xian");break;
          case 6:  
                command("perform strike.hua");break;
          default: return 0;
	}

   }   
if(query("family/family_name") == "������")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.riyue "+me->query("id"));
		command("perform sword.riyue");break;
	  case 1:
		command("perform sword.ni "+me->query("id"));
		command("perform sword.ni");break;
          case 2:                     
		command("perform sword.qian "+me->query("id"));
		command("perform sword.qian");break;
	  case 3:
                command("perform cuff.shi "+me->query("id"));
                command("perform cuff.shi");break;
          case 4:                     
                command("perform strike.kong "+me->query("id"));
                command("perform strike.kong");break;
          case 5:
                command("perform sword.riyue "+me->query("id"));
                command("perform sword.riyue");break;
          case 6:  
                command("perform sword.riyue");break;
          default: return 0;
	}

   }   
if(query("family/family_name") == "�����")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.heng "+me->query("id"));
		command("perform sword.heng");break;
	  case 1:
		command("perform sword.huan "+me->query("id"));
		command("perform sword.huan");break;
          case 2:                     
		command("perform strike.hun "+me->query("id"));
		command("perform strike.hun");break;
	  case 3:
                command("perform strike.wan "+me->query("id"));
                command("perform strike.wan");break;
          case 4:                     
                command("perform sword.huan "+me->query("id"));
                command("perform sword.huan");break;
          case 5:
                command("perform sword.heng "+me->query("id"));
                command("perform sword.heng");break;
          case 6:  
                command("perform sword.heng");break;
          default: return 0;
	}

   }    
if(query("family/family_name") == "�嶾��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform whip.bohu "+me->query("id"));
		command("perform whip.bohu");break;
	  case 1:
		command("perform whip.suo "+me->query("id"));
		command("perform whip.suo");break;
          case 2:                     
		command("perform whip.pan "+me->query("id"));
		command("perform whip.pan");break;
	  case 3:
                command("perform claw.lian "+me->query("id"));
                command("perform claw.lian");break;
          case 4:                     
                command("perform strike.chan "+me->query("id"));
                command("perform strike.chan");break;
          case 5:
                command("perform whip.pan "+me->query("id"));
                command("perform whip.pan");break;
          case 6:  
                command("perform whip.suo");break;
          default: return 0;
	}

   } 
if(query("family/family_name") == "��ڤ��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform strike.ying "+me->query("id"));
		command("perform strike.ying");break;
	  case 1:
		command("perform strike.zhe "+me->query("id"));
		command("perform strike.zhe");break;
          case 2:                     
		command("perform strike.lang "+me->query("id"));
		command("perform strike.lang");break;
	  case 3:
                command("perform strike.ying "+me->query("id"));
                command("perform strike.ying");break;
          case 4:                     
                command("perform strike.zhe "+me->query("id"));
                command("perform strike.zhe");break;
          case 5:
                command("perform strike.lang "+me->query("id"));
                command("perform strike.lang");break;
          case 6:  
                command("perform strike.lang");break;
          default: return 0;
	}

   }   
if(query("family/family_name") == "���ư�")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform strike.long "+me->query("id"));
		command("perform strike.long");break;
	  case 1:
		command("perform strike.lei "+me->query("id"));
		command("perform strike.lei");break;
          case 2:                     
		command("perform strike.dao "+me->query("id"));
		command("perform strike.dao");break;
	  case 3:
                command("perform strike.yin "+me->query("id"));
                command("perform strike.yin");break;
          case 4:                     
                command("perform strike.lei "+me->query("id"));
                command("perform strike.lei");break;
          case 5:
                command("perform strike.long "+me->query("id"));
                command("perform strike.long");break;
          case 6:  
                command("perform strike.dao");break;
          default: return 0;
	}

   }    
if(query("family/family_name") == "�̼ұ�")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform blade.mang "+me->query("id"));
		command("perform blade.mang");break;
	  case 1:
		command("perform parry.zhen "+me->query("id"));
		command("perform parry.zhen");break;
          case 2:                     
		command("perform blade.sha "+me->query("id"));
		command("perform blade.sha");break;
	  case 3:
                command("perform blade.tian "+me->query("id"));
                command("perform blade.tian");break;
          case 4:                     
                command("perform cuff.gua "+me->query("id"));
                command("perform cuff.gua");break;
          case 5:
                command("perform throwing.zhi "+me->query("id"));
                command("perform throwing.zhi");break;
          case 6:  
                command("perform throwing.xian");break;
          default: return 0;
	}

   }  
if(query("family/family_name") == "ѩɽ��")
   {                              
      if(!ob->query_temp("powerup") && me->query_skill("force",1)>249 ) command("exert powerup");
        if (k>6) k=6;
        switch(k)
      	{
          case 0: 
		command("perform sword.hui "+me->query("id"));
		command("perform sword.hui");break;
	  case 1:
		command("perform sword.chu "+me->query("id"));
		command("perform sword.chu");break;
          case 2:                     
		command("perform sword.feng "+me->query("id"));
		command("perform sword.feng");break;
	  case 3:
                command("perform cuff.san "+me->query("id"));
                command("perform cuff.san");break;
          case 4:                     
                command("perform cuff.jue "+me->query("id"));
                command("perform cuff.jue");break;
          case 5:
                command("perform strike.piao "+me->query("id"));
                command("perform strike.piao");break;
          case 6:  
                command("perform sword.hui");break;
          default: return 0;
	}

   }            

}
