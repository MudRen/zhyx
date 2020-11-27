//newitems.c
//wsw 2002 12
//2004 3���޸�
//�����װ���ļ���
//������ơ������Լ�����  huarong 2004/10
// newweapon.h

#include <ansi.h>
inherit __DIR__"newitemname.c";
object get_weapon(object me,object killer);
object get_armor(object me,object killer);
object get_baoshi(object me,object killer);
mapping tianfu1=([
                "str":"���",
                "int":"����",
                "per":"��ò",
                "kar":"��Ե",
                ]);

mapping tianfu2=([
                "con":"����",
                "cps":"����",
                "spi":"����",
                "cor":"��ʶ",
                ]);

//added by huarong 2004/11
void setname_weapon(object weapon)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=weapon->query("skill_type");
     k=weapon->query("grade");
     if (type=="mace") return 0;
     if (random(100)>90) return 0;
	switch(type)
	{
	  case "sword" :     
                if(random(2))
                {
		temp_name=name_sword1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_sword2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_sword1[k][1]+" sword","sword"});
	        else
		temp_id=({name_sword2[k][1]+" sword","sword"});
		break;
	  case "blade" :     
                if(random(2))
                {
		temp_name=name_blade1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_blade2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"ն";	
		if(mark==1)
		temp_id=({name_blade1[k][1]+" blade","blade"});
	        else
		temp_id=({name_blade2[k][1]+" blade","blade"});
		break;
	  case "fork" :     
                if(random(2))
                {
		temp_name=name_fork1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_fork2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";	
		if(mark==1)
		temp_id=({name_fork1[k][1]+" fork","fork"});
	        else
		temp_id=({name_fork2[k][1]+" fork","fork"});
		break;
	  case "stick" :     
                if(random(2))
                {
		temp_name=name_stick1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_stick2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_stick1[k][1]+" stick","stick"});
	        else
		temp_id=({name_stick2[k][1]+" stick","stick"});
		break;
	  case "whip" :
	       if(random(2))
	       {    
                if(random(2))
                {
		temp_name=name_whip1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_whip1[k][1]+" whip","whip"});
	        else
		temp_id=({name_whip2[k][1]+" whip","whip"});
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_whip3[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_whip4[k][0];
		mark=2;
	        }
		if(k<6) temp_name+=random(2)?"��":"˿";
		else
		  {
                         temp_name+=random(2)?"��":"��";
			 temp_name+="�";	
	          }
		if(mark==1)
		temp_id=({name_whip3[k][1]+" whip","whip"});
	        else
		temp_id=({name_whip4[k][1]+" whip","whip"});
	       }
		break;
	  case "hammer" :     
                if(random(2))
                {
		temp_name=name_hammer1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hammer2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";	
		if(mark==1)
		temp_id=({name_hammer1[k][1]+" hammer","hammer"});
	        else
		temp_id=({name_hammer2[k][1]+" hammer","hammer"});
		break;		
	  case "spear" :     
                if(random(2))
                {
		temp_name=name_spear1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_spear2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"ǹ":"�";	
		if(mark==1)
		temp_id=({name_spear1[k][1]+" spear","spear"});
	        else
		temp_id=({name_spear2[k][1]+" spear","spear"});
		break;				
	  case "staff" :     
                if(random(2))
                {
		temp_name=name_staff1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_staff2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"��":"��";
		temp_name+="��";	
		if(mark==1)
		temp_id=({name_staff1[k][1]+" staff","staff"});
	        else
		temp_id=({name_staff2[k][1]+" staff","staff"});
		break;				
	  case "axe" :     
                if(random(2))
                {
		temp_name=name_axe1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_axe2[k][0];
		mark=2;
	        }
                if(k>5) temp_name+=random(2)?"֮":"��";
		temp_name+="��";	
		if(mark==1)
                temp_id=({name_axe1[k][1]+" axe","axe"});
	        else
                temp_id=({name_axe2[k][1]+" axe","axe"});
		break;						
	   default :
	  	break;
	}	
     temp_name=temp_name+""NOR;
     if(temp_name) weapon->set_name(temp_name, temp_id);	
}			

//added by huarong 2004/11
void setname_armor(object armor)
{
     int k,mark;
     string type;
     string temp_name, *temp_id, long;

     type=armor->query("armor_type");
     k=armor->query("grade");
     if (type=="shield") return 0;
	switch(type)
	{
	  case "armor" :     
                if(random(2))
                {
		temp_name=name_armor1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_armor2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_armor1[k][1]+" armor","armor"});
	        else
		temp_id=({name_armor2[k][1]+" armor","armor"});
		break;
	  case "cloth" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_cloth11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_cloth11[k][1]+" cloth","cloth"});
	        else
		temp_id=({name_cloth12[k][1]+" cloth","cloth"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_cloth21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_cloth22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"����":"ϼ��";
		else temp_name+=random(2)?"��":"ȹ";	
		if(mark==1)
		temp_id=({name_cloth21[k][1]+" cloth","cloth"});
	        else
		temp_id=({name_cloth22[k][1]+" cloth","cloth"});
		armor->set("female_only", 1);
	       }
		break;
	  case "head" :
	       if(random(2))
	       {
                if(random(2))
                {
		temp_name=name_head11[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head12[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"֮":"��";
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_head11[k][1]+" hat","hat"});
	        else
		temp_id=({name_head12[k][1]+" hat","hat"});
		armor->set("male_only", 1);
	       }
	       else
	       {
                if(random(2))
                {
		temp_name=name_head21[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_head22[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"ħ":"��";
		temp_name+=random(2)?"��":"��";	
		if(mark==1)
		temp_id=({name_head21[k][1]+" hat","hat"});
	        else
		temp_id=({name_head22[k][1]+" hat","hat"});
		armor->set("female_only", 1);
	       }
		break;
	  case "boots" :     
                if(random(2))
                {
		temp_name=name_boots1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_boots2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"ħ";
		temp_name+=random(2)?"ѥ":"Ь";	
		if(mark==1)
		  if(random(2)) temp_id=({name_boots1[k][1]+" boots","boots"});
		  else temp_id=({name_boots1[k][1]+" shoes","shoes"});
	        else
		  if(random(2)) temp_id=({name_boots2[k][1]+" boots","boots"});
		  else temp_id=({name_boots2[k][1]+" shoes","shoes"});
		break;
	  case "neck" :     
                if(random(2))
                {
		temp_name=name_neck1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_neck2[k][0];
		mark=2;
	        }
		temp_name+=random(2)?"�����":"����";	
		if(mark==1)
		temp_id=({name_neck1[k][1]+" neck","neck"});
	        else
		temp_id=({name_neck2[k][1]+" neck","neck"});
		break;
	  case "wrists" :     
                if(random(2))
                {
		temp_name=name_wrists1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_wrists2[k][0];
		mark=2;
	        }
                if(k>10) temp_name+=random(2)?"��":"��";
		if(mark==1)
		{
		temp_id=({name_wrists1[k][1]+" wrists","wrists"});
		temp_name+="����";	
	        }
	        else
	        {
		temp_id=({name_wrists2[k][1]+" wrists","wrists"});
		temp_name+="��";	
		}
		break;
	  case "finger" :     
		temp_name=name_ring[k][0];
                if(k>0 && k<=10) temp_name+="֮��";
                else temp_name+="��";
		temp_id=({name_ring[k][1]+" ring","ring"});
		break;
	  case "waist" :     
		temp_name=name_waist[k][0];
                if(k>0 && k<=10) temp_name+="����";
		if(random(2)) temp_id=({name_waist[k][1]+" belt","belt"});
		else temp_id=({name_waist[k][1]+" waist","waist"});
		break;
	  case "surcoat" :     
                if(random(2))
                {
		temp_name=name_surcoat1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_surcoat2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"����":"����";
		if(mark==1)
		temp_id=({name_surcoat1[k][1]+" cloak","cloak"});
	        else
		temp_id=({name_surcoat2[k][1]+" cloak","cloak"});
		break;
	  case "hands" :     
                if(random(2))
                {
		temp_name=name_hands1[k][0];
		mark=1;
	        }
	        else
	        {
		temp_name=name_hands2[k][0];
		mark=2;
	        }
                if(k>0 && k<=10) temp_name+=random(2)?"����":"����";
		if(mark==1)
		temp_id=({name_hands1[k][1]+" gloves","gloves"});
	        else
		temp_id=({name_hands2[k][1]+" gloves","gloves"});
		break;
	  default :
	  	break;
	}	
     temp_name=temp_name+""NOR;
     if(temp_name) armor->set_name(temp_name, temp_id);	
}


object get_item(object me,object killer)
{
	//object item;
      int i,j;
      j=killer->query_temp("mieyao/level")-6;
      if(j<0) j=0;
      if (wizardp(killer)) i=2;
      else i=13-j; 
      		
      switch(random(i))
      	{
		case 0: 
			return get_weapon(me,killer);break;
		case 1:
		        return get_armor(me,killer);break;
                case 2: 
                case 3:
//                case 4:                    
//                        return get_baoshi(me,killer);break;
                default: return 0;
	}
}


object get_weapon(object me,object killer)
{
	object weapon;
	int i,j,value,bind_pro,bind_type;
        int myexp,taexp,exp,max_level;
	string att;
	string *file=({
		"/d/obj/newitem/newweapon/sword.c",
		"/d/obj/newitem/newweapon/blade.c",
		"/d/obj/newitem/newweapon/fork.c",
		"/d/obj/newitem/newweapon/stick.c",
		"/d/obj/newitem/newweapon/whip.c",
		"/d/obj/newitem/newweapon/hammer.c",
		"/d/obj/newitem/newweapon/spear.c",
		"/d/obj/newitem/newweapon/staff.c",
		"/d/obj/newitem/newweapon/axe.c",
		"/d/obj/newitem/newweapon/mace.c"});
	mixed *name=({
		({YEL"��ͭ","bronz",50,3500,2000,50,3,0,3,200,100,20,500,500,1}),
		({HIC"����","steel",75,2500,5000,60,4,0,3,500,120,21,600,600,2}),
		({HIB"����","iron",100,3000,15000,75,5,1,3,1000,150,22,800,800,3}),
		({HIY"�ڽ�","gold",150,4000,25000,95,6,1,4,4000,200,23,1000,1000,4}),
		({HIG"����","jade",200,2000,50000,120,7,2,4,10000,280,24,1500,1500,5}),
		({HIR+BLK"����","xianling",250,2000,100000,140,8,2,5,25000,350,24,2000,2000,6}),
		({HIW"����","datang",250,2000,200000,160,9,3,5,40000,450,24,2500,2500,7})
		});                   
                //0���� 1id 2����;ö� 3���� 4value 5damage 6ħ����ߵȼ� 7luck 8������ 9exp 10skill 11 12max_kee 13 max_sen
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && random(myexp+taexp) < taexp && !wizardp(killer) )
          return 0;   
//�õ���ɫװ��
		i=random(10);
		weapon=new(file[i]);
		
		//�õ������Ĳ���,��Ŀ�����ȡ���ֵ
		exp=random(myexp)/1000;
		if (exp>40000)  i=random(random(8));//���������ϲ��ܵð���װ��
		else if (exp>25000) i=random(random(7));
		else if (exp>10000) i=i=random(random(6));
		else if (exp>4000) i=random(random(5));
		else if (exp>1000) i=random(random(4));
		else if (exp>500) i=random(random(3));
		else  i=0;
		
		
		
		//��������
		//add by wsw 20051010
		weapon->set("primitive_id",killer->query("id")); //������װ�������ID
		weapon->set("unique_code",time()); //��ʱ�䶨��װ��Ψһʶ����
		//�������ʽ
		bind_pro = 10; //�󶨻���,10%��
		bind_pro += to_int(atan(taexp/1000000)*180/3.1415926);
		//weapon->set("bind_pro",bind_pro);//������
 
		bind_pro = random(bind_pro);
		if (bind_pro>70) bind_type = 3;
		else if (bind_pro>40) bind_type = 2;
		else if (bind_pro>10) bind_type = 1;
		else bind_type = 0;
		
		weapon->set("bind_type",bind_type); //0���󶨣�1װ���󶨣�2ʰȡ��,3��ֱ�Ӱ󶨡����޸�wield.c��get.c����Ӧset("bind_id")
	        if (bind_type == 3) weapon->set("bind_id",killer->query("id")); //��id����wield��get������
	        //add end
		weapon->set("changed",1);//�д����ԣ�ϵͳ�Զ������װ��
		weapon->set("unbreak",1);//�д����ԣ��������ܱ���ϣ�ͬʱӦ���޸�weapond.c���ɴ�ϱ�����pfm��cast 
					//����huntian-hammer,perform break,cast dragonfire,�����perform leiting
		weapon->set_name(name[i][0]+weapon->query("name")+NOR,({name[i][1]+" "+weapon->query("id"),weapon->query("id")}));
		weapon->set("durability/max",name[i][2]+random(name[i][2]));//����;ö�,���ڵ���400ʱΪ����ĥ��
		weapon->set("durability/now",random(name[i][2]));//��ǰ�;ö�
		weapon->set_weight((name[i][3]+weapon->query_weight())/2);
		switch(i)
		{
			case 0: att="������ͭ�Ƴɵġ�\n";break;
			case 1: att="���ɰ��������ɵġ�\n";break;
			case 2: att="����ǧ�꺮�����ɵġ�\n";break;
			case 3: att="���������ڽ����ɵġ�\n";break;
			case 4: att="�����Ϲ��������ɵġ�\n";break;
			case 5: att="���ɴ�˵�е�����֮ʯ���ɵġ�\n";break;
                        case 6: att="���ɴ�˵�еĴ�������̫��֮ʯ���ɵġ�\n";break;
		}
        	weapon->set("long",HIG+weapon->query("long")+att+NOR);
        	weapon->set("material", name[i][1]);
        	weapon->set("grade", name[i][14]);//�ȼ� 1��7
        	        	
        	//��������
        	weapon->set("weapon_prop/damage",name[i][5]+name[i][5]*random(20)/100);//������
        	weapon->set("weapon_prop/luck",random(name[i][7]+1));//����ֵ�������еĴ���
        	weapon->set("sockets/max",random(name[i][8]));//���ű�ʯ��
        	weapon->set("sockets/now",0);
        	j=random(5);
        	switch(j)
        	{
        		case  0: att="cold_attack";break;
        		case  1:att="fire_attack";break;
        		case  2:att="lightning_attack";break;
        		case  3:att="poison_attack";break;
        		case  4:att="wind_attack";break;
        		default:att="";
		}
		if (att!="") //ħ������
		{			
			max_level=name[i][6]-random(3);//��ߵȼ�
			if (max_level<1) max_level=1;
			weapon->set((att+"/max_level"),max_level);
			weapon->set("weapon_prop"+"/"+att,1);//��ǰ�ȼ�
			weapon->set((att+"/exp"),0);//����ֵ
		}
		
		//��ֵ
        	value=name[i][4];
        	value+=weapon->query("durability/max")*50;
        	value+=weapon->query("durability/now")*25;
        	value+=weapon->query("weapon_prop/luck")*20000;
        	value+=weapon->query("sockets/max")*2500;
        	value+=weapon->query("cold/max_level")*2500;
        	value+=weapon->query("fire/max_level")*2500;
        	value+=weapon->query("lightning/max_level")*2500;
        	value+=weapon->query("poison/max_level")*2500;
        	value+=weapon->query("wind/max_level")*2500;
        	weapon->set("value", value*(i+1));
		
		//װ��Ҫ��
		weapon->set("weapon_wiel/exp",name[i][9]);
		weapon->set("weapon_wiel/skill",name[i][10]);
                if(random(2))
                weapon->set("weapon_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
                else 
                weapon->set("weapon_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));

		weapon->set("weapon_wiel/max_kee",name[i][12]);
		weapon->set("weapon_wiel/max_sen",name[i][13]);
		setname_weapon(weapon);
     if (wizardp(this_player()))
     tell_object(this_player(),HIM+"���ͣ�"+weapon->query("skill_type")+"     ��ʼ�ȼ���"+weapon->query("grade")+"\n"NOR);
		return weapon;
}


object get_armor(object me,object killer)
{
	object armor;
	int i,j,value,a1,a2,a3,bind_pro,bind_type;
	int myexp,taexp,exp;
	string att;
	string *file=({
		"/d/obj/newitem/newarmor/armor.c",
		"/d/obj/newitem/newarmor/boots.c",
		"/d/obj/newitem/newarmor/cloth.c",
		"/d/obj/newitem/newarmor/finger.c",
		"/d/obj/newitem/newarmor/hands.c",
		"/d/obj/newitem/newarmor/head.c",
		"/d/obj/newitem/newarmor/neck.c",
		"/d/obj/newitem/newarmor/shield.c",
		"/d/obj/newitem/newarmor/surcoat.c",
		"/d/obj/newitem/newarmor/waist.c",
		"/d/obj/newitem/newarmor/wrists.c"});
	mixed *name=({
		({HIY"��Ƥ","boa","40/70",3000,2000,"15/25","15/5/10","5/0/2","5/0/2","5/0/2","5/0/2","",1,50,1}),
		({HIR+BLK"�ڽ�","gold","20/50",2500,5000,"15/30","15/5/15","40/5/15","40/5/15","40/5/15","40/5/15","10/5",1,100,2}),
		({CYN"����","crocodile","50/100",3000,10000,"15/35","15/8/15","5/0/2","5/0/2","5/0/2","5/0/2","",2,200,3}),
		({HIM"����","jade","30/60",2500,20000,"20/40","15/8/20","40/10/15","40/8/15","40/8/15","40/8/15","10/6",2,500,4}),
		({HIG"����","mammoth","60/110",4000,30000,"20/45","15/10/20","5/0/3","5/0/3","5/0/3","5/0/3","",2,1000,5}),
		({YEL"����","amber","40/80",2000,40000,"25/50","15/10/25","40/8/20","40/8/20","40/8/20","40/8/20","10/7",2,2000,6}),
		({MAG"����","kylin","80/120",2500,60000,"25/55","15/10/25","5/0/3","5/0/3","5/0/3","5/0/3","",3,4000,7}),
		({HIM"���","emerald","50/80",2000,80000,"30/60","15/10/30","40/8/16","40/8/16","40/8/16","40/8/16","10/8",3,6000,8}),
		({HIC"����","dragon","100/150",2500,100000,"30/65","15/10/30","5/1/3","5/1/3","5/1/3","5/1/3","",3,10000,9}),
		({HIY"ˮ��","crystal","60/100",1500,120000,"35/70","15/10/35","40/10/22","40/10/22","40/10/22","40/10/22","10/9",3,15000,10}),
		({HIR"ս��","mars","120/170",3000,140000,"35/75","15/10/35","5/1/4","5/1/4","5/1/4","5/1/4","",4,20000,11}),
		({HIB"���","spirit","80/120",1000,160000,"40/80","15/15/35","40/10/25","40/10/25","40/10/25","40/10/25","10/10",4,25000,12}),
		({HIW"�޵�","sunshine","150/250",2000,180000,"40/85","15/15/40","5/2/4","5/2/4","5/2/4","5/2/4","",5,30000,13}),
		({HIR+BLK"����","dark","100/150",1000,200000,"45/90","15/15/40","40/10/30","40/10/30","40/10/30","40/10/30","10/11",5,35000,14})
		});	
	
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && random(myexp+taexp) < taexp && !wizardp(killer) ) 
         return 0;
//�õ���ɫװ��
		i=random(11);
		armor=new(file[i]);
                 if (!armor) return 0;
		
		//�õ����ߵĲ���,��Ŀ�����ȡ���ֵ
		exp=random(myexp)/1000;
		if (exp>35000)  i=random(14);//���������ϲ��ܵð���װ��
		else if (exp>30000) i=random(13);
		else if (exp>25000) i=random(12);
		else if (exp>20000) i=random(11);
		else if (exp>15000) i=random(10);
		else if (exp>10000) i=random(9);
		else if (exp>6000) i=random(8);
		else if (exp>4000) i=random(7);
		else if (exp>2000) i=random(6);
		else if (exp>1000) i=random(5);
		else if (exp>500) i=random(4);
		else if (exp>200) i=random(3);
		else if (exp>100) i=random(2);
           else  i=0;
		//i=6;
		//add by wsw 20051010
		armor->set("primitive_id",killer->query("id")); //������װ�������ID
		armor->set("unique_code",time()); //��ʱ�䶨��װ��Ψһʶ����
		//�������ʽ
		bind_pro = 10; //�󶨻���,10%��
		bind_pro += to_int(atan(taexp/1000000)*180/3.1415926); 
		//armor->set("bind_pro",bind_pro);//������
		bind_pro = random(bind_pro);
		if (bind_pro>70) bind_type = 3;
		else if (bind_pro>40) bind_type = 2;
		else if (bind_pro>10) bind_type = 1;
		else bind_type = 0;
		
		armor->set("bind_type",bind_type); //0���󶨣�1װ���󶨣�2ʰȡ��,3��ֱ�Ӱ󶨡����޸�wield.c��get.c����Ӧset("bind_id")
	        if (bind_type == 3) armor->set("bind_id",killer->query("id")); //��id����wield��get������
	        //add end

		armor->set("changed",1);//�д����ԣ�ϵͳ�Զ������װ��
		armor->set("unbreak",1);//�д����ԣ��������ܱ���ϣ�ͬʱӦ���޸�weapond.c���ɴ�ϱ�����pfm��cast 
					//����huntian-hammer,perform break,cast dragonfire,�����perform leiting
		armor->set_name(name[i][0]+armor->query("name")+NOR,({name[i][1]+" "+armor->query("id"),armor->query("id")}));
		sscanf (name[i][2], "%d/%d", a1, a2) ;
		armor->set("durability/max",a1+random(a2-a1));//����;ö�
		armor->set("durability/now",random(a2));//��ǰ�;ö�
		armor->set_weight((name[i][3]+armor->query_weight())/2);
        	armor->set("long",armor->query("name"));
        	armor->set("material", name[i][1]);	
        	armor->set("grade", name[i][14]);//�ȼ� 1��14
        	
         	//��������
         	sscanf (name[i][5], "%d/%d", a1, a2) ;
        	armor->set("armor_prop/armor",a1+random(a2-a1));//������
        	//armor->set("armor_prop/luck",random(name[i][7]+1));//����ֵ�������еĴ���
        	if (sscanf (name[i][6], "%d/%d/%d", a1, a2,a3)==3)
        	{
                  if (random(200)<=a1) armor->set("armor_prop/cold_defence",a2+random(a3-a2));//��ϵ����
                  if (random(200)<=a1) armor->set("armor_prop/fire_defence",a2+random(a3-a2));//��ϵ����
                  if (random(200)<=a1) armor->set("armor_prop/lightning_defence",a2+random(a3-a2));//��ϵ����
                  if (random(200)<=a1) armor->set("armor_prop/poison_defence",a2+random(a3-a2));//��ϵ����
                  if (random(200)<=a1) armor->set("armor_prop/wind_defence",a2+random(a3-a2));//��ϵ����
        	}
        	switch(random(5000))//�����ȫ���ķ���
        	{
        		case 0 :
        			armor->set("armor_prop/cold_defence",5+random(5));
        			armor->set("armor_prop/fire_defence",5+random(5));
        			armor->set("armor_prop/lightning_defence",5+random(5));
        			armor->set("armor_prop/poison_defence",5+random(5));
        			armor->set("armor_prop/wind_defence",5+random(5));
        			break;
        		case 1 :
        			armor->set("armor_prop/cold_defence",5+random(10));
        			armor->set("armor_prop/fire_defence",5+random(10));
        			armor->set("armor_prop/lightning_defence",5+random(10));
        			armor->set("armor_prop/poison_defence",5+random(10));
        			armor->set("armor_prop/wind_defence",5+random(10));
        			break;	
        		case 2 :
        			armor->set("armor_prop/cold_defence",5+random(15));
        			armor->set("armor_prop/fire_defence",5+random(15));
        			armor->set("armor_prop/lightning_defence",5+random(15));
        			armor->set("armor_prop/poison_defence",5+random(15));
        			armor->set("armor_prop/wind_defence",5+random(15));
        			break;
        	}
        	if (sscanf (name[i][11], "%d/%d", a1, a2)==2) 
        		if (random(100)<=a1) armor->set("armor_prop/chance",random(a2));//ħ��װ�������       	
        	armor->set("sockets/max",random(name[i][12]));//���ű�ʯ��
        	armor->set("sockets/now",0);       		
		
		//��ֵ
        	value=name[i][4];
        	value+=armor->query("durability/max")*50;
        	value+=armor->query("durability/now")*25;
        	value+=armor->query("sockets/max")*2000;
        	value+=armor->query("armor_prop/armor")*100;        	
        	value+=armor->query("armor_prop/cold_defence")*100;
        	value+=armor->query("armor_prop/fire_defence")*100;
        	value+=armor->query("armor_prop/lightning_defence")*100;
        	value+=armor->query("armor_prop/poison_defence")*100;
        	value+=armor->query("armor_prop/wind_defence")*100;
        	value+=armor->query("armor_prop/chance")*500;        	
        	armor->set("value", value);
        	
		//װ��Ҫ��
		armor->set("armor_wiel/exp",name[i][13]);
                if(random(2))
                armor->set("armor_wiel/"+keys(tianfu1)[random(sizeof(tianfu1))],10+random(21));
                else 
                armor->set("armor_wiel/"+keys(tianfu2)[random(sizeof(tianfu2))],10+random(16));

     
		setname_armor(armor);
     if (wizardp(this_player()))
     tell_object(this_player(),HIM+"���ͣ�"+armor->query("armor_type")+"     ��ʼ�ȼ���"+armor->query("grade")+"\n"NOR);
		return armor;
}


object get_baoshi(object me,object killer)
{
	object baoshi;
	int i,j,value;
	int myexp,taexp,exp;
	string *file=({
  		"/d/obj/newitem/dazao/kuangshi.c",
		"/d/obj/newitem/baoshi/baoshi.c"});
	
	myexp=me->query("combat_exp",1);
	taexp=killer->query("combat_exp",1);
      if (myexp<taexp/1.5 && myexp > 3000000 && !wizardp(killer) )
        return 0;
//�õ���ʯ
		baoshi=new(file[random(sizeof(file))]);
		return baoshi;
}
		
������
