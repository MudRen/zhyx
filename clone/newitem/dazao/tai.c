

#include <ansi.h>
inherit ITEM;
//void tai_status();
int get_baoshi(int sta,string mess1);
void baoshi_attribute(object obj,int i);

void create()
{
        set_name(HIM"��������̨(tai)"NOR, ({"tai"}) );
        set("short", HIM"��������̨(tai)"NOR);
        set_max_encumbrance(5000);
        set_max_items(10);
        set("temperature",25);
        set_temp("max_temp",25);
        set_temp("min_temp",25);
        
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                 set("no_get", 1);
                 set("no_put", 1);
	set ("long", @LONG
�������������ĵط���
�����������������������������:
    init    :   ���ý�������̨(ʮ��һ�Σ�
    add     :	�Ѳ��ϷŽ���������̨
    jiawen  :	����������������̨����
    jiangwen:	����������������̨����
    tilian  :	��������
    hecheng : 	�����ϳ�
    tem     :   ����������̨���¶�
LONG);               

                set("value", 50);
        }
}

int is_container() { return 1; }

void init()
{
	add_action("do_init", "init");
	add_action("do_add","add");
	add_action("do_jiawen", "jiawen");
	add_action("do_jiangwen", "jiangwen");
	add_action("do_tilian", "tilian");
	add_action("do_hecheng", "hecheng");
	add_action("do_get","get");
	add_action("do_put","put");
	add_action("do_tem","tem");
	
//         remove_call_out("do_temperature");
//         call_out("do_temperature", 2);
}

int do_init()
{
   	object me = this_player();
   	object obj,ob = this_object();   
   	     
//      if (me->query("balance")<200000) return notify_fail("��������̨�ǰ�����ʮ��һ�Σ�\n");  
     	if(ob->query_temp("user") && ob->query_temp("user") != me->query("id"))
     	{
     		if ( time()-ob->query_temp("init_time")<300 && ((obj=present(ob->query_temp("user"))) || (obj = present(ob->query_temp("user"), environment(me))))) 
   			return notify_fail(obj->name()+"�������أ��������������ԣ�\n");      
   	}
//       me->add("balance",-100000);
	reload_object(ob);
	ob->set_temp("init_time",time());
        ob->set_temp("user",me->query("id"));
         remove_call_out("do_temperature");
         call_out("do_temperature", 2);
         message_vision("$N����ʮ��������"+ob->name()+"׼������������\n",me);
        message("channel:chat",HIM"��ҥ�ԡ�����˵"+me->name()+"��ʼ����������\n"NOR,users());
         return 1;		
}

int do_add(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        object item;
	if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˽�������̨����\n");
        if(!arg) return notify_fail("��Ҫ��ʲô�����ӽ���������̨�\n");
        if( sscanf(arg, "%s in tai", item_name)!=1 )
                return notify_fail("�÷���add <> in tai��\n");
        item=present(item_name, me);
        if (! present(item_name, me)) return notify_fail("������û���ⶫ����\n");
     	if (sizeof(all_inventory(ob))>=2) return notify_fail(ob->name()+"�����Ѿ������ˡ�\n");
        message_vision( "$N��һ"+item->query("unit")+item->query("name")+"�Ž�"+ob->name()+"��\n",me);
        item->move(ob);
        
        return 1;
                
}

int do_get(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        if(!arg) return notify_fail("��Ҫ��ʲô��\n");
        if( sscanf(arg, "%s from tai", item_name)==1 && ob->query_temp("user") != me->query("id"))
                return 1;//notify_fail("��Ҫ�ñ��˵Ķ���\n");
        return 0;
                
}

int do_put(string arg)
{
	string item_name;
        if(!arg) return notify_fail("��Ҫ��ʲô��\n");
        if( sscanf(arg, "%s in tai", item_name)==1 )
                return 1;
        return 0;
                
}

int do_jiawen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;
   
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("��������̨��ʲô��û�У���ʲô�£��տ�������\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˽�������̨����\n");
   if (me->query("neili")<200) return notify_fail("�������������\n");
   if (me->is_busy()) return notify_fail("����æ���ء�\n");
   
      me->add("neili",-150);
   if (random(2)==0) tell_room(environment(me),HIR+me->name()+"Ĭ���񹦣�˫�ֱ��ͨ��,Ȼ����"+ob->name()+HIR+"�ϣ�ʹ�������ر��ȡ� \n"NOR);
   else tell_object(me,HIR+me->name()+"Ĭ���񹦣�˫�ֱ��ͨ��,Ȼ����"+ob->name()+HIR+"�ϣ�ʹ�������ر��ȡ� \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
     ob->add("temperature",100);
   if (ob->query("temperature")>3500) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"�¶ȹ��ߣ�����������ʧ�ˣ�\n");
   	reload_object(ob);
   	return 1;  		
   }
   if (ob->query("temperature")>ob->query_temp("max_temp")) ob->set_temp("max_temp",ob->query("temperature"));
   
   return 1;	
}

int do_jiangwen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;
   
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail(ob->name()+"��ʲô��û�У���ʲô�°���\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˽�������̨����\n");
   if (me->query("neili")<200) return notify_fail("�������������\n");
   if (me->is_busy()) return notify_fail("����æ���ء�\n");
   
       me->add("neili",-150);
   
   if (random(2)==0) tell_room(environment(me),HIW+me->name()+"Ĭ���񹦣�˫������һ�㺮˪,Ȼ����"+ob->name()+HIW+"�ϣ�ʹ�������ر��䡣 \n"NOR);
   else tell_object(me,HIW+me->name()+"Ĭ���񹦣�˫������һ�㺮˪,Ȼ����"+ob->name()+HIW+"�ϣ�ʹ�������ر��䡣 \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
   if (ob->query("temperature")>=100) ob->add("temperature",-100);
   	else ob->add("temperature",-20);
   if (ob->query("temperature")<=-273) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"�¶ȴﵽ�˾�����ȣ����ϱ�������ʧ�ˣ�\n");
   	reload_object(ob);
   	return 1;  		
   }
     
   if (ob->query("temperature")<ob->query_temp("min_temp")) ob->set_temp("min_temp",ob->query("temperature"));
   
   return 1;		
}

int do_tilian()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //staΪ����״̬��0��ʧ�ܣ���Ʒ��ʧ��1��ʧ�ܣ���Ʒ����ʧ��
   		//2���ɹ����õ��ᴿ����

   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˽�������̨����\n");
  
   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("��������̨��ʲô��û�У������ʲô����\n");  
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//һ���ܲ������������ɣ� 
   for(i=0; i<sizeof(inv); i++) //̨�ﺬ�зǽ��������ʡ�������ͬ��sta=0
   	if (inv[i]->query("material") != "metal" ||inv[0]->query("name") !=inv[i]->query("name")
   	   || inv[i]->query("level")>1) 
   	{
   		mess=HIG+"���ƵĲ��������в��������Ĳ��ϡ�\n"+NOR;	
         return get_baoshi(random(2),mess);
   	} 
   	   
   min_temp=-50-(int)inv[0]->query("level")*50;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("max_temp") < max_temp) 
   {
   	mess=HIG+"Ӧ�ü��ȵ��㹻���¶Ȳ���ʹ������ȫ�ڻ���\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   if (ob->query_temp("min_temp") > min_temp) 
   {
   	mess=HIG+"�����ڻ�����Ҫ���������������½ᾧ��\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   

  
/*
   tmp=(int)(((int)(min_temp*1.1)-ob->query_temp("min_temp"))/10);//����¶�Ӱ��
   if (tmp<0) tmp*=-1;
   suss=tmp;
   tmp= (int)(ob->query_temp("max_temp")-(int)(max_temp*1.1)/10);//����¶�Ӱ��
   if (tmp<0) tmp*=-1;
   suss+=tmp;
*/
   suss1=inv[0]->query("level")*10+10;//�ȼ�Խ�ߣ��ɹ���Խ��
   suss=random(100); //�ɹ���
   tmp=(ob->query("temperature")-(inv[0]->query("level")*100))/5; //����¶ȵ�Ӱ��
   if (tmp<0) tmp*=-1;
   suss-=tmp;
   suss=100;//����
 /*  
   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }  
 */ 
   //suss=100;//������
    if (suss>suss1 ) return get_baoshi(2,mess);
     else  return get_baoshi(random(2),mess);
  

}


int do_hecheng()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //staΪ����״̬��0��ʧ�ܣ���Ʒ��ʧ��1��ʧ�ܣ���Ʒ����ʧ��
   		//2���ɹ����õ��ϳɽ���

   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˽�������̨����\n");
  
   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("��������̨��ʲô��û�У������ʲô����\n");  
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//һ���ܲ��������ϳɰɣ� 
   for(i=0; i<sizeof(inv); i++) //̨�ﺬ�зǽ��������ʡ���ͬ�Ĳ��ϣ�sta=0
   	if (inv[i]->query("material") != "metal" ||inv[0]->query("id") ==inv[1]->query("id")
   	   || (inv[i]->query("level")>4 &&inv[i]->query("level")<2) || inv[0]->query("level")!=inv[i]->query("level")) 
   	{
   		mess=HIG+"���ƵĲ��������в��������Ĳ��ϡ�\n"+NOR;	
         return get_baoshi(random(2),mess);
   	} 
   	   
   min_temp=-50-(int)inv[0]->query("level")*50;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("max_temp") < max_temp) 
   {
   	mess=HIG+"Ӧ�ü��ȵ��㹻���¶Ȳ���ʹ������ȫ�ڻ���\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   if (ob->query_temp("min_temp") > min_temp) 
   {
   	mess=HIG+"�����ڻ�����Ҫ���������������½ᾧ��\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   

  
/*
   tmp=(int)(((int)(min_temp*1.1)-ob->query_temp("min_temp"))/10);//����¶�Ӱ��
   if (tmp<0) tmp*=-1;
   suss=tmp;
   tmp= (int)(ob->query_temp("max_temp")-(int)(max_temp*1.1)/10);//����¶�Ӱ��
   if (tmp<0) tmp*=-1;
   suss+=tmp;
*/
   suss1=inv[0]->query("level")*10+10;//�ȼ�Խ�ߣ��ɹ���Խ��
   suss=random(100); //�ɹ���
   tmp=(ob->query("temperature")-(inv[0]->query("level")*100))/5; //����¶ȵ�Ӱ��
   if (tmp<0) tmp*=-1;
   suss-=tmp;
   suss=100;//����
 /*  
   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }  
 */ 
   //suss=100;//������
    if (suss>suss1 ) return get_baoshi(2,mess);
     else  return get_baoshi(random(2),mess);
  

}

int get_baoshi(int sta,string mess1)
{
   object me = this_player();
   object obj,ob = this_object();
   string mess, me_name,ob_name;
   int i,k,sum=0,aaa=0,*kind=({0,0});
   mixed *inv;

   me_name=me->name();
   ob_name=ob->name();
   inv = all_inventory(ob);
   mess=HIG+me_name+"���ò���ˣ������񹦣���ס������С������ش�"+ob_name+"��\n";
   switch(sta)
   {
   	case 0:
   		mess+=HIG+"����"+ob_name+"����տ���Ҳ��ʲô��û�С�\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			destruct(inv[k]);
   		message("channel:chat",HIM"��ҥ�ԡ�����˵"+me_name+"���Ʋ���ʧ�ܣ����в��ϸ�֮һ�档\n"NOR,users());
   		break;
   	case 1:
   		mess+=HIG+"����ԭ�����ƵĲ��ϻ������棬ֻ�������ε����˳�����\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			inv[k]->move(me);
   		message("channel:chat",HIM"��ҥ�ԡ�����˵"+me_name+"���Ʋ���ʧ�ܣ����ã����ϻ��ڡ�\n"NOR,users());
   		break;
   	case 2://�����ɹ�
   		obj=inv[0];
   		if (sizeof(inv)>1) for (k=0;k<sizeof(inv);k++) 
   				   {	if (inv[k]->query("id")=="jinggang") aaa=1;
   				        if (inv[k]->query("id")=="misiyin") aaa=2;
   				        if (inv[k]->query("id")=="chaodangang") aaa=3;
   				   	sum+=inv[k]->query("list");
   				   }	   				   
   		switch(obj->query("level")) 
   		{
   		    case 0:
   			i=random(4)+1;break;//��ʯ������ɴ�������ͭ�����̡�����
   		    case 1:i=obj->query("list")+4;break;
   		    case 2:
			if (aaa==1) //�о��ִ���
			{
				if (sum==11) i=9;
				else if(sum==12) i=10;
				else if(sum==13) i=11;
				else i=5;
			}break;
		    case 3:
			if (aaa==2) //����˹������
			{
				if (sum==20) i=12;
				else if(sum==21) i=13;
				else i=11;
			}break;	
		    case 4:
			if (aaa==3) //�г����ִ���
			{
				if (sum==25) i=14;
				else i=12;
			}break;			    		
			        
   		 }
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]); 
   		baoshi_attribute(obj,i);
   		obj->move(me);
   		mess+=HIG+"��������һ��"+obj->name()+HIG+"�������⡣\n";
   		mess+=me_name+"�Ȳ�������һ��ץ�˳�����\n"+NOR;
   		message("channel:chat",HIM"��ҥ�ԡ�����˵"+me_name+"���Ʋ��ϳɹ���������"+obj->name()+"��\n"NOR,users());
		break;

   }
   mess+=mess1;
   tell_room(environment(me),mess);
   reload_object(ob);
   return 1;	
}

void baoshi_attribute(object obj,int i)
{
   object me = this_player();
   string *attr;
   int k;
   mixed *material=({
   		({GRN"��ʯ",		"kuangshi",	0,0,	"metal",""}),
   		({WHT"����",		"chuntie",	1,1,	"metal",({"damage"})}),
   		({YEL"��ͭ",		"chuntong",	1,2,	"metal",({"damage"})}),   		
   		({WHT"����",		"chunmeng",	1,3,	"metal",({"damage"})}), 
   		({HIW"����",		"chunyin",	1,4,	"metal",({"damage"})}), 
   		({BRED"��"WHT"��",	"jinggang",	2,5,	"metal",({"damage"})}),  
   		({BRED"��"YEL"ͭ",	"jingtong",	2,6,	"metal",({"damage"})}),  		  		
   		({BRED"��"WHT"��",	"jingmeng",	2,7,	"metal",({"damage"})}), 
   		({BRED"��"HIW"��",	"jingyin",	2,8,	"metal",({"damage"})}), 
   		({BMAG"��"YEL"ͭ",	"baitong",	3,9,	"metal",({"damage"})}), 
   		({BMAG"��"WHT"��",	"menggang",	3,10,	"metal",({"damage"})}), 
   		({BMAG"��˹"HIW"��",	"misiyin",	3,11,	"metal",({"damage"})}), 
   		({MAG"����"WHT"��",	"chaodangang",	4,12,	"metal",({"damage"})}), 
   		({MAG"�Ͻ�"WHT"��",	"hejingang",	4,13,	"metal",({"damage"})}), 
   		({HIM"��"HIR"ķ"HIG"��"HIY"��","nimuhejin",	5,14,	"metal",({"damage"})}), 

   	});

 //  	if (j>5) j=5;
   	obj->set_name(material[i][0]+NOR,({material[i][1]}));
   	obj->set("level",material[i][2]);
   	obj->set("changed",1);   
   	obj->set("list",material[i][3]);	
   	switch (obj->query("level"))
   	{
   	    case 1:
   		obj->set("long","һ�����������"+obj->name()+"��\n���Դ���װ����Ҳ���Խ�һ���ᴿ��\n����("+me->query("name")+")���Ƶġ�\n");
   		break;
   	    case 2:
   	    case 3:
   	    case 4:
   		obj->set("long","һ�����������"+obj->name()+"��\n���Դ���װ����Ҳ���Ժϳɸ��߼��Ĳ��ϡ�\n����("+me->query("name")+")���Ƶġ�\n");
   		break;
   	    case 5:	
   		obj->set("long","һ�����������"+obj->name()+"��\n����װ�����ռ����ϡ�\n����("+me->query("name")+")���Ƶġ�\n");
   		break;
  		
   	}


}

int do_tem()
{
   object me=this_player();
   object ob=this_object();
   if (!ob->query_temp("user"))  return notify_fail("��Ҫ���\n");;
   if ( wizardp(me) ||( me==present(ob->query_temp("user")) && (me == present(ob->query_temp("user"), environment(me))))) 
   	tell_object(me,"�¶ȣ�"+this_object()->query("temperature")+" \n");
   else  tell_object(me,"�������������أ���Ҫ���ң���׼͵����\n");
   return 1;
}

void do_temperature()
{
	if (this_object()->query("temperature") > 25) 
	{
		this_object()->add("temperature",-1);
	}	   
	else if (this_object()->query("temperature") < 25)
	{
		this_object()->add("temperature",1);
	}
	call_out("do_temperature", 2);
	
}

