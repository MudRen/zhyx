

#include <ansi.h>
inherit ITEM;
//void tai_status();
int get_baoshi(int sta,string mess1);
void baoshi_attribute(object obj,int i,int j);

void create()
{
        set_name(HIM"��ʯ����̨(tai)"NOR, ({"tai"}) );
        set("short", HIM"��ʯ����̨(tai)"NOR);
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
�������Ʊ�ʯ�ĵط���
������������������������Ʊ�ʯ:
    init    :   ���ñ�ʯ����̨(ʮ��һ�Σ�
    add     :	�ѱ�ʯ�Ž���ʯ����̨
    jiawen  :	�������ͷ�������ʯ����̨����
    jiangwen:	�������ͷ�������ʯ����̨����
    finish  :	��������
    tem     :   ����ʯ����̨���¶�
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
	add_action("do_finish", "finish");
	add_action("do_get","get");
	add_action("do_put","put");
	add_action("do_tem","tem");
	
}

int do_init()
{
   	object me = this_player();
   	object obj,ob = this_object();   
   	     
//     if (me->query("balance")<200000) return notify_fail("��ʯ����̨�ǰ�����ʮ��һ�Σ�\n");  
     	if(ob->query_temp("user") && ob->query_temp("user") != me->query("id"))
     	{
     		if ( time()-ob->query_temp("init_time")<300 && ((obj=present(ob->query_temp("user"))) || (obj = present(ob->query_temp("user"), environment(me))))) 
   			return notify_fail(obj->name()+"�������أ��������������ԣ�\n");      
   	}
//      me->add("balance",-100000);
	reload_object(ob);
	ob->set_temp("init_time",time());
        ob->set_temp("user",me->query("id"));
         message_vision("$N����ʮ��������"+ob->name()+"׼�����Ʊ�ʯ��\n",me);
        message("channel:chat",HIM"����Ѩ���硿����˵"+me->name()+"��ʼ���Ʊ�ʯ��\n"NOR,users());
         remove_call_out("do_temperature");
         call_out("do_temperature", 2);
                return 1;		
}

int do_add(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        object item;
	if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˱�ʯ����̨����\n");
        if(!arg) return notify_fail("��Ҫ��ʲô�����ӽ���ʯ����̨�\n");
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
	return notify_fail("��ʯ����̨��ʲô��û�У���ʲô�£��տ�������\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˱�ʯ����̨����\n");
   if (me->query("force")<200) return notify_fail("�������������\n");
   if (me->query("mana")<200) return notify_fail("��ķ���������\n");
   if (me->is_busy()) return notify_fail("����æ���ء�\n");
   
      me->add("force",-150);
       me->add("mana",-150);
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
   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˱�ʯ����̨����\n");
   if (me->query("force")<200) return notify_fail("�������������\n");
   if (me->query("mana")<200) return notify_fail("��ķ���������\n");
   if (me->is_busy()) return notify_fail("����æ���ء�\n");
   
       me->add("force",-150);
       me->add("mana",-150);
   
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

int do_finish()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //staΪ����״̬��0��ʧ�ܣ���Ʒ��ʧ��1��ʧ�ܣ���Ʒ����ʧ��
   		//2���ɹ����õ�ͬ���ϳɱ�ʯ��3���ɹ����õ���һ���ϳɱ�ʯ

   if (ob->query_temp("user") != me->query("id")) return notify_fail("�������˱�ʯ����̨����\n");
           remove_call_out("do_temperature");
  
   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) ) 
	return notify_fail("��ʯ����̨��ʲô��û�У������ʲô����\n");  
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//һ���ܲ��������ϳɰɣ� 
   for(i=0; i<sizeof(inv); i++) //̨�ﺬ�зǱ�ʯ�����ʡ���ʯ�ȼ���ͬ��sta=0
   	if (inv[i]->query("material") != "baoshi" ||inv[0]->query("level") !=inv[i]->query("level")) 
   	{
   		mess=HIG+"���ƵĲ��Ϻ��󲻴���\n"+NOR;	
         return get_baoshi(random(2),mess);
   	} 
   	   
   min_temp=-50-(int)inv[0]->query("level")*50;
    if (min_temp<-273) min_temp=-270;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("min_temp") > min_temp) 
   {
   	mess=HIG+"�����ڻ�����Ҫ���������������½ᾧ��\n"+NOR;
      return get_baoshi(random(2),mess);
   }
   
   if (ob->query_temp("max_temp") < max_temp) 
   {
   	mess=HIG+"Ӧ�ü��ȵ��㹻���¶Ȳ���ʹ��ʯ��ȫ�ڻ���\n"+NOR;
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
   
   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }  
  
   //suss=100;//������
    if (suss>suss1 && tmp==0) return get_baoshi(2,mess);
    else if (suss>suss1 && tmp==1) return get_baoshi(3,mess);
    else if (suss>suss1-33) return get_baoshi(1,mess);
   else return get_baoshi(0,mess);

}

int get_baoshi(int sta,string mess1)
{
   object me = this_player();
   object obj,ob = this_object();
   string mess, me_name,ob_name;
   int i,k,sum,*kind=({0,0});
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
                message("channel:chat",HIM"����Ѩ���硿����˵"+me_name+"���Ʊ�ʯʧ�ܣ����в��ϸ�֮һ�档\n"NOR,users());
   		break;
   	case 1:
   		mess+=HIG+"����ԭ�����ƵĲ��ϻ������棬ֻ�������ε����˳�����\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			inv[k]->move(me);
                message("channel:chat",HIM"����Ѩ���硿����˵"+me_name+"���Ʊ�ʯʧ�ܣ����ã����ϻ��ڡ�\n"NOR,users());
   		break;
   	case 2://ͬ���ϳɱ�ʯ
   		obj=inv[0];
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]);
   		if (obj->query("color")==0) 
   		{
   			i=random(3)+1;//ԭʯ������ɺ� �� ����ɫ
   			if (i==3) i=4;
   		}else i=obj->query("color");
   		baoshi_attribute(obj,i,obj->query("level")+1);
   		obj->move(me);
   		mess+=HIG+"��������һ��"+obj->name()+HIG+"�������⡣\n";
   		mess+=me_name+"�Ȳ�������һ��ץ�˳�����\n"+NOR;
                message("channel:chat",HIM"����Ѩ���硿����˵"+me_name+"���Ʊ�ʯ�ɹ���������"+obj->name()+"��\n"NOR,users());
		break;
   	case 3:	
   		obj=inv[0];
   		sum=0;
   		for(k=0; k<sizeof(inv);k++) 
   		{
   			sum+=inv[k]->query("color");
   			kind[k]=inv[k]->query("color");
   		}
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]);
   		
   		if (sum>=7)
   		{
   			i=7;
   			if (sum==8 && member_array(6,kind)>=0) i=6;
   			if (sum==9 && member_array(5,kind)>=0) i=5;
   			if (sum==10 && member_array(6,kind)>=0) i=6;
   		}
   		else if (sum<=4) i=3; 
   		else if (sum==5 && member_array(3,kind)>=0) i=3;
   		else if (sum==6 && member_array(5,kind)>=0) i=5;
   		else i=sum;
   		baoshi_attribute(obj,i,obj->query("level"));
   		obj->move(me);
   		mess+="��������һ��"+obj->name()+HIG+"�������⡣\n";
   		mess+=me_name+"�Ȳ�������һ��ץ�˳�����\n"+NOR;
                message("channel:chat",HIM"����Ѩ���硿����˵"+me_name+"���Ʊ�ʯ�ɹ���������"+obj->name()+"��\n"NOR,users());
		break; 
   	
   }
   mess+=mess1;
   tell_room(environment(me),mess);
   reload_object(ob);
   return 1;	
}

void baoshi_attribute(object obj,int i,int j)
{
   object me = this_player();
   string *attr;
   int k;
   mixed *color=({
   		({GRN,"ԭʯ",0,"",""}),
   		({HIR,"��ɫ��ʯ",1,"red",({"damage"})}),
   		({HIB,"��ɫ��ʯ",2,"blue",({"attack"})}),
    		({MAG,"��ɫ��ʯ",3,"purple",({"damage","attack"})}),
                ({HIY,"��ɫ��ʯ",4,"yellow",({"luck"})}),
                ({YEL,"��ɫ��ʯ",5,"orange",({"damage","luck"})}),
   		({HIG,"��ɫ��ʯ",6,"green",({"attack","luck"})}),
   		({HIW,"��ʯ",7,"dimond",({"damage","attack","luck"})})
   	}),
   	*level=({
   		({0,"",""}),
   		({1,"�����",10}),
   		({2,"�����Ƶ�",20}),
   		({3,"��覴õ�",30}),
   		({4,"������",40}),
   		({5,"������",50})
   	});
   	if (j>5) j=5;
   	obj->set_name(color[i][0]+level[j][1]+color[i][1]+NOR,({color[i][3]+" baoshi","baoshi"}));
   	obj->set("color",i);
   	obj->set("level",j);
       obj->set("long","һ�����������"+obj->name()+"\n���������Ƕ(inset)ʲô�������档\n����("+me->query("name")+")���Ƶġ�\n");
   	set("changed",1);
   	attr=color[i][4];
   	for (k=0;k<sizeof(attr);k++)
   	    obj->set("prop/"+attr[k],level[j][2]/2+random(level[j][2]/2)); 
}

int do_tem()
{
   object me=this_player();
   object ob=this_object();
   if (!ob->query_temp("user"))  return notify_fail("��Ҫ���\n");;
   if ( wizardp(me) ||( me==present(ob->query_temp("user")) && (me == present(ob->query_temp("user"), environment(me))))) 
   	tell_object(me,"�¶ȣ�"+this_object()->query("temperature")+" \n");
   else  tell_object(me,"����������ʯ�أ���Ҫ���ң���׼͵����\n");
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

